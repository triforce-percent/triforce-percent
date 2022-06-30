#include "ootmain.h"
#include "object_mm.h"

#define NUM_LIMBS 16
#define LIMB_TORSO 8
#define LIMB_HEAD 15
#define SECONDS_RUN_IN 4

static const Vec3f bridgeEndPos = {
	-1267.4f, -220.27f, 1646.7f
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000004, 0x00, 0x00 },
        TOUCH_NONE, BUMP_ON, OCELEM_ON, },
    { 18, 63, 0, { 0, 0, 0 } },
};

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	ColliderCylinder collider;
    Vec3s jointTable[NUM_LIMBS];
    Vec3s morphTable[NUM_LIMBS];
	Vec3s headRot, torsoRot;
	u8 invisible;
	u8 lookingAtLink;
	u8 mouthTexIndex;
	u8 timer;
} Entity;

static void update_Wait(Entity *en, GlobalContext *globalCtx);
static void update_RunIn(Entity *en, GlobalContext *globalCtx);
static void update_Sitting(Entity *en, GlobalContext *globalCtx);
static void update_Talking(Entity *en, GlobalContext *globalCtx);
static void update_GettingUp(Entity *en, GlobalContext *globalCtx);
static void update_RunOut(Entity *en, GlobalContext *globalCtx);

static void init(Entity *en, GlobalContext *globalCtx) {
	if(en->actor.params != 0 || LINK_IS_CHILD || !(gSaveContext.eventInf[1] & 1)){
		en->actor.destroy = NULL;
		Actor_Kill(&en->actor);
		return;
	}
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, 21.0f);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinder(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &gRunningManSkel, &gRunningManRunAnim, 
		en->jointTable, en->morphTable, NUM_LIMBS);
	en->invisible = 1;
	en->lookingAtLink = 0;
	en->mouthTexIndex = 0;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	Collider_DestroyCylinder(globalCtx, &en->collider);
	SkelAnime_Free(&en->skelAnime, globalCtx);
}

static s32 updateCommon(Entity *en, GlobalContext *globalCtx) {
	if(en->lookingAtLink){
		func_80038290(globalCtx, &en->actor, &en->headRot, &en->torsoRot,
			en->actor.focus.pos);
	}else{
		func_80037F30(&en->headRot, &en->torsoRot);
	}
	Collider_UpdateCylinder(&en->actor, &en->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &en->collider.base);
	Actor_UpdateBgCheckInfo(globalCtx, &en->actor, 0.0f, 0.0f, 0.0f, 4);
	return SkelAnime_Update(&en->skelAnime);
}

static void update_Wait(Entity *en, GlobalContext *globalCtx){
	if(gSaveContext.timer2Value >= -SECONDS_RUN_IN - 1){
		en->invisible = 0;
		en->timer = 0;
		en->actor.update = (ActorFunc)update_RunIn;
	}
}
	
static float moveAlongPath(Entity *en, u16 totalframes, 
		const Vec3f *startPos, const Vec3f *endPos){
	float frac = (float)en->timer / (float)totalframes;
	if(frac >= 1.0f) frac = 1.0f;
	Vec3f dp = *endPos;
	dp.x -= startPos->x; dp.y -= startPos->y; dp.z -= startPos->z;
	en->actor.world.pos = *startPos;
	en->actor.world.pos.x += dp.x * frac;
	en->actor.world.pos.y += dp.y * frac;
	en->actor.world.pos.z += dp.z * frac;
	en->actor.shape.rot.x = en->actor.shape.rot.z = 0;
	en->actor.shape.rot.y = Math_Atan2S(dp.z, dp.x);
	en->actor.world.rot = en->actor.shape.rot;
	++en->timer;
	return frac;
}
	
static void update_RunIn(Entity *en, GlobalContext *globalCtx){
	float frac = moveAlongPath(en, SECONDS_RUN_IN * 20, &en->actor.home.pos, &bridgeEndPos);
	if(frac >= 0.5f) en->lookingAtLink = 1;
	if(frac >= 0.55f) en->mouthTexIndex = 1;
	if(frac >= 1.0f){
		Animation_Change(&en->skelAnime, &gRunningManSitStandAnim, -1.0f,
			Animation_GetLastFrame(&gRunningManSitStandAnim), 0.0f, ANIMMODE_ONCE, -7.0f);
		en->actor.update = (ActorFunc)update_Sitting;
	}
	updateCommon(en, globalCtx);
}

static void update_Sitting(Entity *en, GlobalContext *globalCtx){
	s32 animDone = updateCommon(en, globalCtx);
	if(animDone){
		Animation_Change(&en->skelAnime, &gRunningManExcitedAnim, 1.0f, 0.0f,
			Animation_GetLastFrame(&gRunningManExcitedAnim), ANIMMODE_LOOP, -12.0f);
		en->actor.update = (ActorFunc)update_Talking;
		en->actor.textId = 0x0C10;
		en->actor.flags |= 0x10000; //auto talk
		gSaveContext.eventInf[1] &= ~1;
		gSaveContext.timer2State = 0;
		HIGH_SCORE(HS_MARATHON) = -1;
		RUNNINGMAN_WANTS_TO_BATTLE_VAR |= RUNNINGMAN_WANTS_TO_BATTLE_BIT;
		func_80078884(NA_SE_SY_TRE_BOX_APPEAR);
	}
}

static void update_Talking(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx);
	Actor_RequestToTalkInRange(&en->actor, globalCtx, 1000);
	if(MESSAGE_ADVANCE_EVENT){
		en->actor.flags &= ~0x10000; //auto talk
		Animation_Change(&en->skelAnime, &gRunningManSitWaitAnim, 1.0f, 0.0f,
			Animation_GetLastFrame(&gRunningManSitWaitAnim), ANIMMODE_LOOP, -7.0f);
		en->actor.textId = 0x0C11;
		en->mouthTexIndex = 0;
		MESSAGE_CONTINUE;
	}else if(MESSAGE_ADVANCE_END){
		Animation_Change(&en->skelAnime, &gRunningManSitStandAnim, 1.0f, 0.0f,
			Animation_GetLastFrame(&gRunningManSitStandAnim), ANIMMODE_ONCE, -12.0f);
		en->lookingAtLink = 0;
		en->actor.update = (ActorFunc)update_GettingUp;
	}
}

static void update_GettingUp(Entity *en, GlobalContext *globalCtx){
	s32 animDone = updateCommon(en, globalCtx);
	if(animDone){
		Animation_Change(&en->skelAnime, &gRunningManRunAnim, 1.5f, 0.0f,
			Animation_GetLastFrame(&gRunningManRunAnim), ANIMMODE_LOOP, 0.0f);
		en->timer = 0;
		en->actor.update = (ActorFunc)update_RunOut;
	}
}

static void update_RunOut(Entity *en, GlobalContext *globalCtx){
	float frac = moveAlongPath(en, SECONDS_RUN_IN * 10, &bridgeEndPos, &en->actor.home.pos);
	if(frac >= 1.0f){
		Actor_Kill(&en->actor);
	}
	updateCommon(en, globalCtx);
}


s32 EnMm3_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    Entity* en = (Entity*)thisx;
	if(limbIndex == LIMB_TORSO){
        rot->x += en->torsoRot.y;
        //rot->y -= en->torsoRot.x;
	}else if(limbIndex == LIMB_HEAD){
        rot->x += en->headRot.y;
        rot->z += en->headRot.x * 0.5f;
    }
    return false;
}

void EnMm3_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
    static Vec3f headOffset = { 200.0f, 800.0f, 0.0f };
    Entity* en = (Entity*)thisx;
    if(limbIndex == LIMB_HEAD){
        Matrix_MultVec3f(&headOffset, &en->actor.focus.pos);
    }
}

static void draw(Entity *en, GlobalContext *globalCtx) {
    static const u64* mouthTextures[] = { gRunningManMouthClosedTex, gRunningManMouthOpenTex };
	if(en->invisible) return;
	func_80093D18(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(mouthTextures[en->mouthTexIndex]));
    SkelAnime_DrawFlexOpa(globalCtx, en->skelAnime.skeleton, en->skelAnime.jointTable,
		NUM_LIMBS, EnMm3_OverrideLimbDraw, EnMm3_PostLimbDraw, en);
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_NPC,
	.flags = 0x00000019,
	.objectId = OBJECT_MM,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update_Wait,
	.draw = (ActorFunc)draw
};
