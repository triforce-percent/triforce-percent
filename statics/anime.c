#include "ootmain.h"
#include "anime.h"
#include "statics.h"
#include "../loader/debugger/debugger.h"

static void *MaybeSeg2RAM(void *ptr){
    if((u32)ptr & 0x80000000) return ptr;
    return SEGMENTED_TO_VIRTUAL(ptr);
}

extern AnimationEntry* AnimationContext_AddEntry(AnimationContext *animCtx, s32 type);

static void Patched_SetLoadFrame(GlobalContext* globalCtx, 
    LinkAnimationHeader* animation, s32 frame, s32 limbCount, Vec3s* frameTable) 
{
    LinkAnimationHeader* linkAnimHeader = MaybeSeg2RAM(animation);
    u32 animStepSize = sizeof(Vec3s) * limbCount + 2;
    AnimationEntry* entry = AnimationContext_AddEntry(&globalCtx->animationCtx, 0);
    if (entry == NULL) return;
    
    //zh_draw_debug_text(globalCtx, 0xFF8000FF, 1, 1, "%2d %08X", frame, linkAnimHeader->anim);
    
    osCreateMesgQueue(&entry->data.load.msgQueue, &entry->data.load.msg, 1);
    
    if(linkAnimHeader->segment & 0x80000000){
        //Animation is in RAM
        bcopy((void*)(((s32)linkAnimHeader->segment | 0x80000000) + (animStepSize * frame)), 
            frameTable, animStepSize);
        osSendMesg(&entry->data.load.msgQueue, (OSMesg)0, 0);
    }else{
        //Animation is in ROM
        DmaMgr_SendRequest2((DmaRequest*)&entry->data.load.req, (u32)frameTable,
            (u32)&_link_animetionSegmentRomStart
            + (linkAnimHeader->segment & 0x00FFFFFF)
            + (animStepSize * frame),
            animStepSize, 0, &entry->data.load.msgQueue, 0);
    }
}

/*
extern s16 Animation_GetLength2(AnimationHeaderCommon *animation);
extern s16 Animation_GetLastFrame2(AnimationHeaderCommon *animation);
*/

static s16 Patched_GetLengthOrLastFrame(AnimationHeaderCommon *animation, s16 minus){
    AnimationHeaderCommon *anim = MaybeSeg2RAM(animation);
    return anim->frameCount - minus;
}

typedef struct {
    float w;
    float x;
    float y;
    float z;
} Quaternion;

static inline s16 Fixed_atan2s(float y, float x){
    //atan2 is defined as atan2(y, x). OoT has the arguments backwards, just 
    //like it has them backwards in bcopy and other functions.
    /*
    Debugger_Printf("atan2 %04X %04X %04X %04X",
        Math_Atan2S(0.0f, 1.0f), //should be 0 -> displays 4000
        Math_Atan2S(1.0f, 0.0f), //should be 4000 -> displays 0
        Math_Atan2S(0.0f, -1.0f), //should be 8000 -> displays C000
        Math_Atan2S(-1.0f, 0.0f) //should be C000 -> displays 8000
    );
    */
    if(fabsf(y) < 1e-6f && fabsf(x) < 1e-6f){
        if(sIsLiveRun) Debugger_Printf("atan2s(0,0)!");
        return 0;
    }
    return Math_Atan2S(x, y);
}

static inline void Euler2Quat(const Vec3s *r, Quaternion *q){
    float cx = Math_CosS(r->x / 2);
    float sx = Math_SinS(r->x / 2);
    float cy = Math_CosS(r->y / 2);
    float sy = Math_SinS(r->y / 2);
    float cz = Math_CosS(r->z / 2);
    float sz = Math_SinS(r->z / 2);
    q->w = cx * cy * cz + sx * sy * sz;
    q->x = sx * cy * cz - cx * sy * sz;
    q->y = cx * sy * cz + sx * cy * sz;
    q->z = cx * cy * sz - sx * sy * cz;
    float norm = q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z;
    if(norm < 0.9f || norm > 1.1f){
        if(sIsLiveRun) Debugger_Printf("quat in norm is %f", norm);
    }
}

static inline void Quat2Euler(const Quaternion *q, Vec3s *r){
    float mult = q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z;
    if(mult < 0.001f){
        if(sIsLiveRun) Debugger_Printf("quat out is 0");
        mult = 0.001f;
    }
    mult = 2.0f / mult;
    float temp = mult * (q->w * q->y - q->x * q->z);
    if(temp >= 1.0f){
        r->y = 0x4000;
    }else if(temp <= -1.0f){
        r->y = 0xC000;
    }else{
        r->x = Fixed_atan2s(mult * (q->w * q->x + q->y * q->z), 1.0f - mult * (q->x * q->x + q->y * q->y));
        r->y = Fixed_atan2s(temp, sqrtf(1.0f - temp * temp));
        r->z = Fixed_atan2s(mult * (q->w * q->z + q->x * q->y), 1.0f - mult * (q->y * q->y + q->z * q->z));
        return;
    }
    //for both of the singularity cases above:
    r->x = Math_Atan2S(q->x, q->w);
    r->z = 0;
}

static u8 useSlerp = 1;
void Patched_MorphUseSlerp(u8 enabled){
    useSlerp = enabled;
}

static void Patched_InterpFrameTable(s32 limbCount, Vec3s* dst, Vec3s* start, Vec3s* target, f32 weight) {
    if(weight >= 1.0f){
        bcopy(target, dst, limbCount * sizeof(Vec3s));
        return;
    }
    if(weight <= 0.0f){
        bcopy(start, dst, limbCount * sizeof(Vec3s));
        return;
    }
    for(s32 i=0; i<limbCount; i++, dst++, start++, target++){
        s16 dx = target->x - start->x;
        s16 dy = target->y - start->y;
        s16 dz = target->z - start->z;
        /*
        s32 numLargeRot = 0;
        if(dx <= 0xC000 || dx >= 0x4000) ++numLargeRot;
        if(dy <= 0xC000 || dy >= 0x4000) ++numLargeRot;
        if(dz <= 0xC000 || dz >= 0x4000) ++numLargeRot;
        */
        s32 totalRot = (dx < 0 ? -dx : dx) + (dy < 0 ? -dy : dy) + (dz < 0 ? -dz : dz);
        if(totalRot > 0x2000 && useSlerp && i >= 1){ //i==0 is translation
            //There are at least two large angles; the per-axis interpolation
            //will be pretty far off. Do correct SLERP of quaternions. This is
            //much more expensive, so only done in these cases.
            //Algorithms from https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
            //and http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/
            //http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/Quaternions.pdf
            Quaternion qs, qt, qo;
            Euler2Quat(start, &qs);
            Euler2Quat(target, &qt);
            float cosHalfTheta = qs.w * qt.w + qs.x * qt.x + qs.y * qt.y + qs.z * qt.z;
            float wtmult = 1.0f;
            if(cosHalfTheta < 0.0f){
                //Negate one of the quaternions to get the closer rotation solution
                wtmult = -1.0f;
                cosHalfTheta = -cosHalfTheta;
            }
            float ws, wt;
            //Debugger_Printf("slerping %f", cosHalfTheta);
            if(cosHalfTheta > 0.97f){
                //Rotations are very close; linear interpolation
                ws = 1.0f - weight;
                wt = weight;
            }else{
                float sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);
                s16 halfTheta = Fixed_atan2s(sinHalfTheta, cosHalfTheta);
                float rcpSinHalfTheta = 1.0f / sinHalfTheta;
                ws = Math_SinS((1.0f - weight) * halfTheta) * rcpSinHalfTheta;
                wt = Math_SinS(weight * halfTheta) * rcpSinHalfTheta;
            }
            wt *= wtmult;
            qo.w = ws * qs.w + wt * qt.w;
            qo.x = ws * qs.x + wt * qt.x;
            qo.y = ws * qs.y + wt * qt.y;
            qo.z = ws * qs.z + wt * qt.z;
            /*
            if(i == 26 && weight > 0.45f && weight < 0.55f){
                Debugger_Printf("st %04X %04X %04X", (u16)start->x, (u16)start->y, (u16)start->z);
                Debugger_Printf("tg %04X %04X %04X", (u16)target->x, (u16)target->y, (u16)target->z);
                Debugger_Printf("qs %f %f %f %f", qs.w, qs.x, qs.y, qs.z);
                Debugger_Printf("qt %f %f %f %f", qt.w, qt.x, qt.y, qt.z);
                Debugger_Printf("ws %f wt %f cos(th/2) %f", ws, wt, cosHalfTheta);
                Debugger_Printf("qo %f %f %f %f", qo.w, qo.x, qo.y, qo.z);
            }
            */
            Quat2Euler(&qo, dst);
            //Debugger_Printf("nd %04X %04X %04X", dst->x, dst->y, dst->z);
        }else{
            dst->x = (s16)(dx * weight) + start->x;
            dst->y = (s16)(dy * weight) + start->y;
            dst->z = (s16)(dz * weight) + start->z;
        }
    }
}

static u32 prevAnimBaseAddr = 0;

//Animation table
//LinkAnimationHeader linkAnimPatchTable[...] = {...};
#include "../anim/anim.c"

typedef struct {
    //If positive, passes ptr to function in table D_80854AA4 (debug) indexed
    //by value. 
    //1: just stops Link. 
    //2: also sets Y to 0, changes to anim, play once at full speed, -6 morph
    //3: same as 2 but 2/3 speed and -8 morph
    //4: same as 3 but looping
    //5: once, 2/3 speed, -8 morph, sets moveFlags to 0x1C
    //6: once, full speed, flags 0x9C
    //7: looping, 2/3 speed, flags 0x1C
    //8: looping, full speed, flags 0x9C
    //9: once, full speed, no morph
    //A: looping, full speed, no morph
    //B: just update
    //C: update, if finished, goto 4 and set unk_850
    //D: update, if finished, goto 7 and set unk_850
    //E: Y = 0, freeze on first frame of anim, speed = 0
    //F: once, 2/3 speed, no morph
    //10: looping, 2/3 speed, no morph
    //11: update, if finished, sometimes copy anim translation, goto 10
    //12: update; also some state machine thing
    //If negative (-1), calls func. If zero, does nothing.
    /* 0x00 */ s8 type; 
    /* 0x04 */ union {
        void* ptr;
        void (*func)(GlobalContext*, Player*, void*);
    };
} LinkActionEntry; // size = 0x08

#define NUM_ORIG_LINK_ACTIONS 0x67
#define NUM_CUSTOM_LINK_ACTIONS 0x12
extern LinkActionEntry linkActionInitTable[NUM_ORIG_LINK_ACTIONS];
LinkActionEntry linkActionInitPatchTable[NUM_ORIG_LINK_ACTIONS+NUM_CUSTOM_LINK_ACTIONS] = {
    //Original
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    //Patched
    {3, {&linkAnimPatchTable[0]}}, //ReachUp
    {3, {&linkAnimPatchTable[1]}}, //LookToMeditate
    {4, {&linkAnimPatchTable[2]}}, //Meditate
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
};
extern LinkActionEntry linkActionRunTable[NUM_ORIG_LINK_ACTIONS];
LinkActionEntry linkActionRunPatchTable[NUM_ORIG_LINK_ACTIONS+NUM_CUSTOM_LINK_ACTIONS] = {
    //Original
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    //Patched
    {11, {NULL}},
    {11, {NULL}},
    {11, {NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
    {0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},{0,{NULL}},
};

#define NUM_ORIG_CS_ACTIONS 0x4E
#define NUM_CUSTOM_CS_ACTIONS 0x12
extern s8 csActionToLinkActionTable[NUM_ORIG_CS_ACTIONS];
s8 csActionToLinkActionPatchTable[NUM_ORIG_CS_ACTIONS+NUM_CUSTOM_CS_ACTIONS] = {
    //Original
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //Custom
    NUM_ORIG_LINK_ACTIONS,
    NUM_ORIG_LINK_ACTIONS+1,
    NUM_ORIG_LINK_ACTIONS+2,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

void Statics_AnimePlayerUpdate(){
    static u8 alreadyrun = 0;
    if(alreadyrun) return;
    alreadyrun = 1;
    //Copy original, relocated, animation tables to patch tables in statics.
    bcopy(PlayerVRAMtoRAM(csActionToLinkActionTable), csActionToLinkActionPatchTable, 
        sizeof(s8) * NUM_ORIG_CS_ACTIONS);
    bcopy(PlayerVRAMtoRAM(linkActionInitTable), linkActionInitPatchTable,
        sizeof(LinkActionEntry) * NUM_ORIG_LINK_ACTIONS);
    bcopy(PlayerVRAMtoRAM(linkActionRunTable), linkActionRunPatchTable,
        sizeof(LinkActionEntry) * NUM_ORIG_LINK_ACTIONS);
}

void Statics_AnimeRegisterStaticData(void* ram_addr){
    for(s32 i=0; i<(sizeof(linkAnimPatchTable)/sizeof(linkAnimPatchTable[0])); ++i){
        linkAnimPatchTable[i].segment += (u32)ram_addr - prevAnimBaseAddr;
    }
    prevAnimBaseAddr = (u32)ram_addr;
}

void Statics_AnimeCodePatches(u8 isLiveRun){
    //Patch Link animation loader
    *( (u32*)AnimationContext_SetLoadFrame   ) = JUMPINSTR(Patched_SetLoadFrame);
	*(((u32*)AnimationContext_SetLoadFrame)+1) = 0;
    *( (u32*)Animation_GetLength       ) = JUMPINSTR(Patched_GetLengthOrLastFrame);
	*(((u32*)Animation_GetLength    )+1) = 0x34050000; //ori a1, zero, 0x0000
    *( (u32*)Animation_GetLastFrame    ) = JUMPINSTR(Patched_GetLengthOrLastFrame);
	*(((u32*)Animation_GetLastFrame )+1) = 0x34050001; //ori a1, zero, 0x0001
    // *( (u32*)Animation_GetLength2      ) = JUMPINSTR(Patched_GetLengthOrLastFrame);
	// *(((u32*)Animation_GetLength2   )+1) = 0x34050000; //ori a1, zero, 0x0000
    // *( (u32*)Animation_GetLastFrame2   ) = JUMPINSTR(Patched_GetLengthOrLastFrame);
	// *(((u32*)Animation_GetLastFrame2)+1) = 0x34050001; //ori a1, zero, 0x0001
    //Patch SkelAnime_InterpFrameTable
    *( (u32*)SkelAnime_InterpFrameTable   ) = JUMPINSTR(Patched_InterpFrameTable);
    *(((u32*)SkelAnime_InterpFrameTable)+1) = 0;
}

typedef s32 (*Player_SetUpCutscene_t)(GlobalContext *, Actor *, s32);
extern s32 Player_SetUpCutscene(GlobalContext *globalCtx, Actor *actor, s32 csMode);

void Statics_AnimeTest(s32 a){
    Player_SetUpCutscene_t fp = (Player_SetUpCutscene_t)PlayerVRAMtoRAM(&Player_SetUpCutscene);
    s32 action = 0;
    if(a < 0){
        action = 13;
    }else{
        action = a + NUM_ORIG_LINK_ACTIONS;
    }
    fp(&gGlobalContext, NULL, action);
}
