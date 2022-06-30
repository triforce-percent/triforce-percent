OUTPUT_FORMAT("elf32-bigmips", "elf32-bigmips", "elf32-littlemips")
OUTPUT_ARCH (mips)

_UnicornFountain_room_0SegmentRomStart = 0xDEADBEEF;
_UnicornFountain_room_0SegmentRomEnd = 0xDEADBEEF;
_TestVAlpha_room_0SegmentRomStart = 0xDEADBEEF;
_TestVAlpha_room_0SegmentRomEnd = 0xDEADBEEF;
_ChamberOfSages_room_0SegmentRomStart = 0xDEADBEEF;
_ChamberOfSages_room_0SegmentRomEnd = 0xDEADBEEF;
_TriforceRoom_room_0SegmentRomStart = 0xDEADBEEF;
_TriforceRoom_room_0SegmentRomEnd = 0xDEADBEEF;
_Ending_room_0SegmentRomStart = 0xDEADBEEF;
_Ending_room_0SegmentRomEnd = 0xDEADBEEF;

ENTRY_POINT = 0x02000000;
ENTRY(ENTRY_POINT);

SECTIONS {
	. = ENTRY_POINT;
	.data ALIGN(16): { *(.data) *(.rodata) *(.bss) }
	.text ALIGN(16): { *(.text) }
	.MIPS.abiflags ALIGN(16): { *(.MIPS.abiflags) }
}
