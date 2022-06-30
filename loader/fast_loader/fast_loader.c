#include "ootmain.h"
#include "fast_loader.h"

#define RUMBLE_CRCFAIL 1
#define RUMBLE_Q_FALSE 2
#define RUMBLE_Q_TRUE 3
#define RUMBLE_INVALID 4
#define RUMBLE_NOP 5
#define RUMBLE_VALID 6

//Padmgr

typedef union {
	u8 bytes[6];
	u16 halves[3];
	struct {
		u8 b1, b2, x, y;
		u16 status;
	};
	struct {
		s8 b1, b2, x, y;
		u16 status;
	} s;
	struct {
		u8 a :1;
		u8 b :1;
		u8 z :1;
		u8 s :1;
		u8 du:1;
		u8 dd:1;
		u8 dl:1;
		u8 dr:1;
		u8 reset:1;
		u8 unused:1;
		u8 l :1;
		u8 r :1;
		u8 cu:1;
		u8 cd:1;
		u8 cl:1;
		u8 cr:1;
		u8 x, y;
		u16 status;
	} buttons;
} RawInput;

typedef struct {
	u8 unused1[656];
	RawInput pads[4];
	u8 unused2[10];
	u8 rumble_enable[4];
	u8 rumble_counter[4];
	u8 unused3[418];
	u8 rumble_off_frames;
	u8 rumble_on_frames;
	u8 unused4[10];
} FakePadMgr;

extern FakePadMgr padmgr;

#define POLLS 8
#define DATA_LEN (45 * ((POLLS) >> 2))
#define COMMAND_LEN ((DATA_LEN) - 5)
#define HUGE_T_SIZE 23 /* ceiling((30 bits * 3 pads * 8 polls) / 32)*/

#define EXTRA_FAKE_POLLS 0

// Command format:
// 4 poll format: struct { u32 crc32; u8 data[40]; u8 command_id; }
// 8 poll format: struct { u32 crc32; u8 data[85]; u8 command_id; }
typedef union {
	struct {
		u32 crc;
		union {
			u8 bytes[COMMAND_LEN];
			
			// Command 1: Load 81 bytes to given address
			// Command 2: Load up to 80 bytes to given address
			struct {
				u8* address;
				u8  data[COMMAND_LEN - 5];
				u8  length; // Is last data byte when run as command 1
			} __attribute__((packed)) cmd01;
			
			// Command 3: Load X counts of byte Y to specified address
			struct {
				u8* address;
				u32 length;
				u8  byte;
				u8  padding[COMMAND_LEN - 9];
			} __attribute__((packed)) cmd03;
			
			// Command 4: DMA uncompressed data
			// Command 5: DMA compressed data
			struct {
				u32 vram;
				u32 vrom;
				u32 size;
				u8  padding[COMMAND_LEN - 12];
			} __attribute__((packed)) cmd04;
			
			// Command 6: Call command data as code
			//No need for a separate struct--just call `bytes`
			
			// Command 7: Call specified address with up to 4 args
			struct {
				void(*function_pointer)(s32 a0, s32 a1, s32 a2, s32 a3);
				s32 a0;
				s32 a1;
				s32 a2;
				s32 a3;
				u8  padding[COMMAND_LEN - 20];
			} __attribute__((packed)) cmd07;
			
		};
		u8 id;
	} __attribute__((packed)) command;
	u8 bytes[DATA_LEN];
	u16 halves[DATA_LEN>>1];
} OutData;

#define STATIC_ASSERT(COND,MSG) typedef char static_assertion_##MSG[(COND)?1:-1]
STATIC_ASSERT(sizeof(OutData) == DATA_LEN, OutDataSize);

static OutData out_data;

//Other data

static RawInput pad_data[4];
static u32 crc_table[256]; // 1024 bytes
void(*fp_precmd)(void);
void(*fp_postcmd)(void);
s32 fl_disable_green_bar;

//Profiling

// #define NUM_FL_COUNTS 16
// static u32 recent_fl_counts[NUM_FL_COUNTS];
// static u8 recent_count_counter;
u32 last_fl_count;
u32 avg_fl_count;

//Twitch messages
TwitchMessage twitch_msg_buf[MAX_TWITCH_MESSAGES];
static u16 twitch_write_idx;

//Function prototypes

void fl_init();
static void fl_run(OSMesgQueue* queue);
static void fl_rumble_message(u32 bits);
static u32 fl_crc_data(void* data, u32 size);


// entry point
__attribute__((section(".start"))) void fl_init() {
	// generate CRC table
	u32 r, i; u8 counter;
	for(i = 0; i < 256; ++i) {
		r = i;
		for(counter = 0; counter < 8; ++counter)
			r = ((r & 1) ? 0 : 0xEDB88320) ^ (r >> 1);
		crc_table[i] = r ^ 0xFF000000;
	}
	
	// patch padmgr to call run() every frame
	*((u32*)0x800A2640) = JALINSTR(fl_run); // construct jal to run() (also disable zeroing of pad 4)
	*((u32*)0x800A2644) = 0x8FA4002C; // first argument is address to queue
	
	// PadMgr_RumbleControl will only poll other controllers for rumble paks
	// if it hasn't attempted to send a rumble message to another controller
	// on the same frame. Since we're messing with the rumble pack sending
	// so that messages are sent every frame, once one controller is successfully
	// polled it'll get messages every frame and then no other controllers will
	// be polled for rumble pak. So, patch out the check so it will always
	// poll for rumble paks even if other rumble paks have been accessed this frame.
	// Line "if (!triedRumbleComm) {" in decomp
	// Instruction  B3E824 800C7684 16A00052   bnez  $s5, .L800C77D0 in Debug ROM
	// Instruction         800A21E4            bne    s3, $zero, lbl_800A22C0 in 1.0
	*((u32*)0x800A21E4) = 0;
	
	// Initialize out_data to something invalid to see if controller polling is working
	for(i=0; i<DATA_LEN; ++i){
		out_data.bytes[i] = 0xA5;
	}
	
	fl_disable_green_bar = 0;
	//recent_count_counter = 0;
	last_fl_count = 0;
	avg_fl_count = 0;
	
	gSaveContext.naviTimer = 1;
	
	// Twitch
	twitch_write_idx = 0;
	bzero(twitch_msg_buf, sizeof(TwitchMessage) * MAX_TWITCH_MESSAGES);
}

// called by padmgr
static void fl_run(OSMesgQueue* queue) {
	// Draw green bar in the corner
	const u64 green64 = 0x7c107c107c107c1ULL;
	const s32 framebuffer1 = 0x80400000 - (320*240*2);
	const s32 framebuffer2 = 0x80400000 - (320*240*2)*2;
	if(!fl_disable_green_bar){
		/*(*((volatile u64**)0x8011F56C))*/
		((volatile u64*)(framebuffer1))[1286] = green64; // shifted two pixels to the right of the "real" one
		((volatile u64*)(framebuffer1))[1287] = green64; // due to longword alignment
		((volatile u64*)(framebuffer2))[1286] = green64;
		((volatile u64*)(framebuffer2))[1287] = green64;
	}
	/*
	static u64 chaser = 0x0102040880204010ull;
	((volatile u64*)(framebuffer1))[1288] = chaser;
	((volatile u64*)(framebuffer2))[1288] = chaser;
	chaser = (chaser << 1) | ((chaser >> 63) ^ ((chaser >> 56) & 1) ^ ((chaser >> 3) & 1));
	*/
	
	//u32 count_start = osGetCount();
	
	// Poll controllers
	u32 i;
	
	for(i = 0; i < (POLLS); ++i) {
		RawInput* p;
		
		// Preserve the original pad input as polled by the original code
		if(!i) { // the first time, use pad data from the original game poll
			p = &padmgr.pads[0];
		} else { // afterwards, poll the pads ourselves, and discard data for pad 1
			for(u32 j=0; j<24; ++j){
				((u8*)pad_data)[j] = 0xFF;
			}
			p = pad_data;
			while(osContStartReadData(queue) != 0){
				//Wait until ready
				osWritebackDCache(NULL, 0x4000); //busy wait, this should take a little time
			}
			// msg = NULL, to_block = 1
			osRecvMesg(queue, NULL, 1);
			osContGetReadData((OSContPad*)p); // actually get the pad data
		}
		
		// We use halfwords, because two of the RawInput objects are 2-byte
		// aligned and two are 4-byte aligned.
		u16* data_out = &out_data.halves[6*i];
		data_out[0] = p[1].halves[0] & 0xFF3F;
		data_out[1] = p[1].halves[1];
		data_out[2] = p[2].halves[0] & 0xFF3F;
		if(i < POLLS-1){
			data_out[3] = p[2].halves[1];
			data_out[4] = p[3].halves[0] & 0xFF3F;
			data_out[5] = p[3].halves[1];
		}else{
			u32 j = 1, k, temp;
			for(temp = p[3].halves[1], k=0; k<8; ++k, j+=4, temp>>=2) out_data.bytes[j] |= (u8)(temp&3)<<6;
			for(temp = p[3].bytes[1] , k=0; k<3; ++k, j+=4, temp>>=2) out_data.bytes[j] |= (u8)(temp&3)<<6;
			for(temp = p[3].bytes[0] , k=0; k<4; ++k, j+=4, temp>>=2) out_data.bytes[j] |= (u8)(temp&3)<<6;
			for(temp = p[2].halves[1], k=0; k<8; ++k, j+=4, temp>>=2) out_data.bytes[j] |= (u8)(temp&3)<<6;
		}
	}
	
	/*
	for(i=0; i<EXTRA_FAKE_POLLS; ++i){
		while(osContStartQuery(queue) != 0){
			//Wait until ready
			osWritebackDCache(NULL, 0x4000); //busy wait, this should take a little time
		}
		// msg = NULL, to_block = 1
		osRecvMesg(queue, NULL, 1);
		OSContStatus status;
		osContGetQuery(&status);
	}
	*/
	
	// zero pads 1 and 3 ourselves
	bzero(&padmgr.pads[1], 6);
	bzero(&padmgr.pads[3], 6);
	
	if(fp_precmd) fp_precmd();
	
	u8 rumble_result;
	if(out_data.command.id == 0 && out_data.command.crc == 0){
		// Assume it's all zero
		rumble_result = RUMBLE_NOP;
	} else if(fl_crc_data(out_data.command.bytes, DATA_LEN - 4) != out_data.command.crc) {
		// CRC everything except for the CRC itself
		rumble_result = RUMBLE_CRCFAIL;
	} else {
		rumble_result = RUMBLE_VALID;
		switch(out_data.command.id) {
			
			case 1: //   fixed 81 byte size
			case 2: { // up to 80 byte size
				int i, len;
				len = (out_data.command.id == 1) ? (COMMAND_LEN - 4) : out_data.command.cmd01.length;
				for(i = 0; i < len; ++i)
					*(out_data.command.cmd01.address++) = out_data.command.cmd01.data[i];
			} break;
			
			case 3: { // load X counts of byte Y to specified address
				while(out_data.command.cmd03.length > 0) {
					*(out_data.command.cmd03.address++) = out_data.command.cmd03.byte;
					--out_data.command.cmd03.length;
				}
			} break;
			
			case 4: { // DMA uncompressed or compressed data--handled on DmaMgr thread
				DmaMgr_SendRequest0(
					out_data.command.cmd04.vram,
					out_data.command.cmd04.vrom,
					out_data.command.cmd04.size
				);
			} break;
			
			/*
			case 5: { // DMA compressed data--this would be on this thread, problems!
				Yaz0_Decompress(
					out_data.command.cmd04.vrom,
					out_data.command.cmd04.vram,
					out_data.command.cmd04.size
				);
			} break;
			*/
			
			case 6: { // Treat command data as instructions and jump to them (can execute `2.5 * POLLS` instructions)
				//Addr is weird, it's a cache line address not a normal address.
				//Just set addr to 0 and size to >= 0x2000 to write back the whole cache.
				osWritebackDCache(NULL, 0x4000);
				//Set addr to 0 and size to >= 0x4000 to invalidate the whole cache.
				osInvalICache(NULL, 0x4000);
				((void(*)(void))&out_data.command.bytes)();
			} break;
			
			case 7: { // Call specified address
				out_data.command.cmd07.function_pointer(
					out_data.command.cmd07.a0,
					out_data.command.cmd07.a1,
					out_data.command.cmd07.a2,
					out_data.command.cmd07.a3
				);
			} break;
			
			case 10: { // Twitch message
				for(i=0; i<NUM_TWITCH_PER_PACKET; ++i){
					bcopy(&out_data.command.bytes[TWITCH_BYTES*i], 
						&twitch_msg_buf[twitch_write_idx], TWITCH_BYTES);
					twitch_msg_buf[twitch_write_idx].timer = 0xFF;
					++twitch_write_idx;
					if(twitch_write_idx >= MAX_TWITCH_MESSAGES) twitch_write_idx = 0;
				}
			} break;
			
			default: {
				rumble_result = RUMBLE_INVALID;
			} break;
		}
	}
	fl_rumble_message(rumble_result);
	
	// Profiling
	
	/*
	last_fl_count = osGetCount() - count_start;
	recent_fl_counts[recent_count_counter] = last_fl_count;
	++recent_count_counter;
	if(recent_count_counter == NUM_FL_COUNTS) recent_count_counter = 0;
	avg_fl_count = 0;
	for(i=0; i<NUM_FL_COUNTS; ++i){
		avg_fl_count += recent_fl_counts[i];
	}
	avg_fl_count /= NUM_FL_COUNTS;
	*/
	
	// Finally 
	
	if(fp_postcmd) fp_postcmd();
}

static void fl_rumble_message(u32 bits) {
	int i;
	padmgr.rumble_on_frames = 0xF0; // ???
	for(i = 1; i < 4; ++i) {
		padmgr.rumble_counter[i] = 2;
		padmgr.rumble_enable[i] = bits & 1;
		bits >>= 1;
	}	
}

static u32 fl_crc_data(void* data, u32 size) {
	u32 state;
	state = 0U;
	while(size) {
		state = crc_table[(state & 0xFF) ^ *((u8*)data)] ^ (state >> 8);
		++data;
		--size;
	}
	return state;
}
