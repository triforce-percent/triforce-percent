
#include "HereTogetherBank.h"

/* 0x0 */
AudioBank HereTogetherBank = 
{
    .drums = HereTogetherBank_DrumList,
    .sfx = NULL,
    .instruments = {
        &PanFlute_Inst,
        &Oboe_Inst,
        &Clarinet_Inst,
        &Bassoon_Inst,
        &Horn_Inst,
        &Trumpet_Inst,
        &Trombone_Inst,
        &Tuba_Inst,
        &Glockenspiel_Inst,
        NULL,
        &Strings_Inst,
        &Strings_Inst,
        &Pizzicato_Inst,
        &Piano_Inst,
        &Harp_Inst,
        &Bell_Inst,
    },
};

/* 0x50 */
AudioBankSample PanFlute_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x4686,
    .sampleAddr = (u8*)0x108690,
    .loop = &PanFlute_Loop,
    .book = &PanFlute_Book,
};

/* 0x60 */
AdpcmBook PanFlute_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x5a2, -0x8e7, -0xa17, -0x9ac, -0x82c, -0x619, -0x3e0, -0x1d4,
        0xca3, 0xe54, 0xdbc, 0xb9a, 0x8a8, 0x580, 0x298, 0x39,
        -0x770, -0xda0, -0x120a, -0x1460, -0x148c, -0x12b0, -0xf21, -0xa55,
        0xea7, 0x1367, 0x15ea, 0x1619, 0x1419, 0x1045, 0xb1c, 0x539,
    },
};

/* 0xb0 */
AdpcmLoop PanFlute_Loop = 
{
    .start = 0x76bd,
    .end = 0x7d45,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x43a9, 0x3d82, 0x2592, 0x3f9, -0x1029, -0x1c5c, -0x3162, -0x4a0d,
        -0x5234, -0x49ad, -0x3e88, -0x3ad7, -0x24ef, -0xe0, 0x149a, 0x192e,
    },
};

/* 0xe0 */
AudioBankSample Oboe_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x12a2,
    .sampleAddr = (u8*)0x33a980,
    .loop = &Oboe_Loop,
    .book = &Oboe_Book,
};

/* 0xf0 */
AdpcmBook Oboe_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x73e, -0xbdf, -0xce5, -0xa61, -0x555, 0xa9, 0x5e9, 0x916,
        0xd1c, 0xe3d, 0xb76, 0x5e3, -0xbb, -0x687, -0xa09, -0xa89,
        -0x6f6, -0xc09, -0xec3, -0xf10, -0xd34, -0x9bc, -0x559, -0xc8,
        0xdd6, 0x10f8, 0x1150, 0xf2e, 0xb30, 0x626, 0xe6, -0x3cc,
    },
};

/* 0x140 */
AdpcmLoop Oboe_Loop = 
{
    .start = 0x169b,
    .end = 0x2108,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x2376, 0x17c7, 0x6da, -0x24d, -0x1f8, 0xada, 0x1f90, 0x31e2,
        0x392b, 0x3080, 0x1fb5, 0xa, -0x2ca4, -0x5d31, -0x704a, -0x6ba2,
    },
};

/* 0x170 */
AudioBankSample Clarinet_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0xbec,
    .sampleAddr = (u8*)0x397a60,
    .loop = &Clarinet_Loop,
    .book = &Clarinet_Book,
};

/* 0x180 */
AdpcmBook Clarinet_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x729, -0xcca, -0x1070, -0x11eb, -0x114d, -0xede, -0xb14, -0x67c,
        0xe4a, 0x125e, 0x1406, 0x1355, 0x109d, 0xc61, 0x73f, 0x1de,
        -0x7cf, -0xf08, -0x1554, -0x1a67, -0x1e06, -0x200d, -0x206a, -0x1f24,
        0xf68, 0x15db, 0x1b0e, 0x1ec4, 0x20d7, 0x2137, 0x1fe9, 0x1d09,
    },
};

/* 0x1d0 */
AdpcmLoop Clarinet_Loop = 
{
    .start = 0xd7c,
    .end = 0x1520,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x24e8, 0x258d, 0x284a, 0x2deb, 0x371d, 0x4050, 0x4712, 0x4a19,
        0x4753, 0x3f0b, 0x2fcb, 0x1a79, 0x25c, -0x144d, -0x285d, -0x34e9,
    },
};

/* 0x200 */
AudioBankSample Bassoon_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x14fe,
    .sampleAddr = (u8*)0x33bc30,
    .loop = &Bassoon_Loop,
    .book = &Bassoon_Book,
};

/* 0x210 */
AdpcmBook Bassoon_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x795, -0xeaa, -0x152c, -0x1b0d, -0x2040, -0x24bd, -0x287c, -0x2b7b,
        0xf79, 0x1657, 0x1c8b, 0x2208, 0x26c4, 0x2ab8, 0x2de1, 0x303e,
        -0x7cd, -0xf5d, -0x16aa, -0x1dac, -0x245b, -0x2ab1, -0x30a8, -0x363c,
        0xfc3, 0x173f, 0x1e6f, 0x254a, 0x2bca, 0x31e8, 0x37a1, 0x3cee,
    },
};

/* 0x260 */
AdpcmLoop Bassoon_Loop = 
{
    .start = 0x18bf,
    .end = 0x253d,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        -0x5027, -0x4cd2, -0x48c8, -0x4411, -0x3ebe, -0x3908, -0x32ff, -0x2caa,
        -0x264e, -0x200c, -0x1a13, -0x145e, -0xf1f, -0xa49, -0x5e5, -0x1f2,
    },
};

/* 0x290 */
AudioBankSample Horn_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x795c,
    .sampleAddr = (u8*)0x351810,
    .loop = &Horn_Loop,
    .book = &Horn_Book,
};

/* 0x2a0 */
AdpcmBook Horn_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x7bb, -0xf0d, -0x15d5, -0x1bf6, -0x2157, -0x25e5, -0x298f, -0x2c4c,
        0xf93, 0x1698, 0x1cf0, 0x2281, 0x2738, 0x2b03, 0x2dd8, 0x2fb1,
        -0x7c7, -0xf45, -0x166c, -0x1d2f, -0x2383, -0x295c, -0x2eb2, -0x337c,
        0xfb5, 0x1711, 0x1e07, 0x2489, 0x2a8d, 0x300b, 0x34f8, 0x3950,
    },
};

/* 0x2f0 */
AdpcmLoop Horn_Loop = 
{
    .start = 0x4bd0,
    .end = 0xd7a9,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x1c9, -0x41b, -0xa8b, -0x11b7, -0x192a, -0x2110, -0x2957, -0x31a7,
        -0x3a0d, -0x421b, -0x4a07, -0x5154, -0x57f7, -0x5db8, -0x6278, -0x660b,
    },
};

/* 0x320 */
AudioBankSample Trumpet_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x37de,
    .sampleAddr = (u8*)0x2f9a90,
    .loop = &Trumpet_Loop,
    .book = &Trumpet_Book,
};

/* 0x330 */
AdpcmBook Trumpet_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x765, -0xd23, -0x1082, -0x1131, -0xf49, -0xb45, -0x5e6, -0x10,
        0xe37, 0x11dd, 0x1299, 0x108a, 0xc32, 0x662, 0x12, -0x5c7,
        -0x6b0, -0xbc1, -0xf11, -0x10a8, -0x10af, -0xf66, -0xd1e, -0xa2f,
        0xe0f, 0x1206, 0x13ee, 0x13f5, 0x126c, 0xfb1, 0xc2f, 0x84c,
    },
};

/* 0x380 */
AdpcmLoop Trumpet_Loop = 
{
    .start = 0x58ed,
    .end = 0x6333,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0xa58, 0x1aa, -0x69e, -0xd49, -0x117e, -0x12cc, -0x193c, -0x2378,
        -0x43b3, -0x6f84, -0x7f8d, -0x5f92, -0x37ec, -0xf0b, 0x14f5, 0x2f29,
    },
};

/* 0x3b0 */
AudioBankSample Trombone_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x4c4a,
    .sampleAddr = (u8*)0x2fd270,
    .loop = &Trombone_Loop,
    .book = &Trombone_Book,
};

/* 0x3c0 */
AdpcmBook Trombone_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x6a9, -0xb5c, -0xdd4, -0xe1f, -0xc92, -0x9af, -0x60b, -0x23f,
        0xda5, 0x109b, 0x10f6, 0xf19, 0xba1, 0x742, 0x2b3, -0x171,
        -0x787, -0xe14, -0x133e, -0x16be, -0x186c, -0x1847, -0x166c, -0x1317,
        0xef6, 0x1474, 0x182c, 0x19f5, 0x19ce, 0x17d5, 0x144a, 0xf85,
    },
};

/* 0x410 */
AdpcmLoop Trombone_Loop = 
{
    .start = 0x3e96,
    .end = 0x8785,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0xf75, 0xeba, 0xd41, 0xaaa, 0x73e, 0x340, -0x13d, -0x620,
        -0xb8b, -0x1092, -0x1461, -0x1604, -0x1501, -0x11d0, -0xd4d, -0x79c,
    },
};

/* 0x440 */
AudioBankSample Tuba_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x2f64,
    .sampleAddr = (u8*)0x301ec0,
    .loop = &Tuba_Loop,
    .book = &Tuba_Book,
};

/* 0x450 */
AdpcmBook Tuba_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x5f7, -0xa4e, -0xd5a, -0xf61, -0x109d, -0x113b, -0x1161, -0x112c,
        0xdd2, 0x11e8, 0x14a1, 0x1649, 0x171d, 0x174f, 0x1708, 0x1668,
        -0x7db, -0xf86, -0x16f5, -0x1e1e, -0x24f5, -0x2b72, -0x318c, -0x373b,
        0xfcf, 0x1760, 0x1eaa, 0x25a1, 0x2c3c, 0x3273, 0x383c, 0x3d91,
    },
};

/* 0x4a0 */
AdpcmLoop Tuba_Loop = 
{
    .start = 0x26a8,
    .end = 0x5429,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        -0x3de, -0x35c, -0x2e4, -0x269, -0x1f1, -0x17c, -0x112, -0xa9,
        -0x49, 0xa, 0x43, 0x7b, 0xa5, 0xc1, 0xd0, 0xd1,
    },
};

/* 0x4d0 */
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

/* 0x4e0 */
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

/* 0x530 */
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

/* 0x560 */
AudioBankSample BassDrum1_BassDrum2_BassDrum3_Etc_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x4d98,
    .sampleAddr = (u8*)0x304e30,
    .loop = &BassDrum1_BassDrum2_BassDrum3_Etc_Loop,
    .book = &BassDrum1_BassDrum2_BassDrum3_Etc_Book,
};

/* 0x570 */
AdpcmBook BassDrum1_BassDrum2_BassDrum3_Etc_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x68c, -0xbc5, -0xfcf, -0x12cb, -0x14dd, -0x1623, -0x16bc, -0x16c5,
        0xe63, 0x1352, 0x16f9, 0x1980, 0x1b0f, 0x1bca, 0x1bd5, 0x1b50,
        -0x7bb, -0xf2d, -0x164f, -0x1d1e, -0x2396, -0x29b3, -0x2f72, -0x34d1,
        0xfb3, 0x1715, 0x1e21, 0x24d2, 0x2b25, 0x3117, 0x36a5, 0x3bcd,
    },
};

/* 0x5c0 */
AdpcmLoop BassDrum1_BassDrum2_BassDrum3_Etc_Loop = 
{
    .start = 0x0,
    .end = 0x89f1,
    .count = 0x0,
    .origSpls = 0x0,
};

/* 0x5d0 */
AudioBankSample HeavySnare1_HeavySnare2_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x278e,
    .sampleAddr = (u8*)0x309bd0,
    .loop = &HeavySnare1_HeavySnare2_Loop,
    .book = &HeavySnare1_HeavySnare2_Book,
};

/* 0x5e0 */
AdpcmBook HeavySnare1_HeavySnare2_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x347, -0x381, -0x267, -0x122, -0x3a, 0x38, 0x54, 0x43,
        0x88d, 0x5de, 0x2c5, 0x8f, -0x8a, -0xce, -0xa3, -0x5b,
        -0x34d, -0x47c, -0x4bb, -0x494, -0x446, -0x3ea, -0x38f, -0x338,
        0xadf, 0xb79, 0xb1b, 0xa5b, 0x97e, 0x8a1, 0x7cf, 0x70d,
    },
};

/* 0x630 */
AdpcmLoop HeavySnare1_HeavySnare2_Loop = 
{
    .start = 0x0,
    .end = 0x4651,
    .count = 0x0,
    .origSpls = 0x0,
};

/* 0x640 */
AudioBankSample LightSnare1_LightSnare2_LightSnare3_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x278e,
    .sampleAddr = (u8*)0x30c360,
    .loop = &LightSnare1_LightSnare2_LightSnare3_Loop,
    .book = &LightSnare1_LightSnare2_LightSnare3_Book,
};

/* 0x650 */
AdpcmBook LightSnare1_LightSnare2_LightSnare3_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x34a, -0x385, -0x269, -0x122, -0x38, 0x3b, 0x56, 0x44,
        0x88f, 0x5dd, 0x2c0, 0x88, -0x90, -0xd2, -0xa6, -0x5b,
        -0x345, -0x46f, -0x4ac, -0x484, -0x436, -0x3dd, -0x383, -0x32e,
        0xad8, 0xb6c, 0xb0c, 0xa4d, 0x972, 0x896, 0x7c7, 0x707,
    },
};

/* 0x6a0 */
AdpcmLoop LightSnare1_LightSnare2_LightSnare3_Loop = 
{
    .start = 0x0,
    .end = 0x4651,
    .count = 0x0,
    .origSpls = 0x0,
};

/* 0x6b0 */
AudioBankSample Cymbals1_Cymbals2_Cymbals3_Etc_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x8764,
    .sampleAddr = (u8*)0x30eaf0,
    .loop = &Cymbals1_Cymbals2_Cymbals3_Etc_Loop,
    .book = &Cymbals1_Cymbals2_Cymbals3_Etc_Book,
};

/* 0x6c0 */
AdpcmBook Cymbals1_Cymbals2_Cymbals3_Etc_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x577, -0x5af, -0x22d, 0x19e, 0x32b, 0x231, 0x1d, -0x161,
        0x851, 0x32f, -0x25f, -0x4a4, -0x335, -0x2a, 0x205, 0x236,
        -0x672, -0x966, -0x885, -0x4db, -0x38, 0x397, 0x56a, 0x501,
        0xbab, 0xa93, 0x607, 0x46, -0x475, -0x6b9, -0x637, -0x3a6,
    },
};

/* 0x710 */
AdpcmLoop Cymbals1_Cymbals2_Cymbals3_Etc_Loop = 
{
    .start = 0x0,
    .end = 0xf0b1,
    .count = 0x0,
    .origSpls = 0x0,
};

/* 0x720 */
AudioBankSample Timpani1_Timpani2_Timpani3_Etc_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x83e0,
    .sampleAddr = (u8*)0x317260,
    .loop = &Timpani1_Timpani2_Timpani3_Etc_Loop,
    .book = &Timpani1_Timpani2_Timpani3_Etc_Book,
};

/* 0x730 */
AdpcmBook Timpani1_Timpani2_Timpani3_Etc_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x702, -0xd1d, -0x1266, -0x16f0, -0x1ace, -0x1e10, -0x20c5, -0x22fc,
        0xef8, 0x1501, 0x1a2f, 0x1e99, 0x2251, 0x2569, 0x27f0, 0x29f6,
        -0x16e, -0x110, -0x89, -0x35, -0xf, -0x2, 0x1, 0x1,
        0x5f3, 0x2fe, 0x129, 0x54, 0x9, -0x8, -0x8, -0x4,
    },
};

/* 0x780 */
AdpcmLoop Timpani1_Timpani2_Timpani3_Etc_Loop = 
{
    .start = 0xb0f2,
    .end = 0xea5c,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        -0xc1, -0x36, 0x58, 0xe3, 0x16d, 0x1fb, 0x289, 0x313,
        0x3a0, 0x42f, 0x4bf, 0x54b, 0x5dc, 0x66b, 0x6fd, 0x790,
    },
};

/* 0x7b0 */
AudioBankSample Strings_Low_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x5020,
    .sampleAddr = (u8*)0x31f640,
    .loop = &Strings_Low_Loop,
    .book = &Strings_Low_Book,
};

/* 0x7c0 */
AdpcmBook Strings_Low_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x6c4, -0xc45, -0x1088, -0x139b, -0x1593, -0x168c, -0x16a5, -0x1600,
        0xe82, 0x138c, 0x172f, 0x1983, 0x1aa9, 0x1ac7, 0x1a03, 0x1888,
        -0x76d, -0xe47, -0x1493, -0x1a51, -0x1f87, -0x2436, -0x2865, -0x2c15,
        0xf63, 0x162b, 0x1c5c, 0x21f9, 0x2706, 0x2b87, 0x2f81, 0x32f9,
    },
};

/* 0x810 */
AdpcmLoop Strings_Low_Loop = 
{
    .start = 0x41f2,
    .end = 0x8e53,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        -0x518, -0x31e, -0x163, 0x59, 0x275, 0x506, 0x7c4, 0xae3,
        0xe7b, 0x1220, 0x154b, 0x17c4, 0x1a32, 0x1c95, 0x1f08, 0x218a,
    },
};

/* 0x840 */
AudioBankSample Strings_Norm_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x46aa,
    .sampleAddr = (u8*)0x324660,
    .loop = &Strings_Norm_Loop,
    .book = &Strings_Norm_Book,
};

/* 0x850 */
AdpcmBook Strings_Norm_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x6a0, -0xba4, -0xef8, -0x10aa, -0x10e4, -0xfe1, -0xdec, -0xb50,
        0xe0f, 0x1214, 0x1420, 0x1466, 0x132e, 0x10d0, 0xdaa, 0xa16,
        -0x716, -0xd40, -0x127f, -0x16d8, -0x1a54, -0x1cfd, -0x1ee0, -0x200d,
        0xef5, 0x14e1, 0x19ca, 0x1db8, 0x20b9, 0x22db, 0x242e, 0x24c5,
    },
};

/* 0x8a0 */
AdpcmLoop Strings_Norm_Loop = 
{
    .start = 0x26da,
    .end = 0x7d95,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x4f7, 0x798, 0xb0d, 0xeae, 0x1129, 0x1115, 0xebc, 0xa6b,
        0x66d, 0x2c9, -0x23c, -0x7e5, -0xd89, -0x130f, -0x18a5, -0x1db2,
    },
};

/* 0x8d0 */
AudioBankSample Strings_High_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x3ce4,
    .sampleAddr = (u8*)0x328d10,
    .loop = &Strings_High_Loop,
    .book = &Strings_High_Book,
};

/* 0x8e0 */
AdpcmBook Strings_High_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x6dd, -0xb84, -0xd70, -0xcab, -0x9ba, -0x574, -0xce, 0x353,
        0xd6d, 0xfa9, 0xec4, 0xb56, 0x65b, 0xf1, -0x3e0, -0x750,
        -0x6bf, -0xc17, -0xff9, -0x126e, -0x138f, -0x1381, -0x1275, -0x10a1,
        0xe56, 0x12f1, 0x15db, 0x1731, 0x1721, 0x15e4, 0x13b9, 0x10e2,
    },
};

/* 0x930 */
AdpcmLoop Strings_High_Loop = 
{
    .start = 0x25d2,
    .end = 0x6c2d,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        -0x1b6d, -0x1048, -0x311, 0x73e, 0xc92, 0xf67, 0x1001, 0x10b3,
        0x136d, 0x17ba, 0x1b25, 0x1fa1, 0x21c9, 0x1fe1, 0x1aa3, 0x14d9,
    },
};

/* 0x960 */
AudioBankSample Pizzicato_Norm_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x32bc,
    .sampleAddr = (u8*)0x33d130,
    .loop = &Pizzicato_Norm_Loop,
    .book = &Pizzicato_Norm_Book,
};

/* 0x970 */
AdpcmBook Pizzicato_Norm_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x5a9, -0x9a6, -0xc72, -0xe64, -0xfbb, -0x10a3, -0x113d, -0x119e,
        0xda3, 0x1198, 0x1458, 0x163d, 0x1785, 0x185e, 0x18e7, 0x1938,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    },
};

/* 0x9c0 */
AdpcmLoop Pizzicato_Norm_Loop = 
{
    .start = 0x560d,
    .end = 0x5a19,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x40c, 0x3c1, 0x379, 0x32d, 0x2e4, 0x28f, 0x241, 0x1f0,
        0x19d, 0x152, 0x103, 0xb3, 0x5a, 0xb, -0x45, -0x9e,
    },
};

/* 0x9f0 */
AudioBankSample Pizzicato_High_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x3474,
    .sampleAddr = (u8*)0x3403f0,
    .loop = &Pizzicato_High_Loop,
    .book = &Pizzicato_High_Book,
};

/* 0xa00 */
AdpcmBook Pizzicato_High_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x472, -0x6b8, -0x7b1, -0x7e6, -0x7ac, -0x737, -0x6a6, -0x60c,
        0xc19, 0xdda, 0xe39, 0xdd1, 0xcfe, 0xbf9, 0xae3, 0x9d0,
        -0x79f, -0xebe, -0x1545, -0x1b1e, -0x2037, -0x2482, -0x27f6, -0x2a8e,
        0xf7b, 0x1656, 0x1c79, 0x21d3, 0x2655, 0x29f5, 0x2cae, 0x2e7f,
    },
};

/* 0xa50 */
AdpcmLoop Pizzicato_High_Loop = 
{
    .start = 0x55ee,
    .end = 0x5d2c,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x43, 0x50, 0x55, 0x58, 0x5a, 0x60, 0x5a, 0x50,
        0x45, 0x3b, 0x3b, 0x34, 0x1e, 0x9, -0x6, -0x17,
    },
};

/* 0xa80 */
AudioBankSample Piano_Low_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x79c8,
    .sampleAddr = (u8*)0x2c8510,
    .loop = &Piano_Low_Loop,
    .book = &Piano_Low_Book,
};

/* 0xa90 */
AdpcmBook Piano_Low_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x692, -0xb68, -0xe67, -0xfa2, -0xf4e, -0xdbb, -0xb43, -0x846,
        0xde3, 0x1189, 0x1308, 0x12a3, 0x10b7, 0xdb6, 0xa12, 0x639,
        -0x6db, -0xc9e, -0x115a, -0x1522, -0x1809, -0x1a23, -0x1b85, -0x1c44,
        0xeba, 0x1441, 0x18ab, 0x1c0d, 0x1e81, 0x201f, 0x20fd, 0x2135,
    },
};

/* 0xae0 */
AdpcmLoop Piano_Low_Loop = 
{
    .start = 0xb94a,
    .end = 0xd862,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        -0x806, -0x7a5, -0x66d, -0x561, -0x44f, -0x3d0, -0x394, -0x395,
        -0x3c8, -0x39f, -0x2ad, -0x1ad, -0x36, 0x83, 0x10, -0x191,
    },
};

/* 0xb10 */
AudioBankSample Piano_Norm_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x97b4,
    .sampleAddr = (u8*)0x2cfee0,
    .loop = &Piano_Norm_Loop,
    .book = &Piano_Norm_Book,
};

/* 0xb20 */
AdpcmBook Piano_Norm_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x74f, -0xddc, -0x1398, -0x187b, -0x1c83, -0x1fae, -0x2202, -0x2387,
        0xf2b, 0x1571, 0x1acb, 0x1f34, 0x22ac, 0x2538, 0x26e1, 0x27b3,
        -0x7af, -0xf05, -0x15fc, -0x1c8d, -0x22b4, -0x286d, -0x2db3, -0x3284,
        0xfa4, 0x16e4, 0x1dbb, 0x2423, 0x2a18, 0x2f96, 0x349a, 0x3922,
    },
};

/* 0xb70 */
AdpcmLoop Piano_Norm_Loop = 
{
    .start = 0xc3d2,
    .end = 0x10d93,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x2d9, 0xe8, -0x116, -0x31e, -0x515, -0x6f2, -0x8ba, -0xa5b,
        -0xbce, -0xd20, -0xe44, -0xf48, -0x1024, -0x10e9, -0x118f, -0x1226,
    },
};

/* 0xba0 */
AudioBankSample Piano_High_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x68a0,
    .sampleAddr = (u8*)0x2d96a0,
    .loop = &Piano_High_Loop,
    .book = &Piano_High_Book,
};

/* 0xbb0 */
AdpcmBook Piano_High_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x791, -0xe91, -0x14e3, -0x1a6f, -0x1f22, -0x22f0, -0x25d1, -0x27c2,
        0xf67, 0x1615, 0x1bf3, 0x20eb, 0x24f1, 0x27fc, 0x2a0a, 0x2b1e,
        -0x7d1, -0xf63, -0x16a8, -0x1d94, -0x2418, -0x2a2b, -0x2fc2, -0x34d5,
        0xfc0, 0x1731, 0x1e47, 0x24f3, 0x2b2a, 0x30e3, 0x3615, 0x3ab6,
    },
};

/* 0xc00 */
AdpcmLoop Piano_High_Loop = 
{
    .start = 0xa3e2,
    .end = 0xb9e3,
    .count = 0xffffffff,
    .origSpls = 0x0,
    .state = {
        0x59c, 0x352, 0x108, -0x131, -0x352, -0x54e, -0x71c, -0x8c2,
        -0xa3c, -0xb98, -0xccd, -0xdee, -0xeec, -0xfce, -0x109a, -0x114c,
    },
};

/* 0xc30 */
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

/* 0xc40 */
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

/* 0xc90 */
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

/* 0xcc0 */
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

/* 0xcd0 */
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

/* 0xd20 */
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

/* 0x9f0 */
AudioBankSample Bell_Sample = 
{
    .codec = 0x0,
    .medium = 0x0,
    .unk_bit26 = 0x0,
    .unk_bit25 = 0x0,
    .size = 0x4c4a,
    .sampleAddr = (u8*)0x3e8000,
    .loop = &Bell_Loop,
    .book = &Bell_Book,
};

/* 0xa00 */
AdpcmBook Bell_Book = 
{
    .order = 0x2,
    .npredictors = 0x2,
    .book = {
        -0x761, -0xd98, -0x1238, -0x1504, -0x15e3, -0x14ec, -0x1255, -0xe75,
        0xebb, 0x13c0, 0x16c7, 0x17ba, 0x16ad, 0x13df, 0xfac, 0xa87,
        -0x78f, -0xe7b, -0x149b, -0x19cc, -0x1df6, -0x2108, -0x22fc, -0x23d3,
        0xf54, 0x15cf, 0x1b4e, 0x1fb7, 0x22f7, 0x2508, 0x25eb, 0x25aa,
    },
};

/* 0xa50 */
AdpcmLoop Bell_Loop = 
{
    .start = 0x0,
    .end = 0x87a0,
    .count = 0x0,
    .origSpls = 0x0,
};

AdsrEnvelopePoint PanFlute_Oboe_Clarinet_Etc_Env[4] = 
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

AdsrEnvelopePoint BassDrum1_BassDrum2_BassDrum3_Etc_Env[4] = 
{
    {
        .rate = 0x2,
        .level = 0x7fbc,
    },
    {
        .rate = 0x12a,
        .level = 0x0,
    },
    {
        .rate = 0x1,
        .level = 0x0,
    },
    {
        .rate = -0x1,
        .level = 0x0,
    },
};

AdsrEnvelopePoint Strings_Env[4] = 
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

AdsrEnvelopePoint Pizzicato_Env[4] = 
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

AdsrEnvelopePoint Piano_Env[4] = 
{
    {
        .rate = 0x2,
        .level = 0x7fbc,
    },
    {
        .rate = 0xe5,
        .level = 0x0,
    },
    {
        .rate = 0x1,
        .level = 0x0,
    },
    {
        .rate = -0x1,
        .level = 0x0,
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

AdsrEnvelopePoint Bell_Env[4] = 
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

/* 0xef0 */
Instrument PanFlute_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x7f,
    .releaseRate = 0xef,
    .envelope = PanFlute_Oboe_Clarinet_Etc_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &PanFlute_Sample,
        .tuning = 0.3337100148200989,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};

/* 0xf10 */
Instrument Oboe_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x7f,
    .releaseRate = 0xef,
    .envelope = PanFlute_Oboe_Clarinet_Etc_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &Oboe_Sample,
        .tuning = 0.39684998989105225,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};

/* 0xf30 */
Instrument Clarinet_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x7f,
    .releaseRate = 0xef,
    .envelope = PanFlute_Oboe_Clarinet_Etc_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &Clarinet_Sample,
        .tuning = 0.5,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};

/* 0xf50 */
Instrument Bassoon_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x7f,
    .releaseRate = 0xef,
    .envelope = PanFlute_Oboe_Clarinet_Etc_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &Bassoon_Sample,
        .tuning = 2.3784139156341553,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};

/* 0xf70 */
Instrument Horn_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x7f,
    .releaseRate = 0xef,
    .envelope = PanFlute_Oboe_Clarinet_Etc_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &Horn_Sample,
        .tuning = 1.0,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};

/* 0xf90 */
Instrument Trumpet_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x7f,
    .releaseRate = 0xef,
    .envelope = PanFlute_Oboe_Clarinet_Etc_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &Trumpet_Sample,
        .tuning = 0.5,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};

/* 0xfb0 */
Instrument Trombone_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x7f,
    .releaseRate = 0xef,
    .envelope = PanFlute_Oboe_Clarinet_Etc_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &Trombone_Sample,
        .tuning = 0.6674200296401978,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};

/* 0xfd0 */
Instrument Tuba_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x7f,
    .releaseRate = 0xef,
    .envelope = PanFlute_Oboe_Clarinet_Etc_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &Tuba_Sample,
        .tuning = 3.1748030185699463,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};

/* 0xff0 */
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

/* 0x1010 */
Instrument Strings_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x19,
    .normalRangeHi = 0x28,
    .releaseRate = 0xef,
    .envelope = Strings_Env,
    .lowNotesSound = {
        .sample = &Strings_Low_Sample,
        .tuning = 4.0,
    },
    .normalNotesSound = {
        .sample = &Strings_Norm_Sample,
        .tuning = 1.2599209547042847,
    },
    .highNotesSound = {
        .sample = &Strings_High_Sample,
        .tuning = 0.6299610137939453,
    },
};

/* 0x1050 */
Instrument Pizzicato_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x2b,
    .releaseRate = 0xe1,
    .envelope = Pizzicato_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &Pizzicato_Norm_Sample,
        .tuning = 2.1189260482788086,
    },
    .highNotesSound = {
        .sample = &Pizzicato_High_Sample,
        .tuning = 0.5612310171127319,
    },
};

/* 0x1070 */
Instrument Piano_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x18,
    .normalRangeHi = 0x2c,
    .releaseRate = 0xba,
    .envelope = Piano_Env,
    .lowNotesSound = {
        .sample = &Piano_Low_Sample,
        .tuning = 2.317720890045166,
    },
    .normalNotesSound = {
        .sample = &Piano_Norm_Sample,
        .tuning = 1.0,
    },
    .highNotesSound = {
        .sample = &Piano_High_Sample,
        .tuning = 0.5,
    },
};

/* 0x1090 */
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

/* 0xc80 */
Instrument Bell_Inst = 
{
    .loaded = 0x0,
    .normalRangeLo = 0x0,
    .normalRangeHi = 0x7f,
    .releaseRate = 0xf8,
    .envelope = Bell_Env,
    .lowNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
    .normalNotesSound = {
        .sample = &Bell_Sample,
        .tuning = 0.668f,
    },
    .highNotesSound = {
        .sample = NULL,
        .tuning = 0.0,
    },
};

/* 0x10d0 */
Drum BassDrum1_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.3858463168144226,
    },
};

/* 0x10e0 */
Drum BassDrum2_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.40879026055336,
    },
};

/* 0x10f0 */
Drum BassDrum3_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.4330981969833374,
    },
};

/* 0x1100 */
Drum BassDrum4_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.45885127782821655,
    },
};

/* 0x1110 */
Drum BassDrum5_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.4861360788345337,
    },
};

/* 0x1120 */
Drum BassDrum6_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.5150433778762817,
    },
};

/* 0x1130 */
Drum BassDrum7_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.545669436454773,
    },
};

/* 0x1140 */
Drum BassDrum8_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.5781167149543762,
    },
};

/* 0x1150 */
Drum BassDrum9_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.6124930381774902,
    },
};

/* 0x1160 */
Drum BassDrum10_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.648914098739624,
    },
};

/* 0x1170 */
Drum BassDrum11_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.6875,
    },
};

/* 0x1180 */
Drum BassDrum12_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.7283807992935181,
    },
};

/* 0x1190 */
Drum BassDrum13_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.7716926336288452,
    },
};

/* 0x11a0 */
Drum BassDrum14_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.8175798058509827,
    },
};

/* 0x11b0 */
Drum BassDrum15_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.8661956787109375,
    },
};

/* 0x11c0 */
Drum BassDrum16_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x12,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &BassDrum1_BassDrum2_BassDrum3_Etc_Sample,
        .tuning = 0.9177025556564331,
    },
};

/* 0x11d0 */
Drum HeavySnare1_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x32,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &HeavySnare1_HeavySnare2_Sample,
        .tuning = 1.0,
    },
};

/* 0x11e0 */
Drum HeavySnare2_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x32,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &HeavySnare1_HeavySnare2_Sample,
        .tuning = 1.0594630241394043,
    },
};

/* 0x11f0 */
Drum LightSnare1_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x36,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &LightSnare1_LightSnare2_LightSnare3_Sample,
        .tuning = 1.0594630241394043,
    },
};

/* 0x1200 */
Drum LightSnare2_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x36,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &LightSnare1_LightSnare2_LightSnare3_Sample,
        .tuning = 1.1224620342254639,
    },
};

/* 0x1210 */
Drum LightSnare3_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x36,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &LightSnare1_LightSnare2_LightSnare3_Sample,
        .tuning = 1.1892069578170776,
    },
};

/* 0x1220 */
Drum Cymbals1_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x1c,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Cymbals1_Cymbals2_Cymbals3_Etc_Sample,
        .tuning = 0.6674200296401978,
    },
};

/* 0x1230 */
Drum Cymbals2_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x1c,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Cymbals1_Cymbals2_Cymbals3_Etc_Sample,
        .tuning = 0.7071070075035095,
    },
};

/* 0x1240 */
Drum Cymbals3_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x1c,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Cymbals1_Cymbals2_Cymbals3_Etc_Sample,
        .tuning = 0.7491539716720581,
    },
};

/* 0x1250 */
Drum Cymbals4_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x1c,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Cymbals1_Cymbals2_Cymbals3_Etc_Sample,
        .tuning = 0.7937009930610657,
    },
};

/* 0x1260 */
Drum Cymbals5_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x1c,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Cymbals1_Cymbals2_Cymbals3_Etc_Sample,
        .tuning = 0.8408970236778259,
    },
};

/* 0x1270 */
Drum Cymbals6_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x1c,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Cymbals1_Cymbals2_Cymbals3_Etc_Sample,
        .tuning = 0.8908990025520325,
    },
};

/* 0x1280 */
Drum Cymbals7_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x1c,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Cymbals1_Cymbals2_Cymbals3_Etc_Sample,
        .tuning = 0.9438750147819519,
    },
};

/* 0x1290 */
Drum Cymbals8_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x1c,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Cymbals1_Cymbals2_Cymbals3_Etc_Sample,
        .tuning = 1.0,
    },
};

/* 0x12a0 */
Drum Cymbals9_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x1c,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Cymbals1_Cymbals2_Cymbals3_Etc_Sample,
        .tuning = 1.0594630241394043,
    },
};

/* 0x12b0 */
Drum Cymbals10_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x1c,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Cymbals1_Cymbals2_Cymbals3_Etc_Sample,
        .tuning = 1.1224620342254639,
    },
};

/* 0x12c0 */
Drum Cymbals11_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x1c,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Cymbals1_Cymbals2_Cymbals3_Etc_Sample,
        .tuning = 1.1892069578170776,
    },
};

/* 0x12d0 */
Drum Cymbals12_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x1c,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Cymbals1_Cymbals2_Cymbals3_Etc_Sample,
        .tuning = 1.2599209547042847,
    },
};

/* 0x12e0 */
Drum Timpani1_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.35355299711227417,
    },
};

/* 0x12f0 */
Drum Timpani2_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.37457698583602905,
    },
};

/* 0x1300 */
Drum Timpani3_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.39684998989105225,
    },
};

/* 0x1310 */
Drum Timpani4_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.4204480051994324,
    },
};

/* 0x1320 */
Drum Timpani5_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.44544899463653564,
    },
};

/* 0x1330 */
Drum Timpani6_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.47193700075149536,
    },
};

/* 0x1340 */
Drum Timpani7_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.5,
    },
};

/* 0x1350 */
Drum Timpani8_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.5297319889068604,
    },
};

/* 0x1360 */
Drum Timpani9_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.5612310171127319,
    },
};

/* 0x1370 */
Drum Timpani10_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.5946040153503418,
    },
};

/* 0x1380 */
Drum Timpani11_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.6299610137939453,
    },
};

/* 0x1390 */
Drum Timpani12_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.6674200296401978,
    },
};

/* 0x13a0 */
Drum Timpani13_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.7071070075035095,
    },
};

/* 0x13b0 */
Drum Timpani14_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.7491539716720581,
    },
};

/* 0x13c0 */
Drum Timpani15_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.7937009930610657,
    },
};

/* 0x13d0 */
Drum Timpani16_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.8408970236778259,
    },
};

/* 0x13e0 */
Drum Timpani17_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.8908990025520325,
    },
};

/* 0x13f0 */
Drum Timpani18_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 0.9438750147819519,
    },
};

/* 0x1400 */
Drum Timpani19_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 1.0,
    },
};

/* 0x1410 */
Drum Timpani20_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 1.0594630241394043,
    },
};

/* 0x1420 */
Drum Timpani21_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 1.1224620342254639,
    },
};

/* 0x1430 */
Drum Timpani22_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 1.1892069578170776,
    },
};

/* 0x1440 */
Drum Timpani23_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 1.2599209547042847,
    },
};

/* 0x1450 */
Drum Timpani24_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 1.3348400592803955,
    },
};

/* 0x1460 */
Drum Timpani25_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 1.414214015007019,
    },
};

/* 0x1470 */
Drum Timpani26_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 1.4983069896697998,
    },
};

/* 0x1480 */
Drum Timpani27_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 1.587401032447815,
    },
};

/* 0x1490 */
Drum Timpani28_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 1.681792974472046,
    },
};

/* 0x14a0 */
Drum Timpani29_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 1.781798005104065,
    },
};

/* 0x14b0 */
Drum Timpani30_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 1.8877489566802979,
    },
};

/* 0x14c0 */
Drum Timpani31_Drum = 
{
    .releaseRate = 0xf2,
    .pan = 0x4a,
    .loaded = 0x0,
    .envelope = BassDrum1_BassDrum2_BassDrum3_Etc_Env,
    .sound = {
        .sample = &Timpani1_Timpani2_Timpani3_Etc_Sample,
        .tuning = 2.0,
    },
};

/* 0x14d0*/
Drum* HereTogetherBank_DrumList[64] __attribute__((aligned(16))) = 
{
    &BassDrum1_Drum,
    &BassDrum2_Drum,
    &BassDrum3_Drum,
    &BassDrum4_Drum,
    &BassDrum5_Drum,
    &BassDrum6_Drum,
    &BassDrum7_Drum,
    &BassDrum8_Drum,
    &BassDrum9_Drum,
    &BassDrum10_Drum,
    &BassDrum11_Drum,
    &BassDrum12_Drum,
    &BassDrum13_Drum,
    &BassDrum14_Drum,
    &BassDrum15_Drum,
    &BassDrum16_Drum,
    &HeavySnare1_Drum,
    &HeavySnare2_Drum,
    &LightSnare1_Drum,
    &LightSnare2_Drum,
    &LightSnare3_Drum,
    &Cymbals1_Drum,
    &Cymbals2_Drum,
    &Cymbals3_Drum,
    &Cymbals4_Drum,
    &Cymbals5_Drum,
    &Cymbals6_Drum,
    &Cymbals7_Drum,
    &Cymbals8_Drum,
    &Cymbals9_Drum,
    &Cymbals10_Drum,
    &Cymbals11_Drum,
    &Cymbals12_Drum,
    &Timpani1_Drum,
    &Timpani2_Drum,
    &Timpani3_Drum,
    &Timpani4_Drum,
    &Timpani5_Drum,
    &Timpani6_Drum,
    &Timpani7_Drum,
    &Timpani8_Drum,
    &Timpani9_Drum,
    &Timpani10_Drum,
    &Timpani11_Drum,
    &Timpani12_Drum,
    &Timpani13_Drum,
    &Timpani14_Drum,
    &Timpani15_Drum,
    &Timpani16_Drum,
    &Timpani17_Drum,
    &Timpani18_Drum,
    &Timpani19_Drum,
    &Timpani20_Drum,
    &Timpani21_Drum,
    &Timpani22_Drum,
    &Timpani23_Drum,
    &Timpani24_Drum,
    &Timpani25_Drum,
    &Timpani26_Drum,
    &Timpani27_Drum,
    &Timpani28_Drum,
    &Timpani29_Drum,
    &Timpani30_Drum,
    &Timpani31_Drum,
};
