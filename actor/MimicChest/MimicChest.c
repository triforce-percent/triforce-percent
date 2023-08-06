#include "ootmain.h"
#include "MimicChestObj.h"
#include "MimicChestObjIdleAnim.h"
#include "MimicChestObjAttackAnim.h"

#define DEP_OBJECT_NUM 0x83
#define SHADOW_SIZE 80.0f
#define LURCH_SPEED 1.0f

static ColliderCylinderInit sCylinderInit = {
    .base = {
		.colType = COLTYPE_HIT5,
		.atFlags = AT_ON | AT_TYPE_ENEMY,
		.acFlags = AC_ON | AC_TYPE_PLAYER,
		.ocFlags1 = OC1_ON | OC1_TYPE_ALL,
		.ocFlags2 = OC1_TYPE_1,
		.shape = COLSHAPE_CYLINDER,
	},
	.info = {
		.elemType = ELEMTYPE_UNK1,
		.bumper = {
			.dmgFlags = DMG_DEFAULT,
		},
		.toucher = {
			.dmgFlags = DMG_UNBLOCKABLE,
			.effect = 0,
			.damage = 0x10
		},
		.toucherFlags = TOUCH_ON,
		.bumperFlags = BUMP_ON,
		.ocElemFlags = OCELEM_ON,
	},
	.dim = {
		.radius = 30,
		.height = 60,
		.yShift = 0,
		.pos = { 0 }
	},
};

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	ColliderCylinder collider;
    Vec3s jointTable[MIMICCHESTOBJ_NUM_LIMBS];
    Vec3s morphTable[MIMICCHESTOBJ_NUM_LIMBS];
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, SHADOW_SIZE);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinder(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &MimicChestObj, &MimicChestObjIdleAnim, 
		en->jointTable, en->morphTable, MIMICCHESTOBJ_NUM_LIMBS);
	Actor_SetScale(&en->actor, 0.01f);
	en->actor.gravity = -8.0f;
	en->actor.colChkInfo.mass = 0xFE;
	en->actor.colChkInfo.health = 0xB0;
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

static void updateAttack(Entity *en, GlobalContext *globalCtx);

static void updateWait(Entity *en, GlobalContext *globalCtx) {
	updateCommon(en, globalCtx);
	if(en->actor.xzDistToPlayer < 100.0f){
		Actor_ChangeCategory(globalCtx, &globalCtx->actorCtx, &en->actor, ACTORCAT_ENEMY);
		en->actor.flags |= 1; //targetable
		Animation_Change(&en->skelAnime, &MimicChestObjAttackAnim,
			1.0f, 0.0f, Animation_GetLastFrame(&MimicChestObjAttackAnim),
			ANIMMODE_LOOP, 6.0f);
		en->actor.update = updateAttack;
		return;
	}
}

static void updateAttack(Entity *en, GlobalContext *globalCtx) {
	Math_SmoothStepToS(&en->actor.shape.rot.y, en->actor.yawTowardsPlayer, 3, 500, 1);
	float x = Math_SinS(en->actor.shape.rot.y);
	float z = Math_CosS(en->actor.shape.rot.y);
	en->actor.velocity.x = x * LURCH_SPEED;
	en->actor.velocity.y = CLAMP_MIN(en->actor.gravity, en->actor.minVelocityY);
	en->actor.velocity.z = z * LURCH_SPEED;
	f32 speedRate = R_UPDATE_RATE * 0.5f;
	en->actor.world.pos.x += (en->actor.velocity.x * speedRate) + en->actor.colChkInfo.displacement.x;
	en->actor.world.pos.y += (en->actor.velocity.y * speedRate) + en->actor.colChkInfo.displacement.y;
	en->actor.world.pos.z += (en->actor.velocity.z * speedRate) + en->actor.colChkInfo.displacement.z;
	en->actor.focus.pos.x = en->actor.world.pos.x;
    en->actor.focus.pos.y = en->actor.world.pos.y + 30.0f;
    en->actor.focus.pos.z = en->actor.world.pos.z;
    en->actor.focus.rot.x = en->actor.world.rot.x;
    en->actor.focus.rot.y = en->actor.world.rot.y;
    en->actor.focus.rot.z = en->actor.world.rot.z;
	
	updateCommon(en, globalCtx);
	if(en->actor.xzDistToPlayer > 300.0f){
		Actor_ChangeCategory(globalCtx, &globalCtx->actorCtx, &en->actor, ACTORCAT_PROP);
		en->actor.flags &= ~1; //targetable
		Animation_Change(&en->skelAnime, &MimicChestObjIdleAnim,
			1.0f, 0.0f, Animation_GetLastFrame(&MimicChestObjIdleAnim),
			ANIMMODE_LOOP, 12.0f);
		en->actor.update = updateWait;
		return;
	}
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	func_80093D18(globalCtx->state.gfxCtx);
	SkelAnime_DrawFlexOpa(globalCtx, en->skelAnime.skeleton, en->skelAnime.jointTable,
		en->skelAnime.dListCount, NULL, NULL, en);
	func_80093D18(globalCtx->state.gfxCtx);
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_PROP,
	.flags = 0x00000018,
	.objectId = DEP_OBJECT_NUM,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)updateWait,
	.draw = (ActorFunc)draw
};
