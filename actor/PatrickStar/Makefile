include ../../toolchain/make/main.mk

ACTORNAME = PatrickStar
ACTORNUM = 123

OBJECTNAME = PatrickStarObj
OBJECTNUM = 127
OBJECTOBJS = \
	PatrickStarObj.o \
	PatrickStarObjIdleAnim.o \
	PatrickStarObjHandupAnim.o
OBJECTHDRS = \
	PatrickStarObj.h \
	PatrickStarObjIdleAnim.h \
	PatrickStarObjHandupAnim.h
LDFILES = \
	$(OBJECTNAME).out.ld \

CCFLAGS += -Wno-missing-braces

default: copyactor copyobject

$(ACTORNAME).o: $(OBJECTHDRS)

$(ACTORNAME).elf: $(LDFILES)

ACTORLDFLAGS += $(addprefix -T , $(LDFILES))

include ../../toolchain/make/object.mk
include ../../toolchain/make/actor.mk
