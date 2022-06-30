include ../../toolchain/make/main.mk

ACTORNAME = betakokiri
ACTORNUM = 49

default: copyactor

$(ACTORNAME).o: object_oE_anime.h object_oE4.h object_oE9.h

$(ACTORNAME).elf: object_oE_anime.ld object_oE4.ld object_oE9.ld

ACTORLDFLAGS += -T object_oE_anime.ld -T object_oE4.ld -T object_oE9.ld

include ../../toolchain/make/actor.mk
