#include "ootmain.h"
#include "../loader/debugger/debugger.h"
#include "../statics/anime.h"
#include "../statics/hairphys.h"
#include "../statics/scene.h"
#include "../statics/statics.h"

#define VO_EXTRA_FRAMES 3

#define LIGHTS_ACTIONNUM 37
#define LIGHTS_ACTIONSLOT 3

//Action-based flags
#define FLAG_INVISIBLE (1 << 8)
#define FLAG_EYESCLOSED (1 << 9)
#define FLAG_DELAYROT (1 << 10)
#define FLAG_NOLOOP (1 << 11)
#define FLAG_ACCEL (1 << 12)
#define FLAG_DECEL (1 << 13)
#define FLAG_ENDEARLY (1 << 14)
#define FLAG_SMOOTHROT (1 << 15)
#define FLAGS_ALLCOMMON 0xFF00

#define CHECK_ON_FRAME(timer, tgtframe) \
	(timer == tgtframe || (Statics_LagRepeatFrame() && (timer == tgtframe + 1)))

typedef struct {
    Actor actor;
	SkelAnime skelAnime;
	u32 flags;
    s16 actionnum;
	u16 actionframe;
	u16 sfx;
	u8 sfxframe;
	u8 eyeTextureIndex;
	u8 eyeState;
	u8 blinkTimer;
	AnimationHeader *anim;
	AnimationHeader *anim_whendone;
	f32 morph_whendone;
	float windX, windZ;
	f32 volume;
	//s8 lightDir[3];
} BotWActor;

typedef void (*BotWCSActionFunc)(BotWActor *botw, GlobalContext* globalCtx);

typedef struct {
    AnimationHeader *anim;
    f32 morph;
    AnimationHeader *anim_whendone;
    f32 morph_whendone;
    u32 flags;
    u16 sfx;
    u8 sfxframe;
    BotWCSActionFunc func;
} BotWCSActionDef;

typedef struct {
    s8 bone;
    u8 dim;
	s8 dir;
} BotWFixRotAnimDef;

static inline void BotWLights_Draw(GlobalContext *globalCtx){
	CsCmdActorAction *action = globalCtx->csCtx.npcActions[LIGHTS_ACTIONSLOT];
	if(globalCtx->csCtx.state == 0 || action == NULL) return;
	float x, y, z;
	y = 1.5f;
	switch(action->action){
	case 0:
		x = 5.0f;
		z = -1.0f;
		break;
	case 1:
		x = 4.0f;
		z = 4.0f;
		break;
	default:
		return;
	}
	float n = 127.0f / sqrt(x * x + y * y + z * z);
	s8 lx, ly, lz;
	lx = x * n;
	ly = y * n;
	lz = z * n;
	
	Lights* lights = Lights_New(globalCtx->state.gfxCtx, 0, 0, 0);
    lights->numLights = 1;
	lights->l.l[0].l.col[0] = lights->l.l[0].l.colc[0] = 255;
	lights->l.l[0].l.col[1] = lights->l.l[0].l.colc[1] = 255;
	lights->l.l[0].l.col[2] = lights->l.l[0].l.colc[2] = 255;
	lights->l.l[0].l.dir[0] = lx;
	lights->l.l[0].l.dir[1] = ly;
	lights->l.l[0].l.dir[2] = lz;
	Lights_Draw(lights, globalCtx->state.gfxCtx);
}

static inline void BotWActor_Init(BotWActor *botw, GlobalContext *globalCtx, 
        FlexSkeletonHeader *skel, AnimationHeader *initAnim,
        Vec3s *jointTable, Vec3s *morphTable, s32 numLimbs, f32 scale, f32 volume) {
    botw->flags = 0;
    botw->actionnum = -1;
	botw->actionframe = 0;
    botw->sfx = 0;
	botw->eyeTextureIndex = 0;
    botw->eyeState = 0;
	botw->blinkTimer = 0;
    botw->anim = initAnim;
	botw->anim_whendone = NULL;
	botw->windX = 0.707f;
	botw->windZ = -0.707f;
	botw->volume = volume;
	//botw->lightDir[0] = 127; botw->lightDir[1] = botw->lightDir[2] = 0;
	Actor_SetScale(&botw->actor, scale);
    SkelAnime_InitFlex(globalCtx, &botw->skelAnime, skel, initAnim, 
		jointTable, morphTable, numLimbs);
}

static inline void BotWActor_Destroy(BotWActor *botw, GlobalContext *globalCtx) {
    SkelAnime_Free(&botw->skelAnime, globalCtx);
}

static inline void BotWActor_VO(BotWActor *botw, u16 sfx) {
    static f32 VoiceFreqScale = 1.0f;
    static u32 VoiceReverbAdd = 0;
    Audio_PlaySoundGeneral(sfx, &botw->actor.projectedPos, 4, 
		&VoiceFreqScale, &botw->volume, (f32*)&VoiceReverbAdd);
}

static inline void BotWActor_SetAnim(BotWActor *botw, AnimationHeader *anim, 
		u8 mode, f32 morphFrames) {
	Animation_Change(&botw->skelAnime, anim, 1.0f, 0.0f, 
		Animation_GetLastFrame(anim), mode, morphFrames);
	if(mode <= ANIMMODE_LOOP_INTERP) botw->skelAnime.animLength -= 1.0f;
}

static inline void BotWActor_UpdateEyes(BotWActor *botw, GlobalContext *globalCtx,
		u8 repeatCurFrame){
	if((botw->flags & FLAG_EYESCLOSED) && (botw->eyeState == 0 || botw->eyeState == 3)){
		botw->eyeState = 1; //Start closing eyes
	}else if(!(botw->flags & FLAG_EYESCLOSED) && (botw->eyeState == 1 || botw->eyeState == 2)){
		botw->eyeState = 3; //Start opening eyes
	}
	if(botw->eyeState == 1){
		botw->blinkTimer += 1 + repeatCurFrame;
		botw->eyeTextureIndex = 1;
		if(botw->blinkTimer > 5){
			botw->eyeState = 2;
		}
	}else if(botw->eyeState == 2){
		botw->eyeTextureIndex = 2;
	}else if(botw->eyeState == 3){
		botw->blinkTimer += 1 + repeatCurFrame;
		botw->eyeTextureIndex = 1;
		if(botw->blinkTimer > 5){
			botw->eyeState = 0;
			botw->blinkTimer = 20;
		}
	}else{
		if(globalCtx->csCtx.frames == 682){
			botw->blinkTimer = 5;
		}else if(botw->blinkTimer == 0){
			botw->blinkTimer = Rand_S16Offset(40, 70);
		}else if(botw->blinkTimer < 4){
			--botw->blinkTimer;
		}else{
			botw->blinkTimer -= 1 + repeatCurFrame;
		}
		botw->eyeTextureIndex = (botw->blinkTimer < 3) ? botw->blinkTimer : 0;
	}
}

static inline void BotWActor_Update(BotWActor *botw, GlobalContext *globalCtx, 
		const BotWCSActionDef *ActionDefs, s32 nActionDefs, s32 actionSlot,
		const BotWFixRotAnimDef *FixRotAnimDefs) {
    u8 repeatCurFrame = Statics_LagRepeatFrame();
	botw->actionframe += 1 + repeatCurFrame;
    CsCmdActorAction *action = globalCtx->csCtx.npcActions[actionSlot];
	bool actionValid = (globalCtx->csCtx.state != 0) && (action != NULL) && (action->action < nActionDefs);
	if(actionValid){
		const BotWCSActionDef *def = &ActionDefs[action->action];
		botw->flags &= ~FLAGS_ALLCOMMON;
		botw->flags |= def->flags;
		if(action->action != botw->actionnum){
			botw->actionnum = action->action;
			botw->actionframe = 0;
			if(def->anim != NULL && def->anim != botw->anim){
				BotWActor_SetAnim(botw, def->anim, 
					(def->anim_whendone == NULL && !(botw->flags & FLAG_NOLOOP))
					 	? ANIMMODE_LOOP_INTERP : ANIMMODE_ONCE_INTERP,
					def->morph);
				botw->anim = def->anim;
				botw->anim_whendone = def->anim_whendone;
				botw->morph_whendone = def->morph_whendone;
			}
			if(def->sfx != 0){
				botw->sfx = def->sfx;
				botw->sfxframe = def->sfxframe;
			}
		}
		f32 frac = Environment_LerpWeightAccelDecel(
			action->endFrame - ((botw->flags & FLAG_ENDEARLY) ? 2 : 0),
			action->startFrame, globalCtx->csCtx.frames,
			(botw->flags & FLAG_ACCEL) ? 8 : 0, (botw->flags & FLAG_DECEL) ? 12 : 0);
		if(frac < 0.0f) frac = 0.0f;
		if(frac > 1.0f) frac = 1.0f;
		f32 finv = 1.0f - frac;
		botw->actor.world.pos.x = finv * (f32)action->startPos.x + frac * (f32)action->endPos.x;
		botw->actor.world.pos.y = finv * (f32)action->startPos.y + frac * (f32)action->endPos.y;
		botw->actor.world.pos.z = finv * (f32)action->startPos.z + frac * (f32)action->endPos.z;
		s16 drot = botw->actor.shape.rot.y - action->rot.y;
        const s16 minrot = 0x100;
		s16 absdrot = drot;
		if(absdrot < 0) absdrot = -absdrot;
		if((botw->flags & FLAG_DELAYROT)){
			(void)0; //don't rotate
		}else if((botw->flags & FLAG_SMOOTHROT)){
			s16 framesleft = action->endFrame - globalCtx->csCtx.frames;
			if(framesleft <= 1){
				botw->actor.shape.rot.y = action->rot.y;
			}else{
				botw->actor.shape.rot.y -= drot / framesleft;
			}
		}else if(absdrot <= minrot){
			botw->actor.shape.rot.y = action->rot.y;
		}else{
			absdrot >>= 3;
			if(absdrot < minrot) absdrot = minrot;
			Math_StepToAngleS(&botw->actor.shape.rot.y, action->rot.y, absdrot);
		}
		if(def->func != NULL) def->func(botw, globalCtx);
	}
	Actor_UpdateBgCheckInfo(globalCtx, &botw->actor, 0.0f, 0.0f, 0.0f, 4);
	BotWActor_UpdateEyes(botw, globalCtx, repeatCurFrame);
	botw->skelAnime.playSpeed = Statics_LagPlaySpeed();
	s32 animFinished = SkelAnime_Update(&botw->skelAnime);
	if(animFinished){
		if(actionValid && (botw->flags & FLAG_DELAYROT)){
			s16 drot = botw->actor.shape.rot.y - action->rot.y;
			botw->actor.shape.rot.y = action->rot.y;
			while(FixRotAnimDefs->bone >= 0){
				(&(botw->skelAnime.jointTable[FixRotAnimDefs->bone].x))[FixRotAnimDefs->dim] 
					+= drot * (s16)FixRotAnimDefs->dir;
				++FixRotAnimDefs;
			}
		}
		if(botw->anim_whendone != NULL){
			BotWActor_SetAnim(botw, botw->anim_whendone, ANIMMODE_LOOP_INTERP,
				botw->morph_whendone);
			botw->anim = botw->anim_whendone;
			botw->anim_whendone = NULL;
		}
	}
	if(botw->sfx != 0 && CHECK_ON_FRAME(botw->actionframe, (u16)botw->sfxframe)){
		BotWActor_VO(botw, botw->sfx);
		botw->sfx = 0;
	}
}

static inline void BotWActor_DrawMain(BotWActor *botw, GlobalContext *globalCtx,
		void *const *EyeTextures, OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw) {
	func_80093D18(globalCtx->state.gfxCtx);
	BotWLights_Draw(globalCtx);
	void *seg08Tex = EyeTextures[botw->eyeTextureIndex];
	gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(seg08Tex));
	SkelAnime_DrawFlexOpa(globalCtx, botw->skelAnime.skeleton, botw->skelAnime.jointTable,
		botw->skelAnime.dListCount, overrideLimbDraw, postLimbDraw, botw);
	func_80093D18(globalCtx->state.gfxCtx);
}
