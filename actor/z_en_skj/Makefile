include ../../toolchain/make/main.mk

ACTORNAME = z_en_skj
ACTORNUM = 277

default: copyactor

$(ACTORNAME).o: object_skj.h

$(ACTORNAME).elf: object_skj.ld

ACTORLDFLAGS += -T object_skj.ld

include ../../toolchain/make/actor.mk
