include ../../toolchain/make/main.mk

# Must escape spaces ugh
ACTORDIR=../../build-romhack/actor/394
FUNCNAME=OceffWipe_Update
FUNCOFFSET=168
ORIGMD5=c09e59cc2653411f695ad73c54b925cf

.PHONY: default clean

default: actor.pat actor.zovl
	echo "${ORIGMD5} ${ACTORDIR}/actor.zovl.orig" | md5sum -c
	cp actor.zovl ${ACTORDIR}/
	touch $(ACTORDIR)/../../update.txt

%.o: %.s
	${AS} -Os -o $@ $<

%.elf: %.o z_oceff_wipe.ld ../../statics/statics.out.ld
	${LD} -T z_oceff_wipe.ld -o $@ $<

%.bin: %.elf
	${OC} -O binary -j .text -j .data $< $@

${ACTORDIR}/actor.zovl.orig:
	cp ${ACTORDIR}/actor.zovl ${ACTORDIR}/actor.zovl.orig
	
actor.zovl: ${ACTORDIR}/actor.zovl.orig ${FUNCNAME}.bin
	cp ${ACTORDIR}/actor.zovl.orig actor.zovl
	dd conv=notrunc if=${FUNCNAME}.bin of=actor.zovl bs=1 seek=${FUNCOFFSET}

actor.pat: actor.zovl ${ACTORDIR}/actor.zovl.orig
	${CREATE_PATCH} ${ACTORDIR}/actor.zovl.orig actor.zovl actor.pat

clean:
	rm -f *.o *.bin *.zovl *.pat
