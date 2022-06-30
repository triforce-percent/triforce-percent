#include "ootmain.h"
#include "RauruStair.h"
#include "RauruStairCollision.h"
#include "SariaStair.h"
#include "SariaStairCollision.h"
#include "SheikStair.h"
#include "SheikStairCollision.h"
#include "TriforceFadeWall.h"
#include "TriforceHallway.h"
#include "TriforceDoor.h"

// Actor Information
#define OBJ_ID 17 // primary object dependency

/*
 * a 0xA6 o 0xA7 En_Rl:   slot 0 (number 39). No rise. 2: stand, 3: pose
 * a 0xC9 o 0xBC Demo_Sa: slot 4 (number 43). Probably params 0. 1: rise, 2: stand, 3: pose
 * a 0xA8 o 0x9D Demo_Du: slot 2 (number 41). Same
 * a 0xD2 o 0xCA En_Ru2:  slot 3 (number 42). Same
 * a 0xC3 o 0xB3 En_Nb:   slot 1 (number 40). Same
 * a 0xA9 o 0x87 Demo_Im: slot 5 (number 44). Same
 * a 0x48 o 0x8A En_Xc:   slots 0 and 4
 
spaceSize for Object_InitBank calculations:
Adult Link object: 222 KiB
gameplay_keep: 368 KiB
gameplay_field_keep: 53 KiB
rl: 31 KiB
sa: 85 KiB
du: 74 KiB
ru2: 63 KiB
nb: 97 KiB
im: 73 KiB
xc: 115 KiB
Total without stairs: 1181 KiB
Stairs: currently 33 KiB
Total plus a bit extra: 1220 KiB -> 1250000
*/
#define STAIRS_SLOT 9 //actor number 0x8F

#define CS_ACTIVATE_RADIUS 120.0f
#define DOOR_OPEN_DIST 255.0f
#define DOOR_OPEN_SPEED 3.5f

#define STATE_INIT 0
#define STATE_WAIT 1
#define STATE_FADEIN 2
#define STATE_FADEOUT 3
#define STATE_IDLE 4
#define STATE_DOOROPENING 5

#define PARAM ((u16)en->dyna.actor.params)

typedef struct {
	DynaPolyActor dyna;
	u8 state;
	u8 timer;
	u8 sound_timer;
	u8 alpha;
	u8 collision;
	u8 cutscene_activated;
	u8 init_timer;
} Entity;

/*
Actor parameter:
0: Rauru stairs
1-5: Saria stairs (Saria, Darunia, Ruto, Nabooru, Impa)
6: Sheik stairs
7: Triforce fade wall
8: Triforce hallway
9: Triforce door
*/

static Gfx * const DLists[] = {
	RauruStair,
	SariaStair, SariaStair, SariaStair, SariaStair, SariaStair, 
	SheikStair,
	TriforceFadeWall, TriforceHallway, TriforceDoor
};

static const u8 DListsTransparent[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 0, 0
};

static CollisionHeader * const ColHeaders[] = {
	&RauruStairCollision_collisionHeader,
	&SariaStairCollision_collisionHeader,
	&SariaStairCollision_collisionHeader,
	&SariaStairCollision_collisionHeader,
	&SariaStairCollision_collisionHeader,
	&SariaStairCollision_collisionHeader,
	&SheikStairCollision_collisionHeader,
	NULL, NULL, NULL,
};

extern s32 CS1Saria[];
extern s32 CS2Darunia[];
extern s32 CS3Ruto[];
extern s32 CS4Nabooru[];
extern s32 CS5Impa[];
extern s32 CS6Sheik[];

static s32 * const Cutscenes[] = {
	NULL,
	CS1Saria,
	CS2Darunia,
	CS3Ruto,
	CS4Nabooru,
	CS5Impa,
	CS6Sheik,
	NULL,
	NULL,
	NULL
};

static const u8 FadeSpeeds[] = {
	6, 6, 6, 6, 6, 6, 8, 40, 10, 10
};

static const u8 WaitTimes[] = {
	20, 20, 20, 20, 20, 20, 20, 31, 5, 5
};

//#define COLLISION_OFF() func_8003EBF8(globalCtx, &globalCtx->colCtx.dyna, en->dyna.bgId)
//#define COLLISION_ON()  func_8003EC50(globalCtx, &globalCtx->colCtx.dyna, en->dyna.bgId)

static void CreateCollision(Entity *en, GlobalContext *globalCtx){
	if(ColHeaders[PARAM] == NULL) return;
	CollisionHeader* colHeaderVRAM;
	CollisionHeader_GetVirtual(ColHeaders[PARAM], &colHeaderVRAM);
    en->dyna.bgId = DynaPoly_SetBgActor(globalCtx, 
		&globalCtx->colCtx.dyna, &en->dyna.actor, colHeaderVRAM);
	en->collision = 1;
}

static void DestroyCollision(Entity *en, GlobalContext *globalCtx){
	DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, en->dyna.bgId);
	en->collision = 0;
}

static void init(Entity *en, GlobalContext *globalCtx) {
	en->state = STATE_INIT;
	en->sound_timer = 0;
	en->alpha = 0;
	en->collision = 0;
	en->cutscene_activated = 0;
	en->init_timer = 0;
	if(PARAM > 9){
		Actor_Kill(&en->dyna.actor);
		return;
	}
	if(PARAM >= 7){
		Actor_ChangeCategory(globalCtx, &globalCtx->actorCtx, &en->dyna.actor, ACTORCAT_BG);
	}
	DynaPolyActor_Init(&en->dyna, DPM_UNK);
	Actor_SetScale(&en->dyna.actor, 0.1f);
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	if(en->collision) DestroyCollision(en, globalCtx);
}

static void update(Entity *en, GlobalContext *globalCtx) {
	if(en->init_timer < 100) ++en->init_timer;
	//Check spawn or despawn, handle collision
	u16 target_action;
	if(PARAM <= 6){ //All stairs
		target_action = PARAM + 1;
	}else{ //wall, hallway, door
		target_action = 8;
	}
	if(!en->collision && en->state == STATE_INIT &&
			(CHECK_NPC_ACTION(STAIRS_SLOT, target_action) ||
			(PARAM == 0 && en->init_timer == 10 && globalCtx->csCtx.state == 0))){
		CreateCollision(en, globalCtx);
		en->state = STATE_WAIT;
		en->timer = 0;
		if(PARAM == 9) en->sound_timer = 1;
	}else if(en->collision && CHECK_NPC_ACTION(STAIRS_SLOT, 0)){
		DestroyCollision(en, globalCtx);
		en->state = STATE_FADEOUT;
	}
	//Sequencing logic
	if(en->state == STATE_WAIT){
		++en->timer;
		if(en->timer >= WaitTimes[PARAM]){
			en->state = STATE_FADEIN;
		}
	}
	//Fade in or out
	s32 temp = en->alpha;
	s32 fade_speed = FadeSpeeds[PARAM];
	if(en->state == STATE_FADEIN){
		temp += fade_speed;
		if(temp >= 255){
			temp = 255;
			en->state = STATE_IDLE;
		}
	}else if(en->state == STATE_FADEOUT){
		temp -= fade_speed;
		if(temp <= 0){
			temp = 0;
			en->state = STATE_IDLE;
		}
	}
	en->alpha = temp;
	//Sounds
	if(en->sound_timer){
		//NA_SE_EV_TRIFORCE_FLASH: used for white out when Sheik transforms
		//NA_SE_EV_TRIFORCE_MARK: when Ganondorf shows his Triforce
		if(en->sound_timer < 40){
			//mid dual synth fall, then "phong" if left for long enough
			Audio_PlayActorSound2(&(en->dyna.actor), NA_SE_EV_SHUT_BY_CRYSTAL - SFX_FLAG);
		}
		if(en->sound_timer >= 25 && en->sound_timer < 45){
			//low sine fall
			Audio_PlayActorSound2(&(en->dyna.actor), NA_SE_EV_FANTOM_WARP_L2 - SFX_FLAG);
		}
		++en->sound_timer;
	}
	if((en->state == 1 || en->state == 2) && PARAM <= 6){ //Any stairs
		Audio_PlayActorSound2(&(en->dyna.actor), NA_SE_EV_RAINBOW_SHOWER - SFX_FLAG);
	}
	//Trigger cutscenes
	if(Cutscenes[PARAM] != NULL
			&& !en->cutscene_activated 
			&& en->dyna.actor.xzDistToPlayer < CS_ACTIVATE_RADIUS){
		globalCtx->csCtx.segment = SEGMENTED_TO_VIRTUAL(Cutscenes[PARAM]);
		gSaveContext.cutsceneTrigger = 1;
		en->cutscene_activated = 1;
	}
	//Open Triforce door
	if(PARAM == 9){
		if(en->state == STATE_IDLE && CHECK_NPC_ACTION(STAIRS_SLOT, 9)){
			en->state = STATE_DOOROPENING;
		}
		if(en->state == STATE_DOOROPENING){
			en->dyna.actor.world.pos.y += DOOR_OPEN_SPEED;
			if(en->dyna.actor.world.pos.y - en->dyna.actor.home.pos.y >= DOOR_OPEN_DIST){
				Audio_PlayActorSound2(&(en->dyna.actor), NA_SE_EV_STONEDOOR_STOP);
				Actor_Kill(&en->dyna.actor);
			}else{
                Audio_PlayActorSound2(&(en->dyna.actor), NA_SE_EV_STONE_STATUE_OPEN - SFX_FLAG);
            }
		}
	}
}

static const s8 KiraType[] = { 0, 1, 1, 1, 1, 1, 2, -1, -1, -1 };
static const float KiraCtrX[] = { -305.0f,  420.0f, 0.0f };
static const float KiraCtrZ[] = { -334.0f,  454.0f, 0.0f };
static const float KiraRad[]  = {  288.0f,  600.0f, 0.0f };
static const float KiraW[]    = {  113.0f,  115.0f, 113.0f };
static const float KiraDY[]   = {   93.0f,  172.0f, 326.0f };
static const s16 KiraAngleLo[] = { 0x0000, 0x6AAA, -122 };
static const s16 KiraAngleHi[] = { 0x6800, 0x9555, -810 };
static Vec3f KiraVelocity = { 0.0f, -11.0f, 0.0f };
static Vec3f KiraAccel = { 0.0f, 1.0f, 0.0f };
static Color_RGBA8 KiraPrimColor = { 170, 255, 255, 255 };
static Color_RGBA8 KiraEnvColor = { 0, 120, 255, 0 };
#define KIRA_ABOVE 60.0f

static Vec3f DustVelocity = { 0.0f, 0.0f, 0.0f };
static Vec3f DustAccel = { 3.0f, 0.0f, 0.0f };
static Color_RGBA8 DustPrimColor = { 150, 150, 170, 255 };
static Color_RGBA8 DustEnvColor = { 40, 40, 120, 255 };

static void draw(Entity *en, GlobalContext *globalCtx) {
	s8 kType = KiraType[PARAM];
    if(kType >= 0 && (en->state == 1 || en->state == 2)){
		float syr = Math_SinS(en->dyna.actor.shape.rot.y);
		float cyr = Math_CosS(en->dyna.actor.shape.rot.y);
        Vec3f pos0 = en->dyna.actor.world.pos;
		pos0.x += cyr * KiraCtrX[kType] + syr * KiraCtrZ[kType];
		pos0.z += cyr * KiraCtrZ[kType] - syr * KiraCtrX[kType];
		pos0.y += KIRA_ABOVE;
		s32 nspawn = en->alpha < 160 ? 3 : en->alpha < 220 ? 2 : 1;
		for(s32 i=0; i<nspawn; ++i){
			Vec3f pos = pos0;
			float along = Rand_ZeroOne();
			float across = Rand_ZeroOne();
			pos.y += along * KiraDY[kType];
			s16 angle = -en->dyna.actor.shape.rot.y + KiraAngleLo[kType] 
				+ (s16)((float)((s16)(KiraAngleHi[kType] - KiraAngleLo[kType])) * along);
			float dw = (across - 0.5f) * KiraW[kType];
			if(kType == 2){
				pos.z += dw;
				pos.x += angle;
			}else{
				float r = KiraRad[kType] + dw;
				pos.x -= r * Math_SinS(angle);
				pos.z += r * Math_CosS(angle);
			}
			EffectSsKiraKira_SpawnFocused(globalCtx, &pos, &KiraVelocity, &KiraAccel,
				&KiraPrimColor, &KiraEnvColor, 6000, 10);
		}
    }else if(en->sound_timer > 0){
		float ratio = (float)((s32)en->sound_timer - (s32)WaitTimes[9]) 
			/ ((s32)WaitTimes[7] + 255 / (s32)FadeSpeeds[7]);
		if(ratio >= 0.0f && ratio <= 1.0f){
			s32 nspawn = 2.5f + 3.0f * ratio;
			for(s32 i=0; i<nspawn; ++i){
				Vec3f pos = en->dyna.actor.world.pos;
				pos.y += 40.0f;
				float dyz = 300.0f * ratio;
				float d = dyz * (2.0f * Rand_ZeroOne() - 1.0f);
				s16 mode = Rand_S16Offset(0, 4);
				if((mode & 1)) dyz = -dyz;
				if((mode & 2)){
					pos.y += d;
					pos.z += dyz;
				}else{
					pos.y += dyz;
					pos.z += d;
				}
				pos.y += 20.0f * Rand_ZeroOne() - 10.0f;
				pos.z += 20.0f * Rand_ZeroOne() - 10.0f;
				EffectSsDust_Spawn(globalCtx, 5, 
					&pos, &DustVelocity, &DustAccel, &DustPrimColor, &DustEnvColor,
					400, 100, 5, 0);
			}
		}
	}
	if(en->alpha == 0) return;
	if(DListsTransparent[PARAM]){
		if(PARAM == 7){ //Fade wall
			gDPSetBlendColor(POLY_XLU_DISP++, 0, 0, 0, 0xFF - en->alpha);
		}else{
			u32 t = globalCtx->gameplayFrames;
			gSPSegment(POLY_XLU_DISP++, 0x0D, Gfx_TwoTexScroll(globalCtx->state.gfxCtx,
				0, t & 0x1FF, 0, 128, 16,
				1, 0x3FF - ((t >> 1) & 0x3FF), 0, 128, 16));
            gDPSetEnvColor(POLY_XLU_DISP++, 0xFF, 0xFF, 0xFF, en->alpha);
        }
		Gfx_DrawDListXlu(globalCtx, DLists[PARAM]);
	}else{
		gDPSetBlendColor(POLY_OPA_DISP++, 0, 0, 0, 0xFF - en->alpha);
		Gfx_DrawDListOpa(globalCtx, DLists[PARAM]);
	}
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_PROP,
	.flags = 0x00000030,
	.objectId = OBJ_ID,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};
