#include "ootmain.h"
#include "interface.h"
#include "statics.h"
#include "../loader/debugger/debugger.h"

extern void Construct_Icon_Start();
extern void Construct_Icon_Target();

extern void InterfaceEffectTex_Start();
extern void InterfaceEffectTex_Target();

extern void KaleidoScope_UpdateEquipAnim(GlobalContext *globalCtx);

extern s16 sEquipState;
extern s16 sEquipAnimTimer;
extern s16 sEquipMoveTimer;

extern Vec3f sSoundParam1;
extern float sSoundParam34;
extern float sSoundParam5;

extern u8 sSubscreenButtonStates[30];

static const u64 TexButterfly[] = {
    #include "../textures/butterfly_bottle.rgba32.inc"
};

void Patched_LoadItemIconMain(GlobalContext *globalCtx, u16 button, u16 num){
    InterfaceContext *interfaceCtx = (InterfaceContext*)&globalCtx->interfaceCtx;
    u32 rom = 0x007BD000; //icon_item_static
    u8 *ram = interfaceCtx->iconItemSegment + button * 0x1000;
    u32 *image = (u32*)ram;
    u32 size = 0x1000;
    u8 item = gSaveContext.equips.buttonItems[button];
    s8 x, y;
    
    if(item >= 0xF0){
        //Empty/no item, clear texture
        bzero(ram, size);
        return;
    }else if(item >= 0x66 && item <= 0x79){
        item -= 0x66;
        size = 0x900;
        rom = 0x00846000; //icon_item_24_static
    }else if(item >= 0x5A){
        item = 0x35; //if invalid item, default to Frog
    }
    rom += item * size;
    
    if(item == ITEM_BIG_POE){
        bcopy(TexButterfly, ram, size);
    }else if(num == 0){
        DmaMgr_SendRequest1(ram, rom, size);
    }else{
        DmaRequest *request = ((num == 1) ? &interfaceCtx->dmaRequest_160 : &interfaceCtx->dmaRequest_180);
        osCreateMesgQueue(&interfaceCtx->loadQueue, &interfaceCtx->loadMsg, OS_MESG_BLOCK);
        DmaMgr_SendRequest2(request, (u32)ram, rom, size, 0, &interfaceCtx->loadQueue, 0);
        osRecvMesg(&interfaceCtx->loadQueue, NULL, OS_MESG_BLOCK);
    }
    
    if(size == 0x1000) return;
    
    //Recenter icon from 24x24 to 32x32.
    for(y=31; y>=0; --y){
        for(x=31; x>=0; --x){
            u32 pixel = 0;
            if(x>=4 && x<28 && y>=4 && y<28){
                pixel = image[24*(y-4) + (x-4)];
            }
            image[32*y+x] = pixel;
        }
    }
}

void Patched_LoadAllItemIcons(){
    Patched_LoadItemIconMain(&gGlobalContext, 0, 0);
    Patched_LoadItemIconMain(&gGlobalContext, 1, 0);
    Patched_LoadItemIconMain(&gGlobalContext, 2, 0);
    Patched_LoadItemIconMain(&gGlobalContext, 3, 0);
}

void Patched_LoadItemIcon1(GlobalContext *globalCtx, u16 button){
    Patched_LoadItemIconMain(globalCtx, button, 1);
}

void Patched_LoadItemIcon2(GlobalContext *globalCtx, u16 button){
    Patched_LoadItemIconMain(globalCtx, button, 2);
}

s32 *Patched_EquipEffectTexLoad(s32 *dl, s32 dummy, PauseContext *pauseCtx){
    s32 gDPLoadBlockW1, gDPSetTileW0, gDPSetTileSizeW1;
    u16 item = pauseCtx->equipTargetItem;
    if(item >= 0x66 && item <= 0x79){
        //24x24 icon
        gDPLoadBlockW1 = 0x0723F0AB;
        gDPSetTileW0 = 0xF5180C00;
        gDPSetTileSizeW1 = 0x0005C05C;
    }else{
        //32x32 icon
        gDPLoadBlockW1 = 0x073FF080;
        gDPSetTileW0 = 0xF5181000;
        gDPSetTileSizeW1 = 0x0007C07C;
    }
    //gDPSetTextureImage
    dl[0x0] = 0xFD180000;
    dl[0x1] = (s32)gItemIcons[item];
    //gDPSetTile
    dl[0x2] = 0xF5180000;
    dl[0x3] = 0x07000000;
    //gDPLoadSync
    dl[0x4] = 0xE6000000;
    dl[0x5] = 0;
    //gDPLoadBlock
    dl[0x6] = 0xF3000000;
    dl[0x7] = gDPLoadBlockW1;
    //gDPPipeSync
    dl[0x8] = 0xE7000000;
    dl[0x9] = 0;
    //gDPSetTile
    dl[0xA] = gDPSetTileW0;
    dl[0xB] = 0;
    //gDPSetTileSize
    dl[0xC] = 0xF2000000;
    dl[0xD] = gDPSetTileSizeW1;
    return dl + 0xE;
}

void Statics_HandleEquipMedallionsToC(){
    static s16 lastCurX, lastCurY;
    PauseContext *pauseCtx = &gGlobalContext.pauseCtx;
    if(!pauseCtx->state) return;
    if(!(SAGES_CHARM_VAR & SAGES_CHARM_BIT)) return;
    
    //Enable C buttons on Quest Status subscreen
	//Have to set once every time the pause menu overlay gets reloaded
	if(pauseCtx->state >= 4 && pauseCtx->state <= 11 && sSubscreenButtonStates[3*5+1] == 0xFF){
		sSubscreenButtonStates[3*5+1] = 0;
		sSubscreenButtonStates[3*5+2] = 0;
		sSubscreenButtonStates[3*5+3] = 0;
	}
    
    if(pauseCtx->debugState || pauseCtx->pageIndex != 2) return;
    
    s16 curX = pauseCtx->cursorVtx[0].v.ob[0];
    s16 curY = pauseCtx->cursorVtx[0].v.ob[1];
    if(curX != 0 && curY != 0){
        lastCurX = curX;
        lastCurY = curY;
    }
    
    u8 item = pauseCtx->cursorItem[2];
    if(item >= 0x66 && item <= 0x79 && //actually has item, not empty
            (CTRLR_PRESS & (BTN_CLEFT | BTN_CDOWN | BTN_CRIGHT))){
        //Equipping a Quest Status item
        if((CTRLR_PRESS & BTN_CLEFT)){
            pauseCtx->equipTargetCBtn = 0;
        }else if((CTRLR_PRESS & BTN_CDOWN)){
            pauseCtx->equipTargetCBtn = 1;
        }else{
            pauseCtx->equipTargetCBtn = 2;
        }
        pauseCtx->equipTargetSlot = 24 + pauseCtx->equipTargetCBtn;
        pauseCtx->equipTargetItem = item;
        pauseCtx->unk_1E4 = 3;
        pauseCtx->equipAnimX = lastCurX * 10; //770;
        pauseCtx->equipAnimY = lastCurY * 10; //50;
        pauseCtx->equipAnimAlpha = 255;
        sEquipAnimTimer = 0;
        sEquipState = 3;
        sEquipMoveTimer = 10;
        Audio_PlaySoundGeneral(NA_SE_SY_DECIDE,
            &sSoundParam1, 4, &sSoundParam34, &sSoundParam34, &sSoundParam5);
    }
}

#define NUM_PATCHED_ITEM_NAMES 3
static u8 patchedItemNameCount = 0;
static struct { u8 item; void *ram_addr; } PatchedItemNameTable[NUM_PATCHED_ITEM_NAMES] = {
    {0, NULL}, {0, NULL}, {0, NULL}
};

void Patched_LoadItemName(void *dest, u32 srcRom, u32 size){
    u8 item = (srcRom - 0x880000) >> 10;
    if(item >= 123) item -= 123; //Japanese / English
    for(u8 i=0; i<patchedItemNameCount; ++i){
        if(PatchedItemNameTable[i].item == item){
            bcopy(PatchedItemNameTable[i].ram_addr, dest, size);
            return;
        }
    }
    DmaMgr_SendRequest1(dest, srcRom, size);
}

typedef struct {
    /* 0x00 */ void (*drawFunc)(GlobalContext*, s16);
    /* 0x04 */ u32 dlists[8];
} DrawItemTableEntry; // size = 0x24

extern DrawItemTableEntry gDrawItemTable[];

typedef struct {
    /* 0x00 */ u8 itemId;
    /* 0x01 */ u8 field; // various bit-packed data
    /* 0x02 */ s8 gi;    // defines the draw id and chest opening animation
    /* 0x03 */ u8 textId;
    /* 0x04 */ u16 objectId;
} GetItemEntry; // size = 0x06

extern GetItemEntry linkGetItemTable[];

extern Gfx gGiSagesCharmDL[];

extern void func_8007E610(/*gfxCtx*/);
extern void MagicBarDrawReturn();

void Patched_MagicBarY1(){
    asm(".set noat\n .set noreorder\n"
	//Starting at 800730EC + 0x34
    "lui     $t2, 0x8012\n"
    "addiu   $t2, $t2, 0xBA00\n"
    "lw      $t9, 0x0000($t2)\n"
    "bne     $at, $zero, lbl_magicbar1\n"
    "lh      $t3, 0x0AF4($t9)\n"
    "lh      $t3, 0x0AF8($t9)\n"
    "lbl_magicbar1:\n"
    "sw      $t0, 0x00E4($sp)\n"
    "jal     func_8007E610\n"
    "sh      $t3, 0x00EA($sp)\n"
    "j       Patched_MagicBarSetup\n"
    "nop\n"
    "nop\n"
    "nop\n"
    "nop\n"
    ".set at\n .set reorder");
}

s32 HasSagesCharm(){
    return (SAGES_CHARM_VAR & SAGES_CHARM_BIT);
}

void Patched_MagicBarSetup(){
    asm(".set noat\n .set noreorder\n"
    "jal HasSagesCharm\n"
    "nop\n"
    "lui   $a0, 0x8012\n"
    "addiu $a0, $a0, 0xA5D0\n"
    "lb    $t0, 0x0033($a0)\n" //magic
    "lh    $t1, 0x13F4($a0)\n"
    "beq   $v0, $zero, lbl_magicbarsetup\n"
    "lh    $t2, 0x13F8($a0)\n"
    "sll   $t0, $t0, 1\n"
    "sll   $t1, $t1, 1\n"
    "sll   $t2, $t2, 1\n"
    "lh    $t3, 0x00EA($sp)\n"
    "addiu $t3, $t3, 0x0003\n"
    "sh    $t3, 0x00EA($sp)\n"
    "lbl_magicbarsetup:\n"
    "sw    $t0, 0x0040($sp)\n" //magic -> 0x40
    "sw    $t1, 0x0044($sp)\n" //0x13F4 -> 0x44
    "j MagicBarDrawReturn\n" //80073154
    "sw    $t2, 0x0048($sp)\n" //0x13F8 -> 0x48
    ".set at\n .set reorder");
}

void Patched_MagicBarLoads(){
    asm(".set noat\n .set noreorder\n" //              line 28 = 80073148
    "lw    $t7, 0x0044($sp)\n" //lh      t7, 0x13F4($ra) line 97
    "lw    $t6, 0x0044($sp)\n" //lh      t6, 0x13F4($ra) line 176
    "lw    $t7, 0x0044($sp)\n" //lh      t7, 0x13F4($ra) line 190
    "lw    $t7, 0x0048($sp)\n" //lh      t7, 0x13F8($ra) line 372
    "lw    $t7, 0x0040($sp)\n" //lb      t7, 0x0033($ra) line 305
    "lw    $t6, 0x0040($sp)\n" //lb      t6, 0x0033($ra) line 477 but one label
    ".set at\n .set reorder");
}

#define MB_BASE 0x80073148
static const s32 Patched_MagicBarLoadAddrs[6] = {
    MB_BASE + 0x114,
    MB_BASE + 0x250,
    MB_BASE + 0x288,
    MB_BASE + 0x560,
    MB_BASE + 0x454,
    MB_BASE + 0x700
};

void Statics_InterfaceCodePatches(){
    //
    *( (u32*)Interface_LoadItemIcon1   ) = JUMPINSTR(Patched_LoadItemIcon1);
	*(((u32*)Interface_LoadItemIcon1)+1) = 0;
    *( (u32*)Interface_LoadItemIcon2   ) = JUMPINSTR(Patched_LoadItemIcon2);
	*(((u32*)Interface_LoadItemIcon2)+1) = 0;
    //At beginning of z_construct item icon loading, jal Patched_LoadAllItemIcons
    *( (u32*)Construct_Icon_Start   ) = JALINSTR(Patched_LoadAllItemIcons);
	*(((u32*)Construct_Icon_Start)+1) = 0;
    //After returning, jump to end of icon loading
    *(((u32*)Construct_Icon_Start)+2) = JUMPINSTR(Construct_Icon_Target);
    *(((u32*)Construct_Icon_Start)+3) = 0;
    //
    //Equip item animation patch
    *( (u32*)InterfaceEffectTex_Start   ) = JALINSTR(Patched_EquipEffectTexLoad);
    *(((u32*)InterfaceEffectTex_Start)+1) = 0x8E8402B0; //lw a0, 0x02B0(s4)
    *(((u32*)InterfaceEffectTex_Start)+2) = JUMPINSTR(InterfaceEffectTex_Target);
    *(((u32*)InterfaceEffectTex_Start)+3) = 0xAE8202B0; //sw v0, 0x02B0(s4)
    //
    //Get item draw patch
    gDrawItemTable[GID_SAGES_CHARM].dlists[0] = (u32)gGiSagesCharmDL;
    //
    //Magic bar patches
    bcopy(&Patched_MagicBarY1, (void*)(0x800730EC + 0x34), 13 * 4);
    for(s32 i=0; i<6; ++i){
        *((u32*)Patched_MagicBarLoadAddrs[i]) = ((u32*)Patched_MagicBarLoads)[i];
    }
}

void Statics_InterfacePlayerUpdate(){
    //Get item entry patch. This only has to be done once every time the Link
    //overlay has been reloaded, but it's cheap and there's no harm to doing it
    //repeatedly.
    GetItemEntry *relocGetItemTable = (GetItemEntry*)PlayerVRAMtoRAM(linkGetItemTable);
    relocGetItemTable[GI_SAGES_CHARM-1].objectId = OBJECT_GI_SAGESCHARM;
}

extern void *gItemIcons[];

void Statics_InterfaceRegisterStaticData(void *ram_addr, u8 type, s32 data1){
    if(data1 < 0 || data1 > ITEM_NUT_UPGRADE_40) return;
    if(type == 4){
        gItemIcons[data1] = ram_addr;
    }else if(type == 5){
        for(u8 i=0; i<patchedItemNameCount; ++i){
            if(PatchedItemNameTable[i].item == data1){
                PatchedItemNameTable[i].ram_addr = ram_addr;
                return;
            }
        }
        if(patchedItemNameCount >= NUM_PATCHED_ITEM_NAMES) return;
        PatchedItemNameTable[patchedItemNameCount].item = data1;
        PatchedItemNameTable[patchedItemNameCount].ram_addr = ram_addr;
        ++patchedItemNameCount;
    }
}
