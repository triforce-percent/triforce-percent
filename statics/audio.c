#define AdsrEnvelope BADAdsrEnvelope
#define AdpcmLoop BADAdpcmLoop
#define AdpcmBook BADAdpcmBook
#define AudioBankSample BADAudioBankSample
#define AudioBankSound BADAudioBankSound
#define Instrument BADInstrument
#define Drum BADDrum

#include "ootmain.h"

#undef AdsrEnvelope
#undef AdpcmLoop
#undef AdpcmBook
#undef AudioBankSample
#undef AudioBankSound
#undef Instrument
#undef Drum

#include "audio.h"
#include "statics.h"
#include "../loader/debugger/debugger.h"
#include "z64audiocompat.h"

#include "../voice/vo_link_zerudahime.c"
#include "../voice/vo_link_isshoni.c"
#include "../voice/vo_zelda_link.c"
#include "../voice/vo_zelda_itseems.c"
#include "../voice/vo_zelda_imsohappy.c"
#include "../voice/vo_zelda_iknowtheyre.c"
#include "../voice/vo_zelda_look.c"
#include "../voice/vo_zelda_youasked.c"
#include "../voice/vo_zelda_hereitis.c"
#include "../voice/vo_zelda_thankyou.c"
#include "../voice/chimes.c"
//#include "../voice/botw_step_stone_l0.c"
//#include "../voice/botw_step_stone_l1.c"
//#include "../voice/botw_step_stone_r0.c"
//#include "../voice/botw_step_stone_r1.c"
//#include "../voice/botw_step_grassstraw_l0.c"
//#include "../voice/botw_step_grassstraw_l1.c"
//#include "../voice/botw_step_grassstraw_r0.c"
//#include "../voice/botw_step_grassstraw_r1.c"
//#include "../voice/botw_rustle_0.c"
//#include "../voice/botw_rustle_1.c"
//#include "../voice/botw_rustle_2.c"

#define NUM_CUST_SAMPLES 11
SoundFontSample *cust_samples[NUM_CUST_SAMPLES] = {
    &vo_link_zerudahimeSample,
    &vo_link_isshoniSample,
    &vo_zelda_linkSample,
    &vo_zelda_itseemsSample,
    &vo_zelda_imsohappySample,
    &vo_zelda_iknowtheyreSample,
    &vo_zelda_lookSample,
    &vo_zelda_youaskedSample,
    &vo_zelda_hereitisSample,
    &vo_zelda_thankyouSample,
    &chimesSample,
    //&botw_step_stone_l0Sample,
    //&botw_step_stone_l1Sample,
    //&botw_step_stone_r0Sample,
    //&botw_step_stone_r1Sample,
    //&botw_step_grassstraw_l0Sample,
    //&botw_step_grassstraw_l1Sample,
    //&botw_step_grassstraw_r0Sample,
    //&botw_step_grassstraw_r1Sample,
    //&botw_rustle_0Sample,
    //&botw_rustle_1Sample,
    //&botw_rustle_2Sample
};
float cust_sample_tuning[NUM_CUST_SAMPLES] = {
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.6f,
    //1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
};
s32 sound_replace_offset[NUM_CUST_SAMPLES] = {
    0x1660 + 8*23, // EN_GANON_LAUGH
    0x1660 + 8*24, // EN_GANON_VOICE_DEMO
    0x1660 + 8*25, // EN_GANON_THROW
    0x1660 + 8*26, // EN_GANON_AT_RETURN
    0x1660 + 8*27, // EN_GANON_HIT_GND
    0x1660 + 8*28, // EN_GANON_DAMAGE1
    0x1660 + 8*29, // EN_GANON_DAMAGE2
    0x1660 + 8*30, // EN_GANON_DOWN
    0x1660 + 8*31, // EN_GANON_RESTORE
    0x1660 + 8*32, // EN_GANON_DEAD
    0x1660 + 8*33, // EN_GANON_BREATH
    //Step
    //0x1660 + 8*34, // EN_GANON_TOKETU
    //0x1660 + 8*35, // EN_GANON_CASBREAK
    //0x1660 + 8*36, // EN_GANON_BIGMASIC
    //0x1660 + 8*37, // EN_GANON_DARKWAVE
    //0x1660 + 8*14, // EN_IRONNACK_DAMAGE
    //0x1660 + 8*15, // EN_IRONNACK_DASH
    //0x1660 + 8*16, // EN_IRONNACK_DEAD
    //0x1660 + 8*17, // EN_IRONNACK_PULLOUT
    //0x1660 + 8*7 , // EN_TWINROBA_YOUNG_DAMAGE2
    //0x1660 + 8*8 , // EN_TWINROBA_YOUNG_SHOOTVC
    //0x1660 + 8*9   // EN_TWINROBA_YOUNG_LAUGH
};
u8 cust_sample_bank_idx[NUM_CUST_SAMPLES] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    //1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
s32 bank_ram_addr[2] = {
    0x80192A10, // Master Bank
    0x80191260  // Actor Bank
};
#define AUDIOTABLE_01_ROM 0x00079470
#define AUDIOTABLE_2_ROM (AUDIOTABLE_01_ROM + 0x3FA9E0)
#define AUDIOTABLE_3_ROM (AUDIOTABLE_01_ROM + 0x4006B0)
#define AUDIOTABLE_4_ROM (AUDIOTABLE_01_ROM + 0x41D760)
#define AUDIOTABLE_5_ROM (AUDIOTABLE_01_ROM + 0x427D30)
#define AUDIOTABLE_6_ROM (AUDIOTABLE_01_ROM + 0x4377E0)

#include "bankdata.c"

//These max values come from the sizes of the LoadStatus fields in AudioContext
#define MAX_SEQS 0x80
#define MAX_BANKS 0x30
#define NUM_ORIG_SEQS 0x6E
#define NUM_ORIG_BANKS 0x26

#define SEQ_OVERTUREOFSAGES_LEARN (NUM_ORIG_SEQS+0)
#define SEQ_OVERTUREOFSAGES_WARP  0x33
#define SEQ_CHAMBEROFSAGES        (NUM_ORIG_SEQS+2)
#define SEQ_OBTAINTHETRIFORCE     (NUM_ORIG_SEQS+3)
#define SEQ_POWEROFTHEGODDESSES   (NUM_ORIG_SEQS+4)
#define SEQ_HERETOGETHER_1        (NUM_ORIG_SEQS+5)
#define SEQ_HERETOGETHER_2        (NUM_ORIG_SEQS+6)
#define SEQ_HERETOGETHER_3        (NUM_ORIG_SEQS+7)
#define SEQ_STAFFROLL             (NUM_ORIG_SEQS+8)

#define BANK_CHAMBEROFSAGES       (NUM_ORIG_BANKS+0)
#define BANK_HERETOGETHER         (NUM_ORIG_BANKS+1)

// For normal seqs: 2 bytes for u16 offset, 1 byte for length (1), 1 byte for bank
// Some seqs have 2 banks, so add a bit after that
// Original size is 0x1C0
#define NEW_SEQBANKSMAP_SIZE (4 * MAX_SEQS + 32)

typedef struct {
    /* 0x0000 */ s16 entryCnt;
    /* 0x0002 */ s16 unk_02;
    /* 0x0004 */ u32 romAddr;
    /* 0x0008 */ char pad[0x8];
} AudioIndexHeader; // size = 0x10

typedef struct {
    /* 0x0000 */ u32 addr;
    /* 0x0004 */ u32 size;
    /* 0x0008 */ s8 loadLocation;
    /* 0x0009 */ s8 seqPlayerIdx;
    //Following used in Audiobank Index only, in others all zeros
    /* 0x000A */ u8 audiotableIdx;
    /* 0x000B */ u8 unk_0B; //0xFF
    /* 0x000C */ u8 numInst;
    /* 0x000D */ u8 numDrum;
    /* 0x000E */ u8 unk_0E; //0x00
    /* 0x000F */ u8 numSfx;
} AudioIndexEntry; // size = 0x10

typedef struct {
    AudioIndexHeader header;
    AudioIndexEntry entries[MAX_SEQS];
} AudioIndex;

typedef struct {
    u8 dummy[0x1E18];
    OSPiHandle* cartHandle;
    OSPiHandle* unk_1E1C;
    u8 dummy2[(0x2830-0x1E20)];
    AudioIndex* audioseqIndex;
    AudioIndex* audiobankIndex;
    AudioIndex* audiotableIndex;
    u8* seqBanksMap;
    u16 seqTabEntCnt;
    CtlEntry* gCtlEntries;
    u8 dummy3[(0x2984-0x2848)];
    volatile s32 resetTimer;
} FakeAudioContext;

static AudioIndex NewAudioseqIndex;
static AudioIndex NewAudiobankIndex;
static CtlEntry NewCtlEntries[MAX_BANKS];
static u8 NewSeqBanksMap[NEW_SEQBANKSMAP_SIZE];
static u16 SeqBanksMapWriteOffset;

extern FakeAudioContext gFakeAudioContext;

extern s32 (*sDmaHandler)(OSPiHandle* handle, OSIoMesg* mb, s32 direction);

extern void Audio_DMA();

static s32 Patched_AudioDMA(OSIoMesg* mesg, u32 priority, s32 direction, u32 devAddr,
    void* ramAddr, u32 size, OSMesgQueue* reqQueue, s32 handleType)
{
    if(gFakeAudioContext.resetTimer > 0x10) return -1;
    
    size = (size + 0xF) & ~0xF;
    
    if(devAddr >= 0x04000000 && devAddr < 0x04800000){
        //Injected data
        osYieldThread();
        bcopy(InjectRomRamMap(devAddr), ramAddr, size);
        osSendMesg(reqQueue, NULL, OS_MESG_NOBLOCK);
        return 0;
    }
    
    OSPiHandle* handle;
    if(handleType == 2) handle = gFakeAudioContext.cartHandle;
    else if(handleType == 3) handle = gFakeAudioContext.unk_1E1C;
    else return 0;
    
    mesg->hdr.pri = priority;
    mesg->hdr.retQueue = reqQueue;
    mesg->dramAddr = ramAddr;
    mesg->devAddr = devAddr;
    mesg->size = size;
    handle->transferInfo.cmdType = 2;
    sDmaHandler(handle, mesg, direction);
    return 0;
}

#define Audio_SeqCmd1(playerIdx, a) Audio_QueueSeqCmd(0x100000FF | ((u8)playerIdx << 24) | ((u8)(a) << 16))

extern void Message_Use_PlayFanfare();

void Patched_PlayWarpSong(u16 song)
{
    if(song == 0x33 /* Bolero of Fire -> Overture of Sages */ 
            && (OVERTUREOFSAGES_VAR & OVERTUREOFSAGES_BIT)
            && gGlobalContext.sceneNum == SCENE_TOKINOMA){
        func_800F5E18(0, song, 0, 7, -1); // Main internal start sequence, on player 0
        Audio_SeqCmd1(1, 0); // Stop player 1
        //Audio_ClearBGMMute(0xD); // Was set by Audio_OcaSetInstrument
        D_801333D0 = 0;
        Audio_SetVolScale(0, 2, 0x7F, 1); // modified to fade back in after 1 frame
        Audio_SetVolScale(3, 2, 0x7F, 1);
    }else{
        func_800F5C64(song); // Normal play fanfare on player 1
    }
}

static inline void CopyReplaceIndex(AudioIndex** origIdx, AudioIndex* newIdx, u32 entries)
{
    bcopy((const void*)*origIdx, (void*)newIdx, 
        sizeof(AudioIndexHeader) + entries * sizeof(AudioIndexEntry));
    *origIdx = newIdx;
}

extern void func_800E3034(s32 bank);

static const u8 PatchedEnv12Chirps[] = {
    0xC0, 0x3F, 0xC0, 0x00,
    0x00, 0x02, 0x00, //NATURE_IO_STREAM_0_TYPE(NATURE_STREAM_RUSHING_WATER),
    0x00, 0x03, 0x00, //NATURE_IO_STREAM_0_PORT3(0),
    0x01, 0x02, 0x00, //NATURE_IO_CRITTER_0_TYPE(NATURE_CRITTER_BIRD_CHIRP_1),
    0x01, 0x03, 0x50, //NATURE_IO_CRITTER_0_BEND_PITCH(80),
    0x01, 0x04, 0x00, //NATURE_IO_CRITTER_0_NUM_LAYERS(0),
    0x01, 0x05, 0x08, //NATURE_IO_CRITTER_0_PORT5(8),
    0x02, 0x02, 0x0A, //NATURE_IO_CRITTER_1_TYPE(NATURE_CRITTER_SMALL_BIRD_CHIRPS),
    0x02, 0x03, 0x50, //NATURE_IO_CRITTER_1_BEND_PITCH(80),
    0x02, 0x04, 0x00, //NATURE_IO_CRITTER_1_NUM_LAYERS(0),
    0x02, 0x05, 0x30, //NATURE_IO_CRITTER_1_PORT5(48),
    0x03, 0x02, 0x06, //NATURE_IO_CRITTER_1_TYPE(NATURE_CRITTER_LOUD_CHIRPING),
    0x03, 0x03, 0x50, //NATURE_IO_CRITTER_1_BEND_PITCH(80),
    0x03, 0x04, 0x00, //NATURE_IO_CRITTER_1_NUM_LAYERS(0),
    0x03, 0x05, 0x30, //NATURE_IO_CRITTER_1_PORT5(48),
    0x04, 0x02, 0x02, //NATURE_IO_CRITTER_1_TYPE(NATURE_CRITTER_BIRD_CHIRP_2),
    0x04, 0x03, 0x50, //NATURE_IO_CRITTER_1_BEND_PITCH(80),
    0x04, 0x04, 0x00, //NATURE_IO_CRITTER_1_NUM_LAYERS(0),
    0x04, 0x05, 0x30, //NATURE_IO_CRITTER_1_PORT5(48),
    0xFF
};

void Statics_AudioCodePatches(u8 isLiveRun)
{
    s32 i = __osDisableInt();
    CopyReplaceIndex(&gFakeAudioContext.audioseqIndex, &NewAudioseqIndex, NUM_ORIG_SEQS);
    CopyReplaceIndex(&gFakeAudioContext.audiobankIndex, &NewAudiobankIndex, NUM_ORIG_BANKS);
    // Banks have metadata copied to gCtlEntries, by func_800E3034 / InitCtlTable
    // This is probably a holdover of the older audio subsystem where the bank metadata
    // was stored at the beginning of the bank (i.e. needs DMA), not in a table in code
    // This is originally allocated from the audio pool, but we need to make it bigger
    bcopy(gFakeAudioContext.gCtlEntries, NewCtlEntries, sizeof(CtlEntry) * NUM_ORIG_BANKS);
    gFakeAudioContext.gCtlEntries = NewCtlEntries;
    // Copy and expand seqBanksMap
    SeqBanksMapWriteOffset = 2 * MAX_SEQS;
    s32 seq = 0;
    for(; seq<NUM_ORIG_SEQS; ++seq){
        u16 readoffset = ((u16*)gFakeAudioContext.seqBanksMap)[seq];
        u8 numBanks = gFakeAudioContext.seqBanksMap[readoffset++];
        ((u16*)&NewSeqBanksMap)[seq] = SeqBanksMapWriteOffset;
        NewSeqBanksMap[SeqBanksMapWriteOffset++] = numBanks;
        for(u8 b=0; b<numBanks; ++b){
            NewSeqBanksMap[SeqBanksMapWriteOffset++] = gFakeAudioContext.seqBanksMap[readoffset++];
        }
    }
    for(; seq<MAX_SEQS; ++seq){
        ((u16*)&NewSeqBanksMap)[seq] = 0;
    }
    gFakeAudioContext.seqBanksMap = NewSeqBanksMap;
    // Patch Audio_DMA
    *( (u32*)Audio_DMA   ) = JUMPINSTR(Patched_AudioDMA);
    *(((u32*)Audio_DMA)+1) = 0;
    // Patch play warp song, originally Audio_PlayFanfare in z_message_PAL
    *((u32*)Message_Use_PlayFanfare) = JALINSTR(Patched_PlayWarpSong);
    // Patch instruments in Master Bank
    AudioBank *bank0 = (AudioBank*)(bank_ram_addr[0]);
    bank0->instruments[83] = &Shehnai_Inst; //replacing accordion
    bank0->instruments[85] = &Choir_Inst; //replacing Malon
    // Patch environment sequence config 0x12 (NATURE_ID_12)
    bcopy(PatchedEnv12Chirps, (u8*)0x80102138, sizeof(PatchedEnv12Chirps));
    __osRestoreInt(i);
}

void Statics_AudioRegisterSample(void* ram_addr, s32 cspl)
{
    if(cspl < 0 || cspl >= NUM_CUST_SAMPLES) return;
    SoundFontSound *replaceSound = (SoundFontSound*)(
        bank_ram_addr[cust_sample_bank_idx[cspl]] + sound_replace_offset[cspl]);
    replaceSound->sample = cust_samples[cspl];
    replaceSound->tuning = cust_sample_tuning[cspl];
    cust_samples[cspl]->sampleAddr = (u8*)(InjectRamRomMap(ram_addr));
}

void Statics_AudioRegisterStaticData(void* ram_addr, s32 size, 
    u8 type, s32 data1, s32 data2)
{
    AudioIndex* index;
    if(type == 1) index = &NewAudioseqIndex;
    else if(type == 2) index = &NewAudiobankIndex;
    else if(type == 3){
        Statics_AudioRegisterSample(ram_addr, data1);
        return;
    }else return;
    u8 idx = (data1 >> 24) & 0xFF;
    //Fix counts
    if(index->header.entryCnt <= idx){
        index->header.entryCnt = idx + 1;
    }
    if(type == 1 && gFakeAudioContext.seqTabEntCnt <= idx){
        gFakeAudioContext.seqTabEntCnt = idx + 1;
    }
    //Write data to index
    AudioIndexEntry* entry = &index->entries[idx];
    entry->addr = InjectRamRomMap(ram_addr);
    entry->size = size;
    entry->loadLocation = (data1 >> 16) & 0xFF;
    entry->seqPlayerIdx = (data1 >>  8) & 0xFF;
    if(type == 1){
        u8 numBanks = data1 & 0xFF;
        u8 oldNumBanks = 0x69;
        u16 offset = ((u16*)NewSeqBanksMap)[idx];
        if(offset != 0){
            oldNumBanks = NewSeqBanksMap[offset++];
        }
        if(numBanks == oldNumBanks){
            for(u8 b=0; b<numBanks; ++b){
                NewSeqBanksMap[offset++] = (data2 >> 24) & 0xFF;
                data2 <<= 8;
            }
        }else{
            ((u16*)NewSeqBanksMap)[idx] = SeqBanksMapWriteOffset;
            NewSeqBanksMap[SeqBanksMapWriteOffset++] = numBanks;
            for(u8 b=0; b<numBanks; ++b){
                NewSeqBanksMap[SeqBanksMapWriteOffset++] = (data2 >> 24) & 0xFF;
                data2 <<= 8;
            }
        }
    }else if(type == 2){
        entry->audiotableIdx = data1 & 0xFF;
        entry->unk_0B = 0xFF;
        entry->numInst = (data2 >> 24) & 0xFF;
        entry->numDrum = (data2 >> 16) & 0xFF;
        entry->unk_0E = 0;
        entry->numSfx = (data2 >>  8) & 0xFF;
        //Need to update the copy of metadata in gCtlEntries
        func_800E3034(idx);
    }
}

void Audio_BGMButtonHandler(){
    static u16 bgm_num = 0x6E;
    const u16 holdbtns = BTN_L | BTN_Z | BTN_A;
    if((CTRLR_RAW & holdbtns) != holdbtns) return;
    if((CTRLR_PRESS & BTN_DLEFT)){
        Audio_SetBGM(0x100100FF);
        if(sIsLiveRun) Debugger_Printf("BGM stop");
    }else if((CTRLR_PRESS & BTN_DRIGHT)){
        Audio_SetBGM(bgm_num);
        if(sIsLiveRun) Debugger_Printf("BGM %X play", bgm_num);
    }else if((CTRLR_PRESS & BTN_DUP)){
        --bgm_num;
        if(sIsLiveRun) Debugger_Printf("BGM %X", bgm_num);
    }else if((CTRLR_PRESS & BTN_DDOWN)){
        ++bgm_num;
        if(sIsLiveRun) Debugger_Printf("BGM %X", bgm_num);
    }
}
