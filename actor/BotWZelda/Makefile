include ../../toolchain/make/main.mk

ACTORNAME = BotWZelda
ACTORNUM = 121

OBJECTNAME = BotWZeldaObj
OBJECTNUM = 125
OBJECTOBJS = \
	BotWZeldaMesh.o \
	BotWZeldaMeshDescendidleAnim.o \
	BotWZeldaMeshHoldinghandsAnim.o \
	BotWZeldaMeshIknowtheyreoutthereAnim.o \
	BotWZeldaMeshLinkitseemsyouveAnim.o \
	BotWZeldaMeshLookpointAnim.o \
	BotWZeldaMeshNormalidleAnim.o \
	BotWZeldaMeshRotatedidleAnim.o \
	BotWZeldaMeshThankyoulinkAnim.o \
	BotWZeldaMeshTurnrightAnim.o \
	BotWZeldaMeshWakeupAnim.o \
	BotWZeldaMeshYouaskedAnim.o \
	BotWZeldaMeshTex.o
OBJECTHDRS = \
	BotWZeldaMesh.h \
	BotWZeldaMeshDescendidleAnim.h \
	BotWZeldaMeshHoldinghandsAnim.h \
	BotWZeldaMeshIknowtheyreoutthereAnim.h \
	BotWZeldaMeshLinkitseemsyouveAnim.h \
	BotWZeldaMeshLookpointAnim.h \
	BotWZeldaMeshNormalidleAnim.h \
	BotWZeldaMeshRotatedidleAnim.h \
	BotWZeldaMeshThankyoulinkAnim.h \
	BotWZeldaMeshTurnrightAnim.h \
	BotWZeldaMeshWakeupAnim.h \
	BotWZeldaMeshYouaskedAnim.h \
	BotWZeldaMeshTex.h
SHDRS = \
	../BotWActors.h \
	../../loader/debugger/debugger.h \
	../../statics/hairphys.h \
	../../statics/statics.h \
	../../statics/anime.h
LDFILES = \
	$(OBJECTNAME).out.ld \
	../../loader/debugger/debugger.out.ld \
	../../statics/statics.out.ld
TEXTURES = \
	eye0.inc \
	eye1.inc \
	eye2.inc

default: copyactor
#copyobject

$(ACTORNAME).o: $(OBJECTHDRS) $(SHDRS)

$(ACTORNAME).elf: $(LDFILES)

BotWZeldaMeshTex.o: $(TEXTURES)

ACTORLDFLAGS += $(addprefix -T , $(LDFILES))

#include ../../toolchain/make/object.mk
include ../../toolchain/make/actor.mk

%.inc: tex-lores/%.png
	$(ZAPD) btex -tt rgba16 -i $< -o $@

.PHONY: clean2

clean: clean2

clean2:
	rm -f *.inc
