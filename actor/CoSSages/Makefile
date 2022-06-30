include ../../toolchain/make/main.mk

ACTORNAME = cossages
ACTORNUM = 31

default: copyactor

$(ACTORNAME).o: sages_objs.h

$(ACTORNAME).elf: sages_objs.ld

ACTORLDFLAGS += -T sages_objs.ld

include ../../toolchain/make/actor.mk
