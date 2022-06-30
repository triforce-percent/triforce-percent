#include "ultra64.h"
#include "global.h"

s16 BotWZeldaMeshYouaskedAnimFrameData[3256] = {
	0x0000, 0x0439, 0xbdf5, 0xac15, 0x0035, 0xbfff, 0xffff, 0x8000, 0x3fbc, 0x0106, 0xbffe, 0xffd3, 0x6dac, 0x0348, 0x01af, 0xf6a1, 
	0xf704, 0xf719, 0xf74e, 0xf792, 0xf7c9, 0xf7ca, 0xf73d, 0xf527, 0xebb4, 0x1c02, 0x0679, 0x02c1, 0x018e, 0x0115, 0x00e1, 0x00c9, 
	0x00bb, 0x00ad, 0x0099, 0x007b, 0x004c, 0x0019, 0xfff0, 0xffd3, 0xffbe, 0xffb0, 0xffa8, 0xffa4, 0xffa3, 0xffa4, 0xffa7, 0xffab, 
	0xffaf, 0xffb3, 0xffb6, 0xffb7, 0xffb7, 0xffb5, 0xffb1, 0xffae, 0xffab, 0xffaa, 0xffac, 0xffbc, 0xffe9, 0x0051, 0x0134, 0x0354, 
	0x0a5c, 0xc2b4, 0xedb8, 0xf385, 0xf568, 0xf63a, 0xf69e, 0xf6cf, 0xf6e7, 0xf6f3, 0xf6fb, 0xf704, 0xf70e, 0xf714, 0xf717, 0xf718, 
	0xf717, 0xf714, 0xf70f, 0xf709, 0xf701, 0xf6f7, 0xf6ed, 0xf6e2, 0xf6d5, 0xf6c8, 0xf6bb, 0xf6ad, 0xf69f, 0xf691, 0xf684, 0xf678, 
	0xf66e, 0xf666, 0xf660, 0xf65f, 0xf662, 0xf66c, 0xf67c, 0xf696, 0xf6b9, 0xf6e6, 0xf71a, 0xf754, 0xf794, 0xf7d9, 0xf823, 0xf870, 
	0xf8c0, 0xf911, 0xf963, 0xf9b4, 0xfa03, 0xfa4f, 0xfa96, 0xfad9, 0xfb15, 0xfb4a, 0xfb78, 0xfb9c, 0xfbb7, 0xfbc7, 0xfbcd, 0xfbcd, 
	0xfbcd, 0xfbcd, 0xfbcd, 0xfbcd, 0xfbcd, 0xfbcd, 0xfbcd, 0xfbcd, 0xd9fc, 0xd987, 0xd836, 0xd61f, 0xd357, 0xcff3, 0xcc10, 0xc7d1, 
	0xc372, 0xbded, 0xb9b9, 0xb55c, 0xb138, 0xad66, 0xa9f4, 0xa6ef, 0xa462, 0xa255, 0xa0d2, 0x9fe1, 0x9f8e, 0x9f8d, 0x9f8d, 0x9f8e, 
	0x9f90, 0x9f93, 0x9f95, 0x9f98, 0x9f9b, 0x9f9e, 0x9fa5, 0x9fb5, 0x9fd1, 0x9fff, 0xa043, 0xa0a2, 0xa121, 0xa1c3, 0xa28e, 0xa385, 
	0xa4af, 0xa637, 0xa83f, 0xaabc, 0xada2, 0xb0e2, 0xb46c, 0xb82c, 0xbbfc, 0xc173, 0xc47d, 0xc843, 0xcbe8, 0xcf49, 0xd252, 0xd4ee, 
	0xd710, 0xd8a7, 0xd9a6, 0xd9fc, 0xd9f2, 0xd9d6, 0xd9ab, 0xd972, 0xd92b, 0xd8d7, 0xd878, 0xd80d, 0xd798, 0xd71b, 0xd695, 0xd608, 
	0xd574, 0xd4db, 0xd43e, 0xd39d, 0xd2fa, 0xd255, 0xd1b0, 0xd10b, 0xd067, 0xcfc5, 0xcf26, 0xce8b, 0xcdf6, 0xcd66, 0xccdd, 0xcc5b, 
	0xcbe3, 0xcb74, 0xcb0e, 0xcab1, 0xca5d, 0xca11, 0xc9cc, 0xc98f, 0xc959, 0xc92a, 0xc901, 0xc8dd, 0xc8bf, 0xc8a5, 0xc890, 0xc87f, 
	0xc872, 0xc868, 0xc860, 0xc85b, 0xc858, 0xc857, 0xc856, 0xc856, 0xc856, 0xc856, 0xc856, 0xc856, 0xc856, 0xc856, 0xc856, 0xc856, 
	0xff7a, 0xffaf, 0x0046, 0x0130, 0x026a, 0x0402, 0x062f, 0x09cf, 0x1496, 0xe549, 0xfb61, 0xff58, 0x00b4, 0x0143, 0x017f, 0x0196, 
	0x01a0, 0x01aa, 0x01c1, 0x01ed, 0x0239, 0x02a8, 0x032d, 0x03bc, 0x0449, 0x04cb, 0x0536, 0x057e, 0x0599, 0x0596, 0x058a, 0x0575, 
	0x0557, 0x052f, 0x04fd, 0x04bf, 0x0475, 0x041e, 0x03b9, 0x0343, 0x02bc, 0x0223, 0x017a, 0x00b7, 0xffce, 0xfea5, 0xfcfb, 0xfa11, 
	0xf23e, 0x391d, 0x0d54, 0x06c9, 0x0430, 0x02b4, 0x01b4, 0x00f8, 0x0069, 0xfffc, 0xffad, 0xff7a, 0xff57, 0xff39, 0xff20, 0xff0c, 
	0xfefc, 0xfef0, 0xfee7, 0xfee3, 0xfee1, 0xfee3, 0xfee8, 0xfeef, 0xfef9, 0xff06, 0xff14, 0xff24, 0xff36, 0xff48, 0xff5b, 0xff6f, 
	0xff82, 0xff94, 0xffa3, 0xffb1, 0xffba, 0xffbe, 0xffbc, 0xffb1, 0xff9e, 0xff83, 0xff64, 0xff42, 0xff1c, 0xfef3, 0xfec8, 0xfe9a, 
	0xfe6b, 0xfe3a, 0xfe09, 0xfdd9, 0xfdaa, 0xfd7d, 0xfd52, 0xfd2b, 0xfd08, 0xfce9, 0xfccf, 0xfcba, 0xfcab, 0xfca2, 0xfc9e, 0xfc9e, 
	0xfc9e, 0xfc9e, 0xfc9e, 0xfc9e, 0xfc9e, 0xfc9e, 0xfc9e, 0xfc9e, 0x5d47, 0x5d47, 0x5d48, 0x5d48, 0x5d48, 0x5d48, 0x5d48, 0x5d48, 
	0x5d48, 0x5d48, 0x5db6, 0x5ea8, 0x5f99, 0x6007, 0x5ea8, 0x5d48, 0x5d83, 0x5e3b, 0x5f2d, 0x6000, 0x605a, 0x5f13, 0x5cb2, 0x5b6a, 
	0x5c53, 0x5e04, 0x5eed, 0x5e2e, 0x5ccc, 0x5c0d, 0x5cbe, 0x5e44, 0x5fca, 0x607b, 0x602b, 0x5f62, 0x5e58, 0x5d48, 0x5c6f, 0x5bda, 
	0x5b7e, 0x5b4b, 0x5b37, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 
	0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 
	0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 
	0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 
	0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 0x5b33, 
	0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 
	0xbfff, 0xbfae, 0xbefe, 0xbe50, 0xbe02, 0xbe84, 0xbf79, 0xbfff, 0xbf54, 0xbe1c, 0xbd78, 0xbe1c, 0xbf54, 0xbfff, 0xbf9b, 0xbebd, 
	0xbde0, 0xbd7b, 0xbd9b, 0xbdf1, 0xbe71, 0xbf0b, 0xbfb3, 0xc05c, 0xc0f6, 0xc175, 0xc1cc, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 
	0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 
	0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 
	0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 
	0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 
	0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 
	0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x9496, 0x938f, 0x9289, 0x9211, 0x92d7, 0x9448, 0x950e, 
	0x93cd, 0x9178, 0x9037, 0x9178, 0x93cd, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 
	0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 
	0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 
	0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 
	0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 
	0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 0x950e, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0xffff, 0x0000, 
	0x0000, 0x0002, 0x0003, 0xffff, 0xfffb, 0x0001, 0x0003, 0x0000, 0x0007, 0x0004, 0xfff9, 0x0004, 0x0007, 0x0000, 0x0000, 0xffff, 
	0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0xffff, 0x0000, 0xffff, 0x0000, 
	0x0000, 0xffff, 0x0000, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0x0000, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 
	0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfff, 0xbfae, 0xbefe, 0xbe50, 0xbe02, 0xbe84, 0xbf79, 0xbfff, 
	0xbf54, 0xbe1c, 0xbd78, 0xbe1c, 0xbf54, 0xbfff, 0xbf9b, 0xbebd, 0xbde0, 0xbd7b, 0xbd9b, 0xbdf1, 0xbe71, 0xbf0b, 0xbfb3, 0xc05c, 
	0xc0f6, 0xc175, 0xc1cc, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 
	0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 
	0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 
	0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 
	0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 0xc1ec, 
	0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 
	0x6af1, 0x6b7a, 0x6ca6, 0x6dd2, 0x6e5a, 0x6d78, 0x6bd4, 0x6af1, 0x6c32, 0x6e85, 0x6fc5, 0x6e85, 0x6c32, 0x6af1, 0x6af1, 0x6af1, 
	0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 
	0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 
	0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 
	0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 
	0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 
	0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0x6af1, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0xffff, 0xffff, 0xfffc, 0xfffb, 0x0000, 0x0004, 0xfffd, 0xfffb, 0x0000, 
	0xfff8, 0xfffb, 0x0006, 0xfffb, 0xfff8, 0xffff, 0x0000, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0xffff, 0xffff, 
	0x0000, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 
	0xffff, 0xffff, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0xffff, 
	0xffff, 0xffff, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0xffff, 
	0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0xffff, 0x0000, 0xffff, 0xffff, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 
	0xffff, 0x0000, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xa3e3, 0xa3e2, 0xa3e2, 0xa3e3, 0xa3e2, 0xa3e3, 0xa3e3, 0xa3e3, 0xa3e3, 0xa3e3, 0xa3e2, 0xa3e3, 0xa3e3, 0xa3e3, 0xa3e2, 0xa3e3, 
	0xa3e3, 0xa3e2, 0xa3e3, 0xa3e3, 0xa3e3, 0xa3e3, 0xa3e3, 0xa3e3, 0xa3e2, 0xa3e3, 0xa3e2, 0xa3e3, 0xa3e2, 0xa3e2, 0xa3e2, 0xa3e3, 
	0xa3e3, 0xa3e2, 0xa413, 0xa496, 0xa558, 0xa644, 0xa744, 0xa845, 0xa930, 0xa9f2, 0xaa76, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 
	0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 
	0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 
	0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 
	0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 
	0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0xaaa6, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 
	0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 0x7727, 
	0x7727, 0x7727, 0x7727, 0x7726, 0x7724, 0x7722, 0x771f, 0x771b, 0x7717, 0x7712, 0x770d, 0x7708, 0x7702, 0x76fc, 0x76f5, 0x76ef, 
	0x76e8, 0x76e1, 0x76db, 0x76d4, 0x76cd, 0x76c6, 0x76bf, 0x76b9, 0x76b2, 0x76ac, 0x76a6, 0x76a0, 0x769a, 0x7694, 0x768f, 0x768a, 
	0x7685, 0x7681, 0x767d, 0x7679, 0x7675, 0x7672, 0x766f, 0x766d, 0x766b, 0x7669, 0x7667, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 
	0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 
	0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 
	0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 0x7666, 
	0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 
	0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4aa, 0xf4ab, 0xf4ac, 0xf4ae, 0xf4b0, 0xf4b3, 
	0xf4b6, 0xf4b9, 0xf4bd, 0xf4c1, 0xf4c5, 0xf4ca, 0xf4ce, 0xf4d3, 0xf4d8, 0xf4dd, 0xf4e3, 0xf4e8, 0xf4ed, 0xf4f2, 0xf4f7, 0xf4fd, 
	0xf502, 0xf507, 0xf50c, 0xf510, 0xf515, 0xf519, 0xf51d, 0xf521, 0xf525, 0xf529, 0xf52c, 0xf52f, 0xf532, 0xf534, 0xf537, 0xf539, 
	0xf53a, 0xf53c, 0xf53d, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 
	0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 
	0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 
	0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0xf53e, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 
	0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 0x0737, 
	0x0737, 0x0737, 0x0738, 0x073c, 0x0743, 0x074c, 0x0758, 0x0766, 0x0776, 0x0788, 0x079b, 0x07b0, 0x07c6, 0x07dd, 0x07f6, 0x080f, 
	0x0828, 0x0843, 0x085d, 0x0878, 0x0893, 0x08ae, 0x08c8, 0x08e3, 0x08fd, 0x0916, 0x092f, 0x0947, 0x095e, 0x0975, 0x098a, 0x099f, 
	0x09b2, 0x09c4, 0x09d5, 0x09e5, 0x09f4, 0x0a01, 0x0a0d, 0x0a17, 0x0a20, 0x0a28, 0x0a2e, 0x0a32, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 
	0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 
	0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 
	0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 0x0a35, 
	0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 
	0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0e, 0x0f0f, 0x0f11, 0x0f13, 0x0f16, 0x0f19, 
	0x0f1d, 0x0f21, 0x0f25, 0x0f29, 0x0f2d, 0x0f31, 0x0f34, 0x0f37, 0x0f3a, 0x0f3c, 0x0f3e, 0x0f3f, 0x0f3f, 0x0f3f, 0x0f3e, 0x0f3c, 
	0x0f39, 0x0f36, 0x0f32, 0x0f2d, 0x0f28, 0x0f22, 0x0f1c, 0x0f15, 0x0f0e, 0x0f07, 0x0f00, 0x0ef9, 0x0ef2, 0x0eeb, 0x0ee4, 0x0ede, 
	0x0ed9, 0x0ed4, 0x0ed0, 0x0ece, 0x0ecc, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 
	0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 
	0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 
	0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0x0ecb, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 
	0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 
	0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdb, 0xfbdb, 0xfbda, 0xfbd9, 0xfbd8, 0xfbd7, 0xfbd6, 0xfbd4, 0xfbd3, 0xfbd1, 0xfbcf, 
	0xfbcd, 0xfbca, 0xfbc8, 0xfbc5, 0xfbc2, 0xfbbf, 0xfbbc, 0xfbb8, 0xfbb5, 0xfbb1, 0xfbad, 0xfba9, 0xfba5, 0xfba1, 0xfb9d, 0xfb99, 
	0xfb95, 0xfb91, 0xfb8e, 0xfb8a, 0xfb86, 0xfb83, 0xfb80, 0xfb7d, 0xfb7b, 0xfb79, 0xfb77, 0xfb76, 0xfb76, 0xfb75, 0xfb75, 0xfb75, 
	0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 
	0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 
	0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 0xfb75, 
	0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 
	0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fb, 0xf2fc, 0xf2fd, 0xf2fe, 0xf300, 
	0xf302, 0xf304, 0xf306, 0xf308, 0xf30b, 0xf30d, 0xf310, 0xf313, 0xf316, 0xf319, 0xf31d, 0xf320, 0xf323, 0xf327, 0xf32a, 0xf32d, 
	0xf331, 0xf334, 0xf337, 0xf33a, 0xf33e, 0xf341, 0xf344, 0xf347, 0xf349, 0xf34c, 0xf34f, 0xf351, 0xf353, 0xf355, 0xf357, 0xf359, 
	0xf35a, 0xf35b, 0xf35c, 0xf35d, 0xf35d, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 
	0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 
	0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 
	0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xf35e, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 
	0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 0xfabf, 
	0xfabf, 0xfabf, 0xfac0, 0xfac1, 0xfac2, 0xfac4, 0xfac7, 0xfaca, 0xfacd, 0xfad1, 0xfad5, 0xfad9, 0xfadd, 0xfae1, 0xfae6, 0xfaeb, 
	0xfaef, 0xfaf3, 0xfaf8, 0xfafc, 0xfb00, 0xfb04, 0xfb07, 0xfb0b, 0xfb0e, 0xfb11, 0xfb13, 0xfb15, 0xfb17, 0xfb19, 0xfb1b, 0xfb1c, 
	0xfb1d, 0xfb1d, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 
	0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 
	0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 
	0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 0xfb1e, 
	0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 
	0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 
	0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a03, 0x8a16, 0x8a4c, 
	0x8aa2, 0x8b18, 0x8bac, 0x8c5e, 0x8d2c, 0x8e13, 0x8f0e, 0x9017, 0x9128, 0x9236, 0x9338, 0x9425, 0x94f4, 0x959c, 0x9614, 0x9655, 
	0x9656, 0x960e, 0x9573, 0x945b, 0x9296, 0x9021, 0x8d24, 0x89f2, 0x86ea, 0x8462, 0x8291, 0x8199, 0x818c, 0x820e, 0x82b1, 0x836c, 
	0x8437, 0x850b, 0x85e6, 0x86c2, 0x879f, 0x8877, 0x894a, 0x8a11, 0x8aca, 0x8b6e, 0x8bf8, 0x8c61, 0x8ca3, 0x8ccb, 0x8ceb, 0x8d04, 
	0x8d18, 0x8d27, 0x8d31, 0x8d38, 0x8d3a, 0x8d38, 0x8d31, 0x8d24, 0x8d0f, 0x8cee, 0x8cbe, 0x8c84, 0x8c74, 0x8cca, 0x8d6a, 0x8ddf, 
	0x8db8, 0x8cd4, 0x8bb5, 0x8ae4, 0x8a59, 0x89fe, 0x89cc, 0x89c0, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 
	0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 
	0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 
	0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x094a, 0x095f, 0x099d, 0x0a02, 0x0a8c, 0x0b35, 0x0bf9, 0x0ccd, 0x0dab, 0x0e8c, 0x0f69, 
	0x103d, 0x1108, 0x11c9, 0x1284, 0x133b, 0x13f4, 0x14b5, 0x1584, 0x1664, 0x175a, 0x1865, 0x196b, 0x1a33, 0x1a8c, 0x1a51, 0x1974, 
	0x1809, 0x163d, 0x1446, 0x125c, 0x10b2, 0x0f30, 0x0da5, 0x0c15, 0x0a84, 0x08f5, 0x076f, 0x05f4, 0x048b, 0x0338, 0x01fc, 0x00db, 
	0xffd3, 0xfee7, 0xfe16, 0xfd5f, 0xfcc4, 0xfc4a, 0xfbf0, 0xfbad, 0xfb7a, 0xfb4f, 0xfb24, 0xfaf0, 0xfaad, 0xfa51, 0xf9d4, 0xf930, 
	0xf85c, 0xf74f, 0xf5ff, 0xf569, 0xf692, 0xf943, 0xfcd6, 0x006f, 0x0371, 0x05b1, 0x070f, 0x07bf, 0x0825, 0x0879, 0x08bd, 0x08d7, 
	0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 
	0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 
	0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x097f, 0x09bc, 0x0a62, 
	0x0b56, 0x0c79, 0x0db3, 0x0ef3, 0x102a, 0x114e, 0x1255, 0x1332, 0x13df, 0x144f, 0x1477, 0x144d, 0x13c8, 0x12dd, 0x1184, 0x0fb4, 
	0x0d66, 0x0a93, 0x0732, 0x0332, 0xfe8e, 0xf964, 0xf3ea, 0xee72, 0xe94d, 0xe4c3, 0xe108, 0xde4c, 0xdcbf, 0xdbef, 0xdb41, 0xdaac, 
	0xda23, 0xd99c, 0xd913, 0xd885, 0xd7f3, 0xd760, 0xd6d4, 0xd655, 0xd5f0, 0xd5ae, 0xd59c, 0xd5c6, 0xd635, 0xd6ac, 0xd6f3, 0xd71e, 
	0xd73b, 0xd758, 0xd783, 0xd7c9, 0xd837, 0xd8d7, 0xd9b3, 0xdad1, 0xdc33, 0xddd5, 0xdfaf, 0xe2c2, 0xe791, 0xed4e, 0xf31f, 0xf839, 
	0xfbf0, 0xfdc4, 0xff1a, 0x017e, 0x044b, 0x06ce, 0x089a, 0x0959, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 
	0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 
	0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 
	0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd7, 0xffd6, 0xffd2, 0xffcd, 0xffc6, 0xffbf, 0xffb8, 0xffb1, 0xffab, 0xffa5, 0xff9f, 
	0xff9a, 0xff96, 0xff92, 0xff8f, 0xff8d, 0xff8b, 0xff8a, 0xff89, 0xff88, 0xff88, 0xff88, 0xff89, 0xff8a, 0xff8c, 0xff8f, 0xff94, 
	0xff99, 0xff9f, 0xffa5, 0xffaa, 0xffad, 0xffaf, 0xffb0, 0xffb0, 0xffb1, 0xffb2, 0xffb2, 0xffb3, 0xffb3, 0xffb4, 0xffb5, 0xffb6, 
	0xffb6, 0xffb6, 0xffb6, 0xffb5, 0xffb3, 0xffb2, 0xffb1, 0xffb1, 0xffb2, 0xffb3, 0xffb4, 0xffb5, 0xffb5, 0xffb5, 0xffb5, 0xffb4, 
	0xffb3, 0xffb2, 0xffb0, 0xffad, 0xffa8, 0xffa5, 0xffa3, 0xffa5, 0xffaa, 0xffb6, 0xffc4, 0xffcc, 0xffd1, 0xffd5, 0xffd7, 0xffd8, 
	0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 
	0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 
	0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1252, 0x1253, 0x1254, 
	0x1256, 0x1259, 0x125c, 0x1261, 0x1265, 0x126a, 0x1270, 0x1276, 0x127c, 0x1282, 0x1288, 0x128d, 0x1293, 0x1297, 0x129b, 0x129e, 
	0x12a0, 0x12a1, 0x12a0, 0x129e, 0x129a, 0x1294, 0x128e, 0x1286, 0x127e, 0x1276, 0x1270, 0x126b, 0x1268, 0x1267, 0x1267, 0x1266, 
	0x1266, 0x1265, 0x1265, 0x1264, 0x1264, 0x1263, 0x1263, 0x1262, 0x1262, 0x1262, 0x1262, 0x1263, 0x1264, 0x1265, 0x1265, 0x1265, 
	0x1265, 0x1264, 0x1264, 0x1263, 0x1263, 0x1262, 0x1263, 0x1263, 0x1264, 0x1265, 0x1266, 0x1269, 0x126d, 0x1270, 0x1272, 0x1270, 
	0x126b, 0x1262, 0x125a, 0x1256, 0x1254, 0x1253, 0x1252, 0x1252, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 
	0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 
	0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 
	0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0daa, 0x0e22, 0x0f71, 0x1164, 0x13c4, 0x166a, 0x1938, 0x1c1c, 0x1f07, 0x21ed, 0x24c5, 
	0x278b, 0x2a33, 0x2cb4, 0x2f06, 0x3122, 0x32f9, 0x3481, 0x35ac, 0x366e, 0x36b3, 0x366a, 0x3581, 0x33f5, 0x31c9, 0x2f0f, 0x2be9, 
	0x287e, 0x250b, 0x21dd, 0x1f57, 0x1deb, 0x1d4b, 0x1cd6, 0x1c84, 0x1c43, 0x1c09, 0x1bcd, 0x1b8a, 0x1b3f, 0x1aef, 0x1aa0, 0x1a5c, 
	0x1a2e, 0x1a24, 0x1a4d, 0x1ab4, 0x1b64, 0x1bfd, 0x1c34, 0x1c23, 0x1be2, 0x1b83, 0x1b1a, 0x1abc, 0x1a78, 0x1a5f, 0x1a7a, 0x1acd, 
	0x1b55, 0x1c05, 0x1cc5, 0x1e30, 0x203a, 0x21fb, 0x22b8, 0x21ef, 0x1f33, 0x1a02, 0x14a0, 0x1178, 0x0fa2, 0x0e60, 0x0d93, 0x0d63, 
	0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 
	0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 
	0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff3e, 0xff17, 0xfea7, 
	0xfdef, 0xfcf0, 0xfbac, 0xfa2c, 0xf878, 0xf69e, 0xf4ae, 0xf2b9, 0xf0d2, 0xef09, 0xed72, 0xec1b, 0xeb15, 0xea6d, 0xea31, 0xea72, 
	0xeb44, 0xecc4, 0xef1e, 0xf185, 0xf2fe, 0xf307, 0xeeea, 0xbefe, 0x0968, 0x03be, 0x01a4, 0xffee, 0xfdaf, 0xfb23, 0xf8eb, 0xf6f3, 
	0xf532, 0xf3a4, 0xf24b, 0xf12c, 0xf04f, 0xefbe, 0xef85, 0xefae, 0xf03e, 0xf135, 0xf283, 0xf406, 0xf58f, 0xf729, 0xf8f7, 0xfae5, 
	0xfce8, 0xfefd, 0x012a, 0x0376, 0x05f6, 0x08c9, 0x0c21, 0x104b, 0x15bf, 0x1d22, 0x2712, 0x37c7, 0xcdea, 0xdf7b, 0xeade, 0xf219, 
	0xf69b, 0xf8fc, 0xfa69, 0xfbe9, 0xfd3f, 0xfe43, 0xfee8, 0xff26, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 
	0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 
	0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 
	0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0cdb, 0x0ce2, 0x0cfa, 0x0d26, 0x0d67, 0x0dc0, 0x0e32, 0x0ebf, 0x0f68, 0x1030, 0x1119, 
	0x1225, 0x1356, 0x14b0, 0x1633, 0x17e2, 0x19bf, 0x1bcc, 0x1e0a, 0x207a, 0x231c, 0x25ec, 0x2986, 0x2e53, 0x33e6, 0x39bd, 0x3e3f, 
	0x4583, 0x49f3, 0x4d6e, 0x4fba, 0x50b9, 0x50ef, 0x50e9, 0x50ac, 0x5040, 0x4fab, 0x4ef4, 0x4e25, 0x4d43, 0x4c59, 0x4b6e, 0x4a8c, 
	0x49ba, 0x4901, 0x4869, 0x47f9, 0x47b8, 0x4798, 0x4789, 0x4787, 0x478c, 0x4795, 0x479c, 0x479d, 0x4793, 0x477a, 0x474e, 0x4711, 
	0x46c6, 0x4681, 0x4669, 0x4696, 0x37d0, 0x33e2, 0x2dcb, 0x2635, 0x1e66, 0x17d0, 0x131d, 0x0ff7, 0x0e0e, 0x0d1a, 0x0cc9, 0x0cc1, 
	0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 
	0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 
	0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x075d, 0x0748, 0x070e, 
	0x06c1, 0x0673, 0x0631, 0x0602, 0x05ec, 0x05ee, 0x0603, 0x0626, 0x064c, 0x066e, 0x0684, 0x0685, 0x066f, 0x0641, 0x0602, 0x05be, 
	0x0586, 0x057c, 0x05cb, 0x05d0, 0x04d4, 0x0271, 0xfbf8, 0xc9c5, 0x120f, 0x0a7f, 0x06d5, 0x03fa, 0x010f, 0xfe29, 0xfbbb, 0xf9ad, 
	0xf7f8, 0xf697, 0xf589, 0xf4d2, 0xf472, 0xf46e, 0xf4c9, 0xf582, 0xf695, 0xf7f3, 0xf982, 0xfb14, 0xfc70, 0xfdd5, 0xff92, 0x018b, 
	0x03a8, 0x05df, 0x082b, 0x0a8d, 0x0d11, 0x0fcf, 0x12f4, 0x16cd, 0x1bd2, 0x22ab, 0x2c00, 0x3c13, 0xd1ca, 0xe33e, 0xee95, 0xf587, 
	0xf9b4, 0xfc78, 0xfeee, 0x014e, 0x0387, 0x0589, 0x0706, 0x0793, };

JointIndex BotWZeldaMeshYouaskedAnimJointIndices[22] = {
	{ 0x0000, 0x0001, 0x0000, },
	{ 0x0002, 0x0003, 0x0004, },
	{ 0x0005, 0x0006, 0x0007, },
	{ 0x0005, 0x0006, 0x0007, },
	{ 0x0005, 0x0006, 0x0007, },
	{ 0x0005, 0x0006, 0x0007, },
	{ 0x0008, 0x0009, 0x000a, },
	{ 0x0010, 0x0088, 0x0100, },
	{ 0x0007, 0x0006, 0x0000, },
	{ 0x0007, 0x0006, 0x0006, },
	{ 0x0007, 0x0006, 0x0006, },
	{ 0x0178, 0x0006, 0x0000, },
	{ 0x01f0, 0x0268, 0x02e0, },
	{ 0x0358, 0x03d0, 0x0448, },
	{ 0x04c0, 0x0006, 0x0006, },
	{ 0x0538, 0x05b0, 0x0628, },
	{ 0x000b, 0x000c, 0x06a0, },
	{ 0x0718, 0x0790, 0x0808, },
	{ 0x0880, 0x08f8, 0x0970, },
	{ 0x09e8, 0x0a60, 0x0ad8, },
	{ 0x0b50, 0x0bc8, 0x0c40, },
	{ 0x000d, 0x000e, 0x000f, },
};

AnimationHeader BotWZeldaMeshYouaskedAnim = { { 120 }, BotWZeldaMeshYouaskedAnimFrameData, BotWZeldaMeshYouaskedAnimJointIndices, 16 };

