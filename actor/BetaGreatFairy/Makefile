include ../../toolchain/make/main.mk

ACTORNAME = betagreatfairy
ACTORNUM = 6
LDFLAGS += -T ../../scene/UnicornFountain/UnicornFountain_scene.out.ld

default: copyactor

$(ACTORNAME).o: ../../statics/statics.h

$(ACTORNAME).elf: ../../statics/statics.out.ld

ACTORLDFLAGS += -T ../../statics/statics.out.ld

include ../../toolchain/make/actor.mk
