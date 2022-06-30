include ../../toolchain/make/main.mk

ACTORNAME = nabooru
ACTORNUM = 34

CCFLAGS += -Wno-missing-braces

default: copyactor

$(ACTORNAME).o: object_nb.h ../../statics/statics.h NbXtraAnimPullingoutshehnaiAnim.c NbXtraAnimHoldingshehnaiAnim.c NbXtraAnimPlayingshehnaiAnim.c ShehnaiDL.c gerudoway_cs.c 

$(ACTORNAME).elf: object_nb.ld ../../statics/statics.out.ld

ACTORLDFLAGS += -T object_nb.ld -T ../../statics/statics.out.ld

include ../../toolchain/make/actor.mk
