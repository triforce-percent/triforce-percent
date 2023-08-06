#include "ootmain.h"
#include "PatrickStarObj.h"
#include "PatrickStarObjIdleAnim.h"
#include "PatrickStarObjHandupAnim.h"

#define DEP_OBJECT_NUM 0x7F
#define SHADOW_SIZE 40.0f

static ColliderCylinderInitType1 sCylinderInit = {
    { COLTYPE_HIT0, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE, BUMP_NONE, OCELEM_ON, },
    { 25, 80, 0, { 0, 0, 0 } },
};

/*
static void *const EyeTextures[3] = {
	&gNabooruEyeOpenTex,  &gNabooruEyeHalfTex,  &gNabooruEyeClosedTex
};
*/

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	ColliderCylinder collider;
    Vec3s jointTable[PATRICKSTAROBJ_NUM_LIMBS];
    Vec3s morphTable[PATRICKSTAROBJ_NUM_LIMBS];
	struct_80034A14_arg1 turnInfo;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	en->actor.textId = 0x0910;
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, SHADOW_SIZE);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinderType1(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &PatrickStarObj, &PatrickStarObjIdleAnim, 
		en->jointTable, en->morphTable, PATRICKSTAROBJ_NUM_LIMBS);
	Actor_SetScale(&en->actor, 0.015f);
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	Collider_DestroyCylinder(globalCtx, &en->collider);
	SkelAnime_Free(&en->skelAnime, globalCtx);
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

static void updateCommon(Entity *en, GlobalContext *globalCtx) {
	Collider_UpdateCylinder(&en->actor, &en->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &en->collider.base);
	Actor_UpdateBgCheckInfo(globalCtx, &en->actor, 75.0f, 30.0f, 30.0f, 5);
	updateTurnInfo(en, globalCtx);
	SkelAnime_Update(&en->skelAnime);
}

static void updateTalking(Entity *en, GlobalContext *globalCtx);

static void updateWait(Entity *en, GlobalContext *globalCtx) {
	updateCommon(en, globalCtx);
	if(Actor_IsTalking(&en->actor, globalCtx)){
		Animation_Change(&en->skelAnime, &PatrickStarObjHandupAnim,
			1.0f, 0.0f, Animation_GetLastFrame(&PatrickStarObjHandupAnim),
			ANIMMODE_LOOP, 10.0f);
		en->actor.update = updateTalking;
		return;
	}
	Actor_RequestToTalk(&en->actor, globalCtx);
}

static void updateTalking(Entity *en, GlobalContext *globalCtx) {
	updateCommon(en, globalCtx);
	if(MESSAGE_ADVANCE_END){
		Animation_Change(&en->skelAnime, &PatrickStarObjIdleAnim,
			1.0f, 0.0f, Animation_GetLastFrame(&PatrickStarObjIdleAnim),
			ANIMMODE_LOOP, 6.0f);
		en->actor.update = updateWait;
	}
}

s32 PatrickStar_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;
	if(limbIndex == PATRICKSTAROBJ_HEAD_LIMB){
		rot->x += en->turnInfo.unk_08.x;
		rot->y += en->turnInfo.unk_08.y;
	}else if(limbIndex == PATRICKSTAROBJ_TORSO_LIMB){
		//rot->x += en->turnInfo.unk_0E.x;
		rot->z += en->turnInfo.unk_0E.y;
	}
	return false;
}

void PatrickStar_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;

    if (limbIndex == PATRICKSTAROBJ_HEAD_LIMB) {
        Vec3f HeadBoneOriginToHeadCenter = { 0.0f, 10.0f, 0.0f };
        Vec3f HeadCenterOut;

        Matrix_MultVec3f(&HeadBoneOriginToHeadCenter, &HeadCenterOut);
        en->actor.focus.pos.x = HeadCenterOut.x;
        en->actor.focus.pos.y = HeadCenterOut.y;
        en->actor.focus.pos.z = HeadCenterOut.z;
        en->actor.focus.rot.x = en->actor.world.rot.x;
        en->actor.focus.rot.y = en->actor.world.rot.y;
        en->actor.focus.rot.z = en->actor.world.rot.z;
    }
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	func_80093D18(globalCtx->state.gfxCtx);
	SkelAnime_DrawFlexOpa(globalCtx, en->skelAnime.skeleton, en->skelAnime.jointTable,
		en->skelAnime.dListCount, PatrickStar_OverrideLimbDraw, PatrickStar_PostLimbDraw, en);
	func_80093D18(globalCtx->state.gfxCtx);
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_NPC,
	.flags = 0x00000019,
	.objectId = DEP_OBJECT_NUM,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)updateWait,
	.draw = (ActorFunc)draw
};
