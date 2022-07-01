include ../../toolchain/make/main.mk

ACTORNAME = z_demo_holy
ACTORNUM = 122

OBJECTNAME = holy_light_gfx
OBJECTNUM = 126
OBJECTOBJS = holy_light_gfx.o
OBJECTHDRS = holy_light_gfx.h

default: copyactor
#copyobject

$(ACTORNAME).o: $(OBJECTHDRS)

$(ACTORNAME).elf: $(OBJECTNAME).out.ld

ACTORLDFLAGS += -T $(OBJECTNAME).out.ld

#include ../../toolchain/make/object.mk
include ../../toolchain/make/actor.mk
