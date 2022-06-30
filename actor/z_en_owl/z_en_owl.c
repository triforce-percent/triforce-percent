#include "ootmain.h"

static void init(Actor *this, GlobalContext *globalCtx) {
	Actor_Kill(this); //sorry, not sorry
}

static void destroy(Actor *this, GlobalContext *globalCtx) {}
static void update(Actor *this, GlobalContext *globalCtx){}
static void draw(Actor *this, GlobalContext *globalCtx) {}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_NPC,
	.flags = 0x00000010,
	.objectId = OBJECT_GAMEPLAY_KEEP,
	.instanceSize = sizeof(Actor),
	.init = init,
	.destroy = destroy,
	.update = update,
	.draw = draw
};
