include ../../toolchain/make/main.mk

INACTORDIR=../../build-romhack/actor/110
OUTACTORDIR=../../build-romhack/actor/23
ORIGMD5=7eb196da6a12aedea615c5071b803f54

.PHONY: default clean

default: actor.pat
	echo "${ORIGMD5} ${INACTORDIR}/actor.zovl" | md5sum -c
	$(PYTHON3) ../../toolchain/apply_patch.py ${INACTORDIR}/actor.zovl actor.pat actor.zovl
	cp actor.zovl ${OUTACTORDIR}/
	cp ${INACTORDIR}/conf.txt ${OUTACTORDIR}/conf.txt
	touch $(OUTACTORDIR)/../../update.txt

clean:
	rm -f *.zovl
