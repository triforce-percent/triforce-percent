extern u8 sIsLiveRun;

void Statics_Player_Init();
void Statics_Update();
void Statics_TimeTravel();

void Statics_GiveLongOfTime();
void Statics_GiveOvertureOfSages();
s32 Statics_ShouldAbortWarp();

bool Statics_UncullObject(GlobalContext* globalCtx, Vec3f *center, float xsize, 
	float yBelow, float yAbove, float zBehind, float zFar);
    
extern void Player_RAM_START();
extern void Player_START();

static inline void *PlayerVRAMtoRAM(void *ptr){
    return ptr - (void*)Player_START + (void*)Player_RAM_START;
}
