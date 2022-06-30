#ifndef _Z64AUDIOCOMPAT_H_
#define _Z64AUDIOCOMPAT_H_

typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
    /* 0x08 */ u32 count;
    /* 0x0C */ u8  unk_0C[4];
    /* 0x10 */ s16 state[]; // elements: count != 0 ? 16 : 0.
} AdpcmLoop __attribute__((aligned(16))); // size = 0x10 or 0x30

typedef struct {
    /* 0x00 */ s32 order;
    /* 0x04 */ s32 npredictors;
    /* 0x08 */ s16 book[]; // elements: 8 * order * npredictors
} AdpcmBook __attribute__((aligned(16)));

typedef struct {
    /* 0x00 */ u32 codec : 4;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 unk_bit26 : 1;
    /* 0x00 */ u32 unk_bit25 : 1;
    /* 0x01 */ u32 size : 24;
    /* 0x04 */ u8* sampleAddr;
    /* 0x08 */ AdpcmLoop* loop;
    /* 0x0C */ AdpcmBook* book;
} SoundFontSample __attribute__((aligned(16))); // size = 0x10

typedef struct {
    /* 0x00 */ SoundFontSample* sample;
    /* 0x04 */ f32 tuning; // frequency scale factor
} SoundFontSound; // size = 0x8

typedef struct {
    /* 0x0 */ s16 rate;
    /* 0x2 */ s16 level;
} AdsrEnvelopePoint; // size = 0x4

typedef struct {
    /*?0x00 */ u8 loaded;
    /* 0x01 */ u8 normalRangeLo;
    /* 0x02 */ u8 normalRangeHi;
    /* 0x03 */ u8 releaseRate;
    /* 0x04 */ AdsrEnvelopePoint* envelope;
    /* 0x08 */ SoundFontSound lowNotesSound;
    /* 0x10 */ SoundFontSound normalNotesSound;
    /* 0x18 */ SoundFontSound highNotesSound;
} Instrument; // size >= 0x20

typedef struct {
    /* 0x00 */ u8 releaseRate;
    /* 0x01 */ u8 pan;
    /* 0x02 */ u8 loaded;
    /* 0x04 */ SoundFontSound sound;
    /* 0x14 */ AdsrEnvelopePoint* envelope;
} Drum; // size >= 0x14

typedef struct {
    Drum** drums; //size of array-of-pointers is numDrum
    SoundFontSound* sfx; //size of array is numSfx;
    Instrument* instruments[]; //size of array is numInst
} AudioBank;

#endif // _Z64AUDIOCOMPAT_H_
