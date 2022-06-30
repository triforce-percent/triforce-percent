#include "ootmain.h"

#define QUOTEX(x) #x
#define QUOTE(x) QUOTEX(x)
#define ACE_DEST_ADDR 0x8011D790

extern void ACE_Dest(void);
asm(".equ ACE_Dest, " QUOTE(ACE_DEST_ADDR));

//Using this to signal ACE done
#define GLOBAL_FLAG ((u8*)&globalCtx->lightCtx.unk_0C)[3]
#define FLAG_ACEDONE 0xA5
#define FLAG_ACEHAPPENING 0xEB

#define AOE 600.0f

static void HackWonderItem_Init(Actor* thisx, GlobalContext *globalCtx) {
	if(GLOBAL_FLAG == FLAG_ACEDONE || thisx->params != 0x0FE0 || thisx->world.rot.z != 1){
		Actor_Kill(thisx);
	}
}

static void HackWonderItem_Destroy(Actor* thisx, GlobalContext *globalCtx) {
	
}

static void HackWonderItem_Update(Actor* thisx, GlobalContext *globalCtx) {
	if(GLOBAL_FLAG == FLAG_ACEDONE){
		Actor_Kill(thisx);
		return;
	}
	if(GLOBAL_FLAG == FLAG_ACEHAPPENING || thisx->xzDistToPlayer < AOE){
		GLOBAL_FLAG = FLAG_ACEHAPPENING;
		osWritebackDCache(NULL, 0x4000);
		osInvalICache(NULL, 0x4000);
		ACE_Dest();
	}
	/*if(thisx->dist_from_link_xz < AOE && GLOBAL_FLAG != 0xBD){
		Audio_PlayActorSound2(thisx, 0x100E);
		GLOBAL_FLAG = 0xBD;
	}else if(thisx->dist_from_link_xz > AOE && GLOBAL_FLAG == 0xBD){
		Audio_PlayActorSound2(thisx, 0x1039);
		GLOBAL_FLAG = 0;
	}*/
}

const char padding[0x9DC] = {};

const ActorInitExplPad init_vars = {
    .id = 0x0112, 
	.category = ACTORCAT_PROP,
	.flags = 0x00000030, //Always run update and draw functions
	.objectId = 1, //gameplay_keep
	.padding = 0x0000,
	.instanceSize = 0x01C0,
	.init = HackWonderItem_Init,
	.destroy = HackWonderItem_Destroy,
	.update = HackWonderItem_Update,
	.draw = NULL
};

const char padding2[0x160] = {};
