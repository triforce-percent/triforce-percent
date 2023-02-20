#include "ootmain.h"
#include "object_ge1.h"

#define DEP_OBJECT_NUM 0x7F
#define SHADOW_SIZE 20.0f

static void *const EyeTextures[3] = {
	&gGerudoWhiteEyeOpenTex,  &gGerudoWhiteEyeHalfTex,  &gGerudoWhiteEyeClosedTex
};

static ColliderCylinderInitType1 sCylinderInit = {
    { COLTYPE_HIT0, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE, BUMP_NONE, OCELEM_ON, },
    { 25, 80, 0, { 0, 0, 0 } },
};

#define RESPONSE_NONE 0
#define RESPONSE_SHOO 1
#define RESPONSE_OPEN 2

typedef struct {
	Actor actor;
	SkelAnime skelAnime;
	ColliderCylinder collider;
    Vec3s jointTable[GE1_LIMB_MAX];
    Vec3s morphTable[GE1_LIMB_MAX];
	struct_80034A14_arg1 turnInfo;
    u8 responseState;
    u8 clappingTimer;
    u8 eyeTextureIndex;
    u8 blinkTimer;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
    en->responseState = RESPONSE_NONE;
	en->eyeTextureIndex = 0;
	en->blinkTimer = 0;
	en->actor.textId = 0x6069; // "A kid like you has no business there"
	ActorShape_Init(&en->actor.shape, 0.0f, ActorShadow_DrawCircle, SHADOW_SIZE);
	Collider_InitCylinder(globalCtx, &en->collider);
    Collider_SetCylinderType1(globalCtx, &en->collider, &en->actor, &sCylinderInit);
	SkelAnime_InitFlex(globalCtx, &en->skelAnime, &gGerudoWhiteSkel, &gGerudoWhiteIdleAnim, 
		en->jointTable, en->morphTable, GE1_LIMB_MAX);
	Actor_SetScale(&en->actor, 0.01f);
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	Collider_DestroyCylinder(globalCtx, &en->collider);
	SkelAnime_Free(&en->skelAnime, globalCtx);
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
	Collider_UpdateCylinder(&en->actor, &en->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &en->collider.base);
	Actor_UpdateBgCheckInfo(globalCtx, &en->actor, 75.0f, 30.0f, 30.0f, 5);
    updateEyes(en);
	updateTurnInfo(en, globalCtx);
	return SkelAnime_Update(&en->skelAnime);
}

static void updateTalking(Entity *en, GlobalContext *globalCtx);

static void updateWait(Entity *en, GlobalContext *globalCtx) {
	updateCommon(en, globalCtx);
	if(Actor_IsTalking(&en->actor, globalCtx)){
        if(en->responseState == RESPONSE_SHOO){
            Animation_Change(&en->skelAnime, &gGerudoWhiteDismissiveAnim,
                1.0f, 0.0f, Animation_GetLastFrame(&gGerudoWhiteDismissiveAnim),
                ANIMMODE_LOOP, 8.0f);
        }
		en->actor.update = (ActorFunc)updateTalking;
		return;
	}
    en->responseState = RESPONSE_NONE;
    if(Player_GetMask(&gGlobalContext) != PLAYER_MASK_GERUDO){
        en->actor.textId = 0x6069; // "A kid like you has no business there"
        en->responseState = RESPONSE_SHOO;
    }else if(en->actor.textId == 0x6001){ // "Hey, newcomer!"
        (void)0;
    }else if((WORKING_GERUDOMASK_VAR & WORKING_GERUDOMASK_BIT)){
        en->actor.textId = 0x0B40; // "A Gerudo child far from the desert?"
        en->responseState = RESPONSE_OPEN;
    }else{
        en->actor.textId = 0x719F; // "You've got guts coming around here"
    }
	Actor_RequestToTalk(&en->actor, globalCtx);
}

#define FENCE_START_DROP_FRAME 24
#define FENCE_DROP_FRAMES 20
#define FENCE_DROP_DIST 75.0f

static void updateClapping(Entity *en, GlobalContext *globalCtx) {
    updateCommon(en, globalCtx);
    if(en->clappingTimer == 17 || en->clappingTimer == 21){
        Audio_PlayActorSound2(&en->actor, NA_SE_IT_HAND_CLAP);
    }
    s8 t = en->clappingTimer - FENCE_START_DROP_FRAME;
    if(t >= FENCE_DROP_FRAMES){
        en->actor.update = (ActorFunc)updateWait;
        Animation_Change(&en->skelAnime, &gGerudoWhiteIdleAnim,
            1.0f, 0.0f, Animation_GetLastFrame(&gGerudoWhiteIdleAnim),
            ANIMMODE_LOOP, 10.0f);
        return;
    }
    if(t >= 0){
        Actor *fence = Actor_FindNearby(globalCtx, &en->actor, ACTOR_BG_UMAJUMP,
            ACTORCAT_PROP, 1000);
        if(!fence) return;
        static const u8 heights[FENCE_DROP_FRAMES] = {
            0xFD, 0xF8, 0xF0, 0xE4, 0xD4, 0xC0, 0xA0, 0x70, 0x38, 0x00,
            0x20, 0x30, 0x38, 0x30, 0x20, 0x00, 0x10, 0x14, 0x10, 0x00
        };
        fence->world.pos.y = fence->home.pos.y - (FENCE_DROP_DIST / 256.0f) * (0x100 - heights[t]);
        if(t == 9 || t == 15 || t == 19){
            Audio_PlayActorSound2(fence, NA_SE_EN_IRONNACK_ARMOR_DEMO);
        }
    }
    ++en->clappingTimer;
}

static void updateTalking(Entity *en, GlobalContext *globalCtx) {
	updateCommon(en, globalCtx);
	if(MESSAGE_ADVANCE_END){
        if(en->responseState == RESPONSE_OPEN){
            Animation_Change(&en->skelAnime, &gGerudoWhiteClapAnim,
    			1.0f, 0.0f, Animation_GetLastFrame(&gGerudoWhiteClapAnim),
    			ANIMMODE_ONCE, 5.0f);
    		en->actor.update = (ActorFunc)updateClapping;
            en->clappingTimer = 0;
            en->actor.textId = 0x6001; // "Hey, newcomer!"
        }else{
    		Animation_Change(&en->skelAnime, &gGerudoWhiteIdleAnim,
    			1.0f, 0.0f, Animation_GetLastFrame(&gGerudoWhiteIdleAnim),
    			ANIMMODE_LOOP, 10.0f);
    		en->actor.update = (ActorFunc)updateWait;
        }
	}
}

s32 Ge1_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;
	if(limbIndex == GE1_LIMB_HEAD){
		rot->x += en->turnInfo.unk_08.y;
		rot->z += en->turnInfo.unk_08.x;
	}
	return false;
}

void Ge1_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;

    if (limbIndex == GE1_LIMB_HEAD) {
        Vec3f HeadBoneOriginToHeadCenter = { 0.0f, 8.0f, 0.0f };
        Vec3f HeadCenterOut;
        
        gSPDisplayList(POLY_OPA_DISP++, &gGerudoWhiteHairstyleSpikyDL);

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
	gSPSegment(POLY_OPA_DISP++, 0x08,
        SEGMENTED_TO_VIRTUAL(EyeTextures[en->eyeTextureIndex]));
	SkelAnime_DrawFlexOpa(globalCtx, en->skelAnime.skeleton, en->skelAnime.jointTable,
		en->skelAnime.dListCount, Ge1_OverrideLimbDraw, Ge1_PostLimbDraw, en);
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_NPC,
	.flags = 0x00000019,
	.objectId = OBJECT_GE1,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)updateWait,
	.draw = (ActorFunc)draw
};
