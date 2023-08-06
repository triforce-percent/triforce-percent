#include "ultra64.h"
#include "global.h"

u64 MimicChestObj_wood_ci8[] = {
	0x0000000000010101, 0x0101010101010202, 0x0202020304040505, 0x0505050505060001, 0x0205050505050505, 0x0606000000020202, 0x0202020202020203, 0x0306050606060606, 
	0x070808080809090a, 0x0b0b0b0b0b0b0c08, 0x0d0d0d0808080e0e, 0x08080f0f0f0f1011, 0x1211111111100f09, 0x090e0e0c0c0c0e08, 0x0808111113080814, 0x1414151515151416, 
	0x0800171717151515, 0x18191818181a1a1b, 0x1c1c1d1616151717, 0x171e1e1e1e1f0202, 0x020202021f1f2017, 0x171715151414211e, 0x1e1e022222222222, 0x2223241e1e1e1f1f, 
	0x0824141616161614, 0x1717171e1e171717, 0x1818181918191919, 0x1818161717171e24, 0x1e1e1e1e1e1e1e1e, 0x1e1e1e1717171717, 0x1717171717171717, 0x171e1e1e1e1e1e25, 
	0x0700171e1e252114, 0x1416161414212125, 0x2525251414141414, 0x1421171717171721, 0x25251e1e26272723, 0x232424241e1e1e25, 0x21212121171e1e17, 0x1717151416161815, 
	0x08021e1e1e1e1714, 0x1616161616141517, 0x1717171e1e1e1e25, 0x252525251e242323, 0x2323242425252525, 0x2525251e1e1e1e1e, 0x1717171718181817, 0x1515171515171717, 
	0x28061e1717171518, 0x1818181818181819, 0x1920202020202020, 0x2020202017171717, 0x1e1e1e1e17171816, 0x16161618151e1e1e, 0x1f1f171717171717, 0x17171717171e1e1e, 
	0x0e1e141414141414, 0x1616161614142121, 0x1414141415181818, 0x1920202020171717, 0x1720200202222222, 0x241e1e1e17211414, 0x1421171717171e1e, 0x1e1e1e1e1e1e1e1e, 
	0x2905050505050505, 0x0606000000020202, 0x0202020202020203, 0x0306050606060606, 0x0000000000010101, 0x0101010101010202, 0x0202020304040505, 0x0505050505060001, 
	0x1211111111100f09, 0x090e0e0c0c0c0e08, 0x0808111113080814, 0x1414151515151416, 0x070808080809090a, 0x0b0b0b0b0b0b0c08, 0x0d0d0d0808080e0e, 0x08080f0f0f0f1011, 
	0x020202021f1f2017, 0x171715151414211e, 0x1e1e022222222222, 0x2223241e1e1e1f14, 0x0020171717151515, 0x19191818181a1a1b, 0x1c1c1d1616151717, 0x171e1e1e1e1f0202, 
	0x1e1e1e1e1e1e1e1e, 0x1e1e1e1717171717, 0x1717171717171717, 0x171e1e1e1e1e1e0c, 0x0214141616161614, 0x1717171e1e171717, 0x1818181918191919, 0x1818161717171e24, 
	0x25251e1e26272723, 0x232424241e1e1e25, 0x21212121171e1e17, 0x1717151416161808, 0x2a17171e1e252114, 0x1416161414212125, 0x2525251414141414, 0x1421171717171721, 
	0x2323242425252525, 0x2525251e1e1e1e1e, 0x1717171718181817, 0x1515171515171708, 0x24211e1e1e1e1714, 0x1616161616141517, 0x1717171e1e1e1e25, 0x252525251e242323, 
	0x1e1e1e1e17171816, 0x16161618151e1e1e, 0x1f1f171717171717, 0x17171717171e1e14, 0x001f1e1717171518, 0x1818181818181819, 0x1920202020202020, 0x2020202017171717, 
	0x1720200202222222, 0x241e1e1e17211414, 0x1421171717171e1e, 0x1e1e1e1e1e1e1e0c, 0x1e28141414141414, 0x1616161614142121, 0x1414141415181818, 0x1920202020171717, 
	
};

u64 MimicChestObj_wood_ci8_pal_rgba16[] = {
	0x5943594561436103, 0x6101590159037207, 0x7a07820581c579c3, 0x79c57a097a058207, 0x82478249828b7a49, 0x71c569c571c76985, 0x69c7698769c96a09, 0x720971c969836183, 
	0x6185718561416941, 0x6943718371816981, 0x71c358c161450000
};

u64 MimicChestObj_teeth_ci8[] = {
	0x0000000000000001, 0x0101000000000000, 0x0000000000000101, 0x0101010000000000, 0x0000000000000102, 0x0201010000000000, 0x0000000000010103, 0x0401010100000000, 
	0x0000000000010506, 0x0607010100000000, 0x0000000001010408, 0x0804010101000000, 0x0000000001050608, 0x0806070101000000, 0x0000000001040808, 0x0808030101010000, 
	0x0000000101060808, 0x0808090501010000, 0x000000010a08080b, 0x0808080301010100, 0x000001010608080c, 0x0d08080905010100, 0x0000010508080b0e, 0x090808080a010101, 
	0x0001010608080f10, 0x0608080811050101, 0x00010a080808120e, 0x08080808080a0101, 0x0101090808081314, 0x0808080808110701, 0x010a0808080f1516, 0x0808080808080a01, 
	
};

u64 MimicChestObj_teeth_ci8_pal_rgba16[] = {
	0xf800f801fd29fe73, 0xfeb5fdadffbdfd6b, 0xffffff7bfdeff7bd, 0xeef7f77be5adef7b, 0xddadff39deb5cd29, 0xddefd529ef390000
};

Vtx MimicChestObj_Root_mesh_layer_Opaque_vtx_0[20] = {
	{{ {-2486, -631, 1232}, 0, {-1270, -912}, {129, 0, 0, 255} }},
	{{ {-2486, 1820, 2486}, 0, {-1270, -1975}, {129, 0, 0, 255} }},
	{{ {-2486, 3091, 4}, 0, {-3240, -1975}, {129, 0, 0, 255} }},
	{{ {-2486, 640, -1250}, 0, {-3240, -912}, {129, 0, 0, 255} }},
	{{ {2486, -631, 1232}, 0, {2215, -912}, {0, 198, 113, 255} }},
	{{ {-2486, 1820, 2486}, 0, {-1270, -1975}, {0, 228, 124, 255} }},
	{{ {-2486, -631, 1232}, 0, {-1270, -912}, {0, 198, 113, 255} }},
	{{ {2486, 1820, 2486}, 0, {2215, -1975}, {0, 228, 124, 255} }},
	{{ {-2486, 640, -1250}, 0, {2204, -4589}, {0, 143, 198, 255} }},
	{{ {2486, -631, 1232}, 0, {-1275, -3448}, {0, 143, 198, 255} }},
	{{ {-2486, -631, 1232}, 0, {2204, -3448}, {0, 143, 198, 255} }},
	{{ {2486, 640, -1250}, 0, {-1275, -4589}, {0, 143, 198, 255} }},
	{{ {-2486, 640, -1250}, 0, {2215, -2181}, {0, 58, 143, 255} }},
	{{ {-2486, 3091, 4}, 0, {2215, -3274}, {0, 58, 143, 255} }},
	{{ {2486, 3091, 4}, 0, {-1292, -3274}, {0, 58, 143, 255} }},
	{{ {2486, 640, -1250}, 0, {-1292, -2181}, {0, 58, 143, 255} }},
	{{ {2486, 640, -1250}, 0, {4185, -912}, {127, 0, 0, 255} }},
	{{ {2486, 1820, 2486}, 0, {2215, -1975}, {127, 0, 0, 255} }},
	{{ {2486, -631, 1232}, 0, {2215, -912}, {127, 0, 0, 255} }},
	{{ {2486, 3091, 4}, 0, {4185, -1975}, {127, 0, 0, 255} }},
};

Gfx MimicChestObj_Root_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(MimicChestObj_Root_mesh_layer_Opaque_vtx_0 + 0, 20, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 11, 9, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 19, 17, 0),
	gsSPEndDisplayList(),
};

Vtx MimicChestObj_Root_mesh_layer_Opaque_vtx_1[4] = {
	{{ {-2486, 1846, 2437}, 0, {-2605, 475}, {0, 251, 127, 255} }},
	{{ {2486, 1846, 2437}, 0, {3068, 475}, {0, 251, 127, 255} }},
	{{ {2356, 2331, 2334}, 0, {2920, -10}, {0, 26, 124, 255} }},
	{{ {-2356, 2331, 2334}, 0, {-2457, -10}, {0, 26, 124, 255} }},
};

Gfx MimicChestObj_Root_mesh_layer_Opaque_tri_1[] = {
	gsSPVertex(MimicChestObj_Root_mesh_layer_Opaque_vtx_1 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Vtx MimicChestObj_Lid_mesh_layer_Opaque_vtx_0[4] = {
	{{ {2486, 2692, -2}, 0, {-2085, 532}, {0, 119, 45, 255} }},
	{{ {-2486, 2692, -2}, 0, {3105, 532}, {0, 119, 45, 255} }},
	{{ {-2386, 2495, 511}, 0, {3001, -21}, {0, 119, 45, 255} }},
	{{ {2386, 2495, 511}, 0, {-1981, -21}, {0, 119, 45, 255} }},
};

Gfx MimicChestObj_Lid_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(MimicChestObj_Lid_mesh_layer_Opaque_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Vtx MimicChestObj_Lid_mesh_layer_Opaque_vtx_1[30] = {
	{{ {-2486, 2794, -2}, 0, {-560, 2064}, {0, 122, 220, 255} }},
	{{ {2486, 2794, -2}, 0, {2691, 2064}, {0, 122, 220, 255} }},
	{{ {2486, 2608, -628}, 0, {2691, 1832}, {0, 110, 192, 255} }},
	{{ {-2486, 2608, -628}, 0, {-560, 1832}, {0, 110, 192, 255} }},
	{{ {2486, 2094, -1153}, 0, {2691, 1572}, {0, 68, 149, 255} }},
	{{ {-2486, 2094, -1153}, 0, {-560, 1572}, {0, 68, 149, 255} }},
	{{ {-2486, 1394, -1402}, 0, {-560, 1308}, {0, 0, 129, 255} }},
	{{ {2486, 1394, -1402}, 0, {2691, 1308}, {0, 0, 129, 255} }},
	{{ {2486, 694, -1153}, 0, {2691, 1044}, {0, 188, 149, 255} }},
	{{ {-2486, 694, -1153}, 0, {-560, 1044}, {0, 188, 149, 255} }},
	{{ {2486, 181, -628}, 0, {2691, 783}, {0, 146, 192, 255} }},
	{{ {-2486, 181, -628}, 0, {-560, 783}, {0, 146, 192, 255} }},
	{{ {2486, 2794, -2}, 0, {1035, -243}, {127, 0, 0, 255} }},
	{{ {2486, 1394, -2}, 0, {1673, -243}, {127, 0, 0, 255} }},
	{{ {2486, 2608, -628}, 0, {1120, -516}, {127, 0, 0, 255} }},
	{{ {2486, 2094, -1153}, 0, {1354, -745}, {127, 0, 0, 255} }},
	{{ {2486, 1394, -1402}, 0, {1673, -853}, {127, 0, 0, 255} }},
	{{ {2486, 694, -1153}, 0, {1992, -745}, {127, 0, 0, 255} }},
	{{ {2486, 181, -628}, 0, {2226, -516}, {127, 0, 0, 255} }},
	{{ {-2486, 2794, -2}, 0, {1033, -243}, {129, 0, 0, 255} }},
	{{ {-2486, 2608, -628}, 0, {948, -516}, {129, 0, 0, 255} }},
	{{ {-2486, 1394, -2}, 0, {395, -243}, {129, 0, 0, 255} }},
	{{ {-2486, 2094, -1153}, 0, {714, -745}, {129, 0, 0, 255} }},
	{{ {-2486, 1394, -1402}, 0, {395, -853}, {129, 0, 0, 255} }},
	{{ {-2486, 694, -1153}, 0, {76, -745}, {129, 0, 0, 255} }},
	{{ {-2486, 181, -628}, 0, {-158, -516}, {129, 0, 0, 255} }},
	{{ {2486, 3091, 4}, 0, {2691, 552}, {0, 134, 220, 255} }},
	{{ {-2486, 3091, 4}, 0, {-560, 552}, {0, 134, 220, 255} }},
	{{ {2486, 3091, 4}, 0, {2311, -243}, {127, 0, 0, 255} }},
	{{ {-2486, 3091, 4}, 0, {-243, -243}, {129, 0, 0, 255} }},
};

Gfx MimicChestObj_Lid_mesh_layer_Opaque_tri_1[] = {
	gsSPVertex(MimicChestObj_Lid_mesh_layer_Opaque_vtx_1 + 0, 26, 0),
	gsSPMatrix(0x0d000000, G_MTX_LOAD),
	gsSPVertex(MimicChestObj_Lid_mesh_layer_Opaque_vtx_1 + 26, 4, 26),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 3, 2, 0, 4, 5, 3, 0),
	gsSP2Triangles(4, 6, 5, 0, 4, 7, 6, 0),
	gsSP2Triangles(8, 6, 7, 0, 8, 9, 6, 0),
	gsSP2Triangles(9, 8, 10, 0, 9, 10, 11, 0),
	gsSP2Triangles(26, 11, 10, 0, 26, 27, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 14, 13, 15, 0),
	gsSP2Triangles(16, 15, 13, 0, 17, 16, 13, 0),
	gsSP2Triangles(18, 17, 13, 0, 18, 13, 28, 0),
	gsSP2Triangles(19, 20, 21, 0, 20, 22, 21, 0),
	gsSP2Triangles(22, 23, 21, 0, 23, 24, 21, 0),
	gsSP2Triangles(24, 25, 21, 0, 29, 21, 25, 0),
	gsSPEndDisplayList(),
};

Gfx mat_MimicChestObj_Wood_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, TEXEL0, 0, SHADE, 0, 0, 0, 0, 1),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, MimicChestObj_wood_ci8_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(7, 42),
	gsDPLoadSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, MimicChestObj_wood_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPLoadBlock(7, 0, 0, 511, 256),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 60),
	gsSPEndDisplayList(),
};

Gfx mat_MimicChestObj_Teeth_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_INTER | CVG_X_ALPHA | ALPHA_CVG_SEL | GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM) | GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, MimicChestObj_teeth_ci8_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(7, 22),
	gsDPLoadSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, MimicChestObj_teeth_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0),
	gsDPLoadBlock(7, 0, 0, 127, 1024),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 2, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 60),
	gsSPEndDisplayList(),
};

Gfx MimicChestObj_Root_mesh_layer_Opaque[] = {
	gsSPDisplayList(mat_MimicChestObj_Wood_layerOpaque),
	gsSPDisplayList(MimicChestObj_Root_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_MimicChestObj_Teeth_layerOpaque),
	gsSPDisplayList(MimicChestObj_Root_mesh_layer_Opaque_tri_1),
	gsSPEndDisplayList(),
};

Gfx MimicChestObj_Lid_mesh_layer_Opaque[] = {
	gsSPDisplayList(MimicChestObj_Lid_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_MimicChestObj_Wood_layerOpaque),
	gsSPDisplayList(MimicChestObj_Lid_mesh_layer_Opaque_tri_1),
	gsSPEndDisplayList(),
};

StandardLimb MimicChestObjLimb_000 = { { 0, 0, 0 }, 1, 255, MimicChestObj_Root_mesh_layer_Opaque };
StandardLimb MimicChestObjLimb_001 = { { 0, 3096, 0 }, 255, 255, MimicChestObj_Lid_mesh_layer_Opaque };

void* MimicChestObjLimbs[2] = {
	&MimicChestObjLimb_000,
	&MimicChestObjLimb_001,
};

FlexSkeletonHeader MimicChestObj = { MimicChestObjLimbs, 2, 2 };

