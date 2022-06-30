INCLUDE ../../statics/statics.out.ld

ENTRY_POINT = 0x80800000;
ENTRY(ENTRY_POINT)
SECTIONS {
	. = ENTRY_POINT;
	.text ALIGN(16): { *(.text) }
}
