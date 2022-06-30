include ../../toolchain/make/main.mk

ACTORDIR=../../build-romhack/actor/4
ACTORORIGMD5=fd26ae9c55818d68b91dd5c63215a08d

.PHONY: default clean

default: actor.zovl
	echo "${ACTORORIGMD5} ${ACTORDIR}/actor.zovl.orig" | md5sum -c
	cp actor.zovl ${ACTORDIR}/
	touch $(ACTORDIR)/../../update.txt

${ACTORDIR}/actor.zovl.orig:
	cp ${ACTORDIR}/actor.zovl ${ACTORDIR}/actor.zovl.orig

actor.zovl: ${ACTORDIR}/actor.zovl.orig actor.pat
	${PYTHON3} ../../toolchain/apply_patch.py ${ACTORDIR}/actor.zovl.orig actor.pat actor.zovl

clean:
	rm -f *.zovl
