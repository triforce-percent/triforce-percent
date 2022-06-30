#include "ootmain.h"
#include "scene.h"
#include "statics.h"
#include "audio.h"

#include "../scene/TriforceRoom/TriforceRoom_scene.h"
#include "../scene/Ending/Ending_scene.h"

#include "../scene/spot03/ZoraRiverFlyover.c"
#include "../scene/spot13/HauntedWastelandFlyover.c"

#include "../loader/debugger/debugger.h"

////////////////////////////////////////////////////////////////////////////////
// Scene Draw Configs
////////////////////////////////////////////////////////////////////////////////

// Scene Draw Config 32
void Patched_CoSSceneDrawConfig(GlobalContext* globalCtx) {
    u32 gameplayFrames = globalCtx->gameplayFrames;

    //OPEN_DISPS(globalCtx->state.gfxCtx, "", 0);

    // Platform waterfall side animation
    gSPSegment(POLY_XLU_DISP++, 0x08, Gfx_TexScroll(globalCtx->state.gfxCtx, 0, (gameplayFrames * 2) % 256, 64, 64));

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_OPA_DISP++, 128, 128, 128, 128);

    // Platform water floor animation
    gSPSegment(POLY_OPA_DISP++, 0x0A,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 127 - gameplayFrames % 128, (gameplayFrames * 1) % 128, 32,
                                32, 1, gameplayFrames % 128, (gameplayFrames * 1) % 128, 32, 32));

    // Chamber background animation
    gSPSegment(POLY_XLU_DISP++, 0x09,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 127 - (gameplayFrames * 1) % 128,
                                (gameplayFrames * 1) % 256, 32, 64, 1, 0, 0, 32, 128));

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_OPA_DISP++, 128, 128, 128, 128);

    gDPPipeSync(POLY_XLU_DISP++);
    gDPSetEnvColor(POLY_XLU_DISP++, 128, 128, 128, 128);

    // Fade out light rays when the player gets close
    {
        // Displaylist containg the color sets for each light ray
        static Gfx rayDL[6 * 2];
        // Position of each light ray
        static const Vec3s rayPos[] = {
            { -419, 215, -725 }, // Saria
            { 419, 394, -725 },  // Darunia
            { 838, 569, 0 },     // Ruto
            { 419, 744, 725 },   // Nabooru
            { -419, 918, 725 },  // Impa
            { -840, 1092, 0 },   // Sheik
        };
        Player* player = PLAYER;
        s32 i; // used for indexing the loop
        s32 j; // used for indexing the displaylist

        #define RANGE_LOW  300  // distance in which the ray is fully faded
        #define RANGE_HIGH 800 // distance in which the ray begins to fade out
        #define ALPHA_FULL (255.0f * 0.6f) 

        for (i = 0, j = 0; i < 6; i++, j += 2) {
            // xz distance between the player and the current light ray
            f32 distance =
                sqrtf(SQ(player->actor.world.pos.x - rayPos[i].x) + SQ(player->actor.world.pos.z - rayPos[i].z));
            u8 alpha;

            if (distance <= RANGE_LOW) {
                // Light ray is fully faded out
                alpha = 0;
            } else if (distance > RANGE_LOW && distance < RANGE_HIGH) {
                // Get alpha value for partially faded out light ray
                alpha = ALPHA_FULL * ((distance - RANGE_LOW) / (f32)(RANGE_HIGH - RANGE_LOW));
            } else {
                // Light ray is fully faded in
                alpha = ALPHA_FULL;
            }

            // Write the displaylist now that we know the alpha that we want
            gDPSetPrimColor(&rayDL[j], 0, 0, 255, 255, 255, alpha);
            gSPEndDisplayList(&rayDL[j + 1]);
        }

        // Segment B for the light rays
        gSPSegment(POLY_OPA_DISP++, 0x0B, rayDL);
    }

    //CLOSE_DISPS(globalCtx->state.gfxCtx, "", 0);
}

typedef void (*SceneDrawConfig)(GlobalContext* globalCtx);

extern SceneDrawConfig sceneDrawConfigJumpTable[0x35];

////////////////////////////////////////////////////////////////////////////////
// Scene Memory Patches
////////////////////////////////////////////////////////////////////////////////

u32 Patched_GetSpaceSize(GlobalContext* globalCtx){
    if (globalCtx->sceneNum == SCENE_GANON_DEMO
            && gSaveContext.sceneSetupIndex != 4) {
        return 1177600;
    } else if (globalCtx->sceneNum == SCENE_JYASINBOSS
            || globalCtx->sceneNum == SCENE_GANON_BOSS) {
        return 1075200;
    } else if (globalCtx->sceneNum == SCENE_KENJYANOMA
            || globalCtx->sceneNum == SCENE_KOKIRI_HOME5){
        //Chamber of Sages or testing CoS
        return 1250000;
    }
    return 1024000;
}

extern void Object_InitBank(GlobalContext* globalCtx, ObjectContext* objectCtx);
extern void Object_InitBank_AfterSpaceSize();

void Patched_ObjectInitBank(){
    asm(".set noat\n .set noreorder\n"
	//Starting at 800813D4 + 0x10
    //a0 = globalCtx, a1 = objectCtx
    "jal     Patched_GetSpaceSize\n"
    "sw      $a1, 0x0004($sp)\n"
    "lw      $a2, 0x0004($sp)\n"
    "or      $a3, $v0, $zero\n"
    "addiu   $a0, $zero, 0x0013\n"
    "j       Object_InitBank_AfterSpaceSize\n"
    "addiu   $v1, $zero, 0x0003\n"
    //Requirements after: a2 = objectCtx, v1 = 3, a0 = 0x13, a3 = spaceSize
    ".set at\n .set reorder");
}

typedef struct {
    s16 sceneId;
    u32 memSize;
} BgCheckSceneMemEntry;

extern BgCheckSceneMemEntry bgCheckSceneMemList[8];

////////////////////////////////////////////////////////////////////////////////
// Cutscene Terminators
////////////////////////////////////////////////////////////////////////////////

extern void* DemoTerminatorTable[];
extern void DemoTerminatorReturn();
#define TERMINATOR_RETURN asm(".set noat\n .set noreorder\nj DemoTerminatorReturn\nnop\n.set at\n .set reorder")

void Statics_TerminatorNabooruToDesertColossus(){
    gGlobalContext.nextEntranceIndex = 0x0123;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0xFFF1;
    gGlobalContext.fadeTransition = 3;
    TERMINATOR_RETURN;
}

void Statics_TerminatorReturnToNabooru(){
    gGlobalContext.nextEntranceIndex = 0x04A6;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0;
    gGlobalContext.fadeTransition = 3;
    TERMINATOR_RETURN;
}

void Statics_TerminatorTriforceToEnding(){
    gGlobalContext.nextEntranceIndex = 0x03FC;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0;
    gGlobalContext.fadeTransition = 3;
    TERMINATOR_RETURN;
}

void Statics_TerminatorWarpToSacredRealm(){
    gGlobalContext.nextEntranceIndex = 0x006B;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0xFFF0;
    gGlobalContext.fadeTransition = 3;
    gSaveContext.nextTransition = 3;
    TERMINATOR_RETURN;
}

void Statics_TerminatorStaffRollHyruleField(){
    gGlobalContext.linkAgeOnLoad = 1;
    gGlobalContext.nextEntranceIndex = 0x00CD;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0xFFF8;
    gGlobalContext.fadeTransition = 2;
    gSaveContext.nextTransition = 2;
    TERMINATOR_RETURN;
}

void Statics_TerminatorStaffRollDeathMountain(){
    gGlobalContext.nextEntranceIndex = 0x13D;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0xFFF3;
    gGlobalContext.fadeTransition = 2;
    gSaveContext.nextTransition = 2;
    TERMINATOR_RETURN;
}

void Statics_TerminatorStaffRollGerudoValley(){
    gGlobalContext.nextEntranceIndex = 0x117;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0xFFF1;
    gGlobalContext.fadeTransition = 2;
    gSaveContext.nextTransition = 2;
    TERMINATOR_RETURN;
}

void Statics_TerminatorStaffRollDekuTree(){
    gGlobalContext.nextEntranceIndex = 0;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0;
    gGlobalContext.fadeTransition = 2;
    gSaveContext.nextTransition = 2;
    TERMINATOR_RETURN;
}

void Statics_TerminatorStaffRollZoraFountain(){
    gGlobalContext.nextEntranceIndex = 0x10E;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0xFFF0;
    gGlobalContext.fadeTransition = 2;
    gSaveContext.nextTransition = 2;
    TERMINATOR_RETURN;
}

void Statics_TerminatorStaffRollZoraRiver(){
    gGlobalContext.nextEntranceIndex = 0x19D;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0;
    gGlobalContext.fadeTransition = 3;
    gSaveContext.nextTransition = 3;
    TERMINATOR_RETURN;
}

void Statics_TerminatorStaffRollKokiriForest(){
    gGlobalContext.nextEntranceIndex = 0x0EE;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0xFFF5;
    gGlobalContext.fadeTransition = 2;
    gSaveContext.nextTransition = 2;
    TERMINATOR_RETURN;
}

void Statics_TerminatorStaffRollLonLonRanch(){
    gGlobalContext.nextEntranceIndex = 0x157;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0xFFF2;
    gGlobalContext.fadeTransition = 2;
    gSaveContext.nextTransition = 2;
    TERMINATOR_RETURN;
}

void Statics_TerminatorStaffRollWasteland(){
    gGlobalContext.nextEntranceIndex = 0x130;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0;
    gGlobalContext.fadeTransition = 2;
    gSaveContext.nextTransition = 2;
    TERMINATOR_RETURN;
}

void Statics_TerminatorStaffRollHyruleCastle(){
    gGlobalContext.nextEntranceIndex = 0x138;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0;
    gGlobalContext.fadeTransition = 2;
    gSaveContext.nextTransition = 2;
    TERMINATOR_RETURN;
}

void Statics_TerminatorStaffRollFinale(){
    gGlobalContext.nextEntranceIndex = 0x30D;
    gGlobalContext.sceneLoadFlag = 0x14;
    gSaveContext.cutsceneIndex = 0xFFF0;
    gGlobalContext.fadeTransition = 2;
    gSaveContext.nextTransition = 2;
    TERMINATOR_RETURN;
}

typedef struct {
    u8 index;
    void (*function)();
} FuncPtrPatchTblEntry;

#define NUM_PATCH_TERMINATOR 15
static const FuncPtrPatchTblEntry DemoTerminatorPatchTable[NUM_PATCH_TERMINATOR] = {
    {0x4F, Statics_TerminatorNabooruToDesertColossus},
    {0x50, Statics_TerminatorReturnToNabooru},
    {0x51, Statics_TerminatorTriforceToEnding},
    {0x52, Statics_TerminatorWarpToSacredRealm},
    {0x53, Statics_TerminatorStaffRollHyruleField},
    {0x54, Statics_TerminatorStaffRollDeathMountain},
    {0x55, Statics_TerminatorStaffRollGerudoValley},
    {0x56, Statics_TerminatorStaffRollDekuTree},
    {0x57, Statics_TerminatorStaffRollZoraFountain},
    {0x58, Statics_TerminatorStaffRollZoraRiver},
    {0x59, Statics_TerminatorStaffRollKokiriForest},
    {0x5A, Statics_TerminatorStaffRollLonLonRanch},
    {0x5B, Statics_TerminatorStaffRollWasteland},
    {0x5C, Statics_TerminatorStaffRollHyruleCastle},
    {0x5D, Statics_TerminatorStaffRollFinale}
};

////////////////////////////////////////////////////////////////////////////////
// Cutscene Misc. Command Patches
////////////////////////////////////////////////////////////////////////////////

extern void* DemoMiscTable[];
extern void DemoMiscReturn();

void Statics_MiscLoadRoom(GlobalContext *globalCtx, s32 isFirstFrame, s32 roomNum){
    if(isFirstFrame) func_8009728C(globalCtx, &globalCtx->roomCtx, roomNum);
}

void Statics_Misc04LoadRoom0(){
    asm(".set noat\n .set noreorder\n"
        "ori $a2, $zero, 0x0000\n"
        "or $a0, $s0, $zero\n"
        "jal Statics_MiscLoadRoom\n"
        "or $a1, $v0, $zero\n"
        "j DemoMiscReturn\n"
        "nop\n"
        ".set at\n .set reorder");
}

void Statics_Misc05LoadRoom1(){
    asm(".set noat\n .set noreorder\n"
        "ori $a2, $zero, 0x0001\n"
        "or $a0, $s0, $zero\n"
        "jal Statics_MiscLoadRoom\n"
        "or $a1, $v0, $zero\n"
        "j DemoMiscReturn\n"
        "nop\n"
        ".set at\n .set reorder");
}

#define NUM_PATCH_MISC 2
static const FuncPtrPatchTblEntry DemoMiscPatchTable[NUM_PATCH_MISC] = {
    {4, Statics_Misc04LoadRoom0},
    {5, Statics_Misc05LoadRoom1}
};

////////////////////////////////////////////////////////////////////////////////
// Entrance Table && Entrance Cutscene Table Patches
////////////////////////////////////////////////////////////////////////////////

static void PatchEntranceTable(u16 entryIdx, u8 count, const EntranceTableEntry *contents)
{
    for(u8 i=0; i<count; ++i)
        gFakeEntranceTable[entryIdx+i] = *contents;
}

static inline void AdjustSREntrySettings(u16 entryIdx, u8 setup, u8 in, u8 out)
{
    gFakeEntranceTable[entryIdx+setup].keepMusic = 1;
    gFakeEntranceTable[entryIdx+setup].titleCard = 0;
    gFakeEntranceTable[entryIdx+setup].transitionIn = in;
    gFakeEntranceTable[entryIdx+setup].transitionOut = out;
}

static u8 sIsStaffRoll = 0;

void Statics_SetUpStaffRoll(){
    sIsStaffRoll = 1;
    gSaveContext.eventChkInf[0xA] &= ~((1 << 8) | (1 << 5));
    gSaveContext.eventChkInf[0xB] &= ~((1 << 0xB) | (1 << 0xC));
}

static void Statics_SetUpRouting(){
    //
    //Patches to remove access to reused scenes
    //Kakariko Village to Granny's Potion Shop -> Kakariko Village to Kakariko Village turnaround
    static const EntranceTableEntry kakariko_to_granny_entry = {
        .scene = SCENE_SPOT01, 
        .spawn = 7, .keepMusic = 1, .titleCard = 0, .transitionIn = 0x20, .transitionOut = 0x20
    };
    PatchEntranceTable(0x0072, 4, &kakariko_to_granny_entry);
    //Goron City to Goron Shop -> Goron City to Goron City turnaround
    static const EntranceTableEntry gcity_to_gshop_entry = {
        .scene = SCENE_SPOT18,
        .spawn = 2, .keepMusic = 1, .titleCard = 0, .transitionIn = 5, .transitionOut = 5
    };
    PatchEntranceTable(0x037C, 4, &gcity_to_gshop_entry);
    //Graveyard to Dampe's Hut -> Graveyard to Graveyard turnaround
    static const EntranceTableEntry graveyard_to_hut_entry = {
        .scene = SCENE_SPOT02,
        .spawn = 2, .keepMusic = 1, .titleCard = 0, .transitionIn = 5, .transitionOut = 5
    };
    PatchEntranceTable(0x030D, 4, &graveyard_to_hut_entry);
    //
    //Main areas
    //Zora's Domain to Lake Hylia -> Zora's Domain to Unicorn Fountain
    static const EntranceTableEntry zoras_to_lake_entry = {
        .scene = SCENE_UNICORNFOUNTAIN, 
        .spawn = 0, .keepMusic = 0, .titleCard = 1, .transitionIn = 4, .transitionOut = 4
    };
    PatchEntranceTable(0x0560, 4, &zoras_to_lake_entry);
    //Lake Hylia to Zora's Domain -> scene not changed, but transition changed
    //Used for Unicorn Fountain to Zora's Domain
    static const EntranceTableEntry lake_to_zoras_entry = {
        .scene = SCENE_SPOT07, 
        .spawn = 4, .keepMusic = 0, .titleCard = 1, .transitionIn = 4, .transitionOut = 4
    };
    PatchEntranceTable(0x0328, 4, &lake_to_zoras_entry);
    //TODO edit Zora's spawn location to be in front of the exit
    //Cutscenes to Chamber of Sages -> Overture of Sages to Chamber of the Sages
    static const EntranceTableEntry cs_to_cos_entry = {
        .scene = SCENE_KENJYANOMA,
        .spawn = 0, .keepMusic = 0, .titleCard = 1, .transitionIn = 7, .transitionOut = 7
    };
    PatchEntranceTable(0x006B, 7, &cs_to_cos_entry);
    //Granny's Potion Shop to Kakariko Village -> Chamber of the Sages to Triforce Room
    static const EntranceTableEntry granny_to_kakariko_entry = {
        .scene = SCENE_TRIFORCEROOM,
        .spawn = 0, .keepMusic = 0, .titleCard = 0, .transitionIn = 2, .transitionOut = 1
    };
    PatchEntranceTable(0x034D, 4, &granny_to_kakariko_entry);
    static const EntranceCutsceneTableEntry spirit_boss_entry = {
        .entrance = 0x034D, .age = 2, .eventChkFlag = TRIFORCE_ROOM_ENTRANCE_CS_EVENTCHKFLAG, 
        .segAddr = TriforceRoom_scene_header00_cutscene
    };
    gEntranceCutsceneTable[30] = spirit_boss_entry;
    //Goron Shop to Goron City -> Triforce Room to Ending
    static const EntranceTableEntry gshop_to_gcity_entry = {
        .scene = SCENE_ENDING,
        .spawn = 0, .keepMusic = 0, .titleCard = 0, .transitionIn = 7, .transitionOut = 7
    };
    PatchEntranceTable(0x03FC, 4, &gshop_to_gcity_entry);
    static const EntranceCutsceneTableEntry dmc2_entry = {
        .entrance = 0x03FC, .age = 2, .eventChkFlag = ENDING_ENTRANCE_CS_EVENTCHKFLAG, 
        .segAddr = FinaleCS
    };
    gEntranceCutsceneTable[32] = dmc2_entry;
    //
    //Other
    //Gerudo's Fortress to Thieves' Hideout -> scene not changed, but disabled title card
    static const EntranceTableEntry return_to_nabooru_entry = {
        .scene = SCENE_GERUDOWAY, 
        .spawn = 8, .keepMusic = 0, .titleCard = 0, .transitionIn = 5, .transitionOut = 5
    };
    PatchEntranceTable(0x04A6, 4, &return_to_nabooru_entry);
    PatchEntranceTable(0x04A7, 4, &return_to_nabooru_entry);
    //Outside Temple of Time -> always child versions
    gFakeEntranceTable[0x0173] = gFakeEntranceTable[0x0171];
    gFakeEntranceTable[0x0174] = gFakeEntranceTable[0x0172];
    gFakeEntranceTable[0x0474] = gFakeEntranceTable[0x0472];
    gFakeEntranceTable[0x0475] = gFakeEntranceTable[0x0473];
    //
    //Staff Roll
    //Hyrule Field
    AdjustSREntrySettings(0x0CD, 12, 2, 2);
    //Death Mountain Trail
    AdjustSREntrySettings(0x13D, 7, 2, 2);
    //Gerudo Valley
    AdjustSREntrySettings(0x117, 5, 2, 2);
    //Deku Tree
    AdjustSREntrySettings(0x000, 0, 2, 2);
    //Zora's Fountain
    AdjustSREntrySettings(0x10E, 4, 2, 3);
    //Zora's River
    gEntranceCutsceneTable[24].entrance = 0x19D;
    gEntranceCutsceneTable[24].segAddr = &ZoraRiverFlyover;
    AdjustSREntrySettings(0x19D, 0, 3, 2);
    //Kokiri Forest
    AdjustSREntrySettings(0x0EE, 9, 2, 2);
    //Lon Lon Ranch
    AdjustSREntrySettings(0x157, 6, 2, 2);
    //Haunted Wasteland
    gEntranceCutsceneTable[25].entrance = 0x130;
    gEntranceCutsceneTable[25].segAddr = &HauntedWastelandFlyover;
    AdjustSREntrySettings(0x130, 0, 2, 2);
    //Hyrule Castle
    AdjustSREntrySettings(0x138, 0, 2, 2);
    //Finale
    static const EntranceTableEntry finale_field_river_water_entry = {
        .scene = SCENE_ENDING, 
        .spawn = 0, .keepMusic = 1, .titleCard = 0, .transitionIn = 2, .transitionOut = 2
    };
    PatchEntranceTable(0x030D+4, 1, &finale_field_river_water_entry);
    //
    //Debugging
    
    //Kokiri Forest to House of the Know-It-All Brothers -> Kokiri Forest to Ending Scene
    static const EntranceTableEntry forest_to_knowitall_entry = {
        .scene = SCENE_ENDING, 
        .spawn = 0, .keepMusic = 0, .titleCard = 0, .transitionIn = 7, .transitionOut = 7
    };
    PatchEntranceTable(0x00C9, 4, &forest_to_knowitall_entry);
    /*
    //Kokiri Forest to House of the Know-It-All Brothers -> Kokiri Forest to Triforce Room
    static const EntranceTableEntry forest_to_knowitall_entry = {
        .scene = SCENE_TRIFORCEROOM,
        .spawn = 0, .keepMusic = 0, .titleCard = 0, .transitionIn = 2, .transitionOut = 1
    };
    PatchEntranceTable(0x00C9, 4, &forest_to_knowitall_entry);
    static const EntranceCutsceneTableEntry dmc2_entry = {
        .entrance = 0x00C9, .age = 2, .eventChkFlag = TRIFORCE_ROOM_ENTRANCE_CS_EVENTCHKFLAG, 
        .segAddr = TriforceRoom_scene_header00_cutscene
    };
    gEntranceCutsceneTable[32] = dmc2_entry;
    */
}

//extern void Environment_PlaySceneSequence(GlobalContext *globalCtx);

extern void Scene_Cmd0x15SoundSettings(GlobalContext* globalCtx, SceneCmd* cmd);

void Statics_PatchedCmd0x15(GlobalContext* globalCtx, SceneCmd* cmd){
    u8 seq = cmd->soundSettings.seqIndex;
    if(sIsStaffRoll && gSaveContext.entranceIndex >= 0x19D && gSaveContext.entranceIndex <= 0x1A0){
        seq = 0x76;
    }
    globalCtx->soundCtx.seqIndex = seq;
    globalCtx->soundCtx.nightSeqIndex = cmd->soundSettings.nightSeqIndex;

    if (gSaveContext.seqIndex == (u8)(0xFFFF)) {
        Audio_QueueSeqCmd(cmd->soundSettings.bgmId | 0xF0000000);
    }
}

////////////////////////////////////////////////////////////////////////////////
// F3DZEX Cel Shading Patch
////////////////////////////////////////////////////////////////////////////////

#define CELSHADING_PATCH_ADDR 0x800E523C

static const u32 CelShadingPatch1[14] = {
    0x4bffad68, 0xc9223016, 0x4bffe728, 0xc9343013,
    0x4bffef40, 0x4a952748, 0x156dffee, 0x4a9c1f48,
    0x4a1bef67, 0x30ac0040, 0x4bbf00e7, 0x11800002,
    0xc9d61206, 0x4abd0750
};

static const u32 CelShadingPatch2[7] = {
    0x4bffad68, 0x4bffef40, 0x4a952748, 0xc9223010,
    0x4a1bef67, 0x0800050e, 0x4afff8e1
};

static void Statics_CelShadingPatch(){
    s32 i = __osDisableInt();
    bcopy(CelShadingPatch1, (void*)CELSHADING_PATCH_ADDR, 14*4);
    bcopy(CelShadingPatch2, (void*)(CELSHADING_PATCH_ADDR + 0x9C), 7*4);
    osWritebackDCache(NULL, 0x4000);
    __osRestoreInt(i);
}

////////////////////////////////////////////////////////////////////////////////
// Finale Cutscene Lag Correction
////////////////////////////////////////////////////////////////////////////////

extern void func_80080BA4(GlobalContext* globalCtx, RoomContext* roomCtx); // debug func_800973FC
extern void func_80052364(GlobalContext* globalCtx, CutsceneContext* csCtx);
extern void func_800523B0(GlobalContext* globalCtx, CutsceneContext* csCtx);
extern void Statics_CameraSplinePatch_ret();

static u32 lastlagcount = 0;
static u16 lagVIscount = 0;
static u8 enablelagcorr = 0;
static u8 repeatCurFrame = 0;
static f32 lagPlaySpeed = 1.0f;

#define CPU_CLOCK 93750000
#define COUNTS_PER_VI ((CPU_CLOCK / 2) / 60)

void Statics_MeasureLag(GlobalContext* globalCtx, RoomContext* roomCtx){
    u32 count = osGetCount();
    repeatCurFrame = 0;
    lagPlaySpeed = 1.0f;
    if(!enablelagcorr || globalCtx->csCtx.state == 0){
        lastlagcount = 0;
    }else if(lastlagcount == 0){
        lastlagcount = count;
    }else{
        s32 d = count - lastlagcount;
        lastlagcount = count;
        d += COUNTS_PER_VI / 2; //round to nearest
        s32 VIsperframe = d / COUNTS_PER_VI;
        if(sIsLiveRun) sPerfCount = VIsperframe;
        s32 lagVIs = VIsperframe - 3;
        if(lagVIs < 0) lagVIs = 0;
        //Need to track 2 things:
        //1. For cutscene frame counts and any actor logic which counts frames,
        //whether to run things twice to make up for a total of 3 lag VIs.
        lagVIscount += lagVIs;
        if(lagVIscount >= 3){
            repeatCurFrame = 1;
            lagVIscount -= 3;
        }
        //2. For camera motion and animation which take a float number of frames
        //to advance by, the playback speed to run.
        lagPlaySpeed = 1.0f + (f32)lagVIs * 0.33333333f;
    }
    if(sIsLiveRun){
        sDbgLagRepeat = repeatCurFrame;
        sDbgLagPlaySpeed = lagPlaySpeed;
    }
    //patch overwrote
    func_80080BA4(globalCtx, roomCtx);
}

void Statics_CallCutsceneFuncsPatched(GlobalContext* globalCtx, CutsceneContext* csCtx){
    //Advance cutscene once normally plus once more if lag frame
    for(u32 i=0; i<=repeatCurFrame; ++i){
        func_80052364(globalCtx, csCtx); //debug: func_80064558
        func_800523B0(globalCtx, csCtx); //debug: func_800645A0
    }
}

void Statics_CameraSplinePatch(){
    //f0: advance
    //f2: *curFrame
    //f8: output to *curFrame
    //f18: 0
    /*overwrote:
    c.lt.s  $f0, $f18                  
    nop
    bc1fl   lbl_80099BF4               
    add.s   $f8, $f2, $f0              # curFrame += advance
    mtc1    $zero, $f0                 ## $f0 = 0.000
    nop
    add.s   $f8, $f2, $f0              # curFrame += advance
    */
    asm(".set noat\n .set noreorder\n"
    "c.lt.s  $f0, $f18\n"
    "lui     $t4, %hi(lagPlaySpeed)\n"
    "bc1fl   Statics_CameraSplinePatch_1\n"
    "lwc1    $f6, %lo(lagPlaySpeed)($t4)\n"
    "mtc1    $zero, $f0\n"
    "Statics_CameraSplinePatch_1:\n"
    "mul.s   $f4, $f6, $f0\n"
    "j       Statics_CameraSplinePatch_ret\n"
    "add.s   $f8, $f2, $f4\n"
    ".set at\n .set reorder");
}

static void Statics_LagPatch(){
    *((u32*)0x8009BD10) = JALINSTR(Statics_MeasureLag);
    *((u32*)0x8009BD74) = JALINSTR(Statics_CallCutsceneFuncsPatched);
    *((u32*)0x8009BD80) = 0; //nop
    *((u32*)0x80099BD8) = JUMPINSTR(Statics_CameraSplinePatch);
}

u8 Statics_LagRepeatFrame(){
    return repeatCurFrame;
}

f32 Statics_LagPlaySpeed(){
    return lagPlaySpeed;
}

void Statics_EnableLagCorr(u8 enabled){
    enablelagcorr = enabled;
}

////////////////////////////////////////////////////////////////////////////////
// Common
////////////////////////////////////////////////////////////////////////////////

void Statics_SceneCodePatches(){
    sIsStaffRoll = 0;
    //Scene Draw Configs
    sceneDrawConfigJumpTable[0x20] = Patched_CoSSceneDrawConfig;
    //Scene Memory Patches
    bcopy((void*)Patched_ObjectInitBank, (void*)Object_InitBank + 4*4, 7*4);
    bgCheckSceneMemList[4].memSize = 0x1CC00; //Temple of Time slot; default mem size
    //Cutscene Terminators & Misc
    for(int i=0; i<NUM_PATCH_TERMINATOR; ++i){
        //Jump table starts at 1
        DemoTerminatorTable[DemoTerminatorPatchTable[i].index - 1] = 
            (void*)DemoTerminatorPatchTable[i].function;
    }
    for(int i=0; i<NUM_PATCH_MISC; ++i){
        //Jump table starts at 1
        DemoMiscTable[DemoMiscPatchTable[i].index - 1] = 
            (void*)DemoMiscPatchTable[i].function;
    }
    //Zora's Fountain scene music cmd patch
    *((u32*)(Scene_Cmd0x15SoundSettings)  ) = JUMPINSTR(Statics_PatchedCmd0x15);
    *((u32*)(Scene_Cmd0x15SoundSettings)+1) = 0;
    //Entrance Table && Entrance Cutscene Table Patches
    Statics_SetUpRouting();
    //F3DZEX Cel Shading Patch
    Statics_CelShadingPatch();
    //Finale Cutscene Lag Correction
    Statics_LagPatch();
}
