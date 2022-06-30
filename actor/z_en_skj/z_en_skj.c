#include "ootmain.h"
#include "object_skj.h"

#define NUM_LIMBS 19
#define STUMP_SIZE 26.0f

/*
static ColliderCylinderInitType1 sCylinderInit = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xFFCFFFFF, 0x00, 0x08 }, { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 8, 48, 0, { 0, 0, 0 } },
};
*/

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	//ColliderCylinder collider;
    Vec3s jointTable[NUM_LIMBS];
    Vec3s morphTable[NUM_LIMBS];
	s32 maskGiving;
} Entity;

static Entity *sSmallStumpSkullKid = NULL;

void invisDestroy(Entity *en, GlobalContext *globalCtx);
void invisUpdate(Entity *en, GlobalContext *globalCtx);
static void update_NotOnStump(Entity *en, GlobalContext *globalCtx);
static void update_OnStump(Entity *en, GlobalContext *globalCtx);

static void init(Entity *en, GlobalContext *globalCtx) {
	//Rupees_ChangeBy(7);
	s16 type = (en->actor.params >> 0xA) & 0x3F;
	if(type == 5){
		//Invisible on Saria's Song stump
		sSmallStumpSkullKid = en;
		en->actor.destroy = (ActorFunc)invisDestroy;
		en->actor.draw = NULL;
		en->actor.update = (ActorFunc)invisUpdate;
		Actor_ChangeCategory(globalCtx, &globalCtx->actorCtx, &en->actor, ACTORCAT_PROP);
		return;
	}else if(type != 0){
		en->actor.destroy = NULL;
		Actor_Kill(&en->actor);
		return;
	}
	//Normal for Saria's Song
	en->actor.naviEnemyId = 0x40;
	en->actor.flags |= 9;
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, 40.0f);
	//Collider_InitCylinder(globalCtx, &en->collider);
    //Collider_SetCylinderType1(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &gSkullKidSkel, &gSkullKidPlayFluteAnim, 
		en->jointTable, en->morphTable, NUM_LIMBS);
	Actor_SetScale(&en->actor, 0.01f);
	en->maskGiving = -1;
}

void invisDestroy(Entity *en, GlobalContext *globalCtx){
	//Rupees_ChangeBy(-1);
	sSmallStumpSkullKid = NULL;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	//Rupees_ChangeBy(-2);
	//Collider_DestroyCylinder(globalCtx, &en->collider);
	SkelAnime_Free(&en->skelAnime, globalCtx);
}

static s32 updateCommon(Entity *en, GlobalContext *globalCtx) {
	//Collider_UpdateCylinder(&en->actor, &en->collider);
    //CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &en->collider.base);
	Actor_UpdateBgCheckInfo(globalCtx, &en->actor, 20.0f, 20.0f, 20.0f, 7);
	return SkelAnime_Update(&en->skelAnime);
}

static s32 isLinkOnStump(){
	return sSmallStumpSkullKid != NULL && sSmallStumpSkullKid->actor.xzDistToPlayer < STUMP_SIZE;
}

void invisUpdate(Entity *en, GlobalContext *globalCtx){
	
}

static void update_NotOnStump(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx);
	if(sSmallStumpSkullKid == NULL) return;
	if(isLinkOnStump()){
		Animation_Change(&en->skelAnime, &gSkullKidWaitAnim, 1.0f, 0.0f, 
			Animation_GetLastFrame(&gSkullKidWaitAnim), ANIMMODE_LOOP, -8.0f);
		en->actor.update = (ActorFunc)update_OnStump;
	}
}

static void update_OnStump(Entity *en, GlobalContext *globalCtx){
	updateCommon(en, globalCtx);
	if(sSmallStumpSkullKid == NULL) return;
	if(!isLinkOnStump()){
		Animation_Change(&en->skelAnime, &gSkullKidPlayFluteAnim, 1.0f, 0.0f, 
			Animation_GetLastFrame(&gSkullKidPlayFluteAnim), ANIMMODE_LOOP, -8.0f);
		en->actor.update = (ActorFunc)update_NotOnStump;
		return;
	}
	//Player* player = PLAYER;
	//player->stateFlags2 |= 0x800000; //fixed camera?
	s32 shouldRequestTalk = 0;
	en->actor.flags &= ~0x10000; //disable auto talk
	s32 isBunny = (Player_GetMask(globalCtx) == PLAYER_MASK_BUNNY) 
		&& !(WORKING_BUNNYHOOD_VAR & WORKING_BUNNYHOOD_BIT);
	s32 isGerudo = (Player_GetMask(globalCtx) == PLAYER_MASK_GERUDO)
		&& !(WORKING_GERUDOMASK_VAR & WORKING_GERUDOMASK_BIT);
	if((SKULLKID_WILL_UPGRADE_VAR & SKULLKID_WILL_UPGRADE_BIT)){
		shouldRequestTalk = 1;
		if(isBunny || isGerudo){
			en->actor.flags |= 0x10000; //auto talk
			en->actor.textId = 0x0B34;
		}else{
			en->actor.textId = 0x0B33;
		}
	}else{
	}
	if(INV_CONTENT(ITEM_TRADE_CHILD) == ITEM_ODD_POTION){
		shouldRequestTalk = 1;
		en->actor.textId = 0x0B30;
	}
	if(shouldRequestTalk){
		f32 xDiff = sSmallStumpSkullKid->actor.world.pos.x - en->actor.world.pos.x;
		f32 zDiff = sSmallStumpSkullKid->actor.world.pos.z - en->actor.world.pos.z;
		f32 talk_range = sqrtf(SQ(xDiff) + SQ(zDiff)) + STUMP_SIZE;
		Actor_RequestToTalkInRange(&en->actor, globalCtx, talk_range);
	}
	if(MESSAGE_ADVANCE_CHOICE){
		if(globalCtx->msgCtx.choiceIndex == 0){
			en->actor.textId = 0x0B32;
			Item_Give(globalCtx, ITEM_SOLD_OUT);
			SKULLKID_WILL_UPGRADE_VAR |= SKULLKID_WILL_UPGRADE_BIT;
		}else{
			en->actor.textId = 0x0B31;
		}
		MESSAGE_CONTINUE;
	}else if(MESSAGE_ADVANCE_END && en->actor.textId == 0x0B34){
		if(isBunny){
			en->maskGiving = GI_MASK_BUNNY;
			WORKING_BUNNYHOOD_VAR |= WORKING_BUNNYHOOD_BIT;
		}else{
			en->maskGiving = GI_MASK_GERUDO;
			WORKING_GERUDOMASK_VAR |= WORKING_GERUDOMASK_BIT;
		}
		Player_UnsetMask(globalCtx);
	}
	if(en->maskGiving >= 0){
		if(en->actor.parent != NULL){
			en->actor.parent = NULL;
			en->maskGiving = -1;
		}else{
			Actor_PickUp(&en->actor, globalCtx, en->maskGiving, 2000.0f, 2000.0f);
		}
	}
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	static Gfx dList[2];
	func_80093D18(globalCtx->state.gfxCtx);
	Gfx *dListHead = dList;
    gDPSetEnvColor(dListHead++, 0, 0, 0, 255);
	gSPEndDisplayList(dListHead++);
    gSPSegment(POLY_OPA_DISP++, 0x0C, dList);
	SkelAnime_DrawFlexOpa(globalCtx, en->skelAnime.skeleton, en->skelAnime.jointTable,
		en->skelAnime.dListCount, NULL, NULL, en);
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_NPC,
	.flags = 0x00000010, //0x02000010,
	.objectId = OBJECT_SKJ,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update_NotOnStump,
	.draw = (ActorFunc)draw
};
