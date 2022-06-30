#include "ootmain.h"
#include "../BotWActors.h"
#include "BotWZeldaMesh.h"
#include "BotWZeldaMeshDescendidleAnim.h"
#include "BotWZeldaMeshHoldinghandsAnim.h"
#include "BotWZeldaMeshIknowtheyreoutthereAnim.h"
#include "BotWZeldaMeshLinkitseemsyouveAnim.h"
#include "BotWZeldaMeshLookpointAnim.h"
#include "BotWZeldaMeshNormalidleAnim.h"
#include "BotWZeldaMeshRotatedidleAnim.h"
#include "BotWZeldaMeshThankyoulinkAnim.h"
#include "BotWZeldaMeshTurnrightAnim.h"
#include "BotWZeldaMeshWakeupAnim.h"
#include "BotWZeldaMeshYouaskedAnim.h"
#include "BotWZeldaMeshTex.h"

// Actor Information
#define OBJ_ID 125 // primary object dependency
#define ACTIONNUM 16
#define ACTIONSLOT 1
#define ACTOR_SCALE 0.035f

#define LIMB_IS_LOWERBODY ( \
	(1 << BOTWZELDAMESH_ROOT_ROT_LIMB) | \
	(1 << BOTWZELDAMESH_DRESSB_LIMB) | \
	(1 << BOTWZELDAMESH_DRESSF_LIMB) | \
	(1 << BOTWZELDAMESH_DRESSL_LIMB) | \
	(1 << BOTWZELDAMESH_DRESSR_LIMB))

#define FLAG_NO_LOWERBODY (1 << 0)

static const s8 limbToPhysMap[BOTWZELDAMESH_NUM_LIMBS] = {
	-1, -1, //root, root
	6, //dressb
	4, //dressf
	3, //dressl
	5, //dressr
	-1, -1, //torso, head
	1, //hairc
	0, //hairl
	2, //hairr,
	-1, -1, -1, -1, -1, -1, -1, //jaw, mouthl, mouthr, mouthu, luparm, lloarm, lhand
	-1, -1, -1, -1 //ruparm, rloarm, rhand, rfingers
};
#define NUM_PHYS 7

static const HairPhysLimits hairLimits   = {{ 0.0f,  0.5f,  1.0f}, {0.0f, 0.0f, 0.0f}};
static const HairPhysLimits dressLLimits = {{-1.0f,  0.1f,  0.0f}, {0.0f, 0.0f, 0.0f}};
static const HairPhysLimits dressFLimits = {{ 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f, 0.0f}};
static const HairPhysLimits dressRLimits = {{ 1.0f,  0.1f,  0.0f}, {0.0f, 0.0f, 0.0f}};
static const HairPhysLimits dressBLimits = {{ 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f, 0.0f}};
static const HairPhysBasic  hairBasic    =  {0.010f, 100.0f,  5.0f, 80.0f, 0.07f, 0.97f, 0.020f, 1, 0, 0};
static const HairPhysDouble hairDouble   = {{0.010f, 100.0f,  8.0f, 80.0f, 0.12f, 0.97f, 0.015f, 0, 0, 0}, &hairLimits};
static const HairPhysBasic  dressBasic   =  {0.002f, 500.0f, 10.0f,100.0f, 0.10f, 0.92f, 0.000f, 2, 0, 0};
static const HairPhysTunic  dressTunic   =  {13.0f, 0.05f};
static const HairPhysConstants physc[NUM_PHYS] = {
	/*hairl*/  {1, &hairBasic, &hairLimits, &hairDouble, NULL},
	/*hairc*/  {1, &hairBasic, &hairLimits, &hairDouble, NULL},
	/*hairr*/  {1, &hairBasic, &hairLimits, &hairDouble, NULL},
	/*dressl*/ {2, &dressBasic, &dressLLimits, NULL, &dressTunic},
	/*dressf*/ {2, &dressBasic, &dressFLimits, NULL, &dressTunic},
	/*dressr*/ {2, &dressBasic, &dressRLimits, NULL, &dressTunic},
	/*dressb*/ {2, &dressBasic, &dressBLimits, NULL, &dressTunic},
};

static void *const EyeTextures[3] = {
	&BotWZeldaEye0Tex, &BotWZeldaEye1Tex, &BotWZeldaEye2Tex
};

typedef struct {
	BotWActor botw;
	Vec3s jointTable[BOTWZELDAMESH_NUM_LIMBS];
	Vec3s morphTable[BOTWZELDAMESH_NUM_LIMBS];
	HairPhysDoubleState physDouble[3];
	HairPhysTunicState physTunic[4];
	void *physStates[NUM_PHYS];
	float windX, windZ;
} Entity;

static void init(Entity *en, GlobalContext *globalCtx) {
	BotWActor_Init(&en->botw, globalCtx, &BotWZeldaMesh, &BotWZeldaMeshDescendidleAnim, 
		en->jointTable, en->morphTable, BOTWZELDAMESH_NUM_LIMBS, ACTOR_SCALE, 1.0f);
    ActorShape_Init(&en->botw.actor.shape, 0.0f, ActorShadow_DrawCircle, 4.0f);
	en->botw.actor.shape.shadowAlpha = 170;
	//Physics initialization
	s32 c = 0;
	for(s32 i=0; i<3; ++i) en->physStates[c++] = &en->physDouble[i];
	for(s32 i=0; i<4; ++i) en->physStates[c++] = &en->physTunic[i];
	for(c=0; c<NUM_PHYS; ++c) HairPhys_Init(en->physStates[c], &physc[c]);
	en->physTunic[0].conn1 = &en->physTunic[1];
	en->physTunic[0].conn2 = &en->physTunic[3];
	en->physTunic[1].conn1 = &en->physTunic[0];
	en->physTunic[1].conn2 = &en->physTunic[2];
	en->physTunic[2].conn1 = &en->physTunic[3];
	en->physTunic[2].conn2 = &en->physTunic[1];
	en->physTunic[3].conn1 = &en->physTunic[2];
	en->physTunic[3].conn2 = &en->physTunic[0];
}

static void destroy(Entity *en, GlobalContext *globalCtx) {
	BotWActor_Destroy(&en->botw, globalCtx);
}

#define VO_ZELDA_LINK NA_SE_EN_GANON_THROW
#define VO_ZELDA_ITSEEMS NA_SE_EN_GANON_AT_RETURN
#define VO_ZELDA_IMSOHAPPY NA_SE_EN_GANON_HIT_GND
#define VO_ZELDA_IKNOWTHEYRE NA_SE_EN_GANON_DAMAGE1
#define VO_ZELDA_LOOK NA_SE_EN_GANON_DAMAGE2
#define VO_ZELDA_YOUASKED NA_SE_EN_GANON_DOWN
#define VO_ZELDA_HEREITIS NA_SE_EN_GANON_RESTORE
#define VO_ZELDA_THANKYOU NA_SE_EN_GANON_DEAD

static void BotWZelda_LinkitseemsyouveCallback(BotWActor *botw, GlobalContext *globalCtx) {
	Entity *en = (Entity*)botw;
	if(CHECK_ON_FRAME(en->botw.actionframe, 35+VO_EXTRA_FRAMES)) BotWActor_VO(&en->botw, VO_ZELDA_ITSEEMS);
	if(CHECK_ON_FRAME(en->botw.actionframe, 122+VO_EXTRA_FRAMES)) BotWActor_VO(&en->botw, VO_ZELDA_IMSOHAPPY);
}

static void BotWZelda_YouaskedCallback(BotWActor *botw, GlobalContext *globalCtx) {
	Entity *en = (Entity*)botw;
	if(CHECK_ON_FRAME(en->botw.actionframe, 75+VO_EXTRA_FRAMES)) BotWActor_VO(&en->botw, VO_ZELDA_HEREITIS);
}

#define NACTIONDEFS 0xC
static const BotWCSActionDef ActionDefs[NACTIONDEFS] = {
	/*0*/{NULL, 0.0f, NULL, 0.0f,
			FLAG_INVISIBLE, 0, 0, NULL},
	/*1*/{&BotWZeldaMeshDescendidleAnim, -8.0f, NULL, 0.0f,
			FLAG_EYESCLOSED | FLAG_DECEL, 0, 0, NULL},
	/*2*/{&BotWZeldaMeshNormalidleAnim, -8.0f, NULL, 0.0f,
			0, 0, 0, NULL},
	/*3*/{&BotWZeldaMeshRotatedidleAnim, -8.0f, NULL, 0.0f,
			0, 0, 0, NULL},
	/*4*/{&BotWZeldaMeshWakeupAnim, -8.0f, &BotWZeldaMeshNormalidleAnim, -8.0f,
			0, 0, 0, NULL},
	/*5*/{&BotWZeldaMeshLinkitseemsyouveAnim, -8.0f, &BotWZeldaMeshNormalidleAnim, -8.0f,
			0, VO_ZELDA_LINK, 5+VO_EXTRA_FRAMES, BotWZelda_LinkitseemsyouveCallback},
	/*6*/{&BotWZeldaMeshIknowtheyreoutthereAnim, -8.0f, &BotWZeldaMeshRotatedidleAnim, -8.0f,
			0, VO_ZELDA_IKNOWTHEYRE, 5+VO_EXTRA_FRAMES, NULL},
	/*7*/{&BotWZeldaMeshLookpointAnim, -8.0f, NULL, 0.0f,
			0, VO_ZELDA_LOOK, 2+VO_EXTRA_FRAMES, NULL},
	/*8*/{&BotWZeldaMeshYouaskedAnim, -8.0f, &BotWZeldaMeshRotatedidleAnim, -8.0f,
			0, VO_ZELDA_YOUASKED, 0+VO_EXTRA_FRAMES, BotWZelda_YouaskedCallback},
	/*9*/{&BotWZeldaMeshThankyoulinkAnim, -8.0f, &BotWZeldaMeshNormalidleAnim, -8.0f,
			0, VO_ZELDA_THANKYOU, 5+VO_EXTRA_FRAMES, NULL},
	/*A*/{&BotWZeldaMeshHoldinghandsAnim, -8.0f, NULL, 0.0f,
			FLAG_NOLOOP, 0, 0, NULL},
	/*B*/{&BotWZeldaMeshTurnrightAnim, -8.0f, &BotWZeldaMeshNormalidleAnim, -8.0f,
			0, 0, 0, NULL},
};

static const BotWFixRotAnimDef FixRotAnimDefs[] = {
	{ -1, 0, 0 }
};

static void update(Entity *en, GlobalContext *globalCtx) {
	BotWActor_Update(&en->botw, globalCtx, ActionDefs, NACTIONDEFS, ACTIONSLOT,
		FixRotAnimDefs);
}

s32 BotWZelda_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
	Entity *en = (Entity*)thisx;
	s8 p = limbToPhysMap[limbIndex];
	u32 limbMask = 1 << limbIndex;
	if(((en->botw.flags & FLAG_NO_LOWERBODY) && (limbMask & LIMB_IS_LOWERBODY)) ||
			(en->botw.flags & FLAG_INVISIBLE)){
		*dList = NULL;
		if(limbIndex == BOTWZELDAMESH_DRESSR_LIMB && !(en->botw.flags & FLAG_INVISIBLE)){
			gSPDisplayList(POLY_OPA_DISP++, mat_BotWZeldaMesh_N_Dress_layerOpaque);
		}
		if(p >= 0) HairPhys_UpdateCulled(en->physStates[p], &physc[p]);
		return false;
	}
	if(p >= 0) HairPhys_Update(en->physStates[p], &physc[p], pos, rot,
		en->botw.windX, en->botw.windZ, ACTOR_SCALE, true);
	return false;
}

void BotWZelda_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
	//Entity *en = (Entity*)thisx;
	(void)0;
}

static void draw(Entity *en, GlobalContext *globalCtx) {
	en->botw.actor.shape.shadowDraw = (en->botw.flags & FLAG_INVISIBLE) ? NULL : ActorShadow_DrawCircle;
	//
	en->botw.flags &= ~FLAG_NO_LOWERBODY;
	Vec3f pos = en->botw.actor.world.pos;
	pos.y += 35.0f;
	if(!Statics_UncullObject(globalCtx, &pos, 15.0f, 100.0f, 0.0f, 15.0f, 1000.0f))
		en->botw.flags |= FLAG_NO_LOWERBODY;
	//
	BotWActor_DrawMain(&en->botw, globalCtx, EyeTextures, BotWZelda_OverrideLimbDraw, BotWZelda_PostLimbDraw);
}

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_PROP,
	.flags = 0x00000010,
	.objectId = OBJ_ID,
	.instanceSize = sizeof(Entity),
	.init = (ActorFunc)init,
	.destroy = (ActorFunc)destroy,
	.update = (ActorFunc)update,
	.draw = (ActorFunc)draw
};
