#include "ootmain.h"
#include "dma_patcher.h"
#include "../debugger/debugger.h"

//Table starts in RAM 0x8000B140
//First empty line after end of table 0x80010FA0 --i.e. 0x5E6 (1510) lines in table
//Next data after empty space 0x800110A0--i.e. 16 blank lines
#define N_DMADATA 0x5E6

// DmaPatcher RAM

typedef struct
{
    u32 vrom;
    u8* patch;
} DmaPatchEntry;

#define DMAPATCHER_MAXPATCHES 256

typedef struct
{
    u32 npatches;
    u32 dummy1;
    u32 dummy2;
    u32 dummy3;
    DmaPatchEntry patches[DMAPATCHER_MAXPATCHES];
} DmaPatcher;

static DmaPatcher patcher;

void DmaPatcher_ProcessMsg(DmaRequest* req);
void DmaPatcher_AudioFastCopyPatch_Pre();
void DmaPatcher_AudioFastCopyPatch_Post();

__attribute__((section(".start"))) void DmaPatcher_Init()
{
    //Debugger_Printf("DmaPatcher loaded");
    s32 i = __osDisableInt();
    patcher.npatches = 0;
    // Patch DmaMgr_ProcessMsg to jump to DmaPatcher_ProcessMsg
	*((u32*)0x80000B0C) = JUMPINSTR(DmaPatcher_ProcessMsg);
	*((u32*)0x80000B10) = 0;
	// Patch Audio_DMAFastCopy / Sound_LoadFile
	*((u32*)0x800B806C) = JUMPINSTR(DmaPatcher_AudioFastCopyPatch_Pre);
	*((u32*)0x800B8184) = JUMPINSTR(DmaPatcher_AudioFastCopyPatch_Post);
    // finally
    osWritebackDCache(NULL, 0x4000);
    osInvalICache(NULL, 0x4000);
    __osRestoreInt(i);
}

void DmaPatcher_AddPatch(u32 vrom, u8* patch)
{
    s32 i = __osDisableInt();
    if(patcher.npatches >= DMAPATCHER_MAXPATCHES){
        Debugger_Printf("AddPatch %08X: Too many patches!", vrom);
    }else{
        //Debugger_Printf("AddPatch %d VROM %08X inj %08X", patcher.npatches+1, vrom, patch);
        s32 flag = 0;
        for(u32 p=0; p<patcher.npatches; ++p){
            if(patcher.patches[p].vrom == vrom){
                patcher.patches[p].patch = patch;
                flag = 1;
                break;
            }
        }
        if(!flag){
            patcher.patches[patcher.npatches].vrom = vrom;
            patcher.patches[patcher.npatches].patch = patch;
            ++patcher.npatches;
        }
    }
    __osRestoreInt(i);
}

void DmaPatcher_ReplaceFile(u32 filenum, void* injectedAddr, u32 newsize)
{
    s32 i = __osDisableInt();
    gDmaDataTable[filenum].romStart = (u32)injectedAddr;
    gDmaDataTable[filenum].vromEnd = gDmaDataTable[filenum].vromStart + newsize;
    __osRestoreInt(i);
}

static void DmaPatcher_ApplyPatch(u8* ram, u32 size, u8* patch)
{
    u16 skipcount;
    u8 writecount;
    u8* ptr = ram;
    u8* ptrend = ram + size;
    while(1){
        skipcount = *patch++;
        if(skipcount >= 0x80){
            skipcount = ((skipcount & 0x7F) << 8) | *patch++;
        }
        writecount = *patch++;
        if(!skipcount && !writecount) return;
        ptr += skipcount;
        if(ptr + writecount > ptrend){
            Debugger_Printf("Patch to %08X overflowing file sz %X!", ram, size);
            return;
        }
        while(writecount--) *ptr++ = *patch++;
    }
}

void DmaPatcher_CheckApplyPatch(u32 vrom, void* ram, u32 size)
{
	u32 p;
	for(p=0; p<patcher.npatches; ++p){
		if(patcher.patches[p].vrom == vrom){
			//Debugger_Printf("DMA @%08X patching file", vrom);
			DmaPatcher_ApplyPatch(ram, size, patcher.patches[p].patch);
			return;
		}
	}
}

void DmaPatcher_AudioFastCopyPatch_Pre()
{
	asm(".set noat\n .set noreorder\n"
	//a0 = romaddr, a1 = ramaddr, a2 = size
    //Store them onto the stack, in their "original" (optimized out) positions
    "sw      $a0, 0x0050($sp)\n"
    "sw      $a1, 0x0054($sp)\n"
    "sw      $a2, 0x0058($sp)\n"
    "j       0x800B8074\n" //three instructions into the function
    "sw      $s2, 0x0038($sp)\n"
    ".set at\n .set reorder");
}

void DmaPatcher_AudioFastCopyPatch_Post()
{
	asm(".set noat\n .set noreorder\n"
    "lw      $a0, 0x0000($sp)\n"
    "lw      $a1, 0x0004($sp)\n"
	"j       DmaPatcher_CheckApplyPatch\n"
    "lw      $a2, 0x0008($sp)\n"
    ".set at\n .set reorder");
}

void DmaPatcher_CopyRAM(void* dest, const void* source, u32 size)
{
    osSetThreadPri(NULL, 0x0A);
    osYieldThread();
    bcopy(source, dest, size);
    osSetThreadPri(NULL, 0x10);
}

void DmaPatcher_ProcessMsg(DmaRequest* req)
{
    u32 vrom = req->vromAddr;
    void* ram = req->dramAddr;
    u32 size = req->size;
    u32 romStart, vromSize, copyStart;
    DmaEntry* iter = gDmaDataTable;
    if(vrom >= 0x04000000 && vrom < 0x04800000){
        //New file not in ROM provided as injection
        //Debugger_Printf("DMA %08X VROM RAM map", vrom);
        DmaPatcher_CopyRAM(ram, InjectRomRamMap(vrom), size);
        return;
    }
    while (iter->vromEnd) {
        if(vrom >= iter->vromStart && (vrom < (iter+1)->vromStart || vrom < iter->vromEnd)){
            //It's in this file
            //Changed from originally checking between vromStart and vromEnd
            //because this way we can patch files to be bigger than they
            //originally were, as long as the file is always loaded starting
            //from its start.
            if(vrom + size > iter->vromEnd){
                Debugger_Printf("!! DMA @%08X sz %X off end %08X", vrom, size, iter->vromEnd);
            }
            romStart = iter->romStart;
            copyStart = romStart + (vrom - iter->vromStart);
            if(romStart & 0x80000000){
                //Replaced whole existing ROM file with injection
                //Debugger_Printf("DMA @%08X replacing file", vrom);
                DmaPatcher_CopyRAM(ram, (const void*)copyStart, size);
                return;
            }
            if (iter->romEnd == 0) {
                DmaMgr_DMARomToRam(copyStart, (u32)ram, size);
            }else{
                if(copyStart != romStart){
                    Debugger_Printf("!! DMA @%08X middle of compressed file %08X", copyStart, romStart);
                }
                vromSize = iter->vromEnd - iter->vromStart;
                if(size != vromSize){
                    Debugger_Printf("!! DMA @%08X wrong size %08X should be %08X", size, vromSize);
                }
                osSetThreadPri(NULL, 0x0A);
                Yaz0_Decompress(romStart, ram, iter->romEnd - romStart); //romSize
                osSetThreadPri(NULL, 0x10);
            }
            //Patch file after loading
            DmaPatcher_CheckApplyPatch(vrom, ram, size);
            return;
        }
        ++iter;
    }
    Debugger_Printf("!! DMA @%08X not found", vrom);
    DmaMgr_DMARomToRam(vrom, (u32)ram, size);
}
