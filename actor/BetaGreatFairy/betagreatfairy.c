#include "ootmain.h"
#include "obj.h"
#include "../../statics/statics.h"

extern s32 UnicornFountain_scene_header00_cutscene[];

// Actor Information
#define OBJ_ID 0x00A // primary object dependency (change if needed)
#define SWITCH_FLAG 0x20
#define FAIRY_SLOT 5

#define RISE_FRAMES 40

#define SPIRAL_ROTATIONS 4
#define LEAN_FORWARD 0x1000
#define LEAN_SHIFT_Z 30.0f
#define LEAN_RATIO 0.15f
#define CYCLE_PERIOD 60.0f
#define CYCLE_HEIGHT 10.0f
#define FLOAT_CENTER_HEIGHT 60.0f

#define SCALE_TINY 0.001f
#define SCALE_MAIN 0.085f

typedef struct {
	Actor actor;
	u8 state;
	u8 frames;
	float ratio;
	float lastFloatY;
	Vec3f wingtip;
	Vec3f lastWingtip;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	en->state = 0;
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	
}

static void update(Entity *en, GlobalContext *globalCtx) {
	if(Flags_GetSwitch(globalCtx, SWITCH_FLAG)){
		Flags_UnsetSwitch(globalCtx, SWITCH_FLAG);
		globalCtx->csCtx.segment = SEGMENTED_TO_VIRTUAL(&UnicornFountain_scene_header00_cutscene);
		gSaveContext.cutsceneTrigger = 1;
	}
	en->actor.world.pos = en->actor.home.pos;
	en->actor.shape.rot.x = 0; en->actor.shape.rot.y = 0; en->actor.shape.rot.z = 0;
	if(en->state == 0){
		//Away, waiting for NPC action
		Actor_SetScale(&en->actor, SCALE_TINY);
		en->actor.world.pos.y -= 1000.0f;
		en->lastFloatY = FLOAT_CENTER_HEIGHT;
		if(CHECK_NPC_ACTION(FAIRY_SLOT, 1)){
			Statics_GiveOvertureOfSages();
			en->frames = 0;
			++en->state;
		}
	}else if(en->state == 2){
		//Floating, waiting for NPC action
		Actor_SetScale(&en->actor, SCALE_MAIN);
		float y = CYCLE_HEIGHT * sinf((float)en->frames * 
			(2.0f * 3.14159f / CYCLE_PERIOD));
		en->actor.world.pos.z -= LEAN_SHIFT_Z;
		en->actor.world.pos.y += y + FLOAT_CENTER_HEIGHT;
		en->lastFloatY = en->actor.world.pos.y;
		en->actor.shape.rot.x = LEAN_FORWARD;
		++en->frames;
		if(en->frames >= CYCLE_PERIOD) en->frames = 0;
		if(CHECK_NPC_ACTION(FAIRY_SLOT, 2)){
			en->frames = 0;
			++en->state;
		}
	}else if(en->state == 1 || en->state == 3){
		//Rising or Falling
		if(en->frames == 0){
			Audio_PlayActorSound2(&(en->actor), NA_SE_VO_FR_LAUGH_0);
		}else if(en->frames == 1){
			Audio_PlayActorSound2(&(en->actor), en->state == 3 ? 
				NA_SE_EV_GREAT_FAIRY_VANISH : NA_SE_EV_GREAT_FAIRY_APPEAR);
		}
		en->ratio = (float)en->frames / (float)RISE_FRAMES;
		if(en->state == 1) en->ratio = 1.0f - en->ratio;
		
		float scale = en->ratio * (SCALE_TINY - SCALE_MAIN) + SCALE_MAIN;
		Actor_SetScale(&en->actor, scale);
		en->actor.world.pos.y += (1.0f - en->ratio) * en->lastFloatY;
		float rot = (en->ratio * en->ratio) * SPIRAL_ROTATIONS * 0x10000;
		en->actor.shape.rot.y = (s16)((s32)rot & 0xFFFF);
		if(en->state == 1) en->actor.shape.rot.y = -en->actor.shape.rot.y;
		
		if(en->ratio < LEAN_RATIO){
			float leanratio = 1.0f - (en->ratio / LEAN_RATIO);
			en->actor.shape.rot.x = (s16)((float)LEAN_FORWARD * leanratio);
			en->actor.world.pos.z -= leanratio * LEAN_SHIFT_Z;
		}
		
		en->lastWingtip = en->wingtip;
		float rad = (130.0f / SCALE_MAIN) * scale;
		float height = (150.0f / SCALE_MAIN) * scale;
		en->wingtip.x = rad *  Math_CosS(en->actor.shape.rot.y);
		en->wingtip.z = rad * -Math_SinS(en->actor.shape.rot.y);
		en->wingtip.y = height;
		
		++en->frames;
		if(en->frames == RISE_FRAMES){
			en->frames = 0;
			en->state = (en->state + 1) & 3;
		}
	}
}

static Vec3f Kira2Velocity = { 0.0f, 0.0f, 0.0f };
static Vec3f Kira2Accel = { 0.0f, 0.0f, 0.0f };
static Color_RGBA8 KiraPrimColor = { 240, 255, 80, 255 };
static Color_RGBA8 KiraEnvColor = { 200, 230, 0, 0 };
#define KIRA1_FRAMES 10

static void draw(Entity *en, GlobalContext *globalCtx) {
	if(en->state == 0) return;
	Gfx_DrawDListOpa(globalCtx, (Gfx*)DL_BETAGREATFAIRY);
	//Fix flower
	Gfx *flowerDL = SEGMENTED_TO_VIRTUAL(DL_BETAGREATFAIRY_FLOWER);
	gDPSetCombineLERP(flowerDL + 10,
		PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0,
		0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
	gDPSetPrimColor(flowerDL + 14,
		0, 0, 0x80, 0x98, 0xFF, 0xFF);
	gDPSetEnvColor(POLY_XLU_DISP++, 0x00, 0x28, 0x60, 0xFF);
	Gfx_DrawDListXlu(globalCtx, (Gfx*)DL_BETAGREATFAIRY_FLOWER);
	//Particles
	if(en->state == 2){
		const s32 nspawn = 1;
		for(s32 i=0; i<nspawn; ++i){
			Vec3f pos = en->actor.world.pos;
			pos.x += 160.0f * (Rand_ZeroOne() - 0.5f);
			pos.y += 120.0f * Rand_ZeroOne();
			pos.z += 70.0f * Rand_ZeroOne() + 10.0f;
			EffectSsKiraKira_SpawnFocused(globalCtx, &pos, &Kira2Velocity, &Kira2Accel,
				&KiraPrimColor, &KiraEnvColor, 3000, 10);
		}
	}else{
		s32 nspawn_perside = 2;
		float size = (1.0f - en->ratio) * 20.0f;
		Vec3f vel, accel;
		vel.x = (en->wingtip.x - en->lastWingtip.x) * 0.1f;
		vel.y = (en->wingtip.y - en->lastWingtip.y) * 0.1f;
		vel.z = (en->wingtip.z - en->lastWingtip.z) * 0.1f;
		accel.x = (1.0f / KIRA1_FRAMES) * -vel.x;
		accel.y = (1.0f / KIRA1_FRAMES) * -vel.y - 0.4f;
		accel.z = (1.0f / KIRA1_FRAMES) * -vel.z;
		for(s32 i=0; i<nspawn_perside; ++i){
			Vec3f mainpos = en->actor.world.pos;
			mainpos.x += size * (Rand_ZeroOne() - 0.5f);
			mainpos.y += size * (Rand_ZeroOne() - 0.5f);
			mainpos.z += size * (Rand_ZeroOne() - 0.5f);
			Vec3f pos = mainpos;
			pos.x += en->wingtip.x;
			pos.y += en->wingtip.y;
			pos.z += en->wingtip.z;
			EffectSsKiraKira_SpawnFocused(globalCtx, &pos, &vel, &accel,
				&KiraPrimColor, &KiraEnvColor, (1.0f - en->ratio) * 3000.0f, KIRA1_FRAMES);
			pos.x = mainpos.x - en->wingtip.x;
			pos.z = mainpos.z - en->wingtip.z;
			vel.x = -vel.x;
			vel.z = -vel.z;
			accel.x = -accel.x;
			accel.z = -accel.z;
			EffectSsKiraKira_SpawnFocused(globalCtx, &pos, &vel, &accel,
				&KiraPrimColor, &KiraEnvColor, (1.0f - en->ratio) * 3000.0f, KIRA1_FRAMES);
			vel.x = -vel.x;
			vel.z = -vel.z;
			accel.x = -accel.x;
			accel.z = -accel.z;
		}
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
