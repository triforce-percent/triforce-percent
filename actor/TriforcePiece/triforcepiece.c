#include "ootmain.h"
#include "obj.h"

// Actor Information
#define OBJ_ID 4

#define NPC_ACTION_NUM 40
#define NPC_ACTION_SLOT 1

#define TRIFORCE_POWER 0
#define TRIFORCE_WISDOM 1
#define TRIFORCE_COURAGE 2

#define TFCOLOR_R 255
#define TFCOLOR_G 217
#define TFCOLOR_B 100

#define STATE_START 0
#define STATE_RISE 1
#define STATE_WAIT0 2
#define STATE_COMBINE 3
#define STATE_WAIT1 4
#define STATE_SINK 5
#define STATE_WAIT2 6
#define STATE_DISAP 7
#define STATE_LINK 8
#define FSM_STATES 9

#define STATE_MODE_LAST 0
#define STATE_MODE_IMM 1
#define STATE_MODE_SMOOTH 2
static const u8 states_mode[] = {
	   1,   2,   2,   2,   2,  2,   2,  1,  0
};
// -- ST  RIS   W0  CMB   W1  SNK  W2  DS  LK
static const u8 states_frames[] = {
	  57,  88,  95,  60,  10,  60, 10, 57,  0
};
//These have an extra value at the beginning so we can interpolate from last
//to current without worrying about crashes
static const u8 states_highpiece_y[] = {
	0, 0, 125, 125, 117, 117,  82, 82,  0, 76
};
static const u8 states_lowpieces_y[] = {
	0, 0,  85,  85,  95,  95,  65, 65,  0, 65
};
// -- ST  RIS   W0  CMB   W1  SNK  W2  DS  LK
static const u8 states_lowpieces_x[] = {
	0, 0,  25,  25,  12,  12,  10, 10, 10,  6
};
static const u8 states_z[] = {
	0, 0,   0,   0,  13,  13,  13, 13,  0, 50
};
// -- ST  RIS   W0  CMB   W1  SNK  W2  DS  LK
static const u8 states_scale[] = {
   64,64, 128, 128, 128, 128, 100,100,  1, 64
};
static const s8 states_brightness[] = {
  -30,-30, 60,  60,  60,  60,  60, 60,  0, 60
};

static const u8 smoothtable[] = {
	0x00, 0x0A, 0x1C, 0x48, 0x80, 0xB8, 0xE4, 0xF6, 0xFF
};
static const s16 pieces_rot[] = {
	1200, -870, 0,
	-580, 0, 1107,
	0, 1337, 420
};

typedef struct {
	Actor actor;
	u8 state, frame, theendmode;
	LightNode *lightnode;
	LightInfo light;
} Entity;

static void setpos(Entity *en, float x, float y, float z){
	en->actor.world.pos.x = x;
	en->actor.world.pos.y = y;
	en->actor.world.pos.z = z;
	if(en->actor.params == 0){
		en->light.params.point.x = (s16)x;
		en->light.params.point.y = (s16)y - 12;
		en->light.params.point.z = (s16)z + 4;
	}
}

static void rotcombine(s16 *r, s16 tbl, s32 framesleft){
	s32 rremain = (s32)(*r);
	if(tbl > 0 && rremain > 0){
		rremain = -0x10000 + rremain;
	}else if(tbl < 0 && rremain < 0){
		rremain = 0x10000 + rremain;
	}
	s32 d = rremain / framesleft;
	if(framesleft > 3){
		//Do a little more than needed; will automatically slow down the
		//last few frames.
		//d += d >> 1;
		d <<= 1;
	}
	*r -= d;
}

static void init(Entity *en, GlobalContext *globalCtx) {
	en->theendmode = en->actor.params >> 2;
	en->actor.params &= 3;
	if(en->actor.params == 0){
		Lights_PointNoGlowSetInfo(&en->light, 0, 0, 0, TFCOLOR_R, TFCOLOR_G, TFCOLOR_B, 2000);
		en->lightnode = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &en->light);
	}
	en->state = en->theendmode ? STATE_WAIT1 : STATE_START;
	en->frame = 0;
	setpos(en, 0.0f, 0.0f, 0.0f);
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	if(en->actor.params == 0){
		LightContext_RemoveLight(globalCtx, &globalCtx->lightCtx, en->lightnode);
	}
}

static void update(Entity *en, GlobalContext *globalCtx) {
	if(CHECK_NPC_ACTION(NPC_ACTION_SLOT, 1)){
		Actor_Kill(&en->actor);
		return;
	}
	float x, y, z, s, brightness, lastx, lasty, lastz, lasts, lastbrightness;
	s16 variable = en->actor.params;
	if(variable >= 3) variable = 0;
	u8 state = en->state;
	u8 frame = en->frame;
	u8 frames = states_frames[state];
	if(frames == 0) frames = 1;
	u8 mode = states_mode[state];
	//Position, Scale, Brightness
	lastx = (float)states_lowpieces_x[state];
	lasty = (float)states_lowpieces_y[state];
	lastz = (float)states_z[state];
	lasts = (float)states_scale[state];
	lastbrightness = (float)states_brightness[state];
	x = (float)states_lowpieces_x[state+1]; //End of current state
	y = (float)states_lowpieces_y[state+1];
	z = (float)states_z[state+1];
	s = (float)states_scale[state+1];
	brightness = (float)states_brightness[state+1];
	if(en->theendmode){
		z = lastz = 0.0f;
	}
	if(variable == TRIFORCE_COURAGE){
		lastx = -lastx;
		x = -x;
	}else if(variable == TRIFORCE_POWER){
		lastx = 0.0f;
		x = 0.0f;
		lasty = (float)states_highpiece_y[state];
		y = (float)states_highpiece_y[state+1];
	}
	float m = 1.0f;
	if(mode >= STATE_MODE_SMOOTH){
		//Interpolate parameters
		m = (float)((u32)frame << 3) / (float)frames;
		u32 smoothidx = (u32)m;
		m -= (float)smoothidx; //fpart
		float smoothstart = (float)smoothtable[smoothidx];
		float smoothend = (float)smoothtable[smoothidx+1];
		m = (smoothend - smoothstart) * m + smoothstart;
		m *= 0.00390625f; //1/256
	}
	x = (x - lastx) * m + lastx;
	y = (y - lasty) * m + lasty;
	z = (z - lastz) * m + lastz;
	s = (s - lasts) * m + lasts;
	brightness = (brightness - lastbrightness) * m + lastbrightness;
	if(y < 40.0f || brightness < 0.0f) brightness = 0.0f;
	setpos(en, x, y, z);
	Actor_SetScale(&en->actor, s * 2.5f * 0.0078125f); //1/128
	if(variable == 0){
		en->light.params.point.radius = (s16)brightness << 4;
	}
	//Rotation
	const s16 *rottable = &pieces_rot[3*variable];
	if(state == STATE_RISE || state == STATE_WAIT0){
		//Free rotation
		en->actor.shape.rot.x += *rottable++;
		en->actor.shape.rot.y += *rottable++;
		en->actor.shape.rot.z += *rottable;
	}else if(state == STATE_COMBINE){
		//Rotate back to upright
		s32 framesleft = frames - frame;
		rotcombine(&en->actor.shape.rot.x, *rottable++, framesleft);
		rotcombine(&en->actor.shape.rot.y, *rottable++, framesleft);
		rotcombine(&en->actor.shape.rot.z, *rottable, framesleft);
	}else{
		//No rotation
		en->actor.shape.rot.x = 0;
		en->actor.shape.rot.y = 0;
		en->actor.shape.rot.z = 0;
	}
	//Increment
	if(!en->theendmode && mode != STATE_MODE_LAST){
		++frame;
		if(frame >= frames){
			frame = 0;
			en->state = state+1;
		}
		en->frame = frame;
	}
	//The end
	if(en->theendmode){
		en->actor.shape.rot.y = (s16)((float)0x4000 * (40.0f / 90.0f));
		float x = en->actor.world.pos.x;
		float z = en->actor.world.pos.z;
		const float sin40 = 0.6427876f;
		const float cos40 = 0.7660444f;
		en->actor.world.pos.x =  cos40 * x + sin40 * z;
		en->actor.world.pos.z = -sin40 * x + cos40 * z;
	}
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	if(en->state == STATE_START || en->state == STATE_DISAP) return;
	Gfx_DrawDListOpa(globalCtx, (Gfx*)DL_TFPIECE);
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
