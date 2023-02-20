/*
 * File: z_bg_spot07_taki.c
 * Overlay: ovl_Bg_Spot07_Taki
 * Description: Zora's Domain Waterfall and Ice
 * Triforce% ice melting magic courtesy of z64me <z64.me>
 * TODO @zel don't forget about that fancy camera angle magic and improved steam particles 8)
 */

#include "ootmain.h"
#include "z_bg_spot07_taki.h"

/* original functions */
static void BgSpot07Taki_Init(Actor* thisx, GlobalContext* globalCtx);
static void BgSpot07Taki_Destroy(Actor* thisx, GlobalContext* globalCtx);
static void BgSpot07Taki_Update(Actor* thisx, GlobalContext* globalCtx);
static void BgSpot07Taki_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_BG,
	.flags = FLAGS,
	.objectId = OBJECT_SPOT07_OBJECT,
	.instanceSize = sizeof(BgSpot07Taki),
	.init = (ActorFunc)BgSpot07Taki_Init,
	.destroy = (ActorFunc)BgSpot07Taki_Destroy,
	.update = (ActorFunc)BgSpot07Taki_Update,
	.draw = (ActorFunc)BgSpot07Taki_Draw
};

static InitChainEntry sInitChain[] = {
	ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

/* this is shared by all instances */
static struct
{
	u8 nonzero; /* XXX must be first */
	u8 objectIsPatched;
	u8 thawingState;
	u8 thawingTimer;
	struct
	{
		u8 water;
		u8 ice;
		u8 frozenWaterfall;
	} maxOpacity;
	struct
	{
		u8 water;
		u8 ice;
		u8 frozenWaterfall;
	} curAlpha;
} g = {-1};

/* disable primcolor in a display list so we can control it through code */
static u8 NopPrimColorAndGetFirst(void *dlist)
{
	u8 *i;
	u8 rval = 0;
	for (i = dlist; *i != 0xdf; i += 8)
	{
		if (*i == 0xfa)
		{
			if (!rval) /* want only first primcolor alpha */
				rval = i[7];
			*(u32*)(i) = 0;
			*(u32*)(i+4) = 0;
			//Lib_MemSet(i, 8, 0);
		}
	}
	return rval;
}

static void PatchWaterfallVtxAlphas(BgSpot07Taki* this)
{
	/* alpha value of each waterfall vertex, used for fade-in */
	static const u8 vertexAlpha[] = {
		127, 127, 127, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 250, 250, 250, 250, 250, 250, 255, 0, 255, 0, 0, 0, 0, 255,
		0, 0, 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 0, 255, 202, 164, 127,
		164, 202, 202, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0
	};
	u8 *v = SEGMENTED_TO_VIRTUAL(0x06000000);
	int i;
	float multiplier = (float)g.curAlpha.water / (float)g.maxOpacity.water;
	
	for (i = 0; i < sizeof(vertexAlpha); ++i, v += 16)
	{
		v[15] = vertexAlpha[i] * multiplier;
	}
}

static void OverwritePrimColorCmd(Gfx *p, u8 r, u8 g, u8 b, u8 a)
{
	gDPSetPrimColor(p++, 0, 0, r, g, b, a);
}

static void OverwriteCombineRenderNoTexAlpha(Gfx *p)
{
	gDPSetCombineLERP(p++, TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, 
		COMBINED, 0, PRIMITIVE, 0, COMBINED, 0, PRIMITIVE, 0);
	gDPSetRenderMode(p++, AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL 
		| GBL_c1(G_BL_CLR_FOG, G_BL_A_SHADE, G_BL_CLR_IN, G_BL_1MA), G_RM_AA_ZB_XLU_SURF2);
}

static void OverwriteCombineRenderTexAlpha(Gfx *p, int stride)
{
	Gfx* pOld = p;
	gDPSetCombineLERP(p++, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, 
		COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED);
	if (stride)
    {
        p = &pOld[stride];
    }
	gDPSetRenderMode(p++, AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL 
		| GBL_c1(G_BL_CLR_FOG, G_BL_A_SHADE, G_BL_CLR_IN, G_BL_1MA), G_RM_AA_ZB_XLU_SURF2);
}

static void PatchObject(BgSpot07Taki *this, GlobalContext *globalCtx)
{
	static bool loadedMaxAlphas = false;
	
	u8 w, i, f;
	w = NopPrimColorAndGetFirst(DLIST_WATER_MAIN);
	NopPrimColorAndGetFirst(DLIST_WATER_CHAMBER);
	i = NopPrimColorAndGetFirst(DLIST_ICE_MAIN);
	NopPrimColorAndGetFirst(DLIST_ICE_CHAMBER);
	f = NopPrimColorAndGetFirst(DLIST_ICE_WATERFALL);
	NopPrimColorAndGetFirst(DLIST_ICE_WATERFALL_EDGE);
	
	if(!loadedMaxAlphas){
		g.maxOpacity.water = w;
		g.maxOpacity.ice = i;
		g.maxOpacity.frozenWaterfall = f;
		loadedMaxAlphas = true;
	}
	
	OverwriteCombineRenderTexAlpha(SETCOMBINE_ICE_MAIN_RING, 0);
	OverwriteCombineRenderTexAlpha(SETCOMBINE_ICE_CHAMBER_EDGE, 5);
	OverwriteCombineRenderNoTexAlpha(SETCOMBINE_ICE_WATERFALL);
	OverwriteCombineRenderNoTexAlpha(SETCOMBINE_ICE_WATERFALL_EDGE);
}

/* this enables/disables the Zora's Domain water caustic effect */
static void SetCaustics(BgSpot07Taki* this, bool enabled)
{
	u32 *v = 0;
	u32 original = 0; /* original opcode */
#ifdef _Z64HDR_MQ_DEBUG_
	v = (void*)(0x8009E730 + 0x54);
	original = 0x00001825; /* or v1, r0, r0 */
#elif defined(_Z64HDR_U10_)
	v = (void*)(0x800871B8 + 0x38);
	original = 0x00004825; /* or t1, r0, r0 */
#else
	#error SetCaustics unsupported game version
	return;
#endif
	if (!v || !original)
		return;
	*v = (enabled ? 0 : original);
	osWritebackDCache(v, 4);
	osInvalICache(v, 4);
}

static void SpawnWaterfallSound(BgSpot07Taki* this, GlobalContext* globalCtx)
{
	Actor *wow;
	Vec3f pos;
	u16 var;
	if (IS_MAIN_ROOM)
		var = 0x0003, pos = (Vec3f){-189, 17, -941};
	else
		var = 0x0000, pos = (Vec3f){652, 857, -1691};
	
	/* don't spawn if already exists */
	this->dyna.actor.world.pos = pos;
	wow = Actor_FindNearby(globalCtx, &this->dyna.actor, ACTOR_EN_RIVER_SOUND, ACTORCAT_BG, 10);
	this->dyna.actor.world.pos = this->dyna.actor.home.pos;
	if (wow)
		return;
	
	Actor_Spawn(
		&globalCtx->actorCtx
		, globalCtx
		, ACTOR_EN_RIVER_SOUND
		, pos.x, pos.y, pos.z
		, 0, 0, 0
		, var
	);
}

static void BgSpot07Taki_Init(Actor* thisx, GlobalContext* globalCtx) {
	BgSpot07Taki* this = THIS;
	CollisionHeader* colHeader = NULL;
	
	//Uncomment this to reset the flag so we can try again
	//globalCtx->actorCtx.flags.chest &= ~(1 << FLAG_THAWED);

	DynaPolyActor_Init(&this->dyna, DPM_PLAYER);
	Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
	PatchObject(this, globalCtx);
	
	if (LINK_IS_ADULT && !FLAG_THAWED_GET)
	{
		//Start up in ice state
		g.curAlpha.water = 0;
		g.curAlpha.ice = g.maxOpacity.ice;
		g.curAlpha.frozenWaterfall = g.maxOpacity.frozenWaterfall;
		SetCaustics(this, false);
		
		this->hasDynaPoly = true;
		if (IS_MAIN_ROOM) {
			CollisionHeader_GetVirtual(COLL_MAIN, &colHeader);
		} else {
			CollisionHeader_GetVirtual(COLL_CHAMBER, &colHeader);
		}
		this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna,
			&this->dyna.actor, colHeader);
	}
	else
	{
		//Start up in water state
		g.curAlpha.water = g.maxOpacity.water;
		g.curAlpha.ice = 0;
		g.curAlpha.frozenWaterfall = 0;
		SetCaustics(this, true);
		
		if(LINK_IS_ADULT) SpawnWaterfallSound(this, globalCtx);
	}
}

static void BgSpot07Taki_Destroy(Actor* thisx, GlobalContext* globalCtx) {
	BgSpot07Taki* this = THIS;
	
	if (this->hasDynaPoly)
		DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

static void BgSpot07Taki_Update(Actor* thisx, GlobalContext* globalCtx) {
	BgSpot07Taki* this = THIS;
	PatchObject(this, globalCtx);
	/*
	//Manual alpha controls
	if(g.thawingState == THAWING_STATE_INIT || g.thawingState == THAWING_STATE_DONE){
		s32 t;
		if((CTRLR_RAW & BTN_DLEFT)){
			t = (s32)g.curAlpha.water - 2; if(t < 0) t = 0; g.curAlpha.water = t;
		}else if((CTRLR_RAW & BTN_DRIGHT)){
			t = (s32)g.curAlpha.water + 2; if(t > 255) t = 255; g.curAlpha.water = t;
		}else if((CTRLR_RAW & BTN_DDOWN)){
			t = (s32)g.curAlpha.ice - 2; if(t < 0) t = 0; g.curAlpha.ice = t;
		}else if((CTRLR_RAW & BTN_DUP)){
			t = (s32)g.curAlpha.ice + 2; if(t > 255) t = 255; g.curAlpha.ice = t;
		}else if((CTRLR_RAW & BTN_L)){
			t = (s32)g.curAlpha.frozenWaterfall - 2; if(t < 0) t = 0; g.curAlpha.frozenWaterfall = t;
		}else if((CTRLR_RAW & BTN_R)){
			t = (s32)g.curAlpha.frozenWaterfall + 2; if(t > 255) t = 255; g.curAlpha.frozenWaterfall = t;
		}
	}
	*/
	if(g.thawingState == THAWING_STATE_INIT){
		if (func_80043590(&this->dyna) /* Link is standing on ice */
			/* used Din's Fire */
			&& Actor_Find(&globalCtx->actorCtx, ACTOR_MAGIC_FIRE, ACTORCAT_ITEMACTION))
		{
			g.thawingTimer = 0;
			g.thawingState = THAWING_STATE_WAITMAGIC;
		}
	}else if(g.thawingState == THAWING_STATE_WAITMAGIC){
		if(g.thawingTimer == WAIT_TIME){
			Audio_PlayActorSound2(&PLAYER->actor, NA_SE_EV_ICE_MELT);
			g.thawingTimer = 0;
			g.thawingState = THAWING_STATE_THAWING;
		}else{
			++g.thawingTimer;
		}
	}else if(g.thawingState == THAWING_STATE_THAWING){
		if(g.thawingTimer == THAW_TIME / 6){
			Audio_PlayActorSound2(&PLAYER->actor, NA_SE_SY_CORRECT_CHIME);
		}
		if(g.thawingTimer == THAW_TIME / 2){
			SetCaustics(this, true);
			SpawnWaterfallSound(this, globalCtx);
			FLAG_THAWED_SET;
		}else if(g.thawingTimer == THAW_TIME){
			if (this->hasDynaPoly){
				DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
				this->hasDynaPoly = false;
			}
			g.thawingState = THAWING_STATE_DONE;
		}
		float ratio = (float)g.thawingTimer / (float)THAW_TIME;
		float invratio = 1.0f - ratio;
		g.curAlpha.water = ratio * g.maxOpacity.water;
		g.curAlpha.ice = invratio * g.maxOpacity.ice;
		g.curAlpha.frozenWaterfall = invratio * g.maxOpacity.frozenWaterfall;
		++g.thawingTimer;
		
		/* wow - unintelligible dust spawning magic courtesy of z64me <z64.me> */
		static int ok = -1;
		static float wow = -1;
		
		if (ok < 0)
		{
			ok = 1;
			wow = 1;
		}
		
		if (ok < 0)
			return;
		
		if (!(ok & 3))
		{
			for(s32 i=0; i<5; ++i){
				if(wow < Rand_ZeroOne()) continue;
				Vec3f pos = PLAYER->actor.world.pos;
				pos.x += Rand_CenteredFloat(180.0f) + Rand_CenteredFloat(80.0f);
				pos.y += Rand_ZeroFloat(40.0f) - 10.0f;
				pos.z += Rand_CenteredFloat(180.0f) + Rand_CenteredFloat(80.0f);
				Vec3f vel = {0.0f, 0.0f, 0.0f};
				Vec3f accel = {0.0f, 0.9f, 0.0f};
				Color_RGBA8 prim = { 255, 0, 0, 255 };
				Color_RGBA8 env = { 160, 0, 0, 255 };
				prim.g = prim.b = (1.0 - wow) * (250 / 2);
				prim.g += 127;
				prim.b *= 2;
				env.g = prim.g / 2;
				env.b = prim.b / 2;
				func_8002829C(globalCtx, &pos, &vel, &accel, &prim, &env,
					600.0f, 120.0f);
			}
			wow -= 0.1f;
			if (wow <= 0)
				ok = -1;
		}
		++ok;
	}
	
	//fade out snow
	if(g.thawingState >= THAWING_STATE_THAWING){
		globalCtx->envCtx.unk_EE[3] = 0; //target number of snowflakes
		//current number of snowflakes
		if(globalCtx->envCtx.unk_EE[2] > 0 && (globalCtx->state.frames % 4) == 0){
			globalCtx->envCtx.unk_EE[2] -= 2;
		}
	}
}

static void BgSpot07Taki_Draw(Actor* thisx, GlobalContext* globalCtx) {
	BgSpot07Taki* this = THIS;
	u32 frames;
	
	//OPEN_DISPS(globalCtx->state.gfxCtx, "../z_bg_spot07_taki.c", 169);
	frames = globalCtx->gameplayFrames;

	gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_bg_spot07_taki.c", 191),
		G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
	
    func_80093D84(globalCtx->state.gfxCtx);
	
	gSPSetOtherMode(POLY_XLU_DISP++, G_SETOTHERMODE_H, 4, 20, 
		G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP 
		| G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE);
	gSPSetOtherMode(POLY_XLU_DISP++, G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL 
		| G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_SURF2);
	gSPSetGeometryMode(POLY_XLU_DISP++, 
		G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH);
	gSPClearGeometryMode(POLY_XLU_DISP++, 
		G_CULL_FRONT | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR);
	
	// Needed for both water and ice
	gSPSegment(
		POLY_XLU_DISP++
		, 0x08
		, Gfx_TwoTexScroll(
			globalCtx->state.gfxCtx
			, 0, ((frames * -1) & 0x7F), ((frames * 1) & 0x7F), 32, 32
			, 1, ((frames * 1) & 0x7F), ((frames * 1) & 0x7F), 32, 32
		)
	);

	if (g.curAlpha.water > 0) {
		// Draw water
		gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, 128);
		gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, g.curAlpha.water);
		s32 mult1, mult2, scrollSz;
		if (IS_MAIN_ROOM) {
			mult1 = 1; mult2 = 3; scrollSz = 64;
		}else{
			mult1 = 0; mult2 = 1; scrollSz = 32;
		}
		gSPSegment(
			POLY_XLU_DISP++
			, 0x09
			, Gfx_TwoTexScroll(
				globalCtx->state.gfxCtx
				, 0, ((-frames * mult1) & 0x7F), ((-frames * mult2) & 0xFF), scrollSz, scrollSz
				, 1, (( frames * mult1) & 0x7F), ((-frames * mult2) & 0xFF), scrollSz, scrollSz
			)
		);
		gSPSegment(
			POLY_XLU_DISP++
			, 0x0A
			, Gfx_TwoTexScroll(
				globalCtx->state.gfxCtx
				, 0, frames * 0, ((frames * 3) & 0x1FF), 32, 128
				, 1, frames * 0, ((frames * 3) & 0x1FF), 32, 128
			)
		);
		if (IS_MAIN_ROOM) {
			PatchWaterfallVtxAlphas(this);
			gSPDisplayList(POLY_XLU_DISP++, DLIST_WATER_MAIN);
		} else {
			gSPDisplayList(POLY_XLU_DISP++, DLIST_WATER_CHAMBER);
		}
	}
	
	if (g.curAlpha.ice > 0) {
    	func_80093D84(globalCtx->state.gfxCtx);
		gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, g.curAlpha.ice);
		OverwritePrimColorCmd(IS_MAIN_ROOM ? PRIM_ICE_MAIN_RING : PRIM_ICE_CHAMBER_EDGE, 
			255, 255, 255, g.curAlpha.frozenWaterfall);
		gSPDisplayList(POLY_XLU_DISP++, IS_MAIN_ROOM ? DLIST_ICE_MAIN : DLIST_ICE_CHAMBER);
		
		gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, g.curAlpha.frozenWaterfall);
		gSPDisplayList(POLY_XLU_DISP++, IS_MAIN_ROOM ? DLIST_ICE_WATERFALL : DLIST_ICE_WATERFALL_EDGE);
	}
	
	//CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_bg_spot07_taki.c", 272);
}
