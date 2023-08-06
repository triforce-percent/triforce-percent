#include "ootmain.h"
#include "AmogusObj.h"
#include "AmogusObjIdleAnim.h"

#define DEP_OBJECT_NUM 0x84
#define SHADOW_SIZE 25.0f
#define ACTOR_SCALE 0.018f

static ColliderCylinderInitType1 sCylinderInit = {
    { COLTYPE_HIT0, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE, BUMP_NONE, OCELEM_ON, },
    { 25, 80, 0, { 0, 0, 0 } },
};

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	ColliderCylinder collider;
    Vec3s jointTable[AMOGUSOBJ_NUM_LIMBS];
    Vec3s morphTable[AMOGUSOBJ_NUM_LIMBS];
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	en->actor.textId = 0x0920;
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, SHADOW_SIZE);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinderType1(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	SkelAnime_Init(globalCtx, &en->skelAnime, &AmogusObj, &AmogusObjIdleAnim, 
		en->jointTable, en->morphTable, AMOGUSOBJ_NUM_LIMBS);
	Actor_SetScale(&en->actor, ACTOR_SCALE);
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	Collider_DestroyCylinder(globalCtx, &en->collider);
	SkelAnime_Free(&en->skelAnime, globalCtx);
}

static void updateCommon(Entity *en, GlobalContext *globalCtx) {
	Collider_UpdateCylinder(&en->actor, &en->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &en->collider.base);
	Actor_UpdateBgCheckInfo(globalCtx, &en->actor, 75.0f, 30.0f, 30.0f, 5);
	SkelAnime_Update(&en->skelAnime);
}

static void updateTalking(Entity *en, GlobalContext *globalCtx);

static void updateWait(Entity *en, GlobalContext *globalCtx) {
	updateCommon(en, globalCtx);
	if(Actor_IsTalking(&en->actor, globalCtx)){
        Audio_SetBGM(0x71);
		Animation_Change(&en->skelAnime, &AmogusObjIdleAnim,
			1.0f, 0.0f, 2,
			ANIMMODE_LOOP, 10.0f);
		en->actor.update = updateTalking;
		return;
	}
	Actor_RequestToTalk(&en->actor, globalCtx);
}

static void updateTalking(Entity *en, GlobalContext *globalCtx) {
	updateCommon(en, globalCtx);
	if(MESSAGE_ADVANCE_END){
		Animation_Change(&en->skelAnime, &AmogusObjIdleAnim,
			1.0f, 0.0f, Animation_GetLastFrame(&AmogusObjIdleAnim),
			ANIMMODE_LOOP, 6.0f);
		en->actor.update = updateWait;
	}
}

s32 Amogus_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	return false;
}

void Amogus_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;

    if (limbIndex == AMOGUSOBJ_ROOT_ROT_LIMB) {
        Vec3f HeadBoneOriginToHeadCenter = { 0.0f, 60.0f / ACTOR_SCALE, 0.0f };
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
	SkelAnime_DrawOpa(globalCtx, en->skelAnime.skeleton, en->skelAnime.jointTable,
		Amogus_OverrideLimbDraw, Amogus_PostLimbDraw, en);
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
