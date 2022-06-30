include ../../toolchain/make/main.mk

CCFLAGS += -Wno-incompatible-pointer-types -Wno-missing-braces -DNO_Z64HDR_GARBAGE

OBJECTNUM = 120

ZZRTLDIR = ../../build-romhack
OBJECTDIR = $(ZZRTLDIR)/object/$(OBJECTNUM)
UPDATETXT = $(ZZRTLDIR)/update.txt

.PHONY: default clean

default: object_gi_sagescharm.bin object_gi_sagescharm.out.ld
	cp object_gi_sagescharm.bin $(OBJECTDIR)/zobj.zobj
	touch $(UPDATETXT)

%.elf %.map: %.o
	$(LD) $(LDFLAGS) -T ../model.ld -o $*.elf -Map $*.map $*.o

clean: cleandir

include ../../toolchain/make/c.mk
