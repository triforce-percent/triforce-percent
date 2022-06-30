
#.PRECIOUS: %.rgba32.inc %.rgb5a1.inc %.ia8.inc %.ci8.inc %.i4.inc %.ia4.inc

%.rgba32.inc: %.rgba32.png
	$(ZAPD) btex -tt rgba32 -i $< -o $@

%.rgba16.inc: %.rgba16.png
	$(ZAPD) btex -tt rgba16 -i $< -o $@

%.ia8.inc: %.ia8.png
	$(ZAPD) btex -tt ia8 -i $< -o $@

%.ci8.inc: %.ci8.png
	$(ZAPD) btex -tt ci8 -i $< -o $@

%.i4.inc: %.i4.png
	$(ZAPD) btex -tt i4 -i $< -o $@

%.ia4.inc: %.ia4.png
	$(ZAPD) btex -tt ia4 -i $< -o $@

texclean:
	rm -f *.rgba32.inc *.rgb5a1.inc *.ia8.inc *.ci8.inc *.i4.inc *.ia4.inc *.pat

%.pat: %
	$(CREATE_PATCH) --full $< $@

%.c: %.inc
	echo "#define NO_Z64HDR_GARBAGE 1\n#include \"ootmain.h\"\nconst u64 temp[] = {\n" > $@
	cat $< >> $@
	echo "};\n" >> $@

TEXLDCOMMAND := $(LD) $(LDFLAGS) -T $(PROJECT_DIR)/scene/scene.ld -o

%.rgba32.elf: %.rgba32.o
	$(TEXLDCOMMAND) $@ $<

%.rgba51.elf: %.rgba51.o
	$(TEXLDCOMMAND) $@ $<
	
%.ia8.elf: %.ia8.o
	$(TEXLDCOMMAND) $@ $<
	
%.ci8.elf: %.ci8.o
	$(TEXLDCOMMAND) $@ $<
	
%.i4.elf: %.i4.o
	$(TEXLDCOMMAND) $@ $<
	
%.ia4.elf: %.ia4.o
	$(TEXLDCOMMAND) $@ $<

%.rgba32: %.rgba32.bin
	cp $< $@

%.rgba51: %.rgba51.bin
	cp $< $@
	
%.ia8: %.ia8.bin
	cp $< $@
	
%.ci8: %.ci8.bin
	cp $< $@
	
%.i4: %.i4.bin
	cp $< $@
	
%.ia4: %.ia4.bin
	cp $< $@
