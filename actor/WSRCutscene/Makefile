include ../../toolchain/make/main.mk

ACTORNAME = wsrcutscene
ACTORNUM = 83

default: copyactor

$(ACTORNAME).o: tokinoma_cs.c tokinoma_cs.h ../../statics/statics.h

$(ACTORNAME).elf: ../../statics/statics.out.ld

ACTORLDFLAGS += -T ../../statics/statics.out.ld

include ../../toolchain/make/actor.mk
