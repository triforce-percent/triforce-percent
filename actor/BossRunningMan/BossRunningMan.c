#include "BossRunningMan.h"
#include "BossRunningManCutscenes.c"

/* -_-_-_-_-_-_-_-_-_- */

#define IsAction(a)        (this->actionFunc == RunningMan_ ## a)
#define SetupAction(a)     this->actionFunc = RunningMan_ ## a
#define ExecuteAction(a)   RunningMan_ ## a(this, globalCtx);
#define AnimAB(a, b)       (this->skelAnime.curFrame >= a && this->skelAnime.curFrame <= b)
#define AnimFromFrame(a)   (this->skelAnime.curFrame >= a)
#define AnimFrameInt(a)    ((s32)this->skelAnime.curFrame == a)
#define SetDamageFlag(a)   this->colliders.cyl.info.toucher.dmgFlags = a; \
	this->colliders.kick.info.toucher.dmgFlags = a;
#define SetDamageAmount(a) this->colliders.cyl.info.toucher.damage = a; \
	this->colliders.kick.info.toucher.damage = a;
#define SetDamageEffect(a) this->colliders.cyl.info.toucher.effect = a; \
	this->colliders.kick.info.toucher.effect = a;
#define DecrHealth(a)      for (s32 i = 0; i < a; i++) { \
		DECR(this->actor.colChkInfo.health); }
#define AnimChange(skel, anim, start, speed, inter, xrate) \
	Animation_Change(skel, anim, speed, start, \
		Animation_GetLastFrame(anim), inter, xrate); \
	this->boss.masterFrame = start

/* -_-_-_-_-_-_-_-_-_- */

void RunningMan_Init(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_Destroy(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_UpdateIntro(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_UpdateDialogue(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_UpdateRunAway(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_BossUpdate(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_Draw(BossRunningMan* this, GlobalContext* globalCtx);

void RunningMan_SetupIntroWait(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_IntroWait(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_SetupOutro(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_Outro(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_SetupRun(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_Run(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_SetupDodge(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_Dodge(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_SetupKick(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_Kick(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_SetupHurt(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_Hurt(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_HurtLand(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_SetupArrow(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_ArrowA(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_ArrowB(BossRunningMan* this, GlobalContext* globalCtx);
void RunningMan_ArrowC(BossRunningMan* this, GlobalContext* globalCtx);

/* -_-_-_-_-_-_-_-_-_- */

const ActorInitExplPad init_vars = {
	.id = 0xDEAD, .padding = 0xBEEF, // <-- magic values, do not change
	.category = ACTORCAT_BOSS,
	.flags = (1 << 2) | ACTORFLAG_UPDATE | ACTORFLAG_DRAW,
	.objectId = DEP_OBJECT_NUM,
	.instanceSize = sizeof(BossRunningMan),
	.init = (ActorFunc)RunningMan_Init,
	.destroy = (ActorFunc)RunningMan_Destroy,
	.update = (ActorFunc)RunningMan_UpdateIntro,
	.draw = (ActorFunc)RunningMan_Draw
};

ColliderCylinderInit sCylInit = {
	.base = {
		.colType = COLTYPE_HIT5,
		.atFlags = AT_ON | AT_TYPE_ENEMY,
		.acFlags = AC_ON | AC_TYPE_PLAYER,
		.ocFlags1 = OC1_ON | OC1_TYPE_ALL,
		.ocFlags2 = OC1_TYPE_1,
		.shape = COLSHAPE_CYLINDER,
	},
	.info = {
		.elemType = ELEMTYPE_UNK1,
		.bumper = {
			.dmgFlags = DMG_DEFAULT,
		},
		.toucher = {
			.dmgFlags = DMG_UNBLOCKABLE,
			.effect = 0,
			.damage = 0x10
		},
		.toucherFlags = TOUCH_ON,
		.bumperFlags = BUMP_ON,
		.ocElemFlags = OCELEM_ON,
	},
	.dim = {
		.radius = 30,
		.height = 60,
		.yShift = 0,
		.pos = { 0 }
	},
};

ColliderCylinderInit sCylKickInit = {
	.base = {
		.colType = COLTYPE_HIT5,
		.atFlags = AT_ON | AT_TYPE_ENEMY,
		.shape = COLSHAPE_CYLINDER,
	},
	.info = {
		.elemType = ELEMTYPE_UNK1,
		.toucher = {
			.dmgFlags = DMG_UNBLOCKABLE,
			.effect = 0,
			.damage = 0x10
		},
		.toucherFlags = TOUCH_ON
	},
	.dim = {
		.radius = 30,
		.height = 80,
		.yShift = -40,
		.pos = { 0 }
	},
};

/* -_-_-_-_-_-_-_-_-_- */

void Actor_Move(Actor* actor, float xSpeed) {
	Vec3f z = {
		Math_SinS(actor->world.rot.y) * actor->speedXZ,
		0,
		Math_CosS(actor->world.rot.y) * actor->speedXZ
	};
	Vec3f x = {
		Math_SinS((s16)(actor->world.rot.y - DEGF_TO_BINANG(90))) * xSpeed,
		0,
		Math_CosS((s16)(actor->world.rot.y - DEGF_TO_BINANG(90))) * xSpeed
	};
	
	actor->velocity.x = z.x + x.x;
	actor->velocity.z = z.z + x.z;
	
	actor->velocity.y = actor->gravity;
	if (actor->velocity.y < actor->minVelocityY) {
		actor->velocity.y = actor->minVelocityY;
	}
	
	f32 speedRate = R_UPDATE_RATE * 0.5f;
	
	actor->world.pos.x += (actor->velocity.x * speedRate) + actor->colChkInfo.displacement.x;
	actor->world.pos.y += (actor->velocity.y * speedRate) + actor->colChkInfo.displacement.y;
	actor->world.pos.z += (actor->velocity.z * speedRate) + actor->colChkInfo.displacement.z;
}

void RunningMan_UpdateTrailingGhosts(BossRunningMan* this) {
	for (s32 i = NUM_GHOSTS; i > 1; i--) {
		this->boss.ghostPos[i - 1] = this->boss.ghostPos[i - 2];
		this->boss.ghostYaw[i - 1] = this->boss.ghostYaw[i - 2];
	}
	this->boss.ghostPos[0] = this->actor.world.pos;
	this->boss.ghostYaw[0] = this->actor.shape.rot.y;
}

void RunningMan_CallDust(BossRunningMan* this, Vec3f* pos, Vec3f* vel, Vec3f* accel, u16 scale, u16 step) {
	if (this->boss.dustNum >= 16)
		return;
	DustCall* call = &this->boss.dustCall[this->boss.dustNum++];
	
	call->pos = *pos;
	call->vel = *vel;
	call->accel = *accel;
	call->scale = scale;
	call->scaleStep = step;
}

void RunningMan_SetDodging(BossRunningMan* this, GlobalContext* globalCtx) {
	Player* p = PLAYER;
	WeaponInfo* swordInfo = NULL;
	s32 passFlag = 0;
	
	for (s32 i = 0; i < 3; i++) {
		if (p->swordInfo[i].active != 0)
			swordInfo = &p->swordInfo[i];
	}
	
	EnMThunder* enThunder = (void*)Actor_Find(&globalCtx->actorCtx, ACTOR_EN_M_THUNDER, ACTORCAT_ITEMACTION);
	
	if (enThunder) {
		f32 thunderDist = Math_Vec3f_DistXZ(&this->actor.world.pos, &enThunder->actor.world.pos) - this->colliders.cyl.dim.radius - enThunder->collider.dim.radius;
		
		if (thunderDist < 20.0f) {
			passFlag++;
		}
	}
	
	if (passFlag || (swordInfo != NULL && Math_Vec3f_DistXZ(&this->actor.world.pos, &swordInfo->tip) < 80.0f)) {
		this->actor.world.pos.x += Math_SinS(this->actor.yawTowardsPlayer + 0x8000) * 26.0f;
		this->actor.world.pos.z += Math_SinS(this->actor.yawTowardsPlayer + 0x8000) * 26.0f;
		ExecuteAction(SetupDodge);
		return;
	}
}

void RunningMan_RelativePos(Vec3f* posOrigin, s16 yawOrigin, Vec3f* result, Vec3f* target) {
	f32 cosRot2Y;
	f32 sinRot2Y;
	f32 deltaX;
	f32 deltaZ;
	
	cosRot2Y = Math_CosS(yawOrigin);
	sinRot2Y = Math_SinS(yawOrigin);
	deltaX = target->x - posOrigin->x;
	deltaZ = target->z - posOrigin->z;
	
	result->x = (deltaX * cosRot2Y) - (deltaZ * sinRot2Y);
	result->z = (deltaX * sinRot2Y) + (deltaZ * cosRot2Y);
	result->y = target->y - posOrigin->y;
}

/* -_-_-_-_-_-_-_-_-_- */

static void RunningMan_ClearReusedVars(BossRunningMan* this){
	bzero(&this->boss, 
		sizeof(this->boss) > sizeof(this->npc) ? sizeof(this->boss) : sizeof(this->npc));
}

static void RunningMan_ChangeToBoss(BossRunningMan* this, GlobalContext* globalCtx) {
	RunningMan_ClearReusedVars(this);
	
	Actor_SetScale(&this->actor, 0.1f);
	Collider_InitCylinder(globalCtx, &this->colliders.cyl);
	Collider_SetCylinder(globalCtx, &this->colliders.cyl, &this->actor, &sCylInit);
	Collider_InitCylinder(globalCtx, &this->colliders.kick);
	Collider_SetCylinder(globalCtx, &this->colliders.kick, &this->actor, &sCylKickInit);
	ActorShape_Init(&this->actor.shape, 0.0f, &ActorShadow_DrawCircle, 3.25f);
	this->actor.gravity = -8.0f;
	this->actor.colorFilterParams = 0x4000;
	this->actor.colChkInfo.mass = 0xFE;
	this->actor.colChkInfo.health = 0xB0;
	this->actor.flags |= 1; //targetable
	
	SkelAnime_InitFlex(
		globalCtx,
		&this->skelAnime,
		&gBossRunningManObj_SkelRunningMan,
		&gBossRunningManObj_AnimRunFast,
		this->jointTable,
		this->morphTable,
		SKEL_RUNNINGMAN_NUMBONES_DT
	);
	this->needDestroy = true;
	
	SetDamageEffect(DAMAGE_NORMAL);
	SetDamageFlag(DMG_DEFAULT);
	SetDamageAmount(0x8);
	
	SetupAction(SetupIntroWait);
}

static void RunningMan_ChangeToNPC(BossRunningMan* this, GlobalContext* globalCtx) {
	//this->actor.shape.rot = this->actor.world.rot = (Vec3s){0, 0, 0};
	AnimChange(&this->skelAnime, &gBossRunningManObj_AnimDeadLoopIdle, 
		0.0f, 1.0f, ANIMMODE_LOOP_INTERP, -4.0f);
	RunningMan_ClearReusedVars(this);
	this->state = (RunManState) {
		.enableDraw = true,
		.deadLookMod = true
	};
	this->actor.update = (void*)RunningMan_UpdateDialogue;
	this->actor.textId = 0x0C30;
	this->actor.flags |= 0x10000; //auto talk
	this->npc.getItemId = -1;
	this->npc.timer = 0;
	Actor_ChangeCategory(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_NPC);
	Vec3f pos = this->actor.world.pos;
	pos.y += 50.0f;
	globalCtx->mainCamera.at = pos;
	pos = PLAYER->actor.world.pos;
	pos.x -= 100.0f;
	pos.y += 70.0f;
	pos.z -= 50.0f;
	globalCtx->mainCamera.eye = globalCtx->mainCamera.eyeNext = pos;
	globalCtx->mainCamera.xzSpeed = 0.0f;
}

void RunningMan_Init(BossRunningMan* this, GlobalContext* globalCtx) {
	if(!(RUNNINGMAN_WANTS_TO_BATTLE_VAR & RUNNINGMAN_WANTS_TO_BATTLE_BIT)
		|| (SAGES_CHARM_VAR & SAGES_CHARM_BIT)
		|| this->actor.params != 0){
		Actor_Kill(&this->actor);
		return;
	}
	this->state.enableDraw = 0;
	this->npc.timer = 0;
	this->actor.textId = 0x0C30;
	Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_EX_RUPPY,
		this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
		0, 0, 0, ACTORPARAM_BETAGIANTRUPEE);
}

void RunningMan_Destroy(BossRunningMan* this, GlobalContext* globalCtx) {
	if(!this->needDestroy) return;
	SkelAnime_Free(&this->skelAnime, globalCtx);
	Collider_DestroyCylinder(globalCtx, &this->colliders.kick);
	Collider_DestroyCylinder(globalCtx, &this->colliders.cyl);
}

void RunningMan_UpdateIntro(BossRunningMan* this, GlobalContext* globalCtx){
	if(this->npc.timer == 0){
		Actor *betaGiantRupee = Actor_Find(&globalCtx->actorCtx, ACTOR_EN_EX_RUPPY, ACTORCAT_PROP);
		if(betaGiantRupee == NULL){
			this->npc.timer = 1;
		    Audio_SetBGM(0x100100FF); //stop music
			Vec3f pos = this->actor.home.pos;
			pos.z -= 30.0f;
			pos.x += 15.0f;
			PLAYER->actor.world.pos = pos;
			func_8002F698(globalCtx, &this->actor, 20.0f, 0x1000, 8.0f, 2, 0);
		}else{
			betaGiantRupee->uncullZoneForward = 10000.0f;
		}
	}else{
		++this->npc.timer;
		if(this->npc.timer == 10){
			//this->actor.world.pos.y += 200.0f;
			this->actor.update = (ActorFunc)RunningMan_BossUpdate;
			globalCtx->csCtx.segment = &BossRunningManIntroCS;
			gSaveContext.cutsceneTrigger = 1;
			RunningMan_ChangeToBoss(this, globalCtx);
			return;
		}
	}
}

void RunningMan_UpdateDialogue(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	BossRunningMan* en = this; //for Triforce% macros
	
	Actor_RequestToTalkInRange(&this->actor, globalCtx, 1000.0f);
	if(Actor_IsTalking(&this->actor, globalCtx)){
		this->actor.flags &= ~0x10000; //auto talk
	}
	if(MESSAGE_ADVANCE_EVENT){
		if(this->actor.textId == 0x0C30){
			state->headTrack = true;
			this->actor.textId = 0x0C31;
			MESSAGE_CONTINUE;
		}else if(this->actor.textId == 0x0C31){
			AnimChange(&this->skelAnime, &gBossRunningManObj_AnimDeadLoopExplain, 
				0.0f, 1.0f, ANIMMODE_LOOP_INTERP, -8.0f);
			this->actor.textId = 0x0C32;
			MESSAGE_CONTINUE;
		}else if(this->actor.textId == 0x0C32){
			state->headTrack = false;
			AnimChange(&this->skelAnime, &gBossRunningManObj_AnimDeadLoopRegret, 
				0.0f, 1.0f, ANIMMODE_LOOP_INTERP, -8.0f);
			this->actor.textId = 0x0C33;
			MESSAGE_CONTINUE;
		}else if(this->actor.textId == 0x0C33){
			state->headTrack = true;
			AnimChange(&this->skelAnime, &gBossRunningManObj_AnimDeadLoopIdle, 
				0.0f, 1.0f, ANIMMODE_LOOP_INTERP, -8.0f);
			this->actor.textId = 0x0C34;
			MESSAGE_CONTINUE;
		}
	}else if(this->actor.textId == 0x0C34 && MESSAGE_ADVANCE_END){
		this->npc.getItemId = GI_SAGES_CHARM;
		this->actor.textId = 0;
	}
	if(this->npc.getItemId >= 0){
		if(this->actor.parent != NULL){
			this->actor.parent = NULL;
			this->npc.getItemId = -1;
			this->npc.timer = 1;
		}else{
			Actor_PickUp(&this->actor, globalCtx, this->npc.getItemId, 2000.0f, 2000.0f);
		}
	}
	if(this->npc.timer >= 1 && this->npc.timer < 100){
		++this->npc.timer;
		if(this->npc.timer == 25){
			SAGES_CHARM_VAR |= SAGES_CHARM_BIT;
			gSaveContext.magic >>= 1; //half magic because we're scaling up the bar 2x
			gSaveContext.unk_13F6 = 0x60; //max magic
			gSaveContext.unk_13F2 = gSaveContext.unk_13F0; //magic mode to return to
			gSaveContext.unk_13F0 = 9; //magic mode = filling
		}
	}
	if(this->actor.textId == 0 && this->npc.getItemId < 0 && this->npc.timer > 40 
			&& func_8010BDBC(&globalCtx->msgCtx) == 0){
		//The timer is because when Link gets the item, while he's in the
		//animation of moving it up to above his head, dialogue is not active
		//and the Running Man would just run away at that time.
		Animation_Change(&this->skelAnime, &gBossRunningManObj_AnimRunFast, 1.0f, 0.0f,
			Animation_GetLastFrame(&gBossRunningManObj_AnimRunFast), ANIMMODE_LOOP_INTERP, 8);
		state->headTrack = false;
		this->actor.world.rot.y = 0xC000;
		this->actor.world.rot.x = this->actor.world.rot.z = 0;
		this->actor.shape.rot = this->actor.world.rot;
		this->actor.speedXZ = 10.0f;
		this->actor.update = (ActorFunc)RunningMan_UpdateRunAway;
		if(gSaveContext.dayTime >= 0xC001 || gSaveContext.dayTime < 0x4555){
			Audio_SetBGM(1); //Night ambience
		}else{
			Audio_SetBGM(2); //Hyrule Field
		}
	}
}

void RunningMan_UpdateRunAway(BossRunningMan* this, GlobalContext* globalCtx) {
	Actor_Move(&this->actor, 0.0f);
	Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 40.0f, 40.0f, 0x1D);
	if(this->actor.xzDistToPlayer > 1500.0f){
		Actor_Kill(&this->actor);
	}
}

#ifndef CHK_ALL
#define CHK_ALL(x, combo) (~((gGlobalContext.state.input[0].x.button) | ~(combo)) == 0)
#endif

void RunningMan_BossUpdate(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	//Player* p = PLAYER;
	
	if (this->actor.colChkInfo.health == 0) {
		this->actor.colChkInfo.health = 1;
		SetupAction(SetupOutro);
	}
	
	if (this->actionFunc)
		this->actionFunc(this, globalCtx);
	
	// Lock time
	gSaveContext.environmentTime = gSaveContext.dayTime = 0xAAAB;
	
	if (state->targetPos == true) {
		s16 dirYaw = Math_Vec3f_Yaw(&this->actor.world.pos, &this->boss.targetPos);
		
		Math_SmoothStepToS(&this->actor.world.rot.y, dirYaw, 3, this->boss.stepMax, 1);
	} else if (state->setDirRot == true) {
		Math_SmoothStepToS(&this->actor.world.rot.y, this->boss.dirTarget, 3, this->boss.stepMax, 1);
	}
	
	if (state->syncRotY == true) {
		this->actor.shape.rot.y = this->actor.world.rot.y;
	} else if (state->setShapeRot == true) {
		Math_SmoothStepToS(&this->actor.shape.rot.y, this->boss.rotShapeTarget, 3, this->boss.stepMax, 1);
		// if (state->syncRotY == true)
		// 	PrintfScreen(17, "Warning!\n Setting setShapeRot & syncRotY!!");
	}
	
	Actor_Move(&this->actor, this->boss.speedX);
	Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 40.0f, 40.0f, 0x1D);
	if (this->actor.floorHeight <= -31000.0f) {
		this->actor.world.pos.x = this->actor.prevPos.x;
		this->actor.world.pos.z = this->actor.prevPos.z;
	}
	
	state->isHurt = 0;
	Math_SmoothStepToS(&this->boss.hurtBlend, 0, 3, 25, 1);
	if (state->colHurt == true) {
		u8 passToucher = false;
		Collider* col = &this->colliders.cyl.base;
		ColliderInfo* info = &this->colliders.cyl.info;
		
		if (col->oc && col->oc->id == ACTOR_EN_BOM_CHU) {
			col->acFlags |= AC_HIT;
			passToucher = true;
		}
		
		if (DECR(this->boss.chuTimer) == 0 && col->acFlags & AC_HIT && !(this->colliders.acFlagLast & AC_HIT)) {
			if ((info->acHitInfo && !(info->acHitInfo->toucher.dmgFlags & DMG_DEKU_NUT)) || passToucher == true) {
				u32 toucherDmg = info->acHitInfo->toucher.dmgFlags;
				
				if (toucherDmg & (DMG_SLASH_MASTER | DMG_SPIN_MASTER)) {
					DecrHealth(0x10);
				} else if (toucherDmg & (DMG_SLASH_GIANT | DMG_SPIN_GIANT | DMG_JUMP_MASTER)) {
					DecrHealth(0x18);
				} else if (toucherDmg & (DMG_JUMP_GIANT)) {
					DecrHealth(0x20);
				} else if (toucherDmg & (DMG_EXPLOSIVE)) {
					DecrHealth(0x10);
				} else {
					DecrHealth(0x2);
				}
				
				state->isHurt = true;
				this->boss.dmgColor = 0;
				this->boss.hurtBlend = 160;
				Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_DAMAGE);
				Audio_PlayActorSound2(&this->actor, NA_SE_VO_IN_CRY_0);
				if (!IsAction(Hurt) && !IsAction(SetupHurt) && !state->blockDmgStun) {
					ExecuteAction(SetupHurt);
				}
			}
			if (info->acHitInfo && info->acHitInfo->toucher.dmgFlags & DMG_DEKU_NUT) {
				this->boss.dmgColor = 1;
				this->boss.hurtBlend = 220;
				// Audio_PlayActorSound2(&this->actor, NA_SE_EN_REDEAD_AIM);
			}
		}
		
		if (col->oc && col->oc->id == ACTOR_EN_BOM_CHU) {
			this->boss.chuTimer = 4;
		}
		
		this->colliders.acFlagLast = this->colliders.cyl.base.acFlags;
		this->colliders.cyl.base.acFlags &= ~AC_HIT;
		
		this->colliders.cyl.dim.pos = (Vec3s) {
			(s16)this->actor.world.pos.x,
			(s16)this->actor.world.pos.y,
			(s16)this->actor.world.pos.z,
		};
		CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliders.cyl.base);
		CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliders.cyl.base);
	} else {
		this->colliders.cyl.base.acFlags &= ~AC_HIT;
	}
	
	//Collider* kicker = &this->colliders.kick.base;
	
	if (state->colKick == true) {
		if (state->attachColToHead != true) {
			this->colliders.cyl.dim.pos = (Vec3s) {
				(s16)this->actor.world.pos.x,
				(s16)this->actor.world.pos.y,
				(s16)this->actor.world.pos.z,
			};
		} else {
			this->colliders.cyl.dim.pos = (Vec3s) {
				(s16)this->actor.focus.pos.x,
				(s16)this->actor.focus.pos.y,
				(s16)this->actor.focus.pos.z,
			};
			this->colliders.kick.dim.pos = (Vec3s) {
				(s16)this->actor.focus.pos.x,
				(s16)this->actor.focus.pos.y,
				(s16)this->actor.focus.pos.z,
			};
		}
		CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliders.kick.base);
		CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliders.cyl.base);
	}
	
	if (this->actor.isTargeted) {
		Camera* cam = ACTIVE_CAM;
		Battle1* batCam = (Battle1*)cam->paramData;
		f32 yawDiff = Math_Vec3f_Yaw(&cam->eye, &this->actor.world.pos) - Math_Vec3f_Yaw(&cam->eye, &cam->at);
		
		yawDiff = BINANG_TO_DEGF(-yawDiff);
		yawDiff = CLAMP(yawDiff, -10.0f, 10.0f);
		
		Math_SmoothStepToF(&batCam->anim.roll, yawDiff, 0.25, 0.25f, 0.0001f);
	}
}

s32 RunningMan_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx, Gfx** disp) {
	BossRunningMan* this = (BossRunningMan*)thisx;
	static Vec3f head = { 0, 38.0f, 38.0f };
	static Vec3f foot = { 0, -34.0f, 0.0f };
	static Vec3f front = { 0, 38.0f, 50.0f };
	Vec3f f;
	s16 targetYaw;
	s16 targetPitch;
	Player* p = PLAYER;
	Vec3f limbPos;
	Vec3f zero = { 0 };
	
	switch (limbIndex) {
	    case RUNMAN_HEAD:
		    if (!this->state.ghosting) {
			    Matrix_MultVec3f(&head, &this->actor.focus.pos);
			    Matrix_MultVec3f(&front, &f);
			    
			    if (this->state.headTrack) {
					Vec3f playerHeadPos = p->actor.world.pos;
					playerHeadPos.y += 70.0f;
				    targetYaw = -Math_Vec3f_Yaw(&this->actor.focus.pos, &f) 
						+ Math_Vec3f_Yaw(&this->actor.focus.pos, &playerHeadPos);
				    targetPitch = -Math_Vec3f_Pitch(&this->actor.focus.pos, &f) 
						+ Math_Vec3f_Pitch(&this->actor.focus.pos, &playerHeadPos);
						
					if(this->state.deadLookMod) targetYaw *= 2;
				    
				    targetYaw = CLAMP(targetYaw, -DEGF_TO_BINANG(80), DEGF_TO_BINANG(80));
				    targetPitch = CLAMP(targetPitch, -DEGF_TO_BINANG(30), DEGF_TO_BINANG(30));
			    } else {
				    targetYaw = 0;
				    targetPitch = 0;
			    }
			    
			    Math_SmoothStepToS(&this->headFocus.y, targetYaw, 7, 4000, 1);
			    Math_SmoothStepToS(&this->headFocus.x, targetPitch, 7, 4000, 1);
		    }
		    
		    rot->x += this->headFocus.x;
		    rot->y += this->headFocus.y;
		    
		    break;
	    case RUNMAN_FOOT_L:
		    if (this->state.ghosting != true) {
			    Matrix_MultVec3f(&foot, &this->actor.shape.feetPos[0]);
		    }
		    break;
	    case RUNMAN_FOOT_R:
		    if (this->state.ghosting != true) {
			    Matrix_MultVec3f(&foot, &this->actor.shape.feetPos[1]);
		    }
		    break;
	    case RUNMAN_UPPERARM_L:
		    Matrix_MultVec3f(&zero, &limbPos);
		    
		    if (this->state.handHitL == true) {
			    if (this->state.ghosting != true)
				    this->colliders.kick.dim.pos = (Vec3s) {
					    limbPos.x,
					    limbPos.y,
					    limbPos.z
				    };
			    
			    rot->x = 0;
			    rot->y = this->actor.yawTowardsPlayer - this->actor.shape.rot.y - 0x4000;
			    rot->z = 0;
		    }
		    break;
	    case RUNMAN_UPPERARM_R:
		    Matrix_MultVec3f(&zero, &limbPos);
		    
		    if (this->state.handHitR == true) {
			    if (this->state.ghosting != true)
				    this->colliders.kick.dim.pos = (Vec3s) {
					    limbPos.x,
					    limbPos.y,
					    limbPos.z
				    };
			    
			    rot->x = 0;
			    rot->y = this->actor.yawTowardsPlayer - this->actor.shape.rot.y + 0x4000;
			    rot->z = 0;
		    }
		    break;
	    case RUNMAN_FOREARM_L:
		case RUNMAN_HAND_L:
		    if (this->state.handHitL) {
			    *rot = (Vec3s) { 0 };
			    if (limbIndex == RUNMAN_HAND_L) {
				    *dList = &gBossRunningManObj_DLFistLLimb10;
			    }
		    }
		    break;
	    case RUNMAN_FOREARM_R:
		case RUNMAN_HAND_R:
		    if (this->state.handHitR) {
			    *rot = (Vec3s) { 0 };
			    if (limbIndex == RUNMAN_HAND_L) {
				    *dList = &gBossRunningManObj_DLFistRLimb13;
			    }
		    }
		    break;
	}
	
	return 0;
}

void RunningMan_OverridePostDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** disp) {
	//BossRunningMan* this = (BossRunningMan*)thisx;
}

void RunningMan_Draw(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	if(!state->enableDraw) return;
	
	// Particles will be handled like this only for draw order reasons
	for (s32 i = 0; i < this->boss.dustNum; i++) {
		Color_RGBA8 col = {
			0x4A, 0x3d, 0x27, 20
		};
		Color_RGBA8 col2 = {
			0xB0, 0x73, 0x28, 20
		};
		DustCall* call = &this->boss.dustCall[this->boss.dustNum - 1];
		EffectSsDust_Spawn(
			&gGlobalContext,
			0,
			&call->pos,
			&call->vel,
			&call->accel,
			&col2,
			&col,
			call->scale,
			call->scaleStep,
			10,
			0
		);
		
		this->boss.dustNum--;
	}
	
	Color_RGB8 dmgCol[] = {
		{ 255, 0, 0 },
		{ 0, 0, 255 }
	};
	
	gDPSetPrimColor(
		POLY_OPA_DISP++,
		0,
		0,
		dmgCol[this->boss.dmgColor].r,
		dmgCol[this->boss.dmgColor].g,
		dmgCol[this->boss.dmgColor].b,
		255 - this->boss.hurtBlend
	);
	
	if (state->drawGhosts == true) {
		f32 animSpeed = this->skelAnime.playSpeed;
		u8 animMode = this->skelAnime.mode;
		
		state->ghosting = true;
		
		Matrix_Push();
		for (s32 i = 0; i < NUM_GHOSTS; i++) {
			Vec3f* ghostPos = this->boss.ghostPos;
			s16* ghostYaw = this->boss.ghostYaw;
			s32 inv_i = NUM_GHOSTS - 1 - i;
			f32 frame = this->boss.masterFrame - inv_i;
			
			if (frame < 0)
				frame += this->skelAnime.endFrame;
			if (frame > this->skelAnime.endFrame)
				frame -= this->skelAnime.endFrame;
			
			gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, 0, 0), G_MTX_LOAD | G_MTX_MODELVIEW | G_MTX_NOPUSH);
			
			Matrix_Translate(ghostPos[inv_i].x, ghostPos[inv_i].y, ghostPos[inv_i].z, MTXMODE_NEW);
			Matrix_Translate(ghostPos[inv_i].x, ghostPos[inv_i].y, ghostPos[inv_i].z, MTXMODE_NEW);
			Matrix_RotateY_s(ghostYaw[inv_i], MTXMODE_APPLY);
			Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
			s8 s = 20 + (i * 40);
			this->skelAnime.curFrame = frame;
			this->skelAnime.playSpeed = 0;
			SkelAnime_Update(&this->skelAnime);
			func_80034CC4(globalCtx, &this->skelAnime, RunningMan_OverrideLimbDraw, 0, &this->actor, s);
		}
		Matrix_Pop();
		
		state->ghosting = false;
		
		this->skelAnime.playSpeed = animSpeed;
		this->skelAnime.curFrame = this->boss.masterFrame;
		this->skelAnime.mode = animMode;
	}
	
	if (globalCtx->gameOverCtx.state < GAMEOVER_DEATH_START)
		SkelAnime_Update(&this->skelAnime);
	this->boss.masterFrame = this->skelAnime.curFrame;
	
	func_80034BA0(globalCtx, &this->skelAnime, RunningMan_OverrideLimbDraw, RunningMan_OverridePostDraw, &this->actor, 255);
}

/* -_-_-_-_-_-_-_-_-_- */

void RunningMan_SetupIntroWait(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	
	//TODO change to some pose for falling in and then some pose for looking
	//ready to attack
	AnimChange(&this->skelAnime, &gBossRunningManObj_AnimRunFast, 
		0.0f, 1.0f, ANIMMODE_LOOP_INTERP, 0);
	
	*state = (RunManState) {
		.headTrack = true,
		.targetPos = true,
		.syncRotY = true,
		.enableDraw = true,
	};
	
	SetupAction(IntroWait);
}

void RunningMan_IntroWait(BossRunningMan* this, GlobalContext* globalCtx) {
	Player* p = PLAYER;
	
	this->boss.targetPos = p->actor.world.pos;
	
	if(globalCtx->csCtx.state == 0){
		SetupAction(SetupRun);
	}
}

/* -_-_-_-_-_-_-_-_-_- */

#define mSpeedFactor this->boss.workFloat[0]
#define mOutroMode this->boss.workInt[0]
#define mTimer this->boss.workInt[1]
#define mLastFrame this->boss.workShort[0]
#define initRunSpeed 7.0f

void RunningMan_SetupOutro(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	
	AnimChange(&this->skelAnime, &gBossRunningManObj_AnimRunFast,
		0.0f, 1.0f, ANIMMODE_LOOP_INTERP, 0);
	
	*state = (RunManState) {
		.enableDraw = true,
	};
	
	this->actor.world.pos = this->actor.prevPos = this->actor.home.pos;
	this->actor.world.rot.x = this->actor.world.rot.z = 0;
	this->actor.world.rot.y = 0xB000;
	this->actor.shape.rot = this->actor.world.rot;
	this->actor.speedXZ = initRunSpeed;
	this->boss.speedX = 0.0f;
	this->actor.velocity.x = this->actor.velocity.y = this->actor.velocity.z = 0;
	mSpeedFactor = 1.0f;
	mOutroMode = 0;
	mLastFrame = -1;
	
	Audio_SetBGM(0x100100FF); //stop music
	Enemy_StartFinishingBlow(globalCtx, &this->actor);
	
	globalCtx->csCtx.segment = &BossRunningManOutroCS;
	gSaveContext.cutsceneTrigger = 1;
	
	SetupAction(Outro);
}

void RunningMan_Outro(BossRunningMan* this, GlobalContext* globalCtx) {
	if(mOutroMode == 0){
		mSpeedFactor -= 0.005f;
		if(mSpeedFactor <= 0.12f/*0.0f*/){
			this->actor.speedXZ = 0.0f;
			this->skelAnime.playSpeed = 0.0f;
			mTimer = 0;
			mOutroMode = 1;
			AnimChange(&this->skelAnime, &gBossRunningManObj_AnimDeadFall,
				0.0f, 1.0f, ANIMMODE_ONCE_INTERP, -8.0f);
		}else{
			this->actor.speedXZ = initRunSpeed * mSpeedFactor;
			this->skelAnime.playSpeed = mSpeedFactor;
			s16 frame = this->skelAnime.curFrame;
			if(frame != mLastFrame && (frame == 2 || frame == 7)){
				Audio_PlayActorSound2(&this->actor, NA_SE_EN_MORIBLIN_WALK);
			}
			mLastFrame = frame;
		}
	}else if(mOutroMode == 1){
		if(fabsf(this->skelAnime.curFrame - 7.0f) < 0.5f){
			Audio_PlayActorSound2(&this->actor, NA_SE_PL_BODY_HIT);
		}
		if(this->skelAnime.curFrame >= this->skelAnime.endFrame){
			RunningMan_ChangeToNPC(this, globalCtx);
		}
		/*
		//Old silly outro
		if(mTimer == 15){
			Audio_PlayActorSound2(&this->actor, NA_SE_VO_IN_LOST);
			mSpeedFactor = 0.2f;
			mOutroMode = 2;
		}else{
			++mTimer;
		}
	}else if(mOutroMode == 2){
		this->actor.world.rot.z += mSpeedFactor * 0x0280;
		this->actor.shape.rot = this->actor.world.rot;
		mSpeedFactor += 0.07f;
		if(this->actor.world.rot.z >= 0x4000){
			this->actor.world.rot.z = 0x4000;
			Audio_PlayActorSound2(&this->actor, NA_SE_PL_BODY_HIT);
			mOutroMode = 3;
			mTimer = 0;
		}
	}else if(mOutroMode == 3){
		if(mTimer == 30){
			RunningMan_ChangeToNPC(this, globalCtx);
		}else{
			++mTimer;
		}
		*/
	}
}

#undef initRunSpeed
#undef mTimer
#undef mSpeedFactor
#undef mOutroMode

/* -_-_-_-_-_-_-_-_-_- */

#define mDirectRand     this->boss.workInt[0]
#define mGetTo          this->boss.workInt[1]
#define mTargetYaw      this->boss.workShort[0]
#define mFlipTimer      this->boss.workShort[1]
#define mVelocityY      this->boss.workFloat[0]
#define mWhileDistancer this->boss.workFloat[1]
void RunningMan_SetupRun(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	
	AnimChange(&this->skelAnime, &gBossRunningManObj_AnimRunFast,
		0.0f, 1.0f, ANIMMODE_LOOP_INTERP, 0);
	
	*state = (RunManState) {
		.drawGhosts = true,
		.targetPos = true,
		.syncRotY = true,
		.colHurt = true,
		.headTrack = true,
		.enableDraw = true,
	};
	
	mGetTo = 120;
	mDirectRand = Rand_ZeroOne() < 0.5 ? 1 : -1;
	mTargetYaw = this->actor.yawTowardsPlayer - 0x4000 * this->boss.workInt[0];
	mFlipTimer = Rand_S16Offset(80, 180);
	mVelocityY = 0;
	mWhileDistancer = 0;
	this->actor.gravity = -8.0f;
	
	for (s32 i = 0; i < NUM_GHOSTS; i++) {
		this->boss.ghostPos[i] = this->actor.world.pos;
		this->boss.ghostYaw[i] = this->actor.shape.rot.y;
	}
	
	SetupAction(Run);
}
void RunningMan_Run(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	Player* p = PLAYER;
	SkelAnime* skelAnime = &this->skelAnime;
	ActorListEntry* bombList = &globalCtx->actorCtx.actorLists[ACTORCAT_EXPLOSIVE];
	Actor* bomb = bombList->head;
	static f32 offsetX;
	//static u16 bgCheckLast;
	
	if (this->boss.dmgColor == 1 && this->boss.hurtBlend > 40) {
		this->actor.speedXZ *= 0.7f;
	} else {
		RunningMan_SetDodging(this, globalCtx);
	}
	
	if (mVelocityY == 0.0f) {
		for (s32 i = 0; i < bombList->length; i++) {
			if (bomb == NULL)
				break;
			if (Actor_WorldDistXYZToActor(&this->actor, bomb) < 100.0f) {
				mVelocityY = 50.0f;
				Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL_JUMP);
				break;
			}
			bomb = bomb->next;
		}
	}
	
	state->colHurt = true;
	
	this->actor.world.pos.y += mVelocityY;
	Math_StepToF(&mVelocityY, -10.0f, 10.0f);
	if (this->actor.bgCheckFlags & 1 && mVelocityY <= 0.0f) {
		mVelocityY = 0.0f;
	}
	if (!(this->actor.bgCheckFlags & 1) && mVelocityY > 0.0f) {
		state->colHurt = false;
	}
	
	offsetX = Math_SinS(DEGF_TO_BINANG(globalCtx->gameplayFrames * 1.35f)) * 7.0f;
	Math_StepToF(&this->actor.speedXZ, 15.0f + Rand_CenteredFloat(10.0f) + Rand_ZeroFloat(10.0f), 2.5f);
	if (skelAnime->animation == &gBossRunningManObj_AnimRunFast) {
		skelAnime->playSpeed = this->actor.speedXZ / 17.5;
	}
	
	f32 distancer = 80.0f + offsetX + mGetTo;
	
	distancer *= 1.0f - 1.0f * (ABS(BINANG_TO_DEGF( (s16)(p->actor.shape.rot.y - Math_Vec3f_Yaw(&p->actor.world.pos, &this->actor.world.pos)) )) / 180.0f);
	distancer = CLAMP_MIN(distancer, 1.0f);
	
	while (Math_Vec3f_DistXZ(&this->actor.world.pos, &this->boss.targetPos) < 60.0f) {
		mTargetYaw += (DEGF_TO_BINANG(8.0f) * mDirectRand);
		this->boss.targetPos.x = p->actor.world.pos.x + Math_SinS(mTargetYaw) * (distancer + mWhileDistancer);
		this->boss.targetPos.z = p->actor.world.pos.z + Math_CosS(mTargetYaw) * (distancer + mWhileDistancer);
		mWhileDistancer *= 2;
	}
	
	mWhileDistancer = 0.0001f;
	
	s32 step = 1000 + Math_Vec3f_DistXZ(&this->actor.world.pos, &this->boss.targetPos) * 50;
	
	this->boss.stepMax = CLAMP_MAX(step, DEGF_TO_BINANG(45));
	this->boss.targetPos.x = p->actor.world.pos.x + Math_SinS(mTargetYaw) * (distancer);
	this->boss.targetPos.z = p->actor.world.pos.z + Math_CosS(mTargetYaw) * (distancer);
	
	DECR(mGetTo);
	
	if (DECR(mFlipTimer) == 0) {
		if(this->boss.numPastChoices >= 3 || (this->boss.numPastChoices >= -1 && Rand_ZeroOne() < 0.3f)){
			if(this->boss.numPastChoices > 0) this->boss.numPastChoices = 0;
			--this->boss.numPastChoices;
			ExecuteAction(SetupArrow);
			return;
		}
		if(this->boss.numPastChoices < 0) this->boss.numPastChoices = 0;
		++this->boss.numPastChoices;
		mDirectRand = -mDirectRand;
		mFlipTimer = Rand_S16Offset(10, 90);
		Math_StepToAngleS(&this->actor.world.rot.y, (s16)(this->actor.yawTowardsPlayer + 0x8000), 4000);
		mGetTo = 80;
	}
	
	RunningMan_UpdateTrailingGhosts(this);
	
	this->boss.rotShapeTarget = this->actor.yawTowardsPlayer;
	
	if (skelAnime->animation != &gBossRunningManObj_AnimDodgeKick) {
		if (globalCtx->gameplayFrames % 2 == 0) {
			Audio_PlayActorSound2(&this->actor, NA_SE_EN_MORIBLIN_WALK);
		}
		
		state->handHitL = 0;
		state->handHitR = 0;
		state->colKick = 0;
		state->syncRotY = true;
		state->targetPos = true;
		
		if (this->actor.xzDistToPlayer < 100.0f && ABS((s16)(this->actor.yawTowardsPlayer - p->actor.shape.rot.y)) < DEGF_TO_BINANG(30)) {
			if (Rand_ZeroOne() < 0.3f) {
				AnimChange(&this->skelAnime, &gBossRunningManObj_AnimDodgeKick,
					20.0f, 1.0f, ANIMMODE_ONCE, 3.0f);
				state->colKick = true;
				state->targetPos = true;
				state->syncRotY = 0;
				Audio_PlayActorSound2(&this->actor, NA_SE_VO_IN_LASH_1);
				Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL_JUMP);
				this->actor.world.rot.y = this->actor.yawTowardsPlayer;
				this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
			}
		}
	} else if (AnimFromFrame(26)) {
		AnimChange(&this->skelAnime, &gBossRunningManObj_AnimRunFast,
			0.0f, 1.0f, ANIMMODE_LOOP_INTERP, 0);
	} else {
	}
	
	Vec3f vel = {
		Math_SinS(this->actor.world.rot.y + 0x8000) * (2.0f + Rand_CenteredFloat(0.5f)),
		1.0f + Rand_ZeroFloat(0.5f),
		Math_CosS(this->actor.world.rot.y + 0x8000) * (2.0f + Rand_CenteredFloat(0.5f))
	};
	Vec3f accel = {
		Math_SinS(this->actor.world.rot.y + 0x8000) * 0.2f,
		-0.5f,
		Math_CosS(this->actor.world.rot.y + 0x8000) * 0.2f
	};
	Vec3f pos = {
		this->actor.shape.feetPos[globalCtx->gameplayFrames % 2].x + Rand_CenteredFloat(6.5f),
		this->actor.world.pos.y + 4.0f,
		this->actor.shape.feetPos[globalCtx->gameplayFrames % 2].z + Rand_CenteredFloat(6.5f),
	};
	
	RunningMan_CallDust(
		this,
		&pos,
		&vel,
		&accel,
		Rand_S16Offset(270, 80) + this->actor.xzDistToPlayer * 0.1,
		Rand_S16Offset(30, 100) + this->actor.xzDistToPlayer * 0.1
	);
#undef mDirectRand
#undef mGetTo
#undef mTargetYaw
#undef mFlipTimer
#undef mVelocityY
#undef mWhileDistancer
}

void RunningMan_SetupDodge(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	
	AnimChange(&this->skelAnime, &gBossRunningManObj_AnimDodgeKick,
		1.0f, 1.75f, ANIMMODE_LOOP, 3.0f);
	
	*state = (RunManState) {
		.syncRotY = true,
		.blockDmgStun = true,
		.enableDraw = true,
	};
	
	this->boss.dirTarget = this->actor.yawTowardsPlayer;
	this->boss.stepMax = 9000;
	this->actor.gravity = -8.0f;
	
	Vec3f vel = {
		Math_SinS(this->boss.dirTarget) * (2.0f + Rand_CenteredFloat(0.5f)),
		1.0f + Rand_ZeroFloat(0.5f),
		Math_CosS(this->boss.dirTarget) * (2.0f + Rand_CenteredFloat(0.5f))
	};
	Vec3f accel = {
		Math_SinS(this->boss.dirTarget) * 0.2f,
		-0.5f,
		Math_CosS(this->boss.dirTarget) * 0.2f
	};
	Vec3f pos = {
		this->actor.shape.feetPos[0].x + Rand_CenteredFloat(6.5f),
		this->actor.shape.feetPos[0].y + 8.0f,
		this->actor.shape.feetPos[0].z + Rand_CenteredFloat(6.5f),
	};
	
	RunningMan_CallDust(
		this,
		&pos,
		&vel,
		&accel,
		Rand_S16Offset(270, 80),
		Rand_S16Offset(30, 100)
	);
	
	pos = (Vec3f) {
		this->actor.shape.feetPos[1].x + Rand_CenteredFloat(6.5f),
		this->actor.shape.feetPos[1].y + 8.0f,
		this->actor.shape.feetPos[1].z + Rand_CenteredFloat(6.5f),
	};
	
	RunningMan_CallDust(
		this,
		&pos,
		&vel,
		&accel,
		Rand_S16Offset(270, 80),
		Rand_S16Offset(30, 100)
	);
	
	this->actor.speedXZ = -16.0f;
	
	Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL_JUMP);
	SetupAction(Dodge);
}
void RunningMan_Dodge(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	//Player* p = PLAYER;
	//SkelAnime* mainSkel = &this->skelAnime;
	
	Math_StepToF(&this->actor.speedXZ, 0.0f, 2.0f);
	this->boss.speedX = 0.0f;
	
	state->drawGhosts = false;
	
	RunningMan_SetDodging(this, globalCtx);
	
	if (AnimAB(0.0f, 11.0f)) {
		RunningMan_UpdateTrailingGhosts(this);
		state->drawGhosts = true;
	}
	
	if (AnimAB(6, 99)) {
		state->colHurt = true;
		Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLOORMASTER_SLIDING);
		
		Vec3f vel = {
			Math_SinS(this->boss.dirTarget) * (2.0f + Rand_CenteredFloat(0.5f)),
			1.0f + Rand_ZeroFloat(0.5f),
			Math_CosS(this->boss.dirTarget) * (2.0f + Rand_CenteredFloat(0.5f))
		};
		Vec3f accel = {
			Math_SinS(this->boss.dirTarget) * 0.2f,
			-0.5f,
			Math_CosS(this->boss.dirTarget) * 0.2f
		};
		Vec3f pos = {
			this->actor.shape.feetPos[0].x + Rand_CenteredFloat(6.5f),
			this->actor.shape.feetPos[0].y + 8.0f,
			this->actor.shape.feetPos[0].z + Rand_CenteredFloat(6.5f),
		};
		
		RunningMan_CallDust(
			this,
			&pos,
			&vel,
			&accel,
			Rand_S16Offset(270, 80),
			Rand_S16Offset(30, 100)
		);
		
		pos = (Vec3f) {
			this->actor.shape.feetPos[1].x + Rand_CenteredFloat(6.5f),
			this->actor.shape.feetPos[1].y + 8.0f,
			this->actor.shape.feetPos[1].z + Rand_CenteredFloat(6.5f),
		};
		
		RunningMan_CallDust(
			this,
			&pos,
			&vel,
			&accel,
			Rand_S16Offset(270, 80),
			Rand_S16Offset(30, 100)
		);
	}
	
	if (AnimFromFrame(10.0f)) {
		if(this->boss.numPastChoices >= 3 || (this->boss.numPastChoices >= -1 && Rand_ZeroOne() < 0.3f)){
			if(this->boss.numPastChoices > 0) this->boss.numPastChoices = 0;
			--this->boss.numPastChoices;
			ExecuteAction(SetupArrow);
		}else{
			if(this->boss.numPastChoices < 0) this->boss.numPastChoices = 0;
			++this->boss.numPastChoices;
			ExecuteAction(SetupKick);
		}
	}
}

#define mKickCounter this->boss.workInt[0]
void RunningMan_SetupKick(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	
	AnimChange(&this->skelAnime, &gBossRunningManObj_AnimDodgeKick,
		11.0f, 1.0f, ANIMMODE_LOOP, 3.0f);
	
	*state = (RunManState) {
		.syncRotY = true,
		.colHurt = true,
		.setDirRot = true,
		.blockDmgStun = true,
		.enableDraw = true,
	};
	
	this->actor.shape.rot.y = this->actor.world.rot.y = this->boss.dirTarget = this->actor.yawTowardsPlayer;
	this->boss.stepMax = 1000;
	this->actor.gravity = -8.0f;
	
	Vec3f vel = {
		Math_SinS(this->boss.dirTarget + 0x8000) * (2.0f + Rand_CenteredFloat(0.5f)),
		1.0f + Rand_ZeroFloat(0.5f),
		Math_CosS(this->boss.dirTarget + 0x8000) * (2.0f + Rand_CenteredFloat(0.5f))
	};
	Vec3f accel = {
		Math_SinS(this->boss.dirTarget + 0x8000) * 0.2f,
		-0.5f,
		Math_CosS(this->boss.dirTarget + 0x8000) * 0.2f
	};
	Vec3f pos = {
		this->actor.shape.feetPos[0].x + Rand_CenteredFloat(6.5f),
		this->actor.shape.feetPos[0].y + 8.0f,
		this->actor.shape.feetPos[0].z + Rand_CenteredFloat(6.5f),
	};
	
	RunningMan_CallDust(
		this,
		&pos,
		&vel,
		&accel,
		Rand_S16Offset(270, 80),
		Rand_S16Offset(30, 100)
	);
	
	pos = (Vec3f) {
		this->actor.shape.feetPos[1].x + Rand_CenteredFloat(6.5f),
		this->actor.shape.feetPos[1].y + 8.0f,
		this->actor.shape.feetPos[1].z + Rand_CenteredFloat(6.5f),
	};
	
	RunningMan_CallDust(
		this,
		&pos,
		&vel,
		&accel,
		Rand_S16Offset(270, 80),
		Rand_S16Offset(30, 100)
	);
	
	mKickCounter = 2;
	
	SetupAction(Kick);
}
void RunningMan_Kick(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	Player* p = PLAYER;
	SkelAnime* skelAnime = &this->skelAnime;
	
	this->boss.speedX = 0.0f;
	
	state->colKick = false;
	state->drawGhosts = false;
	
	if (AnimAB(0.0f, 4.0f)) {
		RunningMan_SetDodging(this, globalCtx);
	}
	
	if (AnimAB(18.0f, 29.0f)) {
		state->colKick = true;
	}
	
	if (AnimAB(18.0f, 38.0f)) {
		if (AnimFrameInt(18)) {
			Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL_JUMP);
			Audio_PlayActorSound2(&this->actor, NA_SE_VO_IN_LASH_0);
			this->actor.speedXZ = 26.0f;
		}
		
		skelAnime->playSpeed = 1.8f;
		RunningMan_UpdateTrailingGhosts(this);
		state->drawGhosts = true;
		this->actor.world.pos.x += Math_SinS(this->boss.dirTarget + 0x8000) * 3.0f;
		this->actor.world.pos.z += Math_SinS(this->boss.dirTarget + 0x8000) * 3.0f;
		
		this->colliders.kick.dim.pos = (Vec3s) {
			this->actor.shape.feetPos[0].x,
			this->actor.shape.feetPos[0].y,
			this->actor.shape.feetPos[0].z
		};
		
		state->blockDmgStun = true;
	}
	
	Vec3f res;
	
	RunningMan_RelativePos(&this->actor.world.pos, this->actor.shape.rot.y, &res, &p->actor.world.pos);
	if (res.z < 160.0f)
		Math_StepToF(&this->actor.speedXZ, 0, 1.0f);
	
	if (AnimFromFrame(30.0f) && DECR(mKickCounter) != 0) {
		AnimChange(&this->skelAnime, &gBossRunningManObj_AnimDodgeKick,
			19.0f, 1.0f, ANIMMODE_LOOP, 3.0f);
	}
	
	if (AnimAB(39, 99)) {
		state->blockDmgStun = false;
		Audio_PlayActorSound2(&this->actor, NA_SE_EN_FLOORMASTER_SLIDING);
		skelAnime->playSpeed = 2.5f;
		
		Vec3f vel = {
			Math_SinS(this->boss.dirTarget) * (2.0f + Rand_CenteredFloat(0.5f)),
			1.0f + Rand_ZeroFloat(0.5f),
			Math_CosS(this->boss.dirTarget) * (2.0f + Rand_CenteredFloat(0.5f))
		};
		Vec3f accel = {
			Math_SinS(this->boss.dirTarget) * 0.2f,
			-0.5f,
			Math_CosS(this->boss.dirTarget) * 0.2f
		};
		Vec3f pos = {
			this->actor.shape.feetPos[0].x + Rand_CenteredFloat(6.5f),
			this->actor.shape.feetPos[0].y + 8.0f,
			this->actor.shape.feetPos[0].z + Rand_CenteredFloat(6.5f),
		};
		
		RunningMan_CallDust(
			this,
			&pos,
			&vel,
			&accel,
			Rand_S16Offset(270, 80),
			Rand_S16Offset(30, 100)
		);
		
		pos = (Vec3f) {
			this->actor.shape.feetPos[1].x + Rand_CenteredFloat(6.5f),
			this->actor.shape.feetPos[1].y + 8.0f,
			this->actor.shape.feetPos[1].z + Rand_CenteredFloat(6.5f),
		};
		
		RunningMan_CallDust(
			this,
			&pos,
			&vel,
			&accel,
			Rand_S16Offset(270, 80),
			Rand_S16Offset(30, 100)
		);
	}
	
	SetDamageEffect(DAMAGE_KNOCKBACK);
	SetDamageFlag(DMG_UNBLOCKABLE);
	SetDamageAmount(0x10);
	
	if (AnimFromFrame(48.0f)) {
		SetDamageEffect(DAMAGE_NORMAL);
		SetDamageFlag(DMG_DEFAULT);
		SetDamageAmount(0x8);
		
		SetupAction(SetupRun);
	}
#undef mKickCounter
}

#define mHurtCountLoop this->boss.workInt[0]
#define mVelocityY     this->boss.workFloat[0]
void RunningMan_SetupHurt(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	
	AnimChange(&this->skelAnime, &gBossRunningManObj_AnimHurt,
		0.0f, 1.0f, ANIMMODE_LOOP, 2.0f);
	
	*state = (RunManState) {
		.colHurt = true,
		.enableDraw = true,
	};
	
	//TODO: When hurt, don't get knocked back directly away from Link. Add about
	//10-30 degrees randomly to one side or the other. This makes it much harder
	//to hit him with a second arrow while he's down.
	this->boss.dirTarget = this->actor.world.rot.y = (s16)(this->actor.yawTowardsPlayer + 0x8000);
	this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
	this->boss.stepMax = 1000;
	
	mVelocityY = 65.0f;
	mHurtCountLoop = 1;
	
	this->boss.speedX = 0;
	this->actor.speedXZ *= 0.65f;
	this->actor.gravity = -8.0f;
	
	SetupAction(Hurt);
}
void RunningMan_Hurt(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	//Player* p = PLAYER;
	//SkelAnime* mainSkel = &this->skelAnime;
	
	RunningMan_UpdateTrailingGhosts(this);
	
	Math_StepToF(&this->actor.speedXZ, 0, 4.0f);
	if (this->actor.speedXZ < 1.0f)
		this->actor.speedXZ = 0;
	
	if (state->isHurt && mHurtCountLoop != 0) {
		AnimChange(&this->skelAnime, &gBossRunningManObj_AnimHurt,
			7.0f, 1.0f, ANIMMODE_LOOP, 1.0f);
		mHurtCountLoop -= state->isHurt;
		
		return;
	}
	
	if (AnimFromFrame(32) && DECR(mHurtCountLoop) != 0) {
		AnimChange(&this->skelAnime, &gBossRunningManObj_AnimHurt,
			15.0f, 2.0f, ANIMMODE_LOOP, 4.0f);
	}
	
	if (mHurtCountLoop == 0 && state->colHurt == true) {
		state->colHurt = false;
		AnimChange(&this->skelAnime, &gBossRunningManObj_AnimHurt,
			42.0f, 1.0f, ANIMMODE_LOOP, 2.0f);
	}
	
	if (AnimFromFrame(45.0f) && mHurtCountLoop == 0) {
		if (AnimFrameInt(45)) {
			Audio_PlayActorSound2(&this->actor, NA_SE_VO_IN_LASH_1);
			Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL_JUMP);
		}
		
		Math_StepToF(&mVelocityY, 0, 5.0f);
		this->actor.gravity = -16.0f;
		this->actor.world.pos.y += mVelocityY;
		this->actor.world.rot.y = this->actor.yawTowardsPlayer;
		state->setShapeRot = true;
		this->boss.rotShapeTarget = this->actor.yawTowardsPlayer;
		this->actor.speedXZ = -16.0f;
		
		state->drawGhosts = true;
	}
	
	if (AnimFromFrame(54.0f)) {
		this->colliders.kick.info.toucher.effect = DAMAGE_NORMAL;
		SetupAction(HurtLand);
	}
}
void RunningMan_HurtLand(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	//Player* p = PLAYER;
	//SkelAnime* mainSkel = &this->skelAnime;
	
	RunningMan_UpdateTrailingGhosts(this);
	
	this->actor.gravity = -16.0f;
	
	Math_StepToF(&mVelocityY, 0, 5.0f);
	Math_StepToF(&this->actor.speedXZ, 0, 0.5f);
	
	this->actor.world.pos.y += mVelocityY;
	
	if (AnimFromFrame(63)) {
		AnimChange(&this->skelAnime, &gBossRunningManObj_AnimHurt,
			52.0f, 1.0f, ANIMMODE_LOOP, 4.0f);
	}
	
	if (this->actor.bgCheckFlags & 0x3) {
		this->actor.gravity = -8.0f;
		state->drawGhosts = state->isHurt = false;
		state->setShapeRot = false;
		ExecuteAction(SetupRun);
	}
#undef mHurtCountLoop
#undef mVelocityY
}

#define mVelocityY  this->boss.workFloat[0]
#define mLaunchPosY this->boss.workFloat[1]
void RunningMan_SetupArrow(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	
	AnimChange(&this->skelAnime, &gBossRunningManObj_AnimJumpRocket,
		0.0f, 1.0f, ANIMMODE_LOOP, 3.0f);
	
	*state = (RunManState) {
		.syncRotY = true,
		.setDirRot = true,
		.blockDmgStun = true,
		.enableDraw = true,
	};
	
	this->actor.speedXZ = 0;
	this->boss.speedX = 0;
	mVelocityY = 0;
	mLaunchPosY = this->actor.world.pos.y;
	this->actor.gravity = -8.0f;
	
	SetupAction(ArrowA);
}
void RunningMan_ArrowA(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	Player* p = PLAYER;
	//SkelAnime* mainSkel = &this->skelAnime;
	u32 trackLinkXZ = 0;
	
	RunningMan_UpdateTrailingGhosts(this);
	
	if (AnimFromFrame(6.0f)) {
		if (this->actor.bgCheckFlags & 1) {
			for (s32 i = 0; i < 8; i++) {
				Vec3f vel = {
					Rand_CenteredFloat(8.5f),
					1.0f + Rand_ZeroFloat(0.5f),
					Rand_CenteredFloat(8.5f)
				};
				Vec3f accel = {
					Rand_CenteredFloat(0.2f),
					-0.5f,
					Rand_CenteredFloat(0.2f)
				};
				Vec3f pos = {
					this->actor.world.pos.x + Rand_CenteredFloat(6.5f),
					this->actor.world.pos.y + 8.0f,
					this->actor.world.pos.z + Rand_CenteredFloat(6.5f),
				};
				
				RunningMan_CallDust(
					this,
					&pos,
					&vel,
					&accel,
					Rand_S16Offset(170, 40),
					Rand_S16Offset(30, 100)
				);
			}
			Audio_PlayActorSound2(&this->actor, NA_SE_EN_STAL_JUMP);
		}
		this->actor.flags &= ~ACTORFLAG_TARGET;
		if (mVelocityY == 0)
			mVelocityY = 45.0f;
		
		Math_StepToF(&this->actor.velocity.y, 8.0f, 5.0f);
		
		state->drawGhosts = true;
		trackLinkXZ = true;
	}
	
	this->actor.world.pos.y += mVelocityY;
	this->actor.shape.yOffset = (mLaunchPosY - this->actor.world.pos.y);
	this->boss.dirTarget = this->actor.yawTowardsPlayer;
	
	if (trackLinkXZ) {
		Math_SmoothStepToF(&this->actor.world.pos.x, p->actor.world.pos.x - Math_SinS(this->actor.yawTowardsPlayer) * 5.0f, 0.25f, 8.0f, 0.0f);
		Math_SmoothStepToF(&this->actor.world.pos.z, p->actor.world.pos.z - Math_CosS(this->actor.yawTowardsPlayer) * 5.0f, 0.25f, 8.0f, 0.0f);
	}
	
	if (AnimFromFrame(20.0f)) {
		mVelocityY = 8.0f;
		*state = (RunManState) {
			.drawGhosts = true,
			.syncRotY = true,
			.colKick = true,
			.setDirRot = true,
			.blockDmgStun = true,
			.attachColToHead = true,
			.enableDraw = true,
		};
		SetupAction(ArrowB);
	}
}
void RunningMan_ArrowB(BossRunningMan* this, GlobalContext* globalCtx) {
	RunManState* state = &this->state;
	Player* p = PLAYER;
	SkelAnime* skelAnime = &this->skelAnime;
	
	RunningMan_UpdateTrailingGhosts(this);
	Math_StepToF(&mVelocityY, -60.0f, 2.5f);
	this->actor.world.pos.y += mVelocityY;
	this->actor.shape.yOffset = (mLaunchPosY - this->actor.world.pos.y);
	Math_SmoothStepToF(&this->actor.world.pos.x, p->actor.world.pos.x - Math_SinS(this->actor.yawTowardsPlayer) * 5.0f, 0.25f, 8.0f, 0.0f);
	Math_SmoothStepToF(&this->actor.world.pos.z, p->actor.world.pos.z - Math_CosS(this->actor.yawTowardsPlayer) * 5.0f, 0.25f, 8.0f, 0.0f);
	
	this->boss.dirTarget = this->actor.yawTowardsPlayer;
	
	skelAnime->playSpeed = 1.0f;
	if (AnimFromFrame(35.0f) && !(this->actor.bgCheckFlags & 1)) {
		skelAnime->playSpeed = 0.0f;
		
		return;
	}
	
	if (this->actor.bgCheckFlags & 1) {
		for (s32 i = 0; i < 12; i++) {
			Vec3f vel = {
				Rand_CenteredFloat(24.5f),
				1.0f + Rand_ZeroFloat(4.5f),
				Rand_CenteredFloat(24.5f)
			};
			Vec3f accel = {
				Rand_CenteredFloat(0.2f) - vel.x * 0.25f,
				-0.5f,
				Rand_CenteredFloat(0.2f) - vel.z * 0.25f
			};
			Vec3f pos = {
				this->actor.world.pos.x + Rand_CenteredFloat(6.5f),
				this->actor.world.pos.y + 30.0f,
				this->actor.world.pos.z + Rand_CenteredFloat(6.5f),
			};
			
			RunningMan_CallDust(
				this,
				&pos,
				&vel,
				&accel,
				Rand_S16Offset(170, 120),
				Rand_S16Offset(30, 100)
			);
		}
		
		if (this->actor.xzDistToPlayer < 100) {
			globalCtx->damagePlayer(globalCtx, -0x20);
			func_8002F71C(globalCtx, &this->actor, 15.0f, this->actor.yawTowardsPlayer, 6.0f);
		}
		
		Audio_PlayActorSound2(&this->actor, NA_SE_EV_STONE_BOUND);
		Audio_PlayActorSound2(&this->actor, NA_SE_PL_BODY_HIT);
		Camera_AddQuake(&globalCtx->mainCamera, 2, 0xB, 8);
		this->actor.shape.yOffset = 0;
		
		this->actor.flags |= ACTORFLAG_TARGET;
		*state = (RunManState) {
			.syncRotY = true,
			.colHurt = true,
			.enableDraw = true,
		};
		
		skelAnime->playSpeed = 1.0f;
		skelAnime->curFrame = 38.0f;
		SetupAction(ArrowC);
		
		return;
	}
	
	Audio_PlayActorSound2(&this->actor, NA_SE_EV_OBJECT_FALL - SFX_FLAG);
	
	// NA_SE_EV_OBJECT_FALL
}
void RunningMan_ArrowC(BossRunningMan* this, GlobalContext* globalCtx) {
	//RunManState* state = &this->state;
	//Player* p = PLAYER;
	SkelAnime* skelAnime = &this->skelAnime;
	
	Math_SmoothStepToF(&this->actor.speedXZ, 0.0f, 0.25f, 3.896f, 0.0f);
	
	if (AnimFrameInt(84)) {
		this->actor.speedXZ = -22.0f;
		skelAnime->playSpeed = 1.25f;
	}
	
	if (AnimFromFrame(119.0f)) {
		ExecuteAction(SetupRun);
	}
#undef mVelocityY
#undef mLaunchPosY
}
