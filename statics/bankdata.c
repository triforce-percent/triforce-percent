// Intended to be included from audio.c

AdpcmBook Choir_Norm_Book = {
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x67d, -0xac5, -0xc9b, -0xc2e, -0x9fc, -0x6b1, -0x300, 0x73,
        0xd46, 0xf8a, 0xf04, 0xc4f, 0x83f, 0x3b3, -0x8e, -0x3eb,
        -0x78f, -0xe18, -0x1325, -0x1664, -0x17ac, -0x16fe, -0x1484, -0x108b,
        0xeeb, 0x1444, 0x17b4, 0x190e, 0x1856, 0x15b8, 0x1183, 0xc23,
    },
};

AdpcmLoop Choir_Norm_Loop = {
    .start = 0x6e7d,
    .end = 0xcf80,
    .count = 0xffffffff,
    .unk_0C = {0,0,0,0},
    .state = {
        0x104b, 0xeff, 0xf94, 0x14de, 0x1a36, 0x1d2c, 0x1ba4, 0x18fa,
        0x1775, 0x182b, 0x17ea, 0x13bf, 0x93d, -0x469, -0xef4, -0x13bf,
    },
};

SoundFontSample Choir_Norm_Sample = {
    .codec = 0x0,
    .medium = 0x2,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x1,
    .size = 0x74c2,
    .sampleAddr = (u8*)(0x2dff40 + AUDIOTABLE_01_ROM),
    .loop = &Choir_Norm_Loop,
    .book = &Choir_Norm_Book,
};

AdpcmBook Choir_High_Book = {
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x5fd, -0x8f1, -0x8df, -0x68e, -0x326, 0x34, 0x2a9, 0x3d3,
        0xbf2, 0xbda, 0x8c2, 0x435, -0x46, -0x38e, -0x51b, -0x4f7,
        -0x6b0, -0xbb6, -0xeed, -0x105b, -0x102d, -0xeaa, -0xc2a, -0x90e,
        0xe03, 0x11dc, 0x1392, 0x135b, 0x118b, 0xe8e, 0xad5, 0x6cf,
    },
};

AdpcmLoop Choir_High_Loop = {
    .start = 0x6a2d,
    .end = 0xe765,
    .count = 0xffffffff,
    .unk_0C = {0,0,0,0},
    .state = {
        0x942, 0x1352, 0x13ec, 0xb4a, -0xd, -0x487, -0x2b9, 0x151,
        -0x200, -0xbf8, -0x1260, -0xc7c, 0x31c, 0x13fd, 0x1985, 0x1126,
    },
};

SoundFontSample Choir_High_Sample = {
    .codec = 0x0,
    .medium = 0x2,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x1,
    .size = 0x8238,
    .sampleAddr = (u8*)(0x2e7410 + AUDIOTABLE_01_ROM),
    .loop = &Choir_High_Loop,
    .book = &Choir_High_Book,
};


AdsrEnvelopePoint Choir_Env[4] = {
    { .rate = 0x15, .level = 0x7fbc, },
    { .rate = 0x1, .level = 0x7fbc, },
    { .rate = 0x7fbc, .level = 0x72f6, },
    { .rate = -0x1, .level = 0x0, },
};

Instrument Choir_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x2d,
    .releaseRate = 0xd3,
    .envelope = Choir_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &Choir_Norm_Sample,
        .tuning = 0.5162138938903809,
    },
    .highNotesSound = {
        .sample = &Choir_High_Sample,
        .tuning = 0.36501842737197876,
    },
};

AdpcmBook Shehnai_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x6ef, -0xc09, -0xee2, -0xf68, -0xdd9, -0xab0, -0x68d, -0x21d,
        0xde3, 0x112c, 0x11c7, 0xffb, 0xc55, 0x790, 0x270, -0x252,
        -0x714, -0xcfd, -0x118e, -0x14b6, -0x1673, -0x16db, -0x160d, -0x143a,
        0xead, 0x13d6, 0x1767, 0x195e, 0x19d3, 0x18eb, 0x16da, 0x13de,
    },
};

AdpcmLoop Shehnai_Loop = 
{
    .start = 0x42cf,
    .end = 0x55bf,
    .count = 0xffffffff,
    .unk_0C = {0,0,0,0},
    .state = {
        0x79e, 0xbdd, 0x5fe, 0x81f, 0x8e9, -0x1394, -0x41b4, -0x5914,
        -0x5daf, -0x5d6c, -0x5505, -0x46a3, -0x38e7, -0x2d9c, -0x19d5, -0x151,
    },
};

SoundFontSample Shehnai_Sample = 
{
    .codec = 0x0,
    .medium = 0x2,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x1,
    .size = 0x3046,
    .sampleAddr = (u8*)(0xb0d0 + AUDIOTABLE_6_ROM),
    .loop = &Shehnai_Loop,
    .book = &Shehnai_Book,
};

AdsrEnvelopePoint Shehnai_Env[4] = 
{
    { .rate = 0x2, .level = 0x7fbc, },
    { .rate = 0x1, .level = 0x7fbc, },
    { .rate = 0x7fbc, .level = 0x72f6, },
    { .rate = -0x1, .level = 0x0, },
};

Instrument Shehnai_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x7f,
    .releaseRate = 0xf6,
    .envelope = Shehnai_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &Shehnai_Sample,
        .tuning = 0.44544899463653564,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};
