#include "ootmain.h"
#include "debugger.h"
#include "../fast_loader/fast_loader.h"

//Screen text stuff

extern volatile u16* volatile framebuffer16;
extern volatile u64* volatile framebuffer64;

#define COLOR_5551(r, g, b) ((u16)((((u16)(r))<<11)|(((u16)(g))<<6)|(((u16)(b))<<1)|1))
#define COLOR_WHITE  (COLOR_5551(0x1F, 0x1F, 0x1F))

static const u16 color_table[16] = {
	COLOR_5551(0x00, 0x00, 0x00), //black
	COLOR_5551(0x10, 0x08, 0x00), //brown
	COLOR_5551(0x1F, 0x0C, 0x00), //orange
	COLOR_5551(0x0C, 0x1F, 0x00), //lime
	COLOR_5551(0x00, 0x1F, 0x0C), //teal
	COLOR_5551(0x06, 0x00, 0x1F), //indigo
	COLOR_5551(0x14, 0x00, 0x1F), //purple
	COLOR_5551(0x14, 0x14, 0x14), //light grey
	COLOR_5551(0x0C, 0x0C, 0x0C), //dark grey
	COLOR_5551(0x1F, 0x00, 0x00), //red
	COLOR_5551(0x00, 0x1F, 0x00), //green
	COLOR_5551(0x00, 0x00, 0x1F), //blue
	COLOR_5551(0x1F, 0x1F, 0x00), //yellow
	COLOR_5551(0x00, 0x1F, 0x1F), //cyan
	COLOR_5551(0x1F, 0x00, 0x1F), //magenta
	COLOR_5551(0x1F, 0x1F, 0x1F), //white
};

#define LETTER_WIDTH  6
#define LETTER_HEIGHT 8

// each byte is a 6px scanline at 1bpp
static const u8 ascii_letters[760] = {
	 8,28,28, 8, 8, 0, 8, 0,
	20,20,20, 0, 0, 0, 0, 0,
	20,20,62,20,62,20,20, 0,
	 8,30,32,28, 2,60,24, 0,
	 0,50,36, 8,16,18,38, 0,
	 8,20, 8,42,36,36,26, 0,
	 8, 8, 4, 0, 0, 0, 0, 0,
	 8,16,32,32,32,16, 8, 0,
	16, 8, 4, 4, 4, 8,16, 0,
	 0,20, 8,62, 8,20, 0, 0,
	 0, 4, 4,31, 4, 4, 0, 0,
	 0, 0, 0, 0, 0, 8, 8,16,
	 0, 0, 0,30, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 8, 8, 0,
	 0, 1, 2, 4, 8,16,32, 0,
	28,34,38,42,50,50,28, 0,
	 8,24,40, 8, 8, 8,62, 0,
	28,34, 2,12,24,34,62, 0,
	28,34, 2,12, 2,34,28, 0,
	 4,12,20,36,62, 4,14, 0,
	62,32,32,60, 2,34,28, 0,
	12,16,32,60,34,34,28, 0,
	62,34, 4, 8,16,16,16, 0,
	28,34,34,28,34,34,28, 0,
	28,34,34,30, 2, 2,28, 0,
	 0, 8, 8, 0, 0, 8, 8, 0,
	 0, 8, 8, 0, 0, 8, 8,16,
	 4, 8,16,32,16, 8, 4, 0,
	 0, 0,62, 0, 0,62, 0, 0,
	16, 8, 4, 2, 4, 8,16, 0,
	28,34, 2, 4, 8, 0, 8, 0,
	28,34,46,42,46,32,28, 0,
	 8,20,34,34,62,34,34, 0,
	60,18,18,28,18,18,60, 0,
	12,18,32,32,32,18,12, 0,
	60,18,18,18,18,18,60, 0,
	62,18,16,28,16,18,62, 0,
	62,18,16,28,16,16,56, 0,
	12,18,32,32,38,18,14, 0,
	34,34,34,62,34,34,34, 0,
	28, 8, 8, 8, 8, 8,28, 0,
	14, 4, 4, 4,36,36,24, 0,
	50,20,20,24,20,20,51, 0,
	56,16,16,16,16,18,62, 0,
	34,54,42,42,34,34,34, 0,
	34,50,42,38,34,34,34, 0,
	28,34,34,34,34,34,28, 0,
	60,18,18,28,16,16,56, 0,
	28,34,34,34,34,42,28, 3,
	60,18,18,28,24,20,50, 0,
	28,34,32,28, 2,34,28, 0,
	62,42, 8, 8, 8, 8,28, 0,
	34,34,34,34,34,34,28, 0,
	34,34,34,34,34,20, 8, 0,
	34,34,34,42,42,42,20, 0,
	34,20,20, 8,20,20,34, 0,
	34,34,20, 8, 8, 8,28, 0,
	62,34, 4, 8,16,34,62, 0,
	56,32,32,32,32,32,56, 0,
	32,32,16, 8, 4, 2, 1, 0,
	56, 8, 8, 8, 8, 8,56, 0,
	 8,20,34,34, 0, 0, 0, 0,
	 0, 0, 0, 0, 0, 0, 0,63,
	 8, 8, 4, 0, 0, 0, 0, 0,
	 0, 0,28, 2,30,34,31, 0,
	48,16,16,20,26,18,44, 0,
	 0, 0,28,34,32,34,28, 0,
	 6, 2, 2,26,38,38,27, 0,
	 0, 0,28,34,62,32,28, 0,
	12,18,16,56,16,16,56, 0,
	 0, 0,26,34,34,30, 2,60,
	48,16,20,26,18,18,50, 0,
	 8, 0,24, 8, 8, 8,28, 0,
	 2, 0, 6, 2, 2,34,34,28,
	48,16,18,20,24,20,18, 0,
	24, 8, 8, 8, 8, 8,28, 0,
	 0, 0,52,42,42,42,42, 0,
	 0, 0,44,50,34,34,34, 0,
	 0, 0,28,34,34,34,28, 0,
	 0, 0,60,18,18,28,16,56,
	 0, 0,26,36,36,28, 4,14,
	 0, 0,54,26,16,16,56, 0,
	 0, 0,30,32,28, 2,60, 0,
	16,16,60,16,16,18,12, 0,
	 0, 0,34,34,34,38,26, 0,
	 0, 0,34,34,34,20, 8, 0,
	 0, 0,34,42,42,42,20, 0,
	 0, 0,34,20, 8,20,34, 0,
	 0, 0,34,34,34,30, 2,60,
	 0, 0,62, 4, 8,16,62, 0,
	 6, 8, 8,48, 8, 8, 6, 0,
	 8, 8, 8, 0, 8, 8, 8, 0,
	48, 8, 8, 6, 8, 8,48, 0,
	18,44, 0, 0, 0, 0, 0, 0,
	 0, 8,20,34,34,34,62, 0
};


// screen bounds:
// 4 <= X <= 316
// 1 <= Y <= 237

inline void put_pixel( u32 x, u32 y, u16 color );
void put_pixel( u32 x, u32 y, u16 color ) {
	if( x >= 320 ) return;
	if( y >= 240 ) return;
	y *= 320;
	y += x;
	//framebuffer16[ y ] = color;
	const s32 framebuffer1 = 0x80400000 - (320*240*2);
	const s32 framebuffer2 = 0x80400000 - (320*240*2)*2;
	((volatile u16*)(framebuffer1))[y] = color;
	((volatile u16*)(framebuffer2))[y] = color;
}

// Print letter to the screen
// c is u16 as it gets multiplied by 8
static void print_char( u16 c, u16 x, u16 y, u16 color ) {
	u8 i, j, scanline;
	if( c < '!' || c > 127 ) return; // if space, or invalid, don't draw anything
	c -= '!';
	c <<= 3;
	for( i = 0; i < 8; ++i ) {
		scanline = ascii_letters[ c + i ];
		for( j = 0; j < 6; ++j ) {
			if( scanline & 32 )
				put_pixel( x + j, y + i, color );
			scanline <<= 1;
		}
	}
}

static void print_string(u16 x, u16 y, char* str) {
	u16 xstart = x;
	u16 color = COLOR_WHITE;
	char c;
	while((c = *str++)) {
		if(c == '\n'){
			x = xstart;
			y += LETTER_HEIGHT;
		}else if(c >= 0x10 && c <= 0x1F){
			color = color_table[c - 0x10];
		}else{
			print_char(c, x, y, color);
			x += LETTER_WIDTH;
		}
	}
}

/*
void _memcpy(void* dest, const void* src, u32 size) {
    if(!(((u32)dest | (u32)src | size) & 0x7)){
        //All multiple of 8 bytes
        u64* dest64 = (u64*)dest;
        const u64* src64 = (const u64*)src;
        while(size){
            *dest64++ = *src64++;
            size -= 8;
        }
        return;
    }
    u8* dest8 = (u8*)dest;
    const u8* src8 = (const u8*)src;
    while(size--) *dest8++ = *src8++;
}
*/


//Debugger proper

#define DBG_MSG_LEN 63
typedef struct
{
    u8 timeout;
    char msg[DBG_MSG_LEN];
} DebugMessage;

#define N_DBG_MSGS 10
typedef struct
{
    char printf_buffer[256];
    DebugMessage messages[N_DBG_MSGS];
    u8 write_msg;
} Debugger;

static Debugger debugger;

#define _printf(x, y, format...) { \
	sprintf(debugger.printf_buffer, format); \
	print_string((x),(y),debugger.printf_buffer); \
}

char *Debugger_GetNextMessageBuffer(u8 timeout)
{
	u8 write_msg = debugger.write_msg;
	debugger.messages[write_msg].timeout = timeout;
	char *ret = debugger.messages[write_msg].msg;
	++write_msg;
	if(write_msg == N_DBG_MSGS) write_msg = 0;
	debugger.write_msg = write_msg;
	return ret;
}

void Debugger_ShowMessage(u8 timeout, const char *msg)
{
	bcopy(msg, Debugger_GetNextMessageBuffer(timeout), DBG_MSG_LEN);
}

/*
//Crash debugger

extern const char **sExceptionNames;

static const u8 is_exception_memory_related[] = {
	0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0
};

static const char* register_names[] = {
	"r0", "at", "v0", "v1", "a0", "a1", "a2", "a3",
	"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
	"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
	"t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"
};

static u32 read_register(OSThread *th, u8 reg){
	if(reg == 0 || reg == 26 || reg == 27) return 0;
	if(reg >= 28) reg -= 2;
	--reg;
	return (u32)((&(th->context.at))[reg]);
}

static s32 is_thread_crashed(OSThread *th){
	if(!th) return 0;
	if(!(th->state & (OS_STATE_WAITING | OS_STATE_RUNNING | OS_STATE_RUNNABLE))) return 1;
	return 0;
}

extern OSThread padmgrth;
*/

/*
static const u32 rsp_target_code[8] = {
	0x4a1bef67, 0x48802300, 0x4b0018e7, 0x48802700,
	0x4bffad68, 0xc9223016, 0x4bffe728, 0xc9343013
};
*/

u32 sPerfCount = 0;
u8 sDbgLagRepeat = 0;
f32 sDbgLagPlaySpeed = 0;

static void Debugger_Draw()
{
	/*
	GlobalContext *globalCtx = &gGlobalContext;
	_printf(8, 8, "\x12sc %d st %d nexte %04X cs %04X nxcs %04X",
		globalCtx->sceneNum, gSaveContext.sceneSetupIndex, 
		globalCtx->nextEntranceIndex, gSaveContext.cutsceneIndex, gSaveContext.nextCutsceneIndex);
	*/
	
	/*
	_printf(4, 4, "%4d %d %d %5.3f", gGlobalContext.csCtx.frames, 
		sPerfCount, sDbgLagRepeat, sDbgLagPlaySpeed);
	*/
	
	/*
	static s32 searchaddr = 0x80000000;
	static s32 searchstate = 0;
	if(searchstate == 0){
		_printf(8, 8, "Searching %08X", searchaddr);
		for(s32 i=0; i<0x1000; i+=4){
			u32* ptr = (u32*)searchaddr;
			s32 c;
			for(c=0; c<8; ++c){
				if(*(ptr+c) != rsp_target_code[c]) break;
			}
			if(c == 8){
				searchstate = 1;
				break;
			}else{
				searchaddr += 4;
			}
		}
		if(searchaddr >= 0x80400000){
			searchstate = 2;
		}
	}else if(searchstate == 1){
		_printf(8, 8, "Found F3DZEX sec at %08X", searchaddr);
	}else{
		_printf(8, 8, "Could not find F3DZEX sec");
	}
	*/
	
	/*
	s32 tcount = 0;
	for(s32 i=0; i<MAX_TWITCH_MESSAGES; ++i){
		if(twitch_msg_buf[i].timer != 0) ++tcount;
	}
	_printf(8, 8, "%d msgs", tcount);
	*/
	
	//_printf(8, 8, "pos %04X len %04X", *(u16*)0x8010A928, *(u16*)0x8010A92C);
	
	u8 msg;
	for(msg=0; msg<N_DBG_MSGS; ++msg){
		if(debugger.messages[msg].timeout){
			print_string(8, 120 + (msg * LETTER_HEIGHT), debugger.messages[msg].msg);
			--debugger.messages[msg].timeout;
		}
	}
	
	/*
	OSThread *th = NULL;
	if(is_thread_crashed(__osFaultedThread)){
		th = __osFaultedThread;
	}else if(is_thread_crashed(&padmgrth)){
		th = &padmgrth;
	}
	if(th){
		u32 causeStrIdx = ((u32)th->context.cause >> 2) & 0x1f;
		u32 causeStrIdxRaw = causeStrIdx;
	    if (causeStrIdx == 0x17) causeStrIdx = 0x10;
	    if (causeStrIdx == 0x1f) causeStrIdx = 0x11;
		const char *causeStr = (causeStrIdx >= 0 ? sExceptionNames[causeStrIdx] : "Unknown");
		_printf(8, 16, "Thread %d: (%d) %s", th->id, causeStrIdxRaw, causeStr);
		if(is_exception_memory_related[causeStrIdx]){
			_printf(8, 24, "Bad VA: %08X", th->context.badvaddr);
		}else{
			_printf(8, 24, "(Press C-right to pay respects)");
		}
		u32 pc = th->context.pc;
		u32 instruction = (pc >= 0x80000000 && pc < 0x80800000) ? *(u32*)pc : 0x69690420;
		//u8 mainop = (instruction & 0xFC000000) >> 24;
		u8 rbs = (instruction & 0x03E00000) >> 21;
		u8 rt = (instruction & 0x001F0000) >> 16;
		u8 rd = (instruction & 0x0000F800) >> 11;
		_printf(8, 32, "@%08X: instr %08X", pc, instruction);
		u8 row = 40;
		if(instruction != 0x08 && instruction != 0x0C){
			if(instruction == 0x00){
				_printf(8, row, "rd = $%s = %08X", register_names[rd], read_register(th, rd));
				row += LETTER_HEIGHT;
			}
			_printf(8, row, "%s = $%s = %08X", instruction >= 0x68 ? "rb" : "rs",
					register_names[rbs], read_register(th, rbs));
			row += LETTER_HEIGHT;
			if(instruction != 0x04){
				_printf(8, row, "rt = $%s = %08X", register_names[rt], read_register(th, rt));
				row += LETTER_HEIGHT;
			}
		}
	}
	*/
}

void FaultPatch(){
	asm(".set noat\n .set noreorder\n" //              line 28 = 80073148
    "addiu $a0, $zero, 3000\n"
    ".set at\n .set reorder");
}

__attribute__((section(".start"))) void Debugger_Init()
{
	fp_postcmd = Debugger_Draw;
    fl_disable_green_bar = 1;
	/*
    Debugger_ShowMessage(180, "\x1FWelcome to \x12T\x16""A\x14S\x1A""b\x1Bo\x1Ct \x13O\x15S\x1F v420.69");
	Debugger_ShowMessage(190, "Hyperspeed polling data loader loaded.");
	Debugger_ShowMessage(200, "Debugger loaded (HI MOM!).");
	*/
	
	// Disable Fault_WaitForButtonCombo so if it crashes, it shows the info immediately
	*((u32*)0x800AF360) = 0;
	*((u32*)0x800AF64C) = 0;
	
	// Patch func_800AD5FC (roughly Fault_WaitForInputImpl) to just wait for 3
	// seconds instead of waiting for controller input
	*((u32*)0x800AD63C) = ((u32*)FaultPatch)[0];
	*((u32*)0x800AD648) = 0;
	*((u32*)0x800AD654) = 0;
	*((u32*)0x800AD65C) = 0;
}
