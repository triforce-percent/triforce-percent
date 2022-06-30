#define _Z64HDR_DISABLE_FABSF_ASM_ 1
#include "ootmain.h" 

Gfx butterflypatch[] = {
    /*
    gsSPTexture(0x8000, 0x7A00, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(0x06000000, G_IM_FMT_IA, G_IM_SIZ_8b, 
        24, 48, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 
        5, 6,
        G_TX_NOLOD, G_TX_NOLOD),
    */
    gsSPTexture(0xC000, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_8b, (24)>>1, 0x06000000),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0, G_TX_LOADTILE, 0, 
        G_TX_CLAMP, 6, 0, G_TX_CLAMP, 5, 0),
    gsDPLoadSync(),
    gsDPLoadTile(G_TX_LOADTILE, 0, 0, (24-1) << 1, (48-1) << 2),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 0, 
        G_TX_CLAMP, 6, 0, G_TX_CLAMP, 5, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, ((32)-1) << 1, ((48)-1) << 2)
};
