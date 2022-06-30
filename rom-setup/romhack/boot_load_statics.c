#define NO_Z64HDR_GARBAGE 1
#include "ootmain.h"

extern u32 statics_START;

typedef struct {
   void* vrom;
   void* vram;
   u32 size;
} FakeDmaRequest;

#define _codeSegmentStart (void*)0x800110A0
#define _codeSegmentRomStart 0x00A87000
#define _codeSegmentRomEnd 0x00B8AD30
#define _codeSegmentBssStart (void*)0x80114DD0
#define _codeSegmentBssEnd (void*)0x8012BE30

// RAM: 0x800005A0, ROM: 0x000011A0
void func_800005A0(void* arg0) {
    static FakeDmaRequest rhstaticsFile = { (void*)0xDEADBEEF, &statics_START, 0x04206969 };
    
    DmaMgr_Init();
    DmaMgr_SendRequest1(_codeSegmentStart, _codeSegmentRomStart, _codeSegmentRomEnd - _codeSegmentRomStart);
    bzero(_codeSegmentBssStart, _codeSegmentBssEnd - _codeSegmentBssStart);
    DmaMgr_ProcessMsg((DmaRequest*)&rhstaticsFile);
    Main(arg0);
}
