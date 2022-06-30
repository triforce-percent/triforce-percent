/* OUTPUT_FORMAT("binary") */
OUTPUT_FORMAT("elf32-bigmips", "elf32-bigmips", "elf32-littlemips")
OUTPUT_ARCH (mips)

INCLUDE fast_loader/fast_loader.out.ld

framebuffer16 = 0x8011F56C;
framebuffer64 = 0x8011F56C;
sExceptionNames = 0x800FF320;
padmgrth = 0x8011D580;

ENTRY(Debugger_Init);

SECTIONS {
	. = fast_loader_END;
	.start ALIGN(16): { *(.start) }
	.text ALIGN(16): { *(.text) }
	.data ALIGN(16): { *(.data) }
	.bss ALIGN(16):  { *(.bss) }
}
