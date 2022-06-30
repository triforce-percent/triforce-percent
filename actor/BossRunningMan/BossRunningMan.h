#ifndef __BOSS_RUNNING_MAN_H__
#define __BOSS_RUNNING_MAN_H__

#include "ootmain.h"
#include "BossRunningManObj.h"

#define DEP_OBJECT_NUM 59
#define NUM_GHOSTS 4
#define ACTORPARAM_BETAGIANTRUPEE 0x0001

typedef enum {
	/* 0 */ DAMAGE_NORMAL,
	/* 1 */ DAMAGE_FIRE,
	/* 2 */ DAMAGE_ICE,
	/* 3 */ DAMAGE_ELECTRIC,
	/* 4 */ DAMAGE_KNOCKBACK
} ColliderDamageType;

struct BossRunningMan;

typedef void (* RunningManFunc)(struct BossRunningMan*, GlobalContext*);

typedef struct {
	Vec3f pos;
	Vec3f vel;
	Vec3f accel;
	u16   scale;
	u16   scaleStep;
} DustCall;

typedef enum {
	RUNMAN_,
	RUNMAN_ROOT,
	RUNMAN_THIGH_L,
	RUNMAN_SHIN_L,
	RUNMAN_FOOT_L,
	RUNMAN_THIGH_R,
	RUNMAN_SHIN_R,
	RUNMAN_FOOT_R,
	RUNMAN_BODY,
	RUNMAN_UPPERARM_L,
	RUNMAN_FOREARM_L,
	RUNMAN_HAND_L,
	RUNMAN_UPPERARM_R,
	RUNMAN_FOREARM_R,
	RUNMAN_HAND_R,
	RUNMAN_HEAD
} RMLimbs;

typedef struct {
	ColliderCylinder cyl;
	ColliderCylinder kick;
	u8 acFlagLast;
} ColliderSet;

typedef struct {
	u8 ghosting        : 1;
	u8 drawGhosts      : 1;
	u8 targetPos       : 1;
	u8 syncRotY        : 1;
	u8 colHurt         : 1;
	u8 colKick         : 1;
	u8 isHurt          : 1;
	u8 setShapeRot     : 1;
	u8 setDirRot       : 1;
	u8 blockDmgStun    : 1;
	u8 handHitR        : 1;
	u8 handHitL        : 1;
	u8 attachColToHead : 1;
	u8 headTrack       : 1;
	u8 enableDraw      : 1;
	u8 deadLookMod     : 1;
} RunManState;

typedef struct BossRunningMan {
	Actor          actor;
	RunManState    state;
	SkelAnime      skelAnime;
	Vec3s          jointTable[SKEL_RUNNINGMAN_NUMBONES_DT];
	Vec3s          morphTable[SKEL_RUNNINGMAN_NUMBONES_DT];
	Vec2s          headFocus;
	ColliderSet    colliders;
	RunningManFunc actionFunc;
	u8             needDestroy;
	union {
		struct {
			f32      speedX;
			Vec3f    targetPos;
			Vec3f    ghostPos[NUM_GHOSTS];
			s16      ghostYaw[NUM_GHOSTS];
			f32      masterFrame;
			s32      workInt[2];
			s16      workShort[2];
			f32      workFloat[2];
			DustCall dustCall[16];
			s32      dustNum;
			u8       dmgColor;
			s16      hurtBlend;
			s16      dirTarget;
			s16      rotShapeTarget;
			s16      stepMax;
			u8       chuTimer;
			s8       numPastChoices;
		} boss;
		struct {
			u16 timer;
			s32 getItemId;
		} npc;
	};
} BossRunningMan;

typedef struct EnMThunder {
	/* 0x0000 */ Actor      actor;
	/* 0x014C */ ColliderCylinder collider;
	/* 0x0198 */ LightNode* lightNode;
	/* 0x019C */ LightInfo  lightInfo;
	/* 0x01AC */ f32        unk_1AC;
	/* 0x01B0 */ f32        unk_1B0;
	/* 0x01B0 */ f32        unk_1B4;
	/* 0x01B0 */ f32        unk_1B8;
	/* 0x01BC */ f32        unk_1BC;
	/* 0x01C0 */ void*      actionFunc;
	/* 0x01C4 */ u16        unk_1C4;
	/* 0x01C6 */ u8         unk_1C6;
	/* 0x01C7 */ u8         unk_1C7;
	/* 0x01C8 */ u8         unk_1C8;
	/* 0x01C9 */ u8         unk_1C9;
	/* 0x01CA */ u8         unk_1CA;
} EnMThunder; // size = 0x01CC

#endif
