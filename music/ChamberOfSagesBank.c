#include "ChamberOfSagesBank.h"

#define AUDIOTABLE_01_ROM 0x00079470
#define AUDIOTABLE_2_ROM (AUDIOTABLE_01_ROM + 0x3FA9E0)
#define AUDIOTABLE_3_ROM (AUDIOTABLE_01_ROM + 0x4006B0)
#define AUDIOTABLE_4_ROM (AUDIOTABLE_01_ROM + 0x41D760)
#define AUDIOTABLE_5_ROM (AUDIOTABLE_01_ROM + 0x427D30)
#define AUDIOTABLE_6_ROM (AUDIOTABLE_01_ROM + 0x4377E0)

/* 0x0 */
AudioBank ChamberOfSagesBank = 
{
    .drums = NULL,
    .sfx = NULL,
    .instruments = {
        NULL,
        NULL,
        &Harp_Inst,
        &Glockenspiel_Inst,
        &Soprano_Inst,
        &Soprano_Inst,
        &Alto_Inst,
        &Tenor_Inst,
        &Tenor_Inst,
        NULL,
        &SynStrings_Inst
    },
};

/* 0x140 */
AudioBankSample Harp_Norm_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x3ca6,
    .sampleAddr = (u8*)0x2ef650,
    .loop = &Harp_Norm_Loop,
    .book = &Harp_Norm_Book,
};

/* 0x150 */
AdpcmBook Harp_Norm_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x754, -0xde6, -0x13a7, -0x188c, -0x1c91, -0x1fb3, -0x21f9, -0x2368,
        0xf2d, 0x1575, 0x1ace, 0x1f31, 0x229d, 0x2518, 0x26a9, 0x275c,
        -0x7ca, -0xf52, -0x168c, -0x1d6e, -0x23ee, -0x2a03, -0x2fa5, -0x34ce,
        0xfbc, 0x1728, 0x1e3a, 0x24e7, 0x2b26, 0x30ef, 0x363c, 0x3b05,
    },
};

/* 0x1a0 */
AdpcmLoop Harp_Norm_Loop = 
{
    .start = 0x4a64,
    .end = 0x6bba,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x477, 0x2f1, 0x172, 0xd, -0x146, -0x27f, -0x395, -0x484,
        -0x551, -0x603, -0x692, -0x706, -0x75a, -0x7a7, -0x7e1, -0x80b,
    },
};

/* 0x1d0 */
AudioBankSample Harp_High_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x4530,
    .sampleAddr = (u8*)0x1026f0,
    .loop = &Harp_High_Loop,
    .book = &Harp_High_Book,
};

/* 0x1e0 */
AdpcmBook Harp_High_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x77c, -0xe39, -0x1405, -0x18bb, -0x1c41, -0x1e8c, -0x1f9a, -0x1f76,
        0xf33, 0x1565, 0x1a6e, 0x1e32, 0x20a5, 0x21c6, 0x219f, 0x2048,
        -0x7e7, -0xf91, -0x16de, -0x1daf, -0x23e6, -0x2969, -0x2e23, -0x3202,
        0xfc3, 0x1728, 0x1e0e, 0x2459, 0x29ee, 0x2eb7, 0x32a2, 0x359f,
    },
};

/* 0x230 */
AdpcmLoop Harp_High_Loop = 
{
    .start = 0x5c4a,
    .end = 0x7af0,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        -0x64a, -0x628, -0x5e3, -0x581, -0x4fa, -0x455, -0x392, -0x2b8,
        -0x1c9, -0xc9, 0x34, 0x12d, 0x225, 0x311, 0x3f0, 0x4b7,
    },
};

/* 0x260 */
AudioBankSample Glockenspiel_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x5388,
    .sampleAddr = (u8*)0x2f3300,
    .loop = &Glockenspiel_Loop,
    .book = &Glockenspiel_Book,
};

/* 0x270 */
AdpcmBook Glockenspiel_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x56e, -0x6dd, -0x4fe, -0x1a6, 0x14e, 0x2c4, 0x29d, 0x16d,
        0xa1d, 0x75a, 0x26e, -0x1ec, -0x414, -0x3d9, -0x219, -0xa,
        -0x603, -0xa19, -0xc74, -0xd56, -0xd0d, -0xbe9, -0xa35, -0x834,
        0xd71, 0x1093, 0x11c0, 0x1160, 0xfdb, 0xd97, 0xaeb, 0x824,
    },
};

/* 0x2c0 */
AdpcmLoop Glockenspiel_Loop = 
{
    .start = 0x8788,
    .end = 0x9470,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0xe42, 0xd46, 0xb55, 0x954, 0x7a8, 0x61c, 0x441, 0x151,
        -0x1fd, -0x513, -0x789, -0x8d9, -0x9f4, -0xb94, -0xcfa, -0xe1b,
    },
};

/* 0x20 */
AudioBankSample ChoirPad_Mid_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x74c2,
    .sampleAddr = (u8*)0x2dff40,
    .loop = &ChoirPad_Mid_Loop,
    .book = &ChoirPad_Mid_Book,
};

/* 0x30 */
AdpcmBook ChoirPad_Mid_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x67d, -0xac5, -0xc9b, -0xc2e, -0x9fc, -0x6b1, -0x300, 0x73,
        0xd46, 0xf8a, 0xf04, 0xc4f, 0x83f, 0x3b3, -0x8e, -0x3eb,
        -0x78f, -0xe18, -0x1325, -0x1664, -0x17ac, -0x16fe, -0x1484, -0x108b,
        0xeeb, 0x1444, 0x17b4, 0x190e, 0x1856, 0x15b8, 0x1183, 0xc23,
    },
};

/* 0x80 */
AdpcmLoop ChoirPad_Mid_Loop = 
{
    .start = 0x6e7d,
    .end = 0xcf80,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x104b, 0xeff, 0xf94, 0x14de, 0x1a36, 0x1d2c, 0x1ba4, 0x18fa,
        0x1775, 0x182b, 0x17ea, 0x13bf, 0x93d, -0x469, -0xef4, -0x13bf,
    },
};

/* 0xb0 */
AudioBankSample ChoirPad_High_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x8238,
    .sampleAddr = (u8*)0x2e7410,
    .loop = &ChoirPad_High_Loop,
    .book = &ChoirPad_High_Book,
};

/* 0xc0 */
AdpcmBook ChoirPad_High_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x5fd, -0x8f1, -0x8df, -0x68e, -0x326, 0x34, 0x2a9, 0x3d3,
        0xbf2, 0xbda, 0x8c2, 0x435, -0x46, -0x38e, -0x51b, -0x4f7,
        -0x6b0, -0xbb6, -0xeed, -0x105b, -0x102d, -0xeaa, -0xc2a, -0x90e,
        0xe03, 0x11dc, 0x1392, 0x135b, 0x118b, 0xe8e, 0xad5, 0x6cf,
    },
};

/* 0x110 */
AdpcmLoop ChoirPad_High_Loop = 
{
    .start = 0x6a2d,
    .end = 0xe765,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x942, 0x1352, 0x13ec, 0xb4a, -0xd, -0x487, -0x2b9, 0x151,
        -0x200, -0xbf8, -0x1260, -0xc7c, 0x31c, 0x13fd, 0x1985, 0x1126,
    },
};

/* 0x3a0 */
AudioBankSample Choir_Low_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x5388,
    .sampleAddr = (u8*)0x2af020,
    .loop = &Choir_Low_Loop,
    .book = &Choir_Low_Book,
};

/* 0x3b0 */
AdpcmBook Choir_Low_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x6a9, -0xa62, -0xaa7, -0x7f9, -0x390, 0x113, 0x4a5, 0x659,
        0xc7a, 0xccd, 0x994, 0x448, -0x14b, -0x594, -0x7a0, -0x740,
        -0x619, -0xa69, -0xd20, -0xe77, -0xeb1, -0xe0d, -0xcca, -0xb1e,
        0xda8, 0x1137, 0x12fa, 0x1346, 0x126f, 0x10c6, 0xe95, 0xc1c,
    },
};

/* 0x400 */
AdpcmLoop Choir_Low_Loop = 
{
    .start = 0x542e,
    .end = 0x9470,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x415b, 0x3e30, 0x3e4f, 0x4007, 0x41bf, 0x406e, 0x39d8, 0x2fb2,
        0x2454, 0x1ca7, 0x1934, 0x173b, 0x1266, 0x8b5, -0x42e, -0x10ba,
    },
};

/* 0x430 */
AudioBankSample Choir_Norm_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x5aa2,
    .sampleAddr = (u8*)0x2b43b0,
    .loop = &Choir_Norm_Loop,
    .book = &Choir_Norm_Book,
};

/* 0x440 */
AdpcmBook Choir_Norm_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x689, -0x9f7, -0x9dc, -0x6e6, -0x277, 0x1df, 0x4de, 0x5e6,
        0xc33, 0xc12, 0x872, 0x305, -0x24b, -0x5f6, -0x738, -0x624,
        -0x5d6, -0x9bb, -0xbf9, -0xcdf, -0xcbb, -0xbd9, -0xa78, -0x8d2,
        0xd57, 0x106a, 0x11a5, 0x1175, 0x103e, 0xe5b, 0xc19, 0x9b4,
    },
};

/* 0x490 */
AdpcmLoop Choir_Norm_Loop = 
{
    .start = 0x48d6,
    .end = 0xa102,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x34f, 0x697, 0x1159, 0x1d11, 0x1c2b, 0xd35, -0x2de, -0x925,
        -0x39b, 0x7f9, 0x1119, 0x1191, 0x6d3, -0x7f1, -0xdaf, -0xc62,
    },
};

/* 0x30 */
AudioBankSample SynStrings_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0xb0ce,
    .sampleAddr = (u8*)0x0 + (AUDIOTABLE_6_ROM - AUDIOTABLE_01_ROM),
    .loop = &SynStrings_Loop,
    .book = &SynStrings_Book,
};

/* 0x40 */
AdpcmBook SynStrings_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x75a, -0xdb8, -0x12d8, -0x168e, -0x18c4, -0x197d, -0x18cd, -0x16db,
        0xeee, 0x1481, 0x188a, 0x1af3, 0x1bbc, 0x1afd, 0x18de, 0x159a,
        -0x781, -0xe71, -0x14c0, -0x1a64, -0x1f53, -0x2387, -0x26fd, -0x29b5,
        0xf65, 0x1620, 0x1c23, 0x2165, 0x25e0, 0x2991, 0x2c78, 0x2e97,
    },
};

/* 0x90 */
AdpcmLoop SynStrings_Loop = 
{
    .start = 0x5148,
    .end = 0x13a36,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x1bf4, 0x192b, 0x15b8, 0x11cd, 0xd82, 0x92f, 0x4e4, 0xac,
        -0x36c, -0x756, -0xb09, -0xebb, -0x1220, -0x1570, -0x1880, -0x1b2c,
    },
};

AdsrEnvelopePoint Harp_Env[4] = 
{
    {
        .rate = 0x2,
        .level = 0x7fbc,
    },
    {
        .rate = 0x12a,
        .level = 0x7fbc,
    },
    {
        .rate = 0x7fbc,
        .level = 0x72f6,
    },
    {
        .rate = -0x1,
        .level = 0x0,
    },
};

AdsrEnvelopePoint Glockenspiel_Env[4] = 
{
    {
        .rate = 0x2,
        .level = 0x7fbc,
    },
    {
        .rate = 0x7f,
        .level = 0x15ef,
    },
    {
        .rate = 0x49,
        .level = 0x0,
    },
    {
        .rate = -0x1,
        .level = 0x0,
    },
};

AdsrEnvelopePoint ChoirPad_Env[4] = 
{
    {
        .rate = 0x15,
        .level = 0x7fbc,
    },
    {
        .rate = 0x1,
        .level = 0x7fbc,
    },
    {
        .rate = 0x7fbc,
        .level = 0x72f6,
    },
    {
        .rate = -0x1,
        .level = 0x0,
    },
};

AdsrEnvelopePoint Choir_Env[4] = 
{
    {
        .rate = 0x2,
        .level = 0x7fbc,
    },
    {
        .rate = 0x1,
        .level = 0x7fbc,
    },
    {
        .rate = 0x7fbc,
        .level = 0x72f6,
    },
    {
        .rate = -0x1,
        .level = 0x0,
    },
};

AdsrEnvelopePoint SynStrings_Env[4] = 
{
    {
        .rate = 0x2,
        .level = 0x7fbc,
    },
    {
        .rate = 0x1,
        .level = 0x7fbc,
    },
    {
        .rate = 0x7fbc,
        .level = 0x72f6,
    },
    {
        .rate = -0x1,
        .level = 0x0,
    },
};

Instrument Harp_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x2f,
    .releaseRate = 0xd3,
    .envelope = Harp_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &Harp_Norm_Sample,
        .tuning = 0.75,
    },
    .highNotesSound = {
        .sample = &Harp_High_Sample,
        .tuning = 0.375,
    },
};

Instrument Glockenspiel_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x7f,
    .releaseRate = 0x75,
    .envelope = Glockenspiel_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &Glockenspiel_Sample,
        .tuning = 0.5297319889068604,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};

Instrument Soprano_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x2f,
    .releaseRate = 0xd3,
    .envelope = Choir_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &ChoirPad_Mid_Sample,
        .tuning = 0.5162138938903809,
    },
    .highNotesSound = {
        .sample = &ChoirPad_High_Sample,
        .tuning = 0.36501842737197876,
    },
};

Instrument Alto_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x2c,
    .normalRangeHi = 0x7f,
    .releaseRate = 0xd3,
    .envelope = Choir_Env,
    .lowNotesSound = {
        .sample = &Choir_Norm_Sample,
        .tuning = 0.6890624761581421,
    },
    .normalNotesSound = {
        .sample = &ChoirPad_Mid_Sample,
        .tuning = 0.5162138938903809,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};

Instrument Tenor_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x22,
    .normalRangeHi = 0x7f,
    .releaseRate = 0xd3,
    .envelope = Choir_Env,
    .lowNotesSound = {
        .sample = &Choir_Low_Sample,
        .tuning = 0.9744818210601807,
    },
    .normalNotesSound = {
        .sample = &Choir_Norm_Sample,
        .tuning = 0.6890624761581421,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};

Instrument SynStrings_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x7f,
    .releaseRate = 0xeb,
    .envelope = SynStrings_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &SynStrings_Sample,
        .tuning = 1.0,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};
