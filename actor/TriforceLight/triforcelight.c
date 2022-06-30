#include "ootmain.h"
#include "obj.h"

// Actor Information
#define OBJ_ID 16 // primary object dependency

#define OPEN_DELAY 60
#define ANIM_LEN 50
#define DISAPPEAR_FRAME 380

typedef struct {
	Actor actor;
	SkelAnime skelanime;
	u8 state;
	u16 frame;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	Actor_SetScale(&en->actor, 1.8f);
	SkelAnime_InitFlex(globalCtx, &en->skelanime, (FlexSkeletonHeader*)SKEL_LIGHT,
		(AnimationHeader*)ANIM_LIGHTANIM, NULL, NULL, 0);
	en->state = 0;
	en->frame = 0;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	
}

static void update(Entity *en, GlobalContext *globalCtx) {
    if(en->frame < OPEN_DELAY){
        Animation_Change(&en->skelanime, (AnimationHeader*)ANIM_LIGHTANIM,
			1.0f, 0.0f, 0.0f, 0, 0.0f);
	}else if(en->frame == OPEN_DELAY){
		en->state = 1;
	}else if(en->frame == OPEN_DELAY + ANIM_LEN - 1){
		en->state = 2;
	}else if(en->frame == DISAPPEAR_FRAME){
		en->state = 3;
	}
	if(en->state < 3) ++en->frame;
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	if(en->state < 2){
		SkelAnime_Update(&en->skelanime);
	}
	if(en->state < 3){
		POLY_XLU_DISP = SkelAnime_DrawFlex(globalCtx, 
			en->skelanime.skeleton, en->skelanime.jointTable,
			en->skelanime.dListCount, NULL, NULL, &en->actor, POLY_XLU_DISP);
	}
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_PROP,
	.flags = 0x00000010,
	.objectId = OBJ_ID,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};
