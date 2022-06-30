#include "ootmain.h"
#include "object_nb.h"
#include "../../statics/statics.h"

#include "NbXtraAnimPullingoutshehnaiAnim.c"
#include "NbXtraAnimHoldingshehnaiAnim.c"
#include "NbXtraAnimPlayingshehnaiAnim.c"
#include "ShehnaiDL.c"
#include "gerudoway_cs.c"

#define DEP_OBJECT_NUM 0xB3
#define NPC_ACTION_NUM 40
#define NPC_ACTION_SLOT 1
#define SHADOW_SIZE 25.0f
#define NUM_LIMBS 19
#define NB_LIMB_TORSO 0x08
#define NB_LIMB_LHAND 0x0B
#define NB_LIMB_HEAD 0x0F

static ColliderCylinderInitType1 sCylinderInit = {
    { COLTYPE_HIT0, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE, BUMP_NONE, OCELEM_ON, },
    { 20, 80, 0, { 0, 0, 0 } },
};

static void *const EyeTextures[3] = {
	&gNabooruEyeOpenTex,  &gNabooruEyeHalfTex,  &gNabooruEyeClosedTex
};

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	ColliderCylinder collider;
    Vec3s jointTable[NUM_LIMBS];
    Vec3s morphTable[NUM_LIMBS];
	struct_80034A14_arg1 turnInfo;
	u8 initted;
	u8 eyeTextureIndex;
	u8 blinkTimer;
	u8 eyeState;
	u8 drawShehnai;
	s16 timer;
	Actor *guardActor;
} Entity;

typedef struct EnGe2 {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ ColliderCylinder collider;
    /* 0x0198 */ SkelAnime skelAnime;
    /* 0x01DC */ Vec3s jointTable[22];
    /* 0x0260 */ Vec3s morphTable[22];
    /* 0x02E4 */ s16 eyeIndex;
    /* 0x02E6 */ s16 blinkTimer;
    /* 0x02E8 */ Vec3s headRot;
    /* 0x02EE */ Vec3s unk_2EE;
    /* 0x02F4 */ u16 stateFlags;
    /* 0x02F6 */ s16 walkDirection;
    /* 0x02F8 */ s16 yawTowardsPlayer;
    /* 0x02FC */ f32 yDetectRange;
    /* 0x0300 */ u16 walkDuration;
    /* 0x0302 */ u16 walkTimer;
    /* 0x0304 */ u8 unk_304;
    /* 0x0305 */ u8 timer;
    /* 0x0306 */ u8 playerSpottedParam;
    /* 0x0308 */ void* actionFunc;
} EnGe2; // size = 0x030C

static void update_Init(Entity *en, GlobalContext *globalCtx);
static void update_Talk1(Entity *en, GlobalContext *globalCtx);
static void update_TalkGuards(Entity *en, GlobalContext *globalCtx);
static void update_WaitGuards(Entity *en, GlobalContext *globalCtx);
static void update_Talk2(Entity *en, GlobalContext *globalCtx);
static void update_Reload(Entity *en, GlobalContext *globalCtx);
static void update_WaitAction1(Entity *en, GlobalContext *globalCtx);
static void update_WaitChoice(Entity *en, GlobalContext *globalCtx);
static void update_WaitAction2(Entity *en, GlobalContext *globalCtx);
static void update_PullingOutShehnai(Entity *en, GlobalContext *globalCtx);
static void update_HoldingShehnai(Entity *en, GlobalContext *globalCtx);
static void update_PlayingShehnai(Entity *en, GlobalContext *globalCtx);
static void update_Done(Entity *en, GlobalContext *globalCtx);

static void init(Entity *en, GlobalContext *globalCtx) {
	en->initted = 0;
	if(en->actor.params != 0){
		Actor_Kill(&en->actor);
		return;
	}
	if((NABOORU_CONTINUE_VAR & NABOORU_CONTINUE_BIT)){
		NABOORU_CONTINUE_VAR &= ~NABOORU_CONTINUE_BIT;
		en->actor.update = (ActorFunc)update_Reload;
		en->actor.textId = 0x0B68;
	}/*else if((LONGOFTIME_VAR & LONGOFTIME_BIT)){
		en->actor.update = (ActorFunc)update_Done;
		en->actor.textId = 0x0B6D;
	}*/else{
		en->actor.update = (ActorFunc)update_Init;
		en->actor.textId = 0x0B60;
	}
	en->eyeTextureIndex = 0;
	en->blinkTimer = 0;
	en->eyeState = 0;
	en->drawShehnai = 0;
	en->timer = 0;
	en->guardActor = NULL;
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, SHADOW_SIZE);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinderType1(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &gNabooruSkel, &gNabooruSittingCrossLeggedAnim, 
		en->jointTable, en->morphTable, NUM_LIMBS);
	en->initted = 1;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	if(!en->initted) return;
	Collider_DestroyCylinder(globalCtx, &en->collider);
	SkelAnime_Free(&en->skelAnime, globalCtx);
}

static void updateEyes(Entity *en){
	if(en->eyeState == 1){
		++en->blinkTimer;
		en->eyeTextureIndex = 1;
		if(en->blinkTimer > 5){
			en->eyeState = 2;
		}
	}else if(en->eyeState == 2){
		en->eyeTextureIndex = 2;
	}else if(en->eyeState == 3){
		++en->blinkTimer;
		en->eyeTextureIndex = 1;
		if(en->blinkTimer > 5){
			en->eyeState = 0;
			en->blinkTimer = 20;
		}
	}else{
		if(en->blinkTimer == 0){
			en->blinkTimer = Rand_S16Offset(60, 60);
		}else{
			--en->blinkTimer;
		}
		en->eyeTextureIndex = (en->blinkTimer < 3) ? en->blinkTimer : 0;
	}
}

static Actor *FindGuardToTalk(Actor *nabooru, GlobalContext *globalCtx){
	Actor* actor = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].head;
    while (actor != NULL) {
        if(actor->id == ACTOR_EN_GE2 && actor->world.pos.x > nabooru->world.pos.x){
			return actor;
		}
		actor = actor->next;
    }
    return NULL;
}

//mode 1: kill all
static void KillGuards(Entity *en, GlobalContext *globalCtx, s32 mode){
	Actor* actor = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].head;
    while (actor != NULL) {
        if(actor->id == ACTOR_EN_GE2 && (mode == 1 || actor != en->guardActor)){
			Actor_Kill(actor);
		}
		actor = actor->next;
    }
	if(mode) en->guardActor = NULL;
}

static void GuardUpdateCommon(EnGe2 *en, GlobalContext *globalCtx){
	Collider_UpdateCylinder(&en->actor, &en->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &en->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &en->actor, 40.0f, 25.0f, 40.0f, 5);
	SkelAnime_Update(&en->skelAnime);
}

static void BetterStepToAngleS(s16 *angle, s16 target, s32 shift){
	s16 step = *angle - target;
	if(step < 0) step = -step;
	s16 delta = step;
	step >>= shift;
	if(step < 0x80) step = 0x80;
	if(step > delta) step = delta;
	Math_StepToAngleS(angle, target, step);
}

static void GuardSetAnim(EnGe2 *en, AnimationHeader *anim, float spd){
	Animation_Change(&en->skelAnime, anim, spd, 0.0f, 
		Animation_GetLastFrame(anim), ANIMMODE_LOOP, -8.0f);
}

static void GuardUpdateEavesdrop(Actor *thisx, GlobalContext *globalCtx){
	EnGe2 *en = (EnGe2*)thisx;
	if(en->unk_304 == 0xFF){ //signal to init
		en->unk_304 = 0;
		en->timer = 30;
		GuardSetAnim(en, &gGerudoPurpleLookingAboutAnim, 1.0f);
		en->eyeIndex = 0;
	}
	//660, 721, 790
	const float center = -720.0f;
	if(en->unk_304 == 0){
		++en->timer;
		if(en->timer == 85){
			en->unk_304 = 1;
			GuardSetAnim(en, &gGerudoPurpleWalkingAnim, 1.0f);
			if(en->actor.world.pos.z > center){
				en->actor.shape.rot.y = 0x8000;
			}else{
				en->actor.shape.rot.y = 0;
			}
		}
	}else{
		float speed = 2.5f;
		if(en->actor.shape.rot.y != 0){
			speed = -speed;
		}
		const float dist = 55.0f;
		en->actor.world.pos.z += speed;
		float dp = en->actor.world.pos.z - center;
		if(fabsf(dp) > dist && dp * speed > 0.0f){
			en->unk_304 = 0;
			en->timer = 0;
			GuardSetAnim(en, &gGerudoPurpleLookingAboutAnim, 1.0f);
		}
	}
	GuardUpdateCommon(en, globalCtx);
}

static void GuardUpdateTurn(Actor *thisx, GlobalContext *globalCtx){
	EnGe2 *en = (EnGe2*)thisx;
	if(en->unk_304 == 0xFF){ //signal to init
		en->unk_304 = 0;
		GuardSetAnim(en, &gGerudoPurpleLookingAboutAnim, 1.0f);
	}
	BetterStepToAngleS(&en->actor.shape.rot.y, en->actor.yawTowardsPlayer, 3);
	GuardUpdateCommon(en, globalCtx);
}

static void GuardUpdateExit(Actor *thisx, GlobalContext *globalCtx){
	EnGe2 *en = (EnGe2*)thisx;
	if(en->unk_304 == 0xFF){ //signal to init
		en->unk_304 = 0; //used as state index
		GuardSetAnim(en, &gGerudoPurpleWalkingAnim, 1.5f);
		en->timer = 0;
	}
	static const Vec3f pathPoints[5] = {
		{2200.0f, 0.0f, -638.0f},
		{2200.0f, 0.0f, -720.0f},
		{2200.0f, 160.0f, -920.0f},
		{2300.0f, 160.0f, -1039.0f},
		{2300.0f, 280.0f, -1280.0f}
	};
	static const u8 nFrames[5] = {15, 10, 35, 15, 20};
	Vec3f curpos = en->actor.world.pos;
	Vec3f dp = pathPoints[en->unk_304];
	dp.x -= curpos.x; dp.y -= curpos.y; dp.z -= curpos.z;
	en->actor.shape.rot.x = en->actor.shape.rot.z = 0;
	en->actor.shape.rot.y = Math_Atan2S(dp.z, dp.x);
	float ratio = 1.0f / (float)(nFrames[en->unk_304] - en->timer);
	dp.x *= ratio; dp.y *= ratio; dp.z *= ratio;
	curpos.x += dp.x; curpos.y += dp.y; curpos.z += dp.z;
	en->actor.world.pos = curpos;
	++en->timer;
	if(en->timer >= nFrames[en->unk_304]){
		en->timer = 0;
		++en->unk_304;
		if(en->unk_304 >= 5){
			Actor_Kill(&en->actor);
		}
	}
	GuardUpdateCommon(en, globalCtx);
}

static void updateTurnInfo(Entity *en, GlobalContext *globalCtx, s32 mode){
	if(mode < 0){
		BetterStepToAngleS(&en->turnInfo.unk_08.x, 0, 2);
		BetterStepToAngleS(&en->turnInfo.unk_08.y, 0, 2);
		BetterStepToAngleS(&en->turnInfo.unk_0E.x, 0, 2);
		BetterStepToAngleS(&en->turnInfo.unk_0E.y, 0, 2);
		return;
	}
	f32 eyeHeight;
	Actor *target;
	if(mode == 1){
		if(en->guardActor == NULL) return;
		target = en->guardActor;
		eyeHeight = 120.0f;
	}else{
		target = &PLAYER->actor;
		eyeHeight = kREG(16) + 9.0f;
	}
	en->turnInfo.unk_18 = target->world.pos; //focusPos
	en->turnInfo.unk_14 = eyeHeight; //eyeHeight
	func_80034A14(&en->actor, &en->turnInfo, kREG(17) + 0xC, 2);
}

static s32 updateCommon(Entity *en, GlobalContext *globalCtx, s32 turnMode) {
	Collider_UpdateCylinder(&en->actor, &en->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &en->collider.base);
	Actor_UpdateBgCheckInfo(globalCtx, &en->actor, 75.0f, 30.0f, 30.0f, 5);
	updateEyes(en);
	updateTurnInfo(en, globalCtx, turnMode);
	return SkelAnime_Update(&en->skelAnime);
}

static void update_Init(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, -1);
	if(Actor_IsTalking(&en->actor, globalCtx)){
		//MESSAGE_START;
		en->actor.update = (ActorFunc)update_Talk1;
		en->guardActor = FindGuardToTalk(&en->actor, globalCtx);
		en->timer = 0;
	}else{
		Actor_RequestToTalk(&en->actor, globalCtx);
	}
}

static inline void SetGuardAction(Entity *en, ActorFunc upd){
	if(en->guardActor != NULL){
		((EnGe2*)en->guardActor)->unk_304 = 0xFF; //signal to init
		en->guardActor->update = upd;
	}
}

static void update_Talk1(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
	++en->timer;
	if(en->timer == 20){
		//wait for camera to finish moving in before killing them
		KillGuards(en, globalCtx, 0);
		SetGuardAction(en, GuardUpdateEavesdrop);
	}
	if(MESSAGE_ADVANCE_EVENT){
		en->actor.update = (ActorFunc)update_TalkGuards;
		en->actor.textId = 0x0B61;
		SetGuardAction(en, GuardUpdateTurn);
		MESSAGE_CONTINUE;
	}
}

static void update_TalkGuards(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 1);
	if(MESSAGE_ADVANCE_EVENT){
		SetGuardAction(en, GuardUpdateExit);
		en->actor.update = (ActorFunc)update_WaitGuards;
		en->timer = 0;
	}
}

static void update_WaitGuards(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 1);
	if(en->timer == 80){
		KillGuards(en, globalCtx, 1);
		en->timer = 0;
		en->actor.update = (ActorFunc)update_Talk2;
		en->actor.textId = 0x0B62;
		MESSAGE_CONTINUE;
	}else{
		++en->timer;
	}
}

static void update_Talk2(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
	if(en->timer >= 0) ++en->timer;
	if(en->timer == 20){
		//TODO trigger Link surprised action
		en->timer = -1;
	}
	if(MESSAGE_ADVANCE_EVENT){
		if(en->actor.textId == 0x0B65){
			gSaveContext.environmentTime = gSaveContext.dayTime = 0x9000;
			NABOORU_CONTINUE_VAR |= NABOORU_CONTINUE_BIT;
			globalCtx->csCtx.segment = &NabooruPanAwayCS;
			gSaveContext.cutsceneTrigger = 1;
		}else{
			++en->actor.textId;
			MESSAGE_CONTINUE;
		}
	}
}

static void update_Reload(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
    Vec3f pos = en->actor.world.pos;
	pos.y += 50.0f;
    pos.z += 70.0f;
	globalCtx->mainCamera.eye = globalCtx->mainCamera.eyeNext = pos;
    pos.x -= 50.0f;
	pos.y -= 30.0f;
	pos.z -= 20.0f;
	globalCtx->mainCamera.at = pos;
	globalCtx->mainCamera.xzSpeed = 0.0f;
	/*
	static const Vec3f reloadLinkPos = {1904.0f, 0.0f, -688.0f};
	static const Vec3s reloadLinkRot = {0, 0x5555, 0};
	PLAYER->actor.world.pos = reloadLinkPos;
	PLAYER->actor.world.rot = reloadLinkRot;
	PLAYER->actor.shape.rot = reloadLinkRot;
	*/
	KillGuards(en, globalCtx, 1);
	globalCtx->csCtx.segment = &NabooruSecondHalfCS;
	gSaveContext.cutsceneTrigger = 1;
	en->actor.update = (ActorFunc)update_WaitAction1;
}

static void update_WaitAction1(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
	if(CHECK_NPC_ACTION(NPC_ACTION_SLOT, 1)){
		en->actor.textId = 0x0B6A;
		MESSAGE_CONTINUE;
		en->actor.update = (ActorFunc)update_WaitChoice;
	}
}

static void update_WaitChoice(Entity *en, GlobalContext *globalCtx){
	globalCtx->csCtx.frames--;
	updateCommon(en, globalCtx, 0);
	if(MESSAGE_ADVANCE_CHOICE){
		if(globalCtx->msgCtx.choiceIndex == 0){
			Statics_GiveLongOfTime();
			en->actor.update = (ActorFunc)update_WaitAction2;
		}else{
			en->actor.textId = 0x0B6B;
			MESSAGE_CONTINUE;
		}
	}else if(MESSAGE_ADVANCE_EVENT){
		en->actor.textId = 0x0B6A;
		MESSAGE_CONTINUE;
	}
}

static void update_WaitAction2(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
	if(CHECK_NPC_ACTION(NPC_ACTION_SLOT, 2)){
		Animation_Change(&en->skelAnime, &NbXtraAnimPullingoutshehnaiAnim, 1.0f, 0.0f, 
			Animation_GetLastFrame(&NbXtraAnimPullingoutshehnaiAnim), ANIMMODE_ONCE, -8.0f);
		en->actor.update = (ActorFunc)update_PullingOutShehnai;
	}
}

static void update_PullingOutShehnai(Entity *en, GlobalContext *globalCtx){
	s32 animFinished = updateCommon(en, globalCtx, 
		en->skelAnime.curFrame >= 24.0f ? 0 : -1);
	if(animFinished){
		Animation_Change(&en->skelAnime, &NbXtraAnimHoldingshehnaiAnim, 1.0f, 0.0f, 
			Animation_GetLastFrame(&NbXtraAnimHoldingshehnaiAnim), ANIMMODE_LOOP, 0.0f);
		en->actor.update = (ActorFunc)update_HoldingShehnai;
	}
	if(en->skelAnime.curFrame >= 12.0f){
		en->drawShehnai = 1;
	}
}

static void update_HoldingShehnai(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
	if(CHECK_NPC_ACTION(NPC_ACTION_SLOT, 3)){
		Animation_Change(&en->skelAnime, &NbXtraAnimPlayingshehnaiAnim, 1.0f, 0.0f, 
			Animation_GetLastFrame(&NbXtraAnimPlayingshehnaiAnim), ANIMMODE_LOOP, -8.0f);
		en->actor.update = (ActorFunc)update_PlayingShehnai;
		en->eyeState = 1;
	}
}

static void update_PlayingShehnai(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, -1);
	if(CHECK_NPC_ACTION(NPC_ACTION_SLOT, 4)){
		Animation_Change(&en->skelAnime, &NbXtraAnimHoldingshehnaiAnim, 1.0f, 0.0f, 
			Animation_GetLastFrame(&NbXtraAnimHoldingshehnaiAnim), ANIMMODE_LOOP, -8.0f);
		en->actor.update = (ActorFunc)update_Done;
		en->actor.textId = 0x0B6D;
		en->eyeState = 3;
	}
}

static void update_Done(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx, 0);
	Actor_RequestToTalk(&en->actor, globalCtx);
}

s32 Nabooru_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;
	if(limbIndex == NB_LIMB_TORSO){
		rot->x += en->turnInfo.unk_0E.y;
		rot->y -= en->turnInfo.unk_0E.x;
	}else if(limbIndex == NB_LIMB_HEAD){
		rot->x += en->turnInfo.unk_08.y;
		rot->z += en->turnInfo.unk_08.x;
	}
	return false;
}

void Nabooru_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;

    if (limbIndex == NB_LIMB_HEAD) {
        Vec3f nbHeadBoneOriginToHeadCenter = { 0.0f, 10.0f, 0.0f };
        Vec3f nbHeadCenterOut;

        Matrix_MultVec3f(&nbHeadBoneOriginToHeadCenter, &nbHeadCenterOut);
        en->actor.focus.pos.x = nbHeadCenterOut.x;
        en->actor.focus.pos.y = nbHeadCenterOut.y;
        en->actor.focus.pos.z = nbHeadCenterOut.z;
        en->actor.focus.rot.x = en->actor.world.rot.x;
        en->actor.focus.rot.y = en->actor.world.rot.y;
        en->actor.focus.rot.z = en->actor.world.rot.z;
    }else if(limbIndex == NB_LIMB_LHAND){
		if(en->drawShehnai){
			gSPDisplayList(POLY_OPA_DISP++, ShehnaiDL);
			func_80093D18(globalCtx->state.gfxCtx);
		}
	}
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	func_80093D18(globalCtx->state.gfxCtx);
	void *seg08Tex = EyeTextures[en->eyeTextureIndex];
	gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(seg08Tex));
    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(seg08Tex));
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gSPSegment(POLY_OPA_DISP++, 0x0C, &gActorXluSetup[2]); //Skips actual setup, just end DL
	SkelAnime_DrawFlexOpa(globalCtx, en->skelAnime.skeleton, en->skelAnime.jointTable,
		en->skelAnime.dListCount, Nabooru_OverrideLimbDraw, Nabooru_PostLimbDraw, en);
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_NPC,
	.flags = 0x00000019,
	.objectId = DEP_OBJECT_NUM,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update_Init,
	.draw = (ActorFunc)draw
};
