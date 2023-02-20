include ../../toolchain/make/main.mk

ACTORNAME = z_en_ge1
ACTORNUM = 312

default: copyactor

$(ACTORNAME).o: object_ge1.h

$(ACTORNAME).elf: object_ge1.ld

ACTORLDFLAGS += -T object_ge1.ld

include ../../toolchain/make/actor.mk
