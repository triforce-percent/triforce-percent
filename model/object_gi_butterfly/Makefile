include ../../toolchain/make/main.mk

CCFLAGS += -Wno-incompatible-pointer-types -Wno-missing-braces

.PHONY: default clean

.PRECIOUS: object_gi_butterfly.bin

default: object_gi_butterfly.pat object_gi_butterfly.bin
	dd if=object_gi_butterfly.bin of=../../build-romhack/object/373/zobj.zobj conv=notrunc bs=1 seek=$$((0xB50))

object_gi_butterfly.pat: object_gi_butterfly.bin
	cat patch_pre.dat $< patch_post.dat > $@

%.elf: %.o
	$(LD) $(LDFLAGS) -o $*.elf $*.o

clean: cleandir

include ../../toolchain/make/c.mk
