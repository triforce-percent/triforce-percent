#include "ootmain.h"
#include "statics.h"

#include "../loader/fast_loader/fast_loader.h"
#include "../loader/debugger/debugger.h"
#include "interface.h"
#include "message.h"
#include "anime.h"
#include "ocarina.h"
#include "audio.h"
#include "scene.h"
#include "ossan_related.h"

u8 sIsLiveRun = 0;

void Statics_SetGameState(){
    //Set some event flags
    gSaveContext.eventChkInf[0x1] |= 0x0100; /*0x0902*/ //Ingo/Epona flags
    gSaveContext.eventChkInf[0x2] |= 0x8000; //Death Mountain not on fire
    gSaveContext.eventChkInf[0x9] |= 0x000F; //Rescued carpenters (not get arrested by Gerudos)
    gSaveContext.eventChkInf[0xA] |= 0x0011; //Entered Hyrule Field and Zora's Domain
    gSaveContext.eventChkInf[0xB] |= 0x010C; //Entered Gerudo Valley, Gerudo's Fortress, Desert Colossus
    gSaveContext.eventChkInf[0xC] |= 0x0002; //Spoke to Saria on Lost Woods Bridge
    gSaveContext.itemGetInf[0x1] |= 0x0008; //Has picked up Deku Seeds before
    gSaveContext.itemGetInf[0x2] |= 0x0478; //Obtained Mask of Truth, all trading masks
    gSaveContext.itemGetInf[0x3] |= 0x8F00; //Obtained Mask of Truth, sold all masks
    //gSaveContext.infTable[0x9] |= 0x0490; //Ingo flags
    //gSaveContext.infTable[0xA] |= 0x0800; //Ingo flags
    gSaveContext.infTable[25] |= 0x0100; //Has picked up magic jar before
    //Set flags so Staff Roll entrance cutscenes are not shown
    gSaveContext.eventChkInf[0xA] |= (1 << 8) | (1 << 5);
    gSaveContext.eventChkInf[0xB] |= (1 << 0xB) | (1 << 0xC);
    //Debugging
    
    //Set up Adult Link inventory to not have the Master Sword
    gSaveContext.adultEquips.buttonItems[0] = 0x3D; //ITEM_SWORD_BGS
    gSaveContext.adultEquips.buttonItems[1] = 0xFF; //ITEM_NONE
    gSaveContext.adultEquips.buttonItems[2] = 0x02; //ITEM_BOMB
    gSaveContext.adultEquips.buttonItems[3] = 0x08; //ITEM_OCARINA_TIME
    gSaveContext.adultEquips.cButtonSlots[0] = 0xFF; //SLOT_NONE
    gSaveContext.adultEquips.cButtonSlots[1] = 0x02; //SLOT_BOMB
    gSaveContext.adultEquips.cButtonSlots[2] = 0x07; //SLOT_OCARINA
    gSaveContext.adultEquips.equipment = 0x1103;
    gSaveContext.bgsFlag = 1; //Giant's Knife -> Biggoron Sword
    gSaveContext.swordHealth = 8;
    //Give magic
    gSaveContext.magicAcquired = 1;
    gSaveContext.magicLevel = 2;
    gSaveContext.magic = 0x60;
    gSaveContext.unk_13F4 = 0x60;
    gSaveContext.doubleMagic = 1;
}

void Statics_RomhackLoadAll();

void Statics_OneTimeRomhackOnly(){
    Statics_RomhackLoadAll();
}

void Statics_OneTime(){
	Statics_InterfaceCodePatches();
    Statics_MessageCodePatches();
    Statics_AnimeCodePatches(sIsLiveRun);
    Statics_OcarinaCodePatches();
    Statics_AudioCodePatches(sIsLiveRun);
    Statics_SceneCodePatches();
    osWritebackDCache(0, 0x4000);
    osInvalICache(0, 0x4000);
    if(!sIsLiveRun){
        Statics_OneTimeRomhackOnly();
    }
}

void Statics_InventoryEditor(){
    //Press L on pause menu to toggle inventory editor
    //The "press" variable doesn't quite work right because this is run on the
    //VI, not in sync with the game loop. So we have to keep our own press flag.
    //Also, the game already has code to press L to turn OFF the inventory
    //editor, which conflicts with this. This is why this is convoluted.
    static u8 sLPress = 0;
    static u8 sWasGameStateSet = 0;
    static u16 sInvEditorLastState = 0;
    if(!sLPress){
        if((CTRLR_RAW & BTN_L)){
            sLPress = 1;
            if(!sInvEditorLastState && gGlobalContext.pauseCtx.state){
                if(!sWasGameStateSet){
                    Statics_SetGameState();
                    sWasGameStateSet = 1;
                }
                gGlobalContext.pauseCtx.debugState = 1;
            }
        }
    }else{
        if(!(CTRLR_RAW & BTN_L)){
            sLPress = 0;
        }
    }
    sInvEditorLastState = gGlobalContext.pauseCtx.debugState;
}

void Statics_LostWoods(){
    static s8 sWoodsState = 0, sWoodsTarget = -1, sWoodsCount = 0;
    static const float sWoodsTargetX[3] = {0.0f, 793.0f, 269.0f}; //north, south, west
    static const float sWoodsTargetZ[3] = {-530.0f, 546.0f, -795.0f};
    static const s8 sWoodsPath[4] = {0, 2, 1, 2};
    const float radius = 80.0f;
    Player *player = PLAYER;
    if(gGlobalContext.sceneNum != 0x5B){ //not in Lost Woods
        if(sWoodsState == 1 && sWoodsCount < 4){
             if(sWoodsTarget == sWoodsPath[sWoodsCount]){
                 ++sWoodsCount;
             }else{
                 sWoodsCount = 0;
             }
             //if(sIsLiveRun) Debugger_Printf("sWoodsCount %d", sWoodsCount);
             sWoodsState = 0;
        }
        return;
    }
    //In Lost Woods
    if(sWoodsCount == 4){
        if(sWoodsState < 20){
            ++sWoodsState;
        }else if(sWoodsState == 20){
            Audio_PlayActorSound2(&(player->actor), 0x4802);
            ++sWoodsState;
            BETAKOKIRI_SPAWNED_VAR |= BETAKOKIRI_SPAWNED_BIT;
        }
    }else{
        sWoodsState = 1;
    }
    sWoodsTarget = -1;
    float x = player->actor.world.pos.x;
    float z = player->actor.world.pos.z;
    for(s32 i=0; i<3; ++i){
        float tx = sWoodsTargetX[i] - x;
        float tz = sWoodsTargetZ[i] - z;
        if(tx * tx + tz * tz < radius * radius){
            sWoodsTarget = i;
            break;
        }
    }
    /*
    zh_draw_debug_text(&gGlobalContext, 0xFF8000FF, 1, 1, "s %d t %d c %d %f %f", 
        sWoodsState, sWoodsTarget, sWoodsCount, x, z);
    */
}

void Statics_Player_PatchedRunning(Player* this, f32 arg1, s16 arg2){
    u16 speed = 0x0226;
    if(WearingWorkingBunnyHood()){
        speed = 0x044C;
        arg1 *= 1.5f;
    }
    R_RUN_SPEED_LIMIT = speed;
    Math_AsymStepToF(&this->linearVelocity, arg1, REG(19) / 100.0f, 1.5f);
    Math_ScaledStepToS(&this->currentYaw, arg2, REG(27));
}

extern float linkJumpYSpeed; //D_808535E8 == 808514A8

void Statics_Player_BunnyHood_YSpeed(){
    Player *player = PLAYER;
    if(player->stateFlags1 & 0x8000000) {
        linkJumpYSpeed = 0.5f;
    }else if(WearingWorkingBunnyHood()){
        linkJumpYSpeed = 1.25f;
    }else{
        linkJumpYSpeed = 1.0f;
    }
}

void Statics_TestShortcuts(){
    GlobalContext* globalCtx = &gGlobalContext;
    //Test/Debugging
    if((CTRLR_RAW & BTN_L) && !(CTRLR_RAW & BTN_R) && !(CTRLR_RAW & BTN_Z)){
        if((CTRLR_PRESS & BTN_DDOWN)){
            //Press L+DD to spawn the Arwing
            Actor *arwing = Actor_Find(&globalCtx->actorCtx, ACTOR_EN_CLEAR_TAG, ACTORCAT_BOSS);
            if(arwing == NULL){
                Player *player = PLAYER;
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                    player->actor.world.pos.x,
                    player->actor.world.pos.y + 120.0f,
                    player->actor.world.pos.z,
                    0, 0, 0, 0);
            }
        }else if((CTRLR_PRESS & BTN_DLEFT)){
            /*
            //Press L+DL for frog
            func_8010B680(&gGlobalContext, 0x0901, NULL); //textbox_begin
            */
        }else if((CTRLR_PRESS & BTN_DRIGHT)){
            //Press L+DR for....
            //race test
            // gSaveContext.eventInf[1] |= 1;
            // gSaveContext.timer2State = -30;
            //Warp to Nabooru
            // NABOORU_CONTINUE_VAR |= NABOORU_CONTINUE_BIT;
            // globalCtx->linkAgeOnLoad = 1;
            // globalCtx->nextEntranceIndex = 0x04A6;
            //Warp to Zora's Domain
            // WORKING_BUNNYHOOD_VAR |= WORKING_BUNNYHOOD_BIT;
            // WORKING_GERUDOMASK_VAR |= WORKING_GERUDOMASK_BIT;
            // Statics_GiveLongOfTime();
            // SAGES_CHARM_VAR |= SAGES_CHARM_BIT;
            // globalCtx->linkAgeOnLoad = 0;
            // globalCtx->nextEntranceIndex = 0x0108;
            //Warp to Unicorn Fountain
            // globalCtx->linkAgeOnLoad = 0;
            // globalCtx->nextEntranceIndex = 0x0560;
            //Warp to Chamber of Sages
            // globalCtx->linkAgeOnLoad = 0;
            // globalCtx->nextEntranceIndex = 0x006B;
            // gSaveContext.cutsceneIndex = 0xFFF0;
            //Warp to Staff Roll
            // globalCtx->linkAgeOnLoad = 1;
            // globalCtx->nextEntranceIndex = 0x00CD;
            // gSaveContext.cutsceneIndex = 0xFFF8;
            // Statics_SetUpStaffRoll();
        }else if((CTRLR_PRESS & BTN_DUP)){
            /*
            //Kill Link (sorry) and try to exit cutscene (this usually does not work)
            gSaveContext.health = 0;
            gGlobalContext.csCtx.state = CS_STATE_IDLE;
            */
        }
    }
    const u16 holdbtns = BTN_L | BTN_R | BTN_Z | BTN_B;
    if((CTRLR_RAW & holdbtns) == holdbtns){
        if((CTRLR_PRESS & BTN_DUP)){
            //Warp to Sacred Forest Meadow from warp pad with butterfly
            BETAKOKIRI_SPAWNED_VAR |= BETAKOKIRI_SPAWNED_BIT;
            LOOKING_FOR_BUTTERFLY_VAR |= LOOKING_FOR_BUTTERFLY_BIT;
            SHOP_HAS_BUTTERFLY_VAR |= SHOP_HAS_BUTTERFLY_BIT;
            globalCtx->linkAgeOnLoad = 1;
            globalCtx->nextEntranceIndex = 0x0600;
        }else if((CTRLR_PRESS & BTN_DLEFT)){
            //Warp to Kokiri Forest from Lost Woods with working masks
            WORKING_BUNNYHOOD_VAR |= WORKING_BUNNYHOOD_BIT;
            WORKING_GERUDOMASK_VAR |= WORKING_GERUDOMASK_BIT;
            globalCtx->linkAgeOnLoad = 1;
            globalCtx->nextEntranceIndex = 0x0286;
        }else if((CTRLR_PRESS & BTN_DDOWN)){
            //Warp to Gerudo's Fortress from Thieves' Hideout with Long of Time
            WORKING_BUNNYHOOD_VAR |= WORKING_BUNNYHOOD_BIT;
            WORKING_GERUDOMASK_VAR |= WORKING_GERUDOMASK_BIT;
            Statics_GiveLongOfTime();
            globalCtx->linkAgeOnLoad = 1;
            globalCtx->nextEntranceIndex = 0x02AA;
        }else if((CTRLR_PRESS & BTN_DRIGHT)){
            //Warp to Hyrule Field from Lost Woods Bridge with running man wants to battle
            WORKING_BUNNYHOOD_VAR |= WORKING_BUNNYHOOD_BIT;
            WORKING_GERUDOMASK_VAR |= WORKING_GERUDOMASK_BIT;
            Statics_GiveLongOfTime();
            RUNNINGMAN_WANTS_TO_BATTLE_VAR |= RUNNINGMAN_WANTS_TO_BATTLE_BIT;
            globalCtx->linkAgeOnLoad = 0;
            globalCtx->nextEntranceIndex = 0x0185;
        }else if((CTRLR_PRESS & BTN_CUP)){
            //Warp to Zora's Domain from Zora's River with Sages' Charm
            WORKING_BUNNYHOOD_VAR |= WORKING_BUNNYHOOD_BIT;
            WORKING_GERUDOMASK_VAR |= WORKING_GERUDOMASK_BIT;
            Statics_GiveLongOfTime();
            SAGES_CHARM_VAR |= SAGES_CHARM_BIT;
            globalCtx->linkAgeOnLoad = 0;
            globalCtx->nextEntranceIndex = 0x0108;
        }else if((CTRLR_PRESS & BTN_CLEFT)){
            //Warp to Temple of Time from warp pad with Overture of Sages
            Statics_GiveOvertureOfSages();
            globalCtx->linkAgeOnLoad = 0;
            globalCtx->nextEntranceIndex = 0x05F4;
        }else if((CTRLR_PRESS & BTN_CDOWN)){
            //Warp to Triforce
            globalCtx->linkAgeOnLoad = 0;
            globalCtx->nextEntranceIndex = 0x034D;
        }else if((CTRLR_PRESS & BTN_CRIGHT)){
            //Warp to finale
            globalCtx->linkAgeOnLoad = 0;
            globalCtx->nextEntranceIndex = 0x03FC;
        }else{
            return;
        }
        //Common warp
        gSaveContext.respawnFlag = -2;
        globalCtx->sceneLoadFlag = 0x14;
        globalCtx->fadeTransition = 0x2C;
        gSaveContext.nextTransition = 5;
    }
}

void Statics_PatchShop(){
    GlobalContext* globalCtx = &gGlobalContext;
    if(globalCtx->sceneNum != SCENE_SHOP1) return;
    //Get actor and overlay
    Actor* ossanActor = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].head;
    while(ossanActor != NULL){
        if(ossanActor->id == ACTOR_EN_OSSAN) break;
        ossanActor = ossanActor->next;
    }
    if(ossanActor == NULL) return;
    EnOssan* ossan = (EnOssan*)ossanActor;
    void* ossanOverlay = gActorOverlayTable[ACTOR_EN_OSSAN].loadedRamAddr;
    if(ossanOverlay == NULL) return;
    //Check logic
    if(!(LOOKING_FOR_BUTTERFLY_VAR & LOOKING_FOR_BUTTERFLY_BIT)) return;
    if(globalCtx->msgCtx.unk_E2F8 == 0x009C){ //textId
        SHOP_HAS_BUTTERFLY_VAR |= SHOP_HAS_BUTTERFLY_BIT;
    }
    if(!(SHOP_HAS_BUTTERFLY_VAR & SHOP_HAS_BUTTERFLY_BIT)) return;
    //Change store item
    ShopItem* sShopkeeperStores = (ShopItem*)(ossanOverlay + 0x58F0);
    ShopItem* butterflyEntry = &sShopkeeperStores[4*8+3];
    if(butterflyEntry->shopItemIndex != SI_BUTTERFLY){
        if(ossan->shelfSlots[3] == NULL){
            //Link actor update ran before ossan actor init
            butterflyEntry->shopItemIndex = SI_BUTTERFLY;
        }else if(ossan->shelves != NULL){
            //Make sure shelves are loaded, otherwise don't do this until next frame
            butterflyEntry->shopItemIndex = SI_BUTTERFLY;
            Actor_Kill(&ossan->shelfSlots[3]->actor);
            ossan->shelfSlots[3] = (EnGirlA*)Actor_Spawn(
                &globalCtx->actorCtx, globalCtx, ACTOR_EN_GIRLA,
                ossan->shelves->actor.world.pos.x + butterflyEntry->xOffset,
                ossan->shelves->actor.world.pos.y + butterflyEntry->yOffset,
                ossan->shelves->actor.world.pos.z + butterflyEntry->zOffset,
                ossan->shelves->actor.shape.rot.x,
                ossan->shelves->actor.shape.rot.y + 0xEAAC,
                ossan->shelves->actor.shape.rot.z,
                SI_BUTTERFLY);
        }
    }
}

void Statics_MoveOddPotionToChild(){
    if(gSaveContext.inventory.items[SLOT_TRADE_ADULT] == ITEM_ODD_POTION){
        gSaveContext.inventory.items[SLOT_TRADE_ADULT] = ITEM_NONE;
        gSaveContext.inventory.items[SLOT_TRADE_CHILD] = ITEM_ODD_POTION;
    }
}

void Statics_FixWaterSpawn(){
    InterfaceContext *interfaceCtx = &gGlobalContext.interfaceCtx;
    if(gGlobalContext.sceneNum == SCENE_UNICORNFOUNTAIN){
        //gSaveContext.equips.equipment = (gSaveContext.equips.equipment & 0x0FFF) | 0x1000;
        //gSaveContext.adultEquips.equipment = (gSaveContext.adultEquips.equipment & 0x0FFF) | 0x1000;
        interfaceCtx->restrictions.hGauge = interfaceCtx->restrictions.bButton =
        interfaceCtx->restrictions.aButton = interfaceCtx->restrictions.bottles =
        interfaceCtx->restrictions.tradeItems = interfaceCtx->restrictions.hookshot =
        interfaceCtx->restrictions.ocarina = interfaceCtx->restrictions.warpSongs =
        interfaceCtx->restrictions.sunsSong = interfaceCtx->restrictions.farores =
        interfaceCtx->restrictions.dinsNayrus = interfaceCtx->restrictions.all = 0;
    }
}

void Statics_KeepTimerNegative(){
    if((gSaveContext.eventInf[1] & 1) && (LINK_IS_CHILD) 
            && gSaveContext.timer2Value < -15 && gSaveContext.timer2Value > -20){
        gSaveContext.timer2Value = -90;
    }
}

void Statics_Player_Init(){
    //Patch overwrote 
    //globalCtx->shootingGalleryStatus = globalCtx->bombchuBowlingStatus = 0;
    //so we have to do that
    ((u8*)&gGlobalContext)[0x11E5C] = 0;
    ((u8*)&gGlobalContext)[0x11E5D] = 0;
    //nothing using this right now
}

static u8 sOneTime = 0;
static u8 sPatchWaitCounter = 0;

void Statics_Player_Update(){
    //Patch overwrote this
    if(PLAYER->unk_A73 != 0) PLAYER->unk_A73--;
    //Custom content
    if(!sIsLiveRun && !sOneTime){
        if(sPatchWaitCounter < 40){
            ++sPatchWaitCounter;
        }else{
            Statics_OneTime();
            sOneTime = 1;
        }
    }
    Statics_TestShortcuts();
    Statics_LostWoods();
    Statics_PatchShop();
    Statics_MoveOddPotionToChild();
    Statics_FixWaterSpawn();
    Statics_KeepTimerNegative();
    Statics_AnimePlayerUpdate();
    Statics_InterfacePlayerUpdate();
    Audio_BGMButtonHandler();
    /*
    static u8 oldMsgMode = 0;
    static u16 oldOcarinaAction = 0;
    if(sIsLiveRun && (gGlobalContext.msgCtx.msgMode != oldMsgMode 
            || gGlobalContext.msgCtx.unk_E3F0 != oldOcarinaAction)){
        Debugger_Printf("msgMode %X oc %04X", 
            gGlobalContext.msgCtx.msgMode, gGlobalContext.msgCtx.unk_E3F0);
        oldMsgMode = gGlobalContext.msgCtx.msgMode;
        oldOcarinaAction = gGlobalContext.msgCtx.unk_E3F0;
    }
    */
}

void Statics_Update(){
    if(sIsLiveRun && !sOneTime){
        Statics_OneTime();
        sOneTime = 1;
    }
    Statics_InventoryEditor();
    Statics_HandleEquipMedallionsToC();
	gSaveContext.naviTimer = 1;
}

__attribute__((section(".start"))) void Statics_Init(){
    fp_precmd = Statics_Update;
    sOneTime = 0;
    sIsLiveRun = 1;
    //Zero bootstrapper 3/4 data at 0x80700000 in case the bss section of some
    //static code ends up there and needs to assume it's zeroed (probably won't
    //happen). Bootstrapper 4 is currently 88 bytes plus 4 for address counter.
    bzero((void*)0x80700000, 256);
}

static void* malloc_addr = (void*)0x80440000;

void* Statics_StaticDataMalloc(u32 size){
    void* ret = malloc_addr;
    malloc_addr = (void*)(((u32)malloc_addr + size + 15) & ~15);
    return ret;
}

void Statics_RegisterStaticData(void* ram_addr, s32 type_and_size, 
        s32 data1, s32 data2){
    u32 size = type_and_size & 0x00FFFFFF;
    u8 type = type_and_size >> 24;
    if(type == 0){
        Statics_AnimeRegisterStaticData(ram_addr);
    }else if(type >= 1 && type <= 3){
        Statics_AudioRegisterStaticData(ram_addr, size, type, data1, data2);
    }else if(type == 4 || type == 5){
        Statics_InterfaceRegisterStaticData(ram_addr, type, data1);
    }
}

//Data here is the four parameters to Statics_RegisterStaticData
#define MAX_STATICDATA 48
static s32 romhackFileInfo[4*MAX_STATICDATA] = { 
    0xDEADBEEF, 0x04206969, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1
};

void Statics_RomhackLoadAll(){
    for(s32 i=0; i<MAX_STATICDATA; ++i){
        s32 addr = romhackFileInfo[4*i];
        if(addr == 0) break;
        s32 type_and_size = romhackFileInfo[4*i+1];
        u32 size = type_and_size & 0x00FFFFFF;
        void* target = Statics_StaticDataMalloc(size);
        DmaRequest req;
        req.vromAddr = addr;
        req.dramAddr = target;
        req.size = size;
        req.filename = NULL;
        req.line = 0;
        req.unk_14 = 0;
        req.notifyQueue = NULL;
        DmaMgr_ProcessMsg(&req);
        Statics_RegisterStaticData(target, type_and_size, 
            romhackFileInfo[4*i+2], romhackFileInfo[4*i+3]);
    }
}

void Statics_TimeTravel(){
    GlobalContext *globalCtx = &gGlobalContext;
    if(!(LONGOFTIME_VAR & LONGOFTIME_BIT) 
        || globalCtx->sceneNum == SCENE_TOKINOMA 
        || globalCtx->sceneNum == SCENE_GERUDOWAY){
        return;
    }
    if((gSaveContext.eventInf[1] & 1)){
        //Timer 2 (Running Man race) is active
        if(LINK_IS_CHILD){
            gSaveContext.timer2Value = -10; //10 seconds to time 0
            gSaveContext.nextDayTime = 0x4000;
        }else{
            //gCounterDigit0Tex = 02003040, size of each digit is 0x80
            //Want to stay in bounds in segment 2. Over 1:30 should be plenty of
            //time to get across Hyrule Field, even without the Bunny Hood
            gSaveContext.timer2Value = -96;
        }
    }
    //Time travel
    globalCtx->linkAgeOnLoad = gSaveContext.linkAge ^ 1;
    gSaveContext.respawnFlag = -2;
    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->nextEntranceIndex = gSaveContext.entranceIndex;
    globalCtx->fadeTransition = 0x2C;
    gSaveContext.nextTransition = 5;
}

void Statics_GiveLongOfTime(){
    LONGOFTIME_VAR |= LONGOFTIME_BIT;
    Ocarina_GiveLongOfTime();
}

void Statics_GiveOvertureOfSages(){
    OVERTUREOFSAGES_VAR |= OVERTUREOFSAGES_BIT;
    Ocarina_GiveOvertureOfSages();
}

s32 Statics_ShouldAbortWarp(){
    GlobalContext *globalCtx = &gGlobalContext;
    Player *player = PLAYER;
    player->csMode = 0;
    player->stateFlags1 &= ~0x20000000;
    if(globalCtx->msgCtx.unk_E3EC != 1 //Bolero of Fire not played
        || !(OVERTUREOFSAGES_VAR & OVERTUREOFSAGES_BIT)) return 0;
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_WSRCUTSCENE, 
        0.0f, 0.0f, 0.0f, 0, 0, 0, 0x0000);
    func_800ED858(0); //disable ocarina
    globalCtx->msgCtx.unk_E3EE = 4; //Link exit ocarina mode
    globalCtx->csCtx.state = 0; //try to go back to normal
    Message_Close(globalCtx);
	gSaveContext.respawn[RESPAWN_MODE_RETURN].playerParams = PLAYER->actor.params;
    return 1;
}

void Statics_Ge2DialogueGet(){
    asm(".set noat\n .set noreorder\n"
    "lui   $t0, %hi(gSaveContext)\n"
    "addiu $t1, $t0, %lo(gSaveContext)\n"
    "lbu   $t2, 0x0F24($t1)\n"
    "srl   $t3, $t2, 6\n"
    "addiu $t5, $t3, 0x0B50\n"
    "jr $ra\n"
    "sh    $t5, 0x010E($s0)\n"
    ".set at\n .set reorder");
}

void Statics_Ge2DialogueUpdate(){
    asm(".set noat\n .set noreorder\n"
    "lh    $t6, 0x001C($s0)\n" //what we replaced
    "lui   $t0, %hi(gSaveContext)\n"
    "addiu $t1, $t0, %lo(gSaveContext)\n"
    "lbu   $t2, 0x0F24($t1)\n"
    "addiu $t3, $t2, 0x0040\n"
    "jr $ra\n"
    "sb    $t3, 0x0F24($t1)\n"
    ".set at\n .set reorder");
}

bool Statics_UncullObject(GlobalContext* globalCtx, Vec3f *center, float xsize, 
	float yBelow, float yAbove, float zBehind, float zFar){
	//Based on func_800314D4
	Vec3f screen;
	float screen_w;
	func_8002BE04(globalCtx, center, &screen, &screen_w);
	//Debugger_Printf("%f %f %f", screen.x * screen_w, screen.y * screen_w, screen.z);
	return (screen.z > -zBehind) &&
		(screen.z < zFar) &&
		((fabsf(screen.x) - xsize) * screen_w < 1.0f) &&
		((screen.y + yAbove) * screen_w > -1.0f) &&
		((screen.y - yBelow) * screen_w < 1.0f);
}
