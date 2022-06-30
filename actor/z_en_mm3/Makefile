include ../../toolchain/make/main.mk

ACTORNAME = z_en_mm3
ACTORNUM = 54

default: copyactor

$(ACTORNAME).o: object_mm.h

$(ACTORNAME).elf: object_mm.ld

ACTORLDFLAGS += -T object_mm.ld

include ../../toolchain/make/actor.mk
