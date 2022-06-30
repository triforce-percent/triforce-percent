#include "ootmain.h"
#include "ocarina.h"

typedef struct {
    u8 num_notes;
    s8 notes[8];
} DetectableSong;

extern DetectableSong DetectableSongs[13]; //extra is short scarecrow's song

typedef struct {
    s8 note;
    u16 time;
    u8 volume;
    u8 vibrato;
    s8 pitch;
} CanonSongCmd;

typedef struct {
    CanonSongCmd cmds[20];
} CanonSong;

extern CanonSong CanonSongs[14]; //extra 2 are short scarecrow's song and minigame song

static const DetectableSong VanillaPatchedDetectableSongs[12] = {
    {6, {0x2, 0xE, 0xB, 0x9, 0xB, 0x9,  -1,  -1}}, //Forest
    {8, {0x5, 0x2, 0x5, 0x2, 0x9, 0x5, 0x9, 0x5}}, //Fire
    {5, {0x2, 0x5, 0x9, 0x9, 0xB,  -1,  -1,  -1}}, //Water
    {6, {0x2, 0x5, 0x2, 0x9, 0x5, 0x2,  -1,  -1}}, //Spirit
    {7, {0xB, 0x9, 0x9, 0x2, 0xB, 0x9, 0x5,  -1}}, //Shadow
    {6, {0xE, 0x9, 0xE, 0x9, 0xB, 0xE,  -1,  -1}}, //Light
    {6, {0x5, 0x9, 0xB, 0x5, 0x9, 0xB,  -1,  -1}}, //Saria
    {6, {0xE, 0xB, 0x9, 0xE, 0xB, 0x9,  -1,  -1}}, //Epona
    {6, {0xB, 0xE, 0x9, 0xB, 0xE, 0x9,  -1,  -1}}, //Zelda
    {6, {0x9, 0x5, 0xE, 0x9, 0x5, 0xE,  -1,  -1}}, //Sun
    {6, {0x9, 0x2, 0x5, 0x9, 0x2, 0x5,  -1,  -1}}, //Time
    {6, {0x2, 0x5, 0xE, 0x2, 0x5, 0xE,  -1,  -1}}  //Storms
};

static const DetectableSong LongOfTime_Detectable = {
    8, {0x7, 0x5, 0x7, 0x9, 0x2, 0x0, 0x4, 0x2} //Long
};

static const DetectableSong OvertureOfSages_Detectable = {
    6, {0xE, 0x5, 0x2, 0x9, 0xB, 0xE,  -1,  -1} //Sages
};

static const CanonSong OvertureOfSages_Canon = {{
    {0xE, 25, 100, 0, 0},
    {0xE, 35, 100, 4, 0},
    {0x5, 30, 100, 0, 0},
    {0x2, 35, 100, 0, 0},
    {0x2, 22, 100, 4, 0},
    { -1,  3,   0, 0, 0},
    {0x9, 30, 100, 0, 0},
    {0xB, 30, 100, 0, 0},
    {0xE, 25, 100, 0, 0},
    {0xE, 35, 100, 4, 0},
    { -1, 60,   0, 0, 0}
}};

static const CanonSong LongOfTime_Canon = {{
    {0x9, 30, 100, 0, 0},
    {0x2, 60, 100, 0, 0},
    {0x5, 30, 100, 0, 0},
    {0x9, 30, 100, 0, 0},
    {0x2, 60, 100, 0, 0},
    {0x5, 30, 100, 0, 0},
    {0x9, 15, 100, 0, 0},
    {0xC, 15, 100, 0, 0},
    {0xB, 30, 100, 0, 0},
    {0x7, 30, 100, 0, 0},
    {0x5, 15, 100, 0, 0},
    {0x7, 15, 100, 0, 0},
    {0x9, 30, 100, 0, 0},
    {0x2, 30, 100, 0, 0},
    {0x0, 15, 100, 0, 0},
    {0x4, 15, 100, 0, 0},
    {0x2, 15, 100, 0, 0}, //17
    {0x2, 48, 100, 4, 0}, //18
    { -1, 30,   0, 0, 0}  //19
}};

/*
Instruments:
0 - none
1 - ocarina (0x34)
2 - Malon (0x55)
3 - Impa (whistle) (0x56)
4 - harp (0x59)
5 - accordion (0x53)
6 - pan flute (0x52)
7 - hack - sparkle_bell (sounds awful) (0x40)
8 - ocarina (0x34)
Line 15739 in oot_1.0U_seq0.mus has the instrument IDs, and there's two extras
set ocarina instrument = func_800C2C90 (1.0) = func_800ED858 (DBG)
*/

static const u64 TexDUp[] = {
    #include "../textures/dup.ia8.inc"
};
static const u64 TexDDn[] = {
    #include "../textures/ddn.ia8.inc"
};
static const u64 TexFlat[] = {
    #include "../textures/flat.ia8.inc"
};
static const u64 TexSharp[] = {
    #include "../textures/sharp.ia8.inc"
};

extern void* sOcaButtonAddrs[5];

static const u8 OcaNoteButtons[18] = {
    0, 0, /*D*/0, 0, 0,
    /*F*/1, 1, 
    2, 2, /*A*/2, 2, 
    /*B*/3, 3, 
    4, /*D*/4, 4, 4, 4
};
//1: flat, 2: sharp, 0x10: down, 0x20: up
static const u8 OcaNoteDecorations[18] = {
    0x10, 0x01, 0x00, 0x02, 0x20,
    0x00, 0x02,
    0x10, 0x01, 0x00, 0x02,
    0x00, 0x02,
    0x01, 0x00, 0x02, 0x20, 0x22
};

#define LOAD_TILE_IA8(addr, sx, sy) \
    gDPLoadTextureBlock(gfx++, addr, \
        G_IM_FMT_IA, G_IM_SIZ_8b, sx, sy, 0, \
        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, \
        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD)

Gfx* PatchOcaButtons(Gfx* gfx, u8 note, s16 x, u8 shadow){
    u8 mainButton = OcaNoteButtons[note];
    u8 decoration = OcaNoteDecorations[note];
    s16 y = (&VREG(45))[mainButton];
    const void* addr;
    s16 yoffset;
    LOAD_TILE_IA8(sOcaButtonAddrs[mainButton], 16, 16);
    gSPTextureRectangle(gfx++, 
        x << 2, y << 2, (x + 16) << 2, (y + 16) << 2, 
        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
    if(decoration){
        u8 pc = shadow ? 155 : 190;
        u8 al = shadow ? 150 : 255;
        gDPSetPrimColor(gfx++, 0, 0, pc, pc, pc, al);
        if(decoration & 0x30){
            if(decoration & 0x10){
                addr = &TexDDn;
                yoffset = 0xB;
            }else{
                addr = &TexDUp;
                yoffset = -4;
            }
            LOAD_TILE_IA8((s32)addr, 16, 8);
            gSPTextureRectangle(gfx++, 
                x << 2, (y + yoffset) << 2, (x + 16) << 2, (y + yoffset + 8) << 2, 
                G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
        }
        if(decoration & 0x3){
            if(decoration & 1){
                addr = &TexFlat;
                yoffset = -1;
            }else{
                addr = &TexSharp;
                yoffset = 0;
            }
            LOAD_TILE_IA8((s32)addr, 8, 16);
            gSPTextureRectangle(gfx++, 
                (x - 5) << 2, (y + yoffset) << 2, (x + 3) << 2, (y + yoffset + 16) << 2, 
                G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
        }
    }
    return gfx;
}

extern void func_8010C39C_1_ret();
extern void func_8010C39C_2_ret();

static const s32 OcaPatchAddrs[] = {
#define OPAT(n, a, l, c) a, 
#include "ocarina_patches.inc"
#undef OPAT
};
static const u32 OcaPatchLens[] = {
#define OPAT(n, a, l, c) l, 
#include "ocarina_patches.inc"
#undef OPAT
};
#define OPAT(n, a, l, c) void Patch_##n() {\
asm(".set noat\n .set noreorder\n" \
    c \
    ".set at\n .set reorder"); \
}
#include "ocarina_patches.inc"
#undef OPAT
static const void* const OcaPatchContents[] = {
#define OPAT(n, a, l, c) Patch_##n,
#include "ocarina_patches.inc"
#undef OPAT
};

void Ocarina_GiveLongOfTime(){
    bcopy(&LongOfTime_Detectable, &DetectableSongs[10], sizeof(DetectableSong));
    bcopy(&LongOfTime_Canon, &CanonSongs[10], sizeof(CanonSong));
}
void Ocarina_GiveOvertureOfSages(){
    bcopy(&OvertureOfSages_Detectable, &DetectableSongs[1], sizeof(DetectableSong));
    bcopy(&OvertureOfSages_Canon, &CanonSongs[1], sizeof(CanonSong));
}

void Statics_OcarinaCodePatches(){
    bcopy(&VanillaPatchedDetectableSongs, &DetectableSongs, sizeof(VanillaPatchedDetectableSongs));
    if((LONGOFTIME_VAR & LONGOFTIME_BIT)) Ocarina_GiveLongOfTime();
    if((OVERTUREOFSAGES_VAR & OVERTUREOFSAGES_BIT)) Ocarina_GiveOvertureOfSages();
    //800DEF90: instruction for setting a0 to instrument for Sheik songs teach
    *((u8*)0x800DEF93) = 0x02; //change from 1, ocarina, to 2, Malon -> choir
    //800DEFC0: instruction for setting at to ocarina action which uses 5 accordion -> shehnai
    *((u8*)0x800DEFC3) = 0x0C; //change from 0xD, storms, to 0xC, time
    //Patches for chromatic Ocarina
    int nPatches = sizeof(OcaPatchAddrs) / sizeof(s32);
    for(int i=0; i<nPatches; ++i){
        bcopy(OcaPatchContents[i], (void*)OcaPatchAddrs[i], OcaPatchLens[i] * 4);
    }
}
