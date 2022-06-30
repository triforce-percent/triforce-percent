include ../../toolchain/make/main.mk

ACTORNAME = SilentPrincess
ACTORNUM = 120

OBJECTNAME = SilentPrincessObj
OBJECTNUM = 123
OBJECTOBJS = SilentPrincessMesh.o

default: copyactor copyobject

$(ACTORNAME).o: SilentPrincessMesh.h ../../statics/statics.h

$(ACTORNAME).elf: $(OBJECTNAME).out.ld ../../statics/statics.out.ld

ACTORLDFLAGS += -T $(OBJECTNAME).out.ld -T ../../statics/statics.out.ld

include ../../toolchain/make/object.mk
include ../../toolchain/make/actor.mk
