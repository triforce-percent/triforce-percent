#include "ootmain.h" 
#include "../loader/fast_loader/fast_loader.h"
#include "../loader/debugger/debugger.h"
#include "../statics/statics.h"

#include "../../textures/twitch/icons.inc"

__attribute__((aligned(16))) static const u64 tw_msg_case0[] = {
    #include "../../textures/tw_msg_case0.i4.inc"
};

__attribute__((aligned(16))) static const u64 tw_msg_case1[] = {
    #include "../../textures/tw_msg_case1.i4.inc"
};

__attribute__((aligned(16))) static const u64 tw_msg_case2[] = {
    #include "../../textures/tw_msg_case2.i4.inc"
};

__attribute__((aligned(16))) static const u64 tw_msg_case3[] = {
    #include "../../textures/tw_msg_case3.i4.inc"
};

__attribute__((aligned(16))) static const u64 tw_msg_exclam[] = {
    #include "../../textures/tw_msg_exclam.i4.inc"
};

__attribute__((aligned(16))) static const u64 username_font[] = {
    #include "../../textures/username_font.i4.inc"
};

static const u16 char_starts[64] = {
    0, 
    //underscore and numbers
    6, 15, 21, 29, 38, 48, 55, 64, 72, 81, 90,
    //uppercase
    100, 109, 119, 128, 136, 144, 154, 164, 168, 175, 184, 191, 203,
    213, 223, 231, 241, 250, 259, 268, 277, 286, 300, 309, 318, 327,
    //lowercase
    335, 343, 351, 359, 367, 372, 380, 388, 391, 396, 404, 408, 420,
    428, 436, 444, 452, 457, 464, 469, 477, 484, 496, 503, 511, 518
};

static const u64 *const tw_msg_cases[4] = {
    tw_msg_case0, tw_msg_case1, tw_msg_case2, tw_msg_case3
};

static const u16 casing_widths[4] = {
    87, 89, 91, 107
};

/*
static const Color_RGB8 uname_colors[16] = {
    {0x00, 0x00, 0xFF}, //0: Blue
    {0xFF, 0x7F, 0x50}, //1: Coral
    {0x1E, 0x90, 0xFF}, //2: DodgerBlue
    {0x00, 0xFF, 0x7F}, //3: SpringGreen
    {0x9A, 0xCD, 0x32}, //4: YellowGreen
    {0x00, 0x80, 0x00}, //5: Green
    {0xFF, 0x45, 0x00}, //6: OrangeRed
    {0xFF, 0x00, 0x00}, //7: Red
    {0xDA, 0xA5, 0x20}, //8: GoldenRod
    {0xFF, 0x69, 0xB4}, //9: HotPink
    {0x5F, 0x9E, 0xA0}, //A: CadetBlue
    {0x2E, 0x8B, 0x57}, //B: SeaGreen
    {0xD2, 0x69, 0x1E}, //C: Chocolate
    {0x8A, 0x2B, 0xE2}, //D: BlueViolet
    {0xB2, 0x22, 0x22}, //E: Firebrick
    {0xFF, 0xFF, 0xFF}  //F: White
};
*/

#define G_CC_UNAME 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0

static const Gfx uname_setup_dl[] = {
    gsSPLoadGeometryMode(G_ZBUFFER),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_UNAME, G_CC_UNAME),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT
        | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP
        | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
        G_AC_NONE | G_ZS_PIXEL | 
        AA_EN | Z_CMP | Z_UPD | IM_RD | FORCE_BL | CLR_ON_CVG |
        CVG_DST_CLAMP | CVG_X_ALPHA | ZMODE_XLU |
        GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA) |
        GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsSPTexture(0x4000, 0x4000, 0, 0, 1),
    gsSPEndDisplayList(),
};

#define G_CC_ICONS 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0
#define SETTILESIZEVAL qu102((ICON_SIZE) - 1) //(ICON_SIZE-1)<<G_TEXTURE_IMAGE_FRAC

static const Gfx icon_setup_dl[] = {
    //Rest of load palettes
    gsDPTileSync(),
    gsDPSetTile(0, 0, 0, 256, 7, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(7, NUM_PALETTES*16 - 1),
    gsDPPipeSync(),
    //Icon tile sizes
    gsDPSetTileSize(0, 0, 0, SETTILESIZEVAL, SETTILESIZEVAL),
    gsDPSetTileSize(1, 0, 0, SETTILESIZEVAL, SETTILESIZEVAL),
    gsDPSetTileSize(2, 0, 0, SETTILESIZEVAL, SETTILESIZEVAL),
    gsDPSetTileSize(3, 0, 0, SETTILESIZEVAL, SETTILESIZEVAL),
    //Icon load tile info
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, 7, 
        0, 0, 0, 0, 0, 0, 0),
    //Rest of pipeline
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetCombineMode(G_CC_ICONS, G_CC_ICONS),
    gsSPEndDisplayList(),
};

#define FRAMES_FADE_MAX 100
#define FRAMES_FADE_MIN 10
#define MSGS_ON_SCREEN_TARGET 40
#define MSG_POS_EXTENT_X 1000.0f
#define MSG_POS_EXTENT_Y 300.0f
#define MSG_POS_EXTENT_Z 300.0f
#define MSG_SCALE 1.6f

typedef struct {
    Actor actor;
    MtxF modelf;
    Mtx modelrsp;
    u16 frames_fade;
    u8 override_icon;
    u8 pause_enabled;
} Entity;

#define NUM_ICON_GROUPS ((NUM_ICONS + ICONS_PER_GROUP - 1) / ICONS_PER_GROUP)
#define NUM_CMDS_PER_TILE_SETUP_DL 8
#define ST_SCALE_PWR 7
#define UNAME_TEX_COLS 128
#define EXCLAM_WIDTH 4

#define RAM_END 0x80800000
#define UNAME_TEX_SZ (UNAME_TEX_COLS * sizeof(u64))
#define UNAME_TEX_BEGIN (RAM_END - MAX_TWITCH_MESSAGES * UNAME_TEX_SZ) //0x20000 / 0x807E0000
#define VTX_EACH_SZ (4 * sizeof(Vtx))
#define VTX_PERMSG_SZ (6 * VTX_EACH_SZ)
#define VTX_BEGIN (UNAME_TEX_BEGIN - MAX_TWITCH_MESSAGES * VTX_PERMSG_SZ) //0xA000 / 0x807D6000

static inline u64 *GetMessageTexture(u16 m) {
    return (u64*)(UNAME_TEX_BEGIN + m * UNAME_TEX_SZ);
}

static inline Vtx *GetMessageVerts(u16 m) {
    return (Vtx*)(VTX_BEGIN + m * VTX_PERMSG_SZ);
}

static inline void SetupRectangleInternal(Vtx *verts, s16 basex, s16 basey, s16 basez){
    for(s32 i=0; i<4; ++i){
        verts[i].v.ob[0] = basex;
        verts[i].v.ob[1] = basey;
        verts[i].v.ob[2] = basez;
        verts[i].v.tc[0] = -16;
        verts[i].v.tc[1] = -16;
    }
}

static inline void SetupRectangle11(Vtx *verts, s16 basex, s16 basey, s16 basez, s16 sx, s16 sy){
    SetupRectangleInternal(verts, basex, basey, basez);
    verts[1].v.ob[0] += sx;
    verts[3].v.ob[0] += sx;
    verts[2].v.ob[1] += sy;
    verts[3].v.ob[1] += sy;
    verts[1].v.tc[1] += sx * (1 << ST_SCALE_PWR);
    verts[3].v.tc[1] += sx * (1 << ST_SCALE_PWR);
    verts[2].v.tc[0] += sy * (1 << ST_SCALE_PWR);
    verts[3].v.tc[0] += sy * (1 << ST_SCALE_PWR);
}

static inline void SetupRectangleBadge(Vtx *verts, s16 basex, s16 basey, s16 basez){
    SetupRectangleInternal(verts, basex, basey, basez);
    verts[1].v.ob[0] += 16;
    verts[3].v.ob[0] += 16;
    verts[2].v.ob[1] += 16;
    verts[3].v.ob[1] += 16;
    verts[1].v.tc[0] += ICON_SIZE * (1 << ST_SCALE_PWR);
    verts[3].v.tc[0] += ICON_SIZE * (1 << ST_SCALE_PWR);
    verts[2].v.tc[1] += ICON_SIZE * (1 << ST_SCALE_PWR);
    verts[3].v.tc[1] += ICON_SIZE * (1 << ST_SCALE_PWR);
}

#define EMOTE_W_SIZE 24
#define EMOTE_XTRA_OFFS ((EMOTE_W_SIZE - 16) >> 1)

static inline void SetupRectangleEmote(Vtx *verts, s16 basex, s16 basey, s16 basez, u8 emote_qty){
    basey -= EMOTE_XTRA_OFFS;
    SetupRectangleInternal(verts, basex, basey, basez);
    verts[1].v.ob[0] += emote_qty * EMOTE_W_SIZE;
    verts[3].v.ob[0] += emote_qty * EMOTE_W_SIZE;
    verts[2].v.ob[1] += EMOTE_W_SIZE;
    verts[3].v.ob[1] += EMOTE_W_SIZE;
    verts[1].v.tc[0] += emote_qty * ICON_SIZE * (1 << ST_SCALE_PWR);
    verts[3].v.tc[0] += emote_qty * ICON_SIZE * (1 << ST_SCALE_PWR);
    verts[2].v.tc[1] += ICON_SIZE * (1 << ST_SCALE_PWR);
    verts[3].v.tc[1] += ICON_SIZE * (1 << ST_SCALE_PWR);
}

static void SetUpMessage(Entity *en, u16 m, TwitchMessage *msg) {
    msg->a = 0xFF;
    
    u64 *tex = GetMessageTexture(m);
    s32 byte = 0;
    s32 ch = 0;
    s32 texcol = 0;
    while(byte < 19){
        u32 temp = msg->uname_encoded[byte++];
        temp |= (u32)msg->uname_encoded[byte++] << 8; //will overread on the last
        temp |= (u32)msg->uname_encoded[byte++] << 16; //but that's okay
        for(s32 ingrp=0; ingrp<4; ++ingrp){
            u8 c = temp & 0x3F;
            temp >>= 6;
            if(ch >= 25) break;
            ++ch;
            if(c == 0){
                //end of message
                byte = 100;
                break;
            }
            --c; //0-62
            //Copy character to texture.
            //Texture is stored flipped so the bytes of each column are consecutive.
            //Conveniently one column is one u64.
            u16 c_start = char_starts[c];
            u16 c_end = char_starts[c+1];
            u16 cols = c_end - c_start;
            if(texcol + cols > UNAME_TEX_COLS){
                byte = 100; //exit outer loop too
                break;
            }
            bcopy(&username_font[c_start], &tex[texcol], cols * sizeof(u64));
            texcol += cols;
        }
    }
    if(texcol < UNAME_TEX_COLS){
        bzero(&tex[texcol], (UNAME_TEX_COLS-texcol) * sizeof(u64));
    }
    
    Vtx *verts = GetMessageVerts(m);
    //Base in lower left corner
    s16 basex = (Rand_ZeroOne() - 0.5f) * MSG_POS_EXTENT_X;
    s16 basey = (Rand_ZeroOne() - 0.5f) * MSG_POS_EXTENT_Y;
    f32 zmin, zmax;
    if((msg->flags & 0x08)){ //bad words
        zmax =  0.5f;
        zmin =  0.1f;
    }else{
        zmax =  0.1f;
        zmin = -0.5f;
    }
    s16 basez = (Rand_ZeroOne() * (zmax - zmin) + zmin) * MSG_POS_EXTENT_Z;
    
    s16 x = 0;
    if(msg->global_badge){
        SetupRectangleBadge(verts, basex + x, basey, basez);
        x += 18;
    }
    if(msg->sub_badge){
        SetupRectangleBadge(verts + 4, basex + x, basey, basez);
        x += 18;
    }
    //Username
    SetupRectangle11(verts + 8, basex + x, basey, basez, 128, 16);
    x += texcol + 2;
    
    //First position for emotes
    u8 content = msg->flags >> 6;
    u8 emote_qty = (msg->quantities & 0xF) + 1;
    s16 x_emotes = 0;
    if(content == 3){
        x_emotes = x;
        x += emote_qty * EMOTE_W_SIZE + 2;
    }
    
    if(content != 1){
        //Message
        s16 w = casing_widths[(msg->flags & 0x30) >> 4];
        SetupRectangle11(verts + 12, basex + x, basey, basez, w, 16);
        x += w;
        u8 exclam_qty = msg->quantities >> 4;
        if(exclam_qty){
            w = exclam_qty * EXCLAM_WIDTH;
            SetupRectangle11(verts + 16, basex + x, basey, basez, w, 16);
            x += w;
        }
        x += 2;
    }
    
    //Second position for emotes
    if(content == 1 || content == 2){
        x_emotes = x;
        x += emote_qty * EMOTE_W_SIZE + 2;
    }
    
    //Draw emotes
    if(content != 0){
        SetupRectangleEmote(verts + 20, basex + x_emotes, basey, basez, emote_qty);
    }
    
    //Get world coordinates center
    Vec3f ctrin;
    ctrin.x = basex + (x >> 1);
    ctrin.y = basey + 8;
    ctrin.z = basez;
    SkinMatrix_Vec3fMtxFMultXYZ(&en->modelf, &ctrin, &msg->center);
}

static void init(Entity *en, GlobalContext *globalCtx) {
    en->frames_fade = FRAMES_FADE_MAX;
    en->override_icon = 0;
    en->pause_enabled = 0;
    bzero((void*)VTX_BEGIN, UNAME_TEX_BEGIN - VTX_BEGIN);
    //Create model matrix
    Matrix_Translate(en->actor.world.pos.x, en->actor.world.pos.y,
        en->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateRPY(0, en->actor.shape.rot.y + 0x8000, 0, MTXMODE_APPLY);
    Matrix_RotateRPY(0, 0, 0x8000, MTXMODE_APPLY);
    Matrix_Scale(MSG_SCALE, MSG_SCALE, MSG_SCALE, MTXMODE_APPLY);
    Matrix_Get(&en->modelf);
    Matrix_ToMtx(&en->modelrsp, "", 0);
}

static void destroy(Entity *en, GlobalContext *globalCtx) {}

static void update(Entity *en, GlobalContext *globalCtx){
    s32 numAlive = 0;
    float fff = 255.0f / (float)en->frames_fade;
    s32 fi = (s32)fff;
    for(s32 m=0; m<MAX_TWITCH_MESSAGES; ++m){
        TwitchMessage *msg = &twitch_msg_buf[m];
        if(msg->timer == 0xFF){
            msg->timer = 1;
            SetUpMessage(en, m, msg);
        }else if(msg->timer != 0){
            s32 a = msg->a;
            a -= fi;
            if(a <= 7){ // RDP has 5-bit alpha, so alpha <= 7 becomes 0, so invisible, so just kill it now
                msg->timer = msg->a = 0;
            }else{
                msg->a = a;
            }
        }
        if(msg->timer != 0) ++numAlive;
    }
    if(numAlive > MSGS_ON_SCREEN_TARGET && en->frames_fade > FRAMES_FADE_MIN){
        en->frames_fade -= 3;
    }else if(numAlive < MSGS_ON_SCREEN_TARGET && en->frames_fade < FRAMES_FADE_MAX){
        en->frames_fade += 2;
    }
    //Debugging
    const u16 holdbtns = BTN_R | BTN_CLEFT;
    if((CTRLR_RAW & holdbtns) == holdbtns){
        --globalCtx->csCtx.frames;
        if((CTRLR_PRESS & BTN_DLEFT)){
            en->override_icon = 0;
        }else if((CTRLR_PRESS & BTN_DUP)){
            ++en->override_icon;
        }else if((CTRLR_PRESS & BTN_DDOWN) && en->override_icon > 1){
            --en->override_icon;
        }else if((CTRLR_PRESS & BTN_DRIGHT)){
            en->pause_enabled ^= 1;
            if(sIsLiveRun){
                Debugger_Printf("Pause %d", en->pause_enabled);
            }
        }
    }else if(en->pause_enabled){
        --globalCtx->csCtx.frames;
    }
}

static inline void LoadI4Clamp(const u64 *tex, s16 cols){
    gDPLoadMultiBlock_4b(POLY_OPA_DISP++, tex,
        0, G_TX_RENDERTILE, G_IM_FMT_I, 16, cols, 0,
        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 
        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

static inline void LoadI4WrapT(const u64 *tex, s16 cols){
    gDPLoadMultiBlock_4b(POLY_OPA_DISP++, tex,
        0, G_TX_RENDERTILE, G_IM_FMT_I, 16, cols, 0,
        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_WRAP,
        G_TX_NOMASK, 2, G_TX_NOLOD, G_TX_NOLOD);
}

static inline void VertsAndTris(s32 m, u32 voffset){
    gSPVertex(POLY_OPA_DISP++, GetMessageVerts(m) + voffset, 4, 0);
    gSP2Triangles(POLY_OPA_DISP++, 0, 1, 2, 0, 2, 1, 3, 0);
}

static inline void DrawTileNoRedundant(s32 m, u32 voffset, u8 *last_tile, u8 tile){
    if(*last_tile != tile){
        if(*last_tile != 0xFF){
            gSPTexture(POLY_OPA_DISP++, 0x4000, 0x4000, 0, *last_tile, G_OFF);
        }
        gSPTexture(POLY_OPA_DISP++, 0x4000, 0x4000, 0, tile, G_ON);
    }
    VertsAndTris(m, voffset);
    *last_tile = tile;
}

static void draw(Entity *en, GlobalContext *globalCtx) {
    gSPMatrix(POLY_OPA_DISP++, &en->modelrsp, G_MTX_MODELVIEW | G_MTX_LOAD);
    //Cull messages not on screen
    for(s32 m=0; m<MAX_TWITCH_MESSAGES; ++m){
        TwitchMessage *msg = &twitch_msg_buf[m];
        if(msg->timer == 0 || msg->timer == 0xFF){
            msg->culled = 1;
            continue;
        }
        msg->culled = !Statics_UncullObject(globalCtx, &msg->center,
            240.0f * MSG_SCALE, 12.0f * MSG_SCALE, 12.0f * MSG_SCALE, 100.0f, 3000.0f);
    }
    //Usernames
    gSPDisplayList(POLY_OPA_DISP++, uname_setup_dl);
    for(s32 m=0; m<MAX_TWITCH_MESSAGES; ++m){
        TwitchMessage *msg = &twitch_msg_buf[m];
        if(msg->culled) continue;
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, msg->rgb.r, msg->rgb.g, msg->rgb.b, msg->a);
        LoadI4Clamp(GetMessageTexture(m), UNAME_TEX_COLS);
        VertsAndTris(m, 8);
    }
    //Messages
    for(s32 casing=0; casing<4; ++casing){
        LoadI4Clamp(tw_msg_cases[casing], casing_widths[casing]);
        for(s32 m=0; m<MAX_TWITCH_MESSAGES; ++m){
            TwitchMessage *msg = &twitch_msg_buf[m];
            if(msg->culled) continue;
            if((msg->flags >> 6) == 1) continue;
            if(((msg->flags & 0x30) >> 4) != casing) continue;
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0xFF, 0xFF, 0xFF, msg->a);
            VertsAndTris(m, 12);
        }
    }
    //Exclamation points
    LoadI4WrapT(tw_msg_exclam, EXCLAM_WIDTH);
    for(s32 m=0; m<MAX_TWITCH_MESSAGES; ++m){
        TwitchMessage *msg = &twitch_msg_buf[m];
        if(msg->culled) continue;
        if(!(msg->quantities & 0xF0)) continue;
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0xFF, 0xFF, 0xFF, msg->a);
        VertsAndTris(m, 16);
    }
    //Icon palettes
    gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, icon_palettes);
    gSPDisplayList(POLY_OPA_DISP++, icon_setup_dl);
    //Icons
    u8 icon = 1;
    u8 last_tile = 0xFF;
    for(s32 icongroup=0; icongroup<NUM_ICON_GROUPS; ++icongroup){
        gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_I, G_IM_SIZ_16b, 1, 
            (u8*)icon_textures + ICON_SIZE * ICON_SIZE / 2 * ICONS_PER_GROUP * icongroup);
        gSPDisplayList(POLY_OPA_DISP++, &icon_tile_setup_dls[NUM_CMDS_PER_TILE_SETUP_DL*icongroup]);
        for(s32 m=0; m<MAX_TWITCH_MESSAGES; ++m){
            TwitchMessage *msg = &twitch_msg_buf[m];
            if(msg->culled) continue;
            u8 global_badge = msg->global_badge;
            u8 sub_badge = msg->sub_badge;
            u8 emote = msg->emote + 1;
            u8 content = msg->flags >> 6;
            bool draw_g = global_badge >= icon && global_badge < icon + ICONS_PER_GROUP;
            bool draw_s = sub_badge != 0 && 
                sub_badge+IDX_SUB_START >= icon &&
                sub_badge+IDX_SUB_START < icon + ICONS_PER_GROUP;
            bool draw_e = content != 0 &&
                emote+IDX_EMOTE_START >= icon &&
                emote+IDX_EMOTE_START < icon + ICONS_PER_GROUP;
            if(en->override_icon != 0){
                bool in_range = en->override_icon >= icon && en->override_icon < icon + ICONS_PER_GROUP;
                draw_g = global_badge != 0 && in_range;
                draw_s = sub_badge != 0 && in_range;
                draw_e = content != 0 && in_range;
            }
            if(draw_g || draw_s || draw_e){
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0xFF, 0xFF, 0xFF, msg->a);
            }
            u8 tile_g = global_badge - icon;
            u8 tile_s = sub_badge+IDX_SUB_START - icon;
            u8 tile_e = emote+IDX_EMOTE_START - icon;
            if(en->override_icon != 0){
                tile_g = tile_s = tile_e = en->override_icon - icon;
            }
            if(draw_g) DrawTileNoRedundant(m,  0, &last_tile, tile_g);
            if(draw_s) DrawTileNoRedundant(m,  4, &last_tile, tile_s);
            if(draw_e) DrawTileNoRedundant(m, 20, &last_tile, tile_e);
        }
        icon += ICONS_PER_GROUP;
    }
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_BG,
	.flags = 0x00000030,
	.objectId = OBJECT_GAMEPLAY_KEEP,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};
