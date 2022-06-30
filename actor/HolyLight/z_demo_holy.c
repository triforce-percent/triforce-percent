/*
 * File: z_demo_holy.c
 * Overlay: ovl_En_HolyLight
 * Description: Holy Light for BotW Zelda
 * Author: MNGoldenEagle
 */

#include "ootmain.h"
#include "z_demo_holy.h"
#include "holy_light_gfx.h"

#define OBJ_ID 126
#define FLAGS ((1 << 4) | (1 << 5) | (1 << 19) | (1 << 22) | (1 << 25) | (1 << 27))

#define  BRIGHT_RANGE ((280.0f - 150.0f) / 2.0f)
#define BRIGHT_OFFSET ((280.0f + 150.0f) / 2.0f)
#define     DIM_RANGE ((255.0f - 50.0f) / 2.0f)
#define    DIM_OFFSET ((255.0f + 50.0f) / 2.0f)
#define  OFFSET_RANGE ((285.0f - 90.0f) / 2.0f)
#define OFFSET_OFFSET ((285.0f + 90.0f) / 2.0f)
#define    FADE_RANGE (128.0f / 2.0f)

#define  PARTICLE_MAX_HEIGHT 150.0f
#define PARTICLE_SCALE_START 200
#define   PARTICLE_SCALE_MAX 1000

void HolyLight_Init(Actor* thisx, GlobalContext* globalCtx);
void HolyLight_Destroy(Actor* thisx, GlobalContext* globalCtx);
void HolyLight_Update(Actor* thisx, GlobalContext* globalCtx);
void HolyLight_Draw(Actor* thisx, GlobalContext* globalCtx);
void Update_WaitForCutscene(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame);
void Update_FadeIn(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame);
void Update_Glow(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame);
void Update_FadeOut(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame);

static Vec3f SparkleVelocity = { 0.0f, 0.1f, 0.0f };
static Vec3f SparkleAccel = { 0.0f, -0.08f, 0.0f };
static Color_RGBA8 SparklePrim = { 253, 255, 199, 0 };
static Color_RGBA8 SparkleEnv = { 60, 60, 20, 0 };

void HolyLight_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHolyLight* this = (EnHolyLight*)thisx;

    this->sound = HLYLGT_SOUND_STOP;
    this->soundVol = 0.4f;

    this->actorSlot = this->actor.params;
    this->update = &Update_WaitForCutscene;
    this->actor.draw = NULL;
    this->scaleFactor = 0.0f;
}

void HolyLight_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void Update_WaitForCutscene(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame) {
    if (globalCtx->csCtx.state != 0 && globalCtx->csCtx.npcActions[this->actorSlot] != NULL) {
        CsCmdActorAction* action = globalCtx->csCtx.npcActions[this->actorSlot];
        if (action->endFrame < globalCtx->csCtx.frames) {
            return;
        }
        this->startFrame = action->startFrame;
        this->endFrame = action->endFrame;
        this->startPos = action->startPos;
        this->endPos = action->endPos;
        this->periodFactor = 10.0f / ((action->endFrame - action->startFrame) * M_PI);
        this->actor.draw = &HolyLight_Draw;
        this->mode = action->action;
        switch (action->action) {
            case HLYLGT_MD_FADEIN:
                this->sound = HLYLGT_SOUND_PLAY;
                this->update = &Update_FadeIn;
                Update_FadeIn(this, globalCtx, currentFrame);
                break;
            case HLYLGT_MD_GLOW_SILENT:
                this->sound = HLYLGT_SOUND_LOWER;
            case HLYLGT_MD_GLOW:
                this->update = &Update_Glow;
                Update_Glow(this, globalCtx, currentFrame);
                break;
            case HLYLGT_MD_FADEOUT:
                this->sound = HLYLGT_SOUND_FADEOUT;
                this->update = &Update_FadeOut;
                Update_FadeOut(this, globalCtx, currentFrame);
                break;
            default:
                // Whoops!
                this->actor.draw = NULL;
                return;
        }
    }
}

// (((ymax - ymin) / 2) * sinf((10 / ((xmax - xmin) * M_PI)) * (x - xmin) - (M_PI / 2)) + ((ymax + ymin) / 2))
void SetLightGlow(EnHolyLight* this, f32 currentFrame) {
    f32 periodFactor = this->periodFactor;
    f32 calc;

    // Bright cycle (30 frames, 225 to 255 to 225)
    calc = BRIGHT_RANGE * sinf(2.0f * periodFactor * (currentFrame - (f32)this->startFrame) - (M_PI / 2.0f)) + BRIGHT_OFFSET;
    this->primColor.r = this->primColor.g = CLAMP_MAX(calc, 255);

    // Dim cycle (60 frames, 80 to 255 to 80)
    calc = DIM_RANGE * sinf(periodFactor * (currentFrame - (f32)this->startFrame) - (M_PI / 2.0f)) + DIM_OFFSET;
    this->primColor.b = CLAMP_MAX(calc, 255);

    // Offset cycle (60 frames, 100 to 255 to 100)
    this->envColor.r = OFFSET_RANGE * sinf(periodFactor * (currentFrame - (f32)this->startFrame) - (M_PI / 2.0f)) + OFFSET_OFFSET;
    this->envColor.g = OFFSET_RANGE * sinf(periodFactor * (currentFrame - (f32)this->startFrame - 8) - (M_PI / 2.0f)) + OFFSET_OFFSET;
    this->envColor.b = OFFSET_RANGE * sinf(periodFactor * (currentFrame - (f32)this->startFrame - 13) - (M_PI / 2.0f)) + OFFSET_OFFSET;
}

void SpawnSparkles(EnHolyLight* this, GlobalContext* globalCtx, s16 scale, u8 count) {
    Vec3f pos, vel;
    f32 r, theta;
    s32 i;

    r = 13.0f * this->scaleFactor;

    for (i = 0; i < count; i++) {
        theta = Rand_ZeroFloat(2 * M_PI);
        Math_Vec3f_Copy(&pos, &this->actor.world.pos);
        pos.x += r * Math_SinF(theta);
        pos.y += Rand_ZeroFloat(PARTICLE_MAX_HEIGHT);
        pos.z += r * Math_CosF(theta);
        Math_Vec3f_Copy(&vel, &SparkleVelocity);
        EffectSsKiraKira_SpawnFocused(globalCtx, &pos, &vel, &SparkleAccel, &SparklePrim, &SparkleEnv, scale, 11);
    }
}

void Update_FadeIn(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame) {
    f32 calc;
    s16 scale;

    SetLightGlow(this, currentFrame);
    calc = FADE_RANGE * sinf(this->periodFactor * (currentFrame - (f32)this->startFrame) - (M_PI / 2.0f)) + FADE_RANGE;
    this->envColor.a = this->primColor.a = CLAMP_MAX(calc, 255.0f);
    this->scaleFactor = calc / 128.0f;
    scale = PARTICLE_SCALE_START + ((PARTICLE_SCALE_MAX / (this->endFrame - this->startFrame)) * ((s16)currentFrame - this->startFrame));
    SpawnSparkles(this, globalCtx, scale, 2);
}

void Update_Glow(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame) {
    SetLightGlow(this, currentFrame);
    this->envColor.a = this->primColor.a = 128;
    SpawnSparkles(this, globalCtx, 1000, 3);
}

void Update_FadeOut(EnHolyLight* this, GlobalContext* globalCtx, f32 currentFrame) {
    s16 scale, mod, frame, third;
    f32 calc;
    frame = (s16)currentFrame;

    SetLightGlow(this, currentFrame);
    calc = FADE_RANGE * sinf(this->periodFactor * (currentFrame - (f32)this->startFrame) + (M_PI / 2.0f)) + FADE_RANGE;
    this->envColor.a = this->primColor.a = CLAMP_MAX(calc, 255.0f);
    this->scaleFactor = calc / 128.0f;
    // frame 0 = 400, frame 20 = 550, frame 40 = 700, frame 60 = 850, frame 80 = 1000
    scale = PARTICLE_SCALE_START + ((PARTICLE_SCALE_MAX / (this->endFrame - this->startFrame)) * (this->endFrame - frame));
    third = (this->endFrame - this->startFrame) / 3;

    if (frame < this->startFrame + third) {
        mod = 1;
    } else if (frame < this->startFrame + (third * 2)) {
        mod = 2;
    } else {
        mod = 3;
    }
    if (frame % mod == 0) {
        SpawnSparkles(this, globalCtx, scale, 4 - mod);
    }
}

void HolyLight_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHolyLight* this = (EnHolyLight*)thisx;

    if (this->actorSlot < ARRAY_COUNT(globalCtx->csCtx.npcActions) && globalCtx->csCtx.frames > this->endFrame) {
        this->update = &Update_WaitForCutscene;
        this->actor.draw = NULL;
        this->startFrame = 0;
        this->endFrame = 0;
    }
    
    f32 currentFrame = globalCtx->csCtx.frames;
    Vec3i startPos = this->startPos, endPos = this->endPos;
    f32 lerp = Environment_LerpWeight(this->endFrame, this->startFrame, globalCtx->csCtx.frames);
    this->actor.world.pos.x = startPos.x + ((endPos.x - startPos.x) * lerp);
    this->actor.world.pos.y = startPos.y + ((endPos.y - startPos.y) * lerp);
    this->actor.world.pos.z = startPos.z + ((endPos.z - startPos.z) * lerp);
    this->update(this, globalCtx, currentFrame);
    
    if(this->sound >= HLYLGT_SOUND_PLAY){
        if(this->sound == HLYLGT_SOUND_LOWER){
            this->soundVol = 0.25f;
        }else if(this->sound == HLYLGT_SOUND_FADEOUT){
            this->soundVol -= 0.025f;
        }
        if(this->soundVol > 0.0f){
            //original: NA_SE_EV_AURORA, other candidates:
            //NA_SE_EV_SPIRIT_STONE, NA_SE_EV_HEALING, NA_SE_EV_TRIFORCE, NA_SE_EV_ZELDA_POWER
            static f32 FreqScale = 1.0f;
            static u32 ReverbAdd = 0;
            Audio_PlaySoundGeneral(NA_SE_EN_GANON_BREATH - SFX_FLAG, 
                &this->actor.projectedPos, 4, &FreqScale, &this->soundVol, (f32*)&ReverbAdd);
        }
    }
}

void HolyLight_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHolyLight* this = (EnHolyLight*)thisx;
    s32 frame = globalCtx->gameplayFrames;

    //OPEN_DISPS(globalCtx->state.gfxCtx, "../z_demo_holy.c", __LINE__);
    gSPSegment(POLY_XLU_DISP++, 10, Gfx_TexScroll(globalCtx->state.gfxCtx, frame * 3, 0, 16, 32));
    gSPSegment(POLY_XLU_DISP++, 11, Gfx_TexScroll(globalCtx->state.gfxCtx, ABS(-frame), 0, 16, 32));
    gDPSetPrimColor(POLY_XLU_DISP++, 128, 128, this->primColor.r, this->primColor.g, this->primColor.b, this->primColor.a);
    gDPSetEnvColor(POLY_XLU_DISP++, this->envColor.r, this->envColor.g, this->envColor.b, 255);
    func_80093D84(globalCtx->state.gfxCtx);
    Matrix_Scale(this->scaleFactor, 2.0f, this->scaleFactor, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_demo_holy.c", __LINE__),
              G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPDisplayList(POLY_XLU_DISP++, &holyLight1);
    gDPSetPrimColor(POLY_XLU_DISP++, 128, 128, this->envColor.r, this->envColor.g, this->envColor.b, this->primColor.a);
    gSPDisplayList(POLY_XLU_DISP++, &holyLight2);
    //CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_demo_holy.c", __LINE__);
}

const ActorInitExplPad init_vars = {
    .id = 0xDEAD, .padding = 0xBEEF,
    .category = ACTORCAT_PROP,
    .flags = FLAGS,
    .objectId = OBJ_ID,
    .instanceSize = sizeof(EnHolyLight),
    .init = (ActorFunc)HolyLight_Init,
    .destroy = (ActorFunc)HolyLight_Destroy,
    .update = (ActorFunc)HolyLight_Update,
    .draw = (ActorFunc)HolyLight_Draw,
};
