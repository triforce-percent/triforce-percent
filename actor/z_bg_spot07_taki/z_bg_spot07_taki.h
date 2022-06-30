#ifndef _Z_BG_SPOT07_TAKI_H_
#define _Z_BG_SPOT07_TAKI_H_

#include "ootmain.h"

struct BgSpot07Taki;

typedef void (*BgSpot07TakiActionFunc)(struct BgSpot07Taki*, GlobalContext*);

typedef struct BgSpot07Taki {
	/* 0x0000 */ DynaPolyActor dyna;
	u8 hasDynaPoly;
} BgSpot07Taki; // size = 0x0168

#define FLAGS 0x00000030
#define THIS ((BgSpot07Taki*)thisx)
#define THAW_TIME 40 /* how many frames thawing takes */
#define WAIT_TIME 30 /* how many frames to wait for the magic to finish */
#define IS_MAIN_ROOM (this->dyna.actor.params == 0)

#define THAWING_STATE_INIT 0
#define THAWING_STATE_WAITMAGIC 1
#define THAWING_STATE_THAWING 2
#define THAWING_STATE_DONE 3

/* persistent flag for keeping track of whether Link has
 * melted the ice yet; the ice will remain melted when
 * leaving and revisiting Zora's Domain
 */
/* TODO please ensure this does not conflict with other flags */
#define FLAG_THAWED (1 << 3)
#define FLAG_THAWED_GET Flags_GetTreasure(globalCtx, FLAG_THAWED)
#define FLAG_THAWED_SET Flags_SetTreasure(globalCtx, FLAG_THAWED)


/* display list stuff */
#define DLIST_WATER_MAIN               SEGMENTED_TO_VIRTUAL(0x06000460)
#define DLIST_WATER_CHAMBER            SEGMENTED_TO_VIRTUAL(0x06000BE0)

#define DLIST_ICE_WATERFALL            SEGMENTED_TO_VIRTUAL(0x06001CF0)
 #define PRIM_ICE_WATERFALL            SEGMENTED_TO_VIRTUAL(0x06001D90)
 #define SETCOMBINE_ICE_WATERFALL      SEGMENTED_TO_VIRTUAL(0x06001D70)
 
#define DLIST_ICE_MAIN                 SEGMENTED_TO_VIRTUAL(0x06001F68)
 #define PRIM_ICE_MAIN_RING            SEGMENTED_TO_VIRTUAL(0x06002090)
 #define SETCOMBINE_ICE_MAIN_RING      SEGMENTED_TO_VIRTUAL(0x06002080)
 
#define DLIST_ICE_WATERFALL_EDGE       SEGMENTED_TO_VIRTUAL(0x06003210)
 #define SETCOMBINE_ICE_WATERFALL_EDGE SEGMENTED_TO_VIRTUAL(0x06003290)
 
#define DLIST_ICE_CHAMBER              SEGMENTED_TO_VIRTUAL(0x060032D8)
 #define PRIM_ICE_CHAMBER_EDGE         SEGMENTED_TO_VIRTUAL(0x06003548)
 #define SETCOMBINE_ICE_CHAMBER_EDGE   SEGMENTED_TO_VIRTUAL(0x06003540)


/* collision headers */
#define COLL_MAIN        SEGMENTED_TO_VIRTUAL(0x06002590)
#define COLL_CHAMBER     SEGMENTED_TO_VIRTUAL(0x060038FC)


#endif
