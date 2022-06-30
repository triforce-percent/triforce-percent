
ACTORNAME ?= actor
ACTORDIR ?= ../../build-romhack/actor/$(ACTORNUM)

.PHONY: default clean

default: $(ACTORNAME).pat $(ACTORNAME).zovl
	echo "${ORIGMD5} ${ACTORDIR}/$(ACTORNAME).zovl.orig" | md5sum -c
	cp $(ACTORNAME).zovl ${ACTORDIR}/
	touch $(ACTORDIR)/../../update.txt

${ACTORDIR}/$(ACTORNAME).zovl.orig:
	cp ${ACTORDIR}/$(ACTORNAME).zovl ${ACTORDIR}/$(ACTORNAME).zovl.orig
	
$(ACTORNAME).zovl: ${ACTORDIR}/$(ACTORNAME).zovl.orig actorpatch.txt $(EXTRALDS)
	cp ${ACTORDIR}/$(ACTORNAME).zovl.orig $(ACTORNAME).zovl
	${PATCHINSTR} $(ACTORNAME).zovl actorpatch.txt $(EXTRALDS)

$(ACTORNAME).pat: $(ACTORNAME).zovl ${ACTORDIR}/$(ACTORNAME).zovl.orig
	${CREATE_PATCH} ${ACTORDIR}/$(ACTORNAME).zovl.orig $(ACTORNAME).zovl $(ACTORNAME).pat

clean:
	rm -f *.zovl *.pat
