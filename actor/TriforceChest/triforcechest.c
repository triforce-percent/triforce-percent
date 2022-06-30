#include "ootmain.h"
#include "obj.h"

// Actor Information
#define OBJ_ID 5 // primary object dependency (change if needed)

#define OPEN_DELAY 60
#define ANIM_LEN 50
#define TIMEWARP_SCALE 0.1f

typedef struct {
	Actor actor;
	SkelAnime skelanime;
	u8 state, frame;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	Actor_SetScale(&en->actor, 1.8f);
	SkelAnime_Init(globalCtx, &en->skelanime, (SkeletonHeader*)SKEL_TRIFORCECHEST,
		(AnimationHeader*)ANIM_CHESTOPENING, NULL, NULL, 0);
	Animation_Change(&en->skelanime, (AnimationHeader*)ANIM_CHESTOPENING,
		0.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f);
	en->state = 0;
	en->frame = 0;
	if(en->actor.params){
		en->state = 1;
		en->skelanime.curFrame = en->skelanime.endFrame = ANIM_LEN;
	}
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	
}

static void update(Entity *en, GlobalContext *globalCtx) {
	Actor *timewarp = Actor_Find(&globalCtx->actorCtx, ACTOR_DEMO_EFFECT, ACTORCAT_BG);
	if(timewarp != NULL){
		timewarp->scale.x = TIMEWARP_SCALE;
		timewarp->scale.z = TIMEWARP_SCALE;
	}
	if(en->state == 0 && en->frame >= OPEN_DELAY){
		Animation_Change(&en->skelanime, (AnimationHeader*)ANIM_CHESTOPENING,
			1.0f, 0.0f, ANIM_LEN, ANIMMODE_ONCE, 0.0f);
		en->state = 1;
	}
	++en->frame;
	SkelAnime_Update(&en->skelanime);
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	func_80093D18(globalCtx->state.gfxCtx);
	SkelAnime_DrawOpa(globalCtx, en->skelanime.skeleton, en->skelanime.jointTable,
		NULL, NULL, &en->actor);
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
