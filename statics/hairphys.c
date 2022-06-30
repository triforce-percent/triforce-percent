#include "ootmain.h"
#include "hairphys.h"
#include "../loader/debugger/debugger.h"

static float dt = 0.05f;
static float fps = 20.0f;
static u8 debug = 0;

void HairPhys_SetDebug(u8 d){
    debug = d;
}

void HairPhys_InitSimple(HairPhysSimpleState *s, const HairPhysConstants *c){
    s->r.x = s->r.y = s->r.z = 0.0f;
    s->v.x = s->v.y = s->v.z = 0.0f;
}

void HairPhys_CulledUpdateSimple(HairPhysSimpleState *s, const HairPhysConstants *c){
    (void)0;
}

void HairPhys_InitDouble(HairPhysDoubleState *s, const HairPhysConstants *c){
    //Can't actually init here because we don't know where the fulcrum is.
    //Defer init to the first time through update.
    s->initted = 0;
    //However these parts we can init.
    s->s1.vel.x = 0.0f;
    s->s1.vel.y = 0.0f;
    s->s1.vel.z = 0.0f;
    s->s1.fnext.x = 0.0f;
    s->s1.fnext.y = 0.0f;
    s->s1.fnext.z = 0.0f;
    s->s2.vel.x = 0.0f;
    s->s2.vel.y = 0.0f;
    s->s2.vel.z = 0.0f;
    s->s2.fnext.x = 0.0f;
    s->s2.fnext.y = 0.0f;
    s->s2.fnext.z = 0.0f;
}

void HairPhys_CulledUpdateDouble(HairPhysDoubleState *s, const HairPhysConstants *c){
    HairPhys_InitDouble(s, c);
}

void HairPhys_InitTunic(HairPhysTunicState *s, const HairPhysConstants *c){
    //Can't actually init here because we don't know where the fulcrum is.
    //Defer init to the first time through update.
    s->initted = 0;
    //However these parts we can init.
    s->conn1 = NULL;
    s->conn2 = NULL;
    s->s.vel.x = 0.0f;
    s->s.vel.y = 0.0f;
    s->s.vel.z = 0.0f;
    s->s.fnext.x = 0.0f;
    s->s.fnext.y = 0.0f;
    s->s.fnext.z = 0.0f;
}

void HairPhys_CulledUpdateTunic(HairPhysTunicState *s, const HairPhysConstants *c){
    //Can't call HairPhys_InitTunic because don't want to clobber conn1, conn2.
    s->initted = 0;
    s->s.vel.x = 0.0f;
    s->s.vel.y = 0.0f;
    s->s.vel.z = 0.0f;
    s->s.fnext.x = 0.0f;
    s->s.fnext.y = 0.0f;
    s->s.fnext.z = 0.0f;
}

void HairPhys_UpdateSimple(HairPhysSimpleState *s, const HairPhysConstants *c,
        Vec3f *lPos, Vec3s *lRot, float windX, float windZ, float actorscale){
	const HairPhysBasic *b = c->b;
	const HairPhysLimits *lim = c->lim;
    Vec3f force; force.x = 0.0f; force.y = 0.0f; force.z = 0.0f;
    //Restore force, proportional to negative distance from 0. This is a
    //spring force, not gravity, so it isn't proportional to mass.
    force.x -= b->restoreforce * s->r.x;
    force.y -= b->restoreforce * s->r.y;
    force.z -= b->restoreforce * s->r.z;
    //Wind force, just random centered.
    float windMag = sqrtf(windX * windX + windZ * windZ);
    force.x += (windMag * b->windpush) * (Rand_ZeroOne() - 0.5f);
    force.y += (windMag * b->windpush) * (Rand_ZeroOne() - 0.5f);
    force.z += (windMag * b->windpush) * (Rand_ZeroOne() - 0.5f);
    //Dampen velocity
    s->v.x *= b->dampening;
    s->v.y *= b->dampening;
    s->v.z *= b->dampening;
    //dv = f / m * dt
    s->v.x += force.x * b->oneovermass * dt;
    s->v.y += force.y * b->oneovermass * dt;
    s->v.z += force.z * b->oneovermass * dt;
    //dx = v * dt
    s->r.x += s->v.x * dt;
    s->r.y += s->v.y * dt;
    s->r.z += s->v.z * dt;
    //Limits
    if(s->r.x < lim->neg.x){ s->r.x = lim->neg.x; s->v.x = 0.0f; }
    if(s->r.x > lim->pos.x){ s->r.x = lim->pos.x; s->v.x = 0.0f; }
    if(s->r.y < lim->neg.y){ s->r.y = lim->neg.y; s->v.y = 0.0f; }
    if(s->r.y > lim->pos.y){ s->r.y = lim->pos.y; s->v.y = 0.0f; }
    if(s->r.z < lim->neg.z){ s->r.z = lim->neg.z; s->v.z = 0.0f; }
    if(s->r.z > lim->pos.z){ s->r.z = lim->pos.z; s->v.z = 0.0f; }
    //Result
    lRot->x += s->r.x * HAIRPHYS_UNITROT;
    lRot->y += s->r.y * HAIRPHYS_UNITROT;
    lRot->z += s->r.z * HAIRPHYS_UNITROT * b->yawmult;
}

static void SafeRestInNegY(Vec3f *v){
    float d = 1.0f - v->x * v->x - v->z * v->z;
    if(d < 0.0f){
        d = 1.0f - d; //x^2 + z^2
        d = 1.0f / sqrtf(d);
        v->x *= d;
        v->z *= d;
        v->y = 0.0f;
    }else{
        v->y = -sqrtf(d);
    }
}

static void PhysSegment(HairPhysSegState *ss, const HairPhysBasic *b, 
        const HairPhysLimits *lim, const Vec3f *newFulcrum, Vec3f *prevFNext,
        float costwist, float sintwist, float windX, float windZ){
    Vec3f force, vel1, vel2, pos1, pos2, dp;
    float d, mag;
    //Initialize force to fnext
    force.x = ss->fnext.x;
    force.y = ss->fnext.y;
    force.z = ss->fnext.z;
    ss->fnext.x = 0.0f;
    ss->fnext.y = 0.0f;
    ss->fnext.z = 0.0f;
    //Gravity
    force.y -= b->restoreforce * b->mass;
    //Wind. Uses windpush for the constant wind force and yawmult for the
    //randomness, since yawmult is not otherwise used.
    force.x += windX * b->windpush + (Rand_ZeroOne() - 0.5f) * b->yawmult;
    force.z += windZ * b->windpush + (Rand_ZeroOne() - 0.5f) * b->yawmult;
    //Tame large forces
    mag = sqrtf(force.x * force.x + force.y * force.y + force.z * force.z);
    const float flimit = 0.6f;
    if(mag > flimit){
        d = sqrtf(flimit / mag);
        force.x *= d;
        force.y *= d;
        force.z *= d;
    }
    //Dampen velocity (applied to true old velocity)
    ss->vel.x *= b->dampening;
    ss->vel.y *= b->dampening;
    ss->vel.z *= b->dampening;
    //Updated velocity due to forces
    vel1.x = ss->vel.x + force.x * b->oneovermass * dt;
    vel1.y = ss->vel.y + force.y * b->oneovermass * dt;
    vel1.z = ss->vel.z + force.z * b->oneovermass * dt;
    //Updated position due to this velocity
    pos1.x = ss->pos.x + vel1.x * dt;
    pos1.y = ss->pos.y + vel1.y * dt;
    pos1.z = ss->pos.z + vel1.z * dt;
    //Fix this position so it's the right distance from the new fulcrum
    dp.x = pos1.x - newFulcrum->x;
    dp.y = pos1.y - newFulcrum->y;
    dp.z = pos1.z - newFulcrum->z;
    //Normalized (length 1) dp
    d = dp.x * dp.x + dp.y * dp.y + dp.z * dp.z;
    if(d < 0.0001f){
        dp.x = 0.0f; dp.y = -1.0f; dp.z = 0.0f;
    }else{
        d = 1.0f / sqrtf(d);
        dp.x *= d;
        dp.y *= d;
        dp.z *= d;
    }
    float ml = lim->neg.x * lim->neg.x + lim->neg.z * lim->neg.z;
    if(ml > 1e-6f){
        float im = 1.0f / sqrtf(ml);
        //Rotate limits into coordinate system relative to Link; normalize
        float lx = (lim->neg.x * costwist + lim->neg.z * sintwist) * im;
        float lz = (lim->neg.z * costwist - lim->neg.x * sintwist) * im;
        //k * b->len is magnitude along limit line normal vector
        float k = dp.x * lx + dp.z * lz;
        float normlim = lim->neg.y / b->len;
        if(k > normlim){
            //d = perp(d, l) + l * normlim
            //  = d - proj(d, l) + l * normlim
            //  = d - k * l + l * normlim
            //  = d - (k - normlim) * l
            dp.x -= (k - normlim) * lx;
            dp.z -= (k - normlim) * lz;
            SafeRestInNegY(&dp);
        }
        if(b->limdrag && normlim < 0.0f){
            float ratio = normlim * -2.0f;
            if(ratio > 1.0f) ratio = 1.0f;
            Vec3f dragdp;
            dragdp.x = lx * normlim;
            dragdp.z = lz * normlim;
            SafeRestInNegY(&dragdp);
            dp.x = (1.0f - ratio) * dp.x + ratio * dragdp.x;
            dp.y = (1.0f - ratio) * dp.y + ratio * dragdp.y;
            dp.z = (1.0f - ratio) * dp.z + ratio * dragdp.z;
        }
    }
    //New position
    pos2.x = newFulcrum->x + b->len * dp.x;
    pos2.y = newFulcrum->y + b->len * dp.y;
    pos2.z = newFulcrum->z + b->len * dp.z;
    //Correct the velocity so as actually to be between pos0 and pos2
    vel2.x = (pos2.x - ss->pos.x) * fps;
    vel2.y = (pos2.y - ss->pos.y) * fps;
    vel2.z = (pos2.z - ss->pos.z) * fps;
    if(prevFNext != NULL){
        //Compute the force needed to change the velocity from vel0 to vel2,
        //minus the force which was actually exerted by other things,
        //and inverted because this would be the force on this mass through
        //the rod, but we want the force on the other mass
        prevFNext->x = force.x - (vel2.x - ss->vel.x) * fps * b->mass;
        prevFNext->y = force.y - (vel2.y - ss->vel.y) * fps * b->mass;
        prevFNext->z = force.z - (vel2.z - ss->vel.z) * fps * b->mass;
    }
    //Tame large velocities
    mag = sqrtf(vel2.x * vel2.x + vel2.y * vel2.y + vel2.z * vel2.z);
    const float vlimit = 10.0f;
    if(mag > vlimit){
        mag = sqrtf(mag * vlimit);
    }
    //Rotate (project and then fix the scale so the speed stays the same) the
    //velocity to be perpendicular to the rod based on the end state
    d = vel2.x * dp.x + vel2.y * dp.y + vel2.z * dp.z;
    vel2.x -= d * dp.x;
    vel2.y -= d * dp.y;
    vel2.z -= d * dp.z; //projection, but have lost speed
    d = sqrtf(vel2.x * vel2.x + vel2.y * vel2.y + vel2.z * vel2.z) + 1e-6f;
    mag /= d; //Divide by d does normalize new value, mul by mag returns to orig
    vel2.x *= mag;
    vel2.y *= mag;
    vel2.z *= mag;
    //Store results
    ss->pos.x = pos2.x;
    ss->pos.y = pos2.y;
    ss->pos.z = pos2.z;
    ss->vel.x = vel2.x;
    ss->vel.y = vel2.y;
    ss->vel.z = vel2.z;
}

s16 Statics_ExtractRotationAxis(float actorscale, u8 axis){
    MtxF *cmf = Matrix_GetCurrent();
    float as = 1.0f / actorscale;
    if(axis == 0){
        if(cmf->mf[0][1] * as >= 1.0f || cmf->mf[0][1] * as <= -1.0f){
            return 0;
        }else{
            return Math_Atan2S(cmf->mf[1][1], -cmf->mf[2][1]);
        }
    }else if(axis == 1){
        /*
        if(cmf->xy * as < 1.0f && cmf->xy * as > -1.0f){
            //These values should all be scaled up by as, but they are only used in
            //asin2, which is scale invariant
            twist = Math_Atan2S(cmf->xx, -cmf->xz);
        }else{
            twist = Math_Atan2S(cmf->zz, cmf->yz);
            if(cmf->xy < 0.0f) twist = -twist;
        }
        */
        if(cmf->mf[1][2] * as >= 1.0f || cmf->mf[1][2] * as <= -1.0f){
            return 0;
        }else{
            return Math_Atan2S(cmf->mf[2][2], -cmf->mf[0][2]);
        }
    }else{ //axis == 2
        if(cmf->mf[2][0] * as >= 1.0f || cmf->mf[2][0] * as <= -1.0f){
            return 0;
        }else{
            return Math_Atan2S(-cmf->mf[0][0], cmf->mf[1][0]); //was + -
        }
    }
}

static s16 ExtractFulcrumTwist(float actorscale, float yoffset, Vec3f *lPos, 
        Vec3f *fulcrum, float *costwist, float *sintwist, u8 parentaxis){
    float as = 1.0f / actorscale;
    //Current hair attachment point--fulcrum of first segment
    Vec3f temp;
    temp.x = lPos->x;
    temp.y = lPos->y + yoffset * as;
    temp.z = lPos->z;
    Matrix_MultVec3f(&temp, fulcrum);
    //Get global Y rotation to use as center for hair twist. Assuming there is
    //only one scale factor of dbl->actorscale applied globally.
    s16 twist = Statics_ExtractRotationAxis(actorscale, parentaxis);
    *costwist = Math_CosS(twist);
    *sintwist = Math_SinS(twist);
    return twist;
}

static void ApplyLimbPosRot(Vec3f *pos1, Vec3f *pos2, float len, float actorscale,
        Vec3f *lPos, Vec3s *lRot, s16 twist){
    //Convert to limb position and rotation
    //We want the transformations to be applied to each vertex in this order:
    //global Y (twist)
    //global X (s2)
    //global Z (s2)
    //actor scale
    //translation (s1)
    //Transformations are constructed on the stack in reverse order.
    //The Matrix_JointPosition call taking lPos and lRot will apply X, Y, Z, T
    //(of course constructing them in the reverse order). However, we need Y
    //first, and we can't insert a transformation after that call, so we have
    //to use that call only for the Y rotation, and do the other transforms
    //ourselves.
    Matrix_Translate(pos1->x, pos1->y, pos1->z, MTXMODE_NEW);
    Matrix_Scale(actorscale, actorscale, actorscale, MTXMODE_APPLY);
    Vec3f dp;
    dp.x = pos2->x - pos1->x;
    dp.y = pos2->y - pos1->y;
    dp.z = pos2->z - pos1->z;
    //Convert relative position to rotation
    float k = len * len - dp.x * dp.x;
    if(k < 0.0f){
        k = 0.0f;
    }else{
        k = sqrtf(k);
    }
    Matrix_RotateRPY(Math_Atan2S(dp.y, dp.z), 0, Math_Atan2S(k, dp.x), MTXMODE_APPLY);
    lPos->x = 0.0f;
    lPos->y = 0.0f;
    lPos->z = 0.0f;
    lRot->x = 0;
    lRot->y = -twist;
    lRot->z = 0;
}

static void HairPhys_StartRunTwice(Vec3f *fulcrum, Vec3f *lastfulcrum, Vec3f *halffulcrum){
    dt = 0.025f;
    fps = 40.0f;
    halffulcrum->x = (lastfulcrum->x + fulcrum->x) * 0.5f;
    halffulcrum->y = (lastfulcrum->y + fulcrum->y) * 0.5f;
    halffulcrum->z = (lastfulcrum->z + fulcrum->z) * 0.5f;
}

static void HairPhys_EndRunTwice(Vec3f *fulcrum, Vec3f *lastfulcrum){
    *lastfulcrum = *fulcrum;
    dt = 0.05f;
    fps = 20.0f;
}

static void HairPhys_UpdateDoubleImpl(
    HairPhysDoubleState *s, const HairPhysConstants *c,
    float costwist, float sintwist, float windX, float windZ, Vec3f *fc){
    PhysSegment(&s->s1, c->b, c->lim, fc, NULL, 
        costwist, sintwist, windX, windZ);
    PhysSegment(&s->s2, &c->dbl->b, c->dbl->lim, &s->s1.pos, &s->s1.fnext, 
        costwist, sintwist, windX, windZ);
}

void HairPhys_UpdateDouble(HairPhysDoubleState *s, const HairPhysConstants *c,
        Vec3f *lPos, Vec3s *lRot, float windX, float windZ, float actorscale, bool ignoreY){
    const HairPhysDouble *dbl = c->dbl;
    Vec3f fulcrum; float costwist, sintwist;
    s16 twist = ExtractFulcrumTwist(actorscale, c->b->len, lPos,
        &fulcrum, &costwist, &sintwist, c->b->parentaxis);
    float oldy = fulcrum.y;
    if(ignoreY) fulcrum.y = 0.0f;
    if(!s->initted){
        s->initted = 1;
        s->s1.pos.x = fulcrum.x;
        s->s1.pos.y = fulcrum.y - c->b->len;
        s->s1.pos.z = fulcrum.z;
        s->s2.pos.x = fulcrum.x;
        s->s2.pos.y = s->s1.pos.y - dbl->b.len;
        s->s2.pos.z = fulcrum.z;
        s->lastfulcrum = fulcrum;
    }else{
        if(c->b->runtwice){
            Vec3f halffulcrum;
            HairPhys_StartRunTwice(&fulcrum, &s->lastfulcrum, &halffulcrum);
            HairPhys_UpdateDoubleImpl(s, c, costwist, sintwist, windX, windZ, &halffulcrum);
        }
        HairPhys_UpdateDoubleImpl(s, c, costwist, sintwist, windX, windZ, &fulcrum);
        if(c->b->runtwice){
            HairPhys_EndRunTwice(&fulcrum, &s->lastfulcrum);
        }
    }
    Vec3f s1p = s->s1.pos, s2p = s->s2.pos;
    if(ignoreY){
        s1p.y += oldy;
        s2p.y += oldy;
    }
    ApplyLimbPosRot(&s1p, &s2p, dbl->b.len, actorscale,
        lPos, lRot, twist);
}

static void TunicPullOther(HairPhysTunicState *s, const HairPhysConstants *c, void *conn){
    if(conn == NULL) return;
    HairPhysTunicState *other = (HairPhysTunicState*)conn;
    float dx = s->s.pos.x - other->s.pos.x;
    float dz = s->s.pos.z - other->s.pos.z;
    float d = sqrtf(dx * dx + dz * dz);
    float n = 1.0f / (d + 0.0001f);
    d -= c->tn->dist;
    if(d > 0.0f){
        if(d > 3.0f) d = 3.0f;
        float mult = n * d * c->tn->pullfmult;
        other->s.fnext.x += mult * dx;
        other->s.fnext.z += mult * dz;
    }
}

static void HairPhys_UpdateTunicImpl(HairPhysTunicState *s, const HairPhysConstants *c,
    float costwist, float sintwist, float windX, float windZ, Vec3f *fc){
    PhysSegment(&s->s, c->b, c->lim, fc, NULL,
        costwist, sintwist, windX, windZ);
    TunicPullOther(s, c, s->conn1);
    TunicPullOther(s, c, s->conn2);
}

void HairPhys_UpdateTunic(HairPhysTunicState *s, const HairPhysConstants *c,
        Vec3f *lPos, Vec3s *lRot, float windX, float windZ, float actorscale, bool ignoreY){
    Vec3f fulcrum; float costwist, sintwist;
    s16 twist = ExtractFulcrumTwist(actorscale, 0.0f, lPos,
        &fulcrum, &costwist, &sintwist, c->b->parentaxis);
    float oldy = fulcrum.y;
    if(ignoreY) fulcrum.y = 0.0f;
    if(!s->initted){
        s->initted = 1;
        s->s.pos.x = fulcrum.x;
        s->s.pos.y = fulcrum.y - c->b->len;
        s->s.pos.z = fulcrum.z;
        s->lastfulcrum = fulcrum;
    }else{
        if(c->b->runtwice){
            Vec3f halffulcrum;
            HairPhys_StartRunTwice(&fulcrum, &s->lastfulcrum, &halffulcrum);
            HairPhys_UpdateTunicImpl(s, c, costwist, sintwist, windX, windZ, &halffulcrum);
        }
        HairPhys_UpdateTunicImpl(s, c, costwist, sintwist, windX, windZ, &fulcrum);
        if(c->b->runtwice){
            HairPhys_EndRunTwice(&fulcrum, &s->lastfulcrum);
        }
    }
    Vec3f sp = s->s.pos;
    if(ignoreY){
        fulcrum.y = oldy;
        sp.y += oldy;
    }
    ApplyLimbPosRot(&fulcrum, &sp, c->b->len, actorscale, lPos, lRot, twist);
}

typedef void (*HairPhysInitFunc)(void *s, const HairPhysConstants *c);
typedef void (*HairPhysUpdateFunc)(void *s, const HairPhysConstants *c, 
        Vec3f *lPos, Vec3s *lRot, float windX, float windZ, float actorscale, bool ignoreY);
typedef void (*HairPhysCulledUpdateFunc)(void *s, const HairPhysConstants *c);
static const HairPhysInitFunc initFuncs[3] = {
    (HairPhysInitFunc)HairPhys_InitSimple,
    (HairPhysInitFunc)HairPhys_InitDouble,
    (HairPhysInitFunc)HairPhys_InitTunic
};
static const HairPhysUpdateFunc updateFuncs[3] = {
    (HairPhysUpdateFunc)HairPhys_UpdateSimple,
    (HairPhysUpdateFunc)HairPhys_UpdateDouble,
    (HairPhysUpdateFunc)HairPhys_UpdateTunic
};
static const HairPhysCulledUpdateFunc culledUpdateFuncs[3] = {
    (HairPhysCulledUpdateFunc)HairPhys_CulledUpdateSimple,
    (HairPhysCulledUpdateFunc)HairPhys_CulledUpdateDouble,
    (HairPhysCulledUpdateFunc)HairPhys_CulledUpdateTunic
};

void HairPhys_Init(void *s, const HairPhysConstants *c){
    if(c->mode >= 3) return;
    initFuncs[c->mode](s, c);
}

void HairPhys_Update(void *s, const HairPhysConstants *c, Vec3f *lPos, 
    Vec3s *lRot, float windX, float windZ, float actorscale, bool ignoreY){
    if(c->mode >= 3) return;
    updateFuncs[c->mode](s, c, lPos, lRot, windX, windZ, actorscale, ignoreY);
}

void HairPhys_UpdateCulled(void *s, const HairPhysConstants *c){
    if(c->mode >= 3) return;
    culledUpdateFuncs[c->mode](s, c);
}
