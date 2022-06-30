include ../../toolchain/make/main.mk

.PHONY: default clean

BUILDDIR = ../../build-romhack
PATCHDIR = $(BUILDDIR)/patch
BUILDRTL = $(BUILDDIR)/oot_build.rtl

#CCFLAGS += --save-temps

default: $(BUILDDIR)/tf-romhack.z64

LOCALBINFILES = boot_load_statics.bin padmgr_call_statics.bin
BINFILES = $(LOCALBINFILES) ../../anim/anim.bin ../../statics/statics.bin 
	
$(BUILDDIR)/tf-romhack.z64: $(BUILDDIR)/update.txt $(LOCALBINFILES) ../../toolchain/zzrtl/oot_build.rtl
	mkdir -p $(PATCHDIR)
	cp $(BINFILES) $(PATCHDIR)
	cp ../../toolchain/zzrtl/oot_build.rtl $(BUILDRTL)
	sed -i 's/build.z64/tf-romhack.z64/g' $(BUILDRTL)
	$(ZZRTL) $(BUILDRTL)
	dd if=../../textures/butterfly_bottle.rgba32.bin of=$@ conv=notrunc bs=1 seek=$$((0x7DB000))
	dd if=../../textures/sages_charm_24.rgba32.bin of=$@ conv=notrunc bs=1 seek=$$((0x84B100))
	dd if=../../textures/triforce.rgba32.bin of=$@ conv=notrunc bs=1 seek=$$((0x84D500))

padmgr_call_statics.o: padmgr_call_statics.s
	$(AS) -Os -o $@ $<

%.elf: %.o boot_load_statics.ld ../../statics/statics.out.ld $(OOTMAINLD)
	$(LD) $(LDFLAGS) -T boot_load_statics.ld -o $*.elf $*.o

clean: cleandir
	rm -f boot_load_statics.s
	find $(BUILDDIR) -mindepth 1 -maxdepth 1 ! -name 'oot_1.0U_uncomp.z64' -exec rm -rf {} +

include ../../toolchain/make/c.mk
