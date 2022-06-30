#include "ootmain.h"
#include "object_oE_anime.h"
#include "object_oE4.h"
#include "object_oE9.h"

#define ANIM_OBJ_NUM 0x34
#define SKEL_OBJ_NUM 0x4C
#define HEAD_OBJ_NUM 0x52

#define SHADOW_SIZE 25.0f
#define NUM_LIMBS 39
#define LIMB_HEAD 23

static ColliderCylinderInitType1 sCylinderInit = {
    { COLTYPE_HIT0, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE, BUMP_NONE, OCELEM_ON, },
    { 20, 80, 0, { 0, 0, 0 } },
};

static void *const EyeTextures[3] = {
	&object_oE9_mintCapEyesOpen, &object_oE9_mintCapEyesHalf, &object_oE9_mintCapEyesClosed
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
	u8 waitingAutoTalk;
	s32 getItemId;
	s32 animBankIdx, skelBankIdx, headBankIdx;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	en->initted = 0;
	if(en->actor.params != 0 || !(BETAKOKIRI_SPAWNED_VAR & BETAKOKIRI_SPAWNED_BIT)){
		Actor_Kill(&en->actor);
		return;
	}
	en->eyeTextureIndex = 0;
	en->blinkTimer = 0;
	en->waitingAutoTalk = 0;
	en->getItemId = -1;
    en->actor.textId = 0x0B10;
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, SHADOW_SIZE);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinderType1(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	en->animBankIdx = Object_GetIndex(&globalCtx->objectCtx, ANIM_OBJ_NUM);
	en->skelBankIdx = Object_GetIndex(&globalCtx->objectCtx, SKEL_OBJ_NUM);
	en->headBankIdx = Object_GetIndex(&globalCtx->objectCtx, HEAD_OBJ_NUM);
	if(en->animBankIdx < 0 || en->skelBankIdx < 0 || en->headBankIdx < 0){
		Actor_Kill(&en->actor);
		return;
	}
	en->initted = 1;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	if(en->initted >= 1) Collider_DestroyCylinder(globalCtx, &en->collider);
	if(en->initted == 2) SkelAnime_Free(&en->skelAnime, globalCtx);
}

static s32 checkObjectsLoaded(Entity *en, GlobalContext *globalCtx){
	return Object_IsLoaded(&globalCtx->objectCtx, en->animBankIdx)
		&& Object_IsLoaded(&globalCtx->objectCtx, en->skelBankIdx)
		&& Object_IsLoaded(&globalCtx->objectCtx, en->headBankIdx);
}

static void setBank(Entity *en, GlobalContext *globalCtx, s32 bank, s32 alsoRCP){
	void* segment = globalCtx->objectCtx.status[bank].segment;
	gSegments[6] = VIRTUAL_TO_PHYSICAL(segment);
	if(alsoRCP) gSPSegment(POLY_OPA_DISP++, 0x06, segment);
}

static void updateEyes(Entity *en){
	if(en->blinkTimer == 0){
		en->blinkTimer = Rand_S16Offset(60, 60);
	}else{
		--en->blinkTimer;
	}
	en->eyeTextureIndex = (en->blinkTimer < 3) ? en->blinkTimer : 0;
}

static void updateTurnInfo(Entity *en, GlobalContext *globalCtx){
	f32 eyeHeight;
	Actor *target;
	target = &PLAYER->actor;
	eyeHeight = kREG(16) + 9.0f;
	en->turnInfo.unk_18 = target->world.pos; //focusPos
	en->turnInfo.unk_14 = eyeHeight; //eyeHeight
	func_80034A14(&en->actor, &en->turnInfo, kREG(17) + 0xC, 2);
}

static s32 updateCommon(Entity *en, GlobalContext *globalCtx) {
	s32 objsLoaded = checkObjectsLoaded(en, globalCtx);
	if(objsLoaded && en->initted == 1){
		en->initted = 2;
		setBank(en, globalCtx, en->skelBankIdx, 0);
		SkelAnime_Init(globalCtx, &en->skelAnime, &object_oE4_betaKokiriSkeleton, 
			NULL, en->jointTable, en->morphTable, NUM_LIMBS);
		setBank(en, globalCtx, en->animBankIdx, 0);
		Animation_Change(&en->skelAnime, &object_oE_anime_kokiriStanding,
			1.0f, 0.0f, Animation_GetLastFrame(&object_oE_anime_kokiriStanding), ANIMMODE_LOOP, 0.0f);
	}
	if(!objsLoaded) return -1;
	Collider_UpdateCylinder(&en->actor, &en->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &en->collider.base);
	Actor_UpdateBgCheckInfo(globalCtx, &en->actor, 75.0f, 30.0f, 30.0f, 5);
	updateEyes(en);
	updateTurnInfo(en, globalCtx);
	return SkelAnime_Update(&en->skelAnime);
}

static void updateWaitGive(Entity *en, GlobalContext *globalCtx);
static void updateWaitPickedUp(Entity *en, GlobalContext *globalCtx);
static void updatePostItem(Entity *en, GlobalContext *globalCtx);

static void updateWaitTalk(Entity *en, GlobalContext *globalCtx){
	Player *player = PLAYER;
	s32 animDone = updateCommon(en, globalCtx);
	if(animDone < 0) return;
	if(Actor_IsTalking(&en->actor, globalCtx)){
		s8 playerExchangeItem = player->exchangeItemId;
		if((BETAKOKIRI_DONE_VAR & BETAKOKIRI_DONE_BIT)){
			en->actor.textId = 0x0B16;
		}else if(playerExchangeItem == EXCH_ITEM_BUG){
			en->actor.textId = 0x0B12;
			func_80078884(NA_SE_SY_ERROR);
		}else if(playerExchangeItem == EXCH_ITEM_BUTTERFLY){
			en->actor.textId = 0x0B13;
			func_80078884(NA_SE_SY_TRE_BOX_APPEAR);
			Player_UpdateBottleHeld(globalCtx, player, ITEM_BOTTLE, PLAYER_AP_BOTTLE);
			en->actor.update = (ActorFunc)updateWaitGive;
		}else if(playerExchangeItem != EXCH_ITEM_NONE){
			en->actor.textId = 0x0B11;
		}else{
			LOOKING_FOR_BUTTERFLY_VAR |= LOOKING_FOR_BUTTERFLY_BIT;
			en->actor.textId = 0x0B10;
		}
		player->actor.textId = en->actor.textId;
		return;
	}
	Actor_RequestToTalk(&en->actor, globalCtx);
	if(!(BETAKOKIRI_DONE_VAR & BETAKOKIRI_DONE_BIT)){
		player->exchangeItemId = EXCH_ITEM_BLUE_FIRE;
	}
}

static void updateWaitGive(Entity *en, GlobalContext *globalCtx){
	s32 animDone = updateCommon(en, globalCtx);
	if(animDone < 0) return;
	if(MESSAGE_ADVANCE_END){
		BETAKOKIRI_DONE_VAR |= BETAKOKIRI_DONE_BIT;
		en->getItemId = GI_ODD_POTION;
        globalCtx->msgCtx.unk_E3E7 = 4;
        globalCtx->msgCtx.msgMode = 0x36;
		Actor_PickUp(&en->actor, globalCtx, en->getItemId, 2000.0f, 2000.0f);
		en->actor.update = (ActorFunc)updateWaitPickedUp;
	}
}

static void updateWaitPickedUp(Entity *en, GlobalContext *globalCtx){
	s32 animDone = updateCommon(en, globalCtx);
	if(animDone < 0) return;
	if(en->actor.parent != NULL){
		en->actor.parent = NULL;
		en->getItemId = -1;
		en->actor.flags |= 0x10000;
		en->actor.textId = 0x0B15;
		en->actor.update = (ActorFunc)updatePostItem;
		return;
	}
	Actor_PickUp(&en->actor, globalCtx, en->getItemId, 2000.0f, 2000.0f);
}

static void updatePostItem(Entity *en, GlobalContext *globalCtx){
	s32 animDone = updateCommon(en, globalCtx);
	if(animDone < 0) return;
	Actor_RequestToTalkInRange(&en->actor, globalCtx, en->actor.colChkInfo.cylRadius +
        ((en->actor.flags & 0x10000) ? 1000.0f : 50.0f));
	if(Actor_IsTalking(&en->actor, globalCtx)){
		en->actor.flags &= ~0x10000;
	}
}

s32 BetaKokiri_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;
	if(limbIndex == LIMB_HEAD){
		setBank(en, globalCtx, en->headBankIdx, 1);
		gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(EyeTextures[en->eyeTextureIndex]));
		*dList = object_oE9_mintCapHeadDL;
		
		rot->x += en->turnInfo.unk_08.y;
		rot->z += en->turnInfo.unk_08.x;
	}
	return false;
}

void BetaKokiri_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;

    if (limbIndex == LIMB_HEAD) {
		setBank(en, globalCtx, en->skelBankIdx, 1);
		
        static Vec3f headBoneOriginToHeadCenter = { 700.0f, 0.0f, 0.0f };
        Matrix_MultVec3f(&headBoneOriginToHeadCenter, &en->actor.focus.pos);
    }
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	static Gfx emptyDL[1];
	gSPEndDisplayList(emptyDL);
	if(en->initted != 2) return;
	setBank(en, globalCtx, en->skelBankIdx, 1);
	gSPSegment(POLY_OPA_DISP++, 0x0D, emptyDL);
	gDPSetEnvColor(POLY_OPA_DISP++, 20, 110, 50, 255);
	SkelAnime_DrawOpa(globalCtx, en->skelAnime.skeleton, en->skelAnime.jointTable,
		BetaKokiri_OverrideLimbDraw, BetaKokiri_PostLimbDraw, en);
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_NPC,
	.flags = 0x00000019,
	.objectId = ANIM_OBJ_NUM,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)updateWaitTalk,
	.draw = (ActorFunc)draw
};
