#ifndef _HAIRPHYS_H_
#define _HAIRPHYS_H_ 

typedef struct {
    float mass;
    float oneovermass;
    float len;
    float restoreforce;
    float yawmult; //also used for wind randomness
    float dampening;
    float windpush;
    u8 parentaxis;
    u8 runtwice;
    u8 limdrag;
} HairPhysBasic;

typedef struct {
    Vec3f neg;
    Vec3f pos;
} HairPhysLimits;

typedef struct {
    HairPhysBasic b;
    const HairPhysLimits *lim;
} HairPhysDouble;

typedef struct {
    float dist;
    float pullfmult;
} HairPhysTunic;

typedef struct {
    u8 mode; // 0 simple, 1 double, 2 tunic
    const HairPhysBasic *b;
    const HairPhysLimits *lim;
    const HairPhysDouble *dbl;
    const HairPhysTunic *tn;
} HairPhysConstants;

#define HAIRPHYS_UNITROT 256.0f

typedef struct {
    Vec3f r; //rotation
    Vec3f v; //angular velocity
} HairPhysSimpleState;

typedef struct {
    Vec3f pos;
    Vec3f vel;
    Vec3f fnext; //Force from next segment on last frame
} HairPhysSegState;

typedef struct {
    HairPhysSegState s1, s2;
    Vec3f lastfulcrum;
    u8 initted;
} HairPhysDoubleState;

typedef struct {
    void *conn1; //Pointer to another HairPhysTunicState to apply force to.
    void *conn2;
    HairPhysSegState s;
    Vec3f lastfulcrum;
    u8 initted;
} HairPhysTunicState;

s16 Statics_ExtractRotationAxis(float actorscale, u8 axis);
void HairPhys_SetDebug(u8 d);
void HairPhys_Init(void *s, const HairPhysConstants *c);
void HairPhys_Update(void *s, const HairPhysConstants *c, Vec3f *lPos, 
    Vec3s *lRot, float windX, float windZ, float actorscale, bool ignoreY);
void HairPhys_UpdateCulled(void *s, const HairPhysConstants *c);

#endif //_HAIRPHYS_H_
