
struct EnTana;

typedef struct EnTana {
    /* 0x0000 */ Actor actor;
} EnTana; // size = 0x014C

struct EnGirlA;

typedef void (*EnGirlAActionFunc)(struct EnGirlA*, GlobalContext*);
typedef void (*EnGirlA2Func)(GlobalContext*, struct EnGirlA*);
typedef void (*EnGirlA3Func)(Actor*, GlobalContext*, s32);
typedef s32 (*EnGirlA4Func)(GlobalContext*, struct EnGirlA*);

typedef struct EnGirlA {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ EnGirlAActionFunc actionFunc;
    /* 0x0194 */ s8 objBankIndex;
    /* 0x0198 */ EnGirlAActionFunc actionFunc2;
    /* 0x019C */ s32 isInitialized;
    /* 0x01A0 */ s16 itemBuyPromptTextId;
    /* 0x01A4 */ s32 getItemId;
    /* 0x01A8 */ s16 isInvisible;
    /* 0x01AC */ EnGirlA2Func setOutOfStockFunc;
    /* 0x01B0 */ EnGirlA2Func updateStockedItemFunc;
    /* 0x01B4 */ s16 isSelected;
    /* 0x01B6 */ s16 yRotationInit;
    /* 0x01B8 */ s16 yRotation;
    /* 0x01BC */ EnGirlA4Func canBuyFunc;
    /* 0x01C0 */ EnGirlA2Func itemGiveFunc;
    /* 0x01C4 */ EnGirlA2Func buyEventFunc;
    /* 0x01C8 */ s16 basePrice;
    /* 0x01CA */ s16 itemCount;
    /* 0x01CC */ s16 giDrawId;
    /* 0x01D0 */ EnGirlA3Func hiliteFunc;
} EnGirlA; // size = 0x01D4

typedef enum {
    /* 0x00 */ SI_DEKU_NUTS_5,
    /* 0x01 */ SI_ARROWS_30,
    /* 0x02 */ SI_ARROWS_50,
    /* 0x03 */ SI_BOMBS_5_R25,
    /* 0x04 */ SI_DEKU_NUTS_10,
    /* 0x05 */ SI_DEKU_STICK,
    /* 0x06 */ SI_BOMBS_10,
    /* 0x07 */ SI_FISH,
    /* 0x08 */ SI_RED_POTION_R30,
    /* 0x09 */ SI_GREEN_POTION,
    /* 0x0A */ SI_BLUE_POTION,
    /* 0x0B */ SI_LONGSWORD,
    /* 0x0C */ SI_HYLIAN_SHIELD,
    /* 0x0D */ SI_DEKU_SHIELD,
    /* 0x0E */ SI_GORON_TUNIC,
    /* 0x0F */ SI_ZORA_TUNIC,
    /* 0x10 */ SI_HEART,
    /* 0x11 */ SI_MILK_BOTTLE,
    /* 0x12 */ SI_WEIRD_EGG,
    /* 0x13 */ SI_19,
    /* 0x14 */ SI_20,
    /* 0x15 */ SI_BOMBCHU_10_1,
    /* 0x16 */ SI_BOMBCHU_20_1,
    /* 0x17 */ SI_BOMBCHU_20_2,
    /* 0x18 */ SI_BOMBCHU_10_2,
    /* 0x19 */ SI_BOMBCHU_10_3,
    /* 0x1A */ SI_BOMBCHU_20_3,
    /* 0x1B */ SI_BOMBCHU_20_4,
    /* 0x1C */ SI_BOMBCHU_10_4,
    /* 0x1D */ SI_DEKU_SEEDS_30,
    /* 0x1E */ SI_KEATON_MASK,
    /* 0x1F */ SI_SPOOKY_MASK,
    /* 0x20 */ SI_SKULL_MASK,
    /* 0x21 */ SI_BUNNY_HOOD,
    /* 0x22 */ SI_MASK_OF_TRUTH,
    /* 0x23 */ SI_ZORA_MASK,
    /* 0x24 */ SI_GORON_MASK,
    /* 0x25 */ SI_GERUDO_MASK,
    /* 0x26 */ SI_SOLD_OUT,
    /* 0x27 */ SI_BLUE_FIRE,
    /* 0x28 */ SI_BUGS,
    /* 0x29 */ SI_BIG_POE,
    /* 0x2A */ SI_POE,
    /* 0x2B */ SI_FAIRY,
    /* 0x2C */ SI_ARROWS_10,
    /* 0x2D */ SI_BOMBS_20,
    /* 0x2E */ SI_BOMBS_30,
    /* 0x2F */ SI_BOMBS_5_R35,
    /* 0x30 */ SI_RED_POTION_R40,
    /* 0x31 */ SI_RED_POTION_R50,
    /* 0x32 */ SI_MAX
} EnGirlAShopItem;

struct EnOssan;

typedef void (*EnOssanActionFunc)(struct EnOssan*, GlobalContext*);

typedef struct {
    /* 0x00 */ u32 stickColorR;
    /* 0x04 */ u32 stickColorG;
    /* 0x08 */ u32 stickColorB;
    /* 0x0C */ u32 stickColorA;
    /* 0x10 */ f32 stickTexX;
    /* 0x14 */ f32 stickTexY;
    /* 0x18 */ u32 arrowColorR;
    /* 0x1C */ u32 arrowColorG;
    /* 0x20 */ u32 arrowColorB;
    /* 0x24 */ u32 arrowColorA;
    /* 0x28 */ f32 arrowTexX;
    /* 0x2C */ f32 arrowTexY;
    /* 0x30 */ f32 z;
    /* 0x34 */ s32 isEnabled;
} StickDirectionPrompt; // size = 0x38

typedef struct EnOssan {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ EnOssanActionFunc actionFunc;
    /* 0x0194 */ void (*obj3ToSeg6Func)(struct EnOssan*, GlobalContext*);
    /* 0x0198 */ ColliderCylinder collider; // unused
    /* 0x01E4 */ s16 timer;
    /* 0x01E6 */ s16 delayTimer;
    /* 0x01E8 */ s8 objBankIndex1;
    /* 0x01E9 */ s8 objBankIndex2;
    /* 0x01EA */ s8 objBankIndex3;
    /* 0x01EB */ u8 happyMaskShopState;
    /* 0x01EC */ u8 happyMaskShopkeeperEyeIdx;
    /* 0x01EE */ s16 headRot;
    /* 0x01F0 */ s16 headTargetRot;
    /* 0x01F2 */ s16 eyeTextureIdx;
    /* 0x01F4 */ s16 blinkTimer;
    /* 0x01F8 */ void (*blinkFunc)(struct EnOssan*);
    /* 0x01FC */ s16 stateFlag;
    /* 0x01FE */ s16 tempStateFlag;
    /* 0x0200 */ EnGirlA* shelfSlots[8];
    // Shelves are indexed as such:
    /* 7 5  3 1 */
    /* 6 4  2 0 */
    /* 0x0220 */ EnTana* shelves;
    /* 0x0224 */ s32 stickAccumX;
    /* 0x0228 */ s32 stickAccumY;
    /* 0x022C */ u8 moveHorizontal;
    /* 0x022D */ u8 moveVertical;
    /* 0x0230 */ f32 cursorX;
    /* 0x0234 */ f32 cursorY;
    /* 0x0238 */ f32 cursorZ;
    /* 0x023C */ u32 cursorColorR;
    /* 0x0240 */ u32 cursorColorG;
    /* 0x0244 */ u32 cursorColorB;
    /* 0x0248 */ u32 cursorColorA;
    /* 0x024C */ f32 cursorAnimTween;
    /* 0x0250 */ u8 cursorAnimState;
    /* 0x0251 */ u8 drawCursor;
    /* 0x0252 */ u8 cursorIndex;
    /* 0x0254 */ StickDirectionPrompt stickLeftPrompt;
    /* 0x028C */ StickDirectionPrompt stickRightPrompt;
    /* 0x02C4 */ f32 arrowAnimTween;
    /* 0x02C4 */ f32 stickAnimTween;
    /* 0x02CC */ u8 arrowAnimState;
    /* 0x02CD */ u8 stickAnimState;
    /* 0x02D0 */ f32 shopItemSelectedTween;
    /* 0x02D4 */ f32 cameraFaceAngle; // stored in degrees
} EnOssan; // size = 0x02D8

typedef struct {
    /* 0x00 */ s16 shopItemIndex;
    /* 0x02 */ s16 xOffset;
    /* 0x04 */ s16 yOffset;
    /* 0x06 */ s16 zOffset;
} ShopItem; // size 0x08
