include ../../toolchain/make/main.mk

ACTORNAME = BotWLink
ACTORNUM = 118

OBJECTNAME = BotWLinkObj
OBJECTNUM = 122
OBJECTOBJS = \
	BotWLinkMesh.o \
	BotWLinkMeshIdleAnim.o \
	BotWLinkMeshLinksdialogAnim.o \
	BotWLinkMeshLookatitselfAnim.o \
	BotWLinkMeshLookstozeldaAnim.o \
	BotWLinkMeshModerate_walk_lookingaroundAnim.o \
	BotWLinkMeshModerate_walkAnim.o \
	BotWLinkMeshTakeszeldahandAnim.o \
	BotWLinkMeshTurnleftAnim.o \
	BotWLinkMeshTurnleftzeldadescendingAnim.o \
	BotWLinkMeshTurnrightAnim.o \
	BotWLinkMeshTurnrightfromspeechAnim.o \
	BotWLinkMeshWalkendAnim.o \
	BotWLinkMeshTex.o
OBJECTHDRS = \
	BotWLinkMesh.h \
	BotWLinkMeshIdleAnim.h \
	BotWLinkMeshLinksdialogAnim.h \
	BotWLinkMeshLookatitselfAnim.h \
	BotWLinkMeshLookstozeldaAnim.h \
	BotWLinkMeshModerate_walk_lookingaroundAnim.h \
	BotWLinkMeshModerate_walkAnim.h \
	BotWLinkMeshTakeszeldahandAnim.h \
	BotWLinkMeshTurnleftzeldadescendingAnim.h \
	BotWLinkMeshTurnrightAnim.h \
	BotWLinkMeshTurnrightfromspeechAnim.h \
	BotWLinkMeshWalkendAnim.h \
	BotWLinkMeshTex.h
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

default: copyactor copyobject

$(ACTORNAME).o: $(OBJECTHDRS) $(SHDRS)

$(ACTORNAME).elf: $(LDFILES)

BotWLinkMeshTex.o: $(TEXTURES)

ACTORLDFLAGS += $(addprefix -T , $(LDFILES))

include ../../toolchain/make/object.mk
include ../../toolchain/make/actor.mk

%.inc: tex/%.png
	$(ZAPD) btex -tt rgba16 -i $< -o $@

.PHONY: clean2

clean: clean2

clean2:
	rm -f *.inc
