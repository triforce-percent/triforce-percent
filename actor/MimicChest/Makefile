include ../../toolchain/make/main.mk

ACTORNAME = MimicChest
ACTORNUM = 126

OBJECTNAME = MimicChestObj
OBJECTNUM = 131
OBJECTOBJS = \
	MimicChestObj.o \
	MimicChestObjIdleAnim.o \
	MimicChestObjAttackAnim.o
OBJECTHDRS = \
	MimicChestObj.h \
	MimicChestObjIdleAnim.h \
	MimicChestObjAttackAnim.h
LDFILES = \
	$(OBJECTNAME).out.ld \

CCFLAGS += -Wno-missing-braces

default: copyactor copyobject

$(ACTORNAME).o: $(OBJECTHDRS)

$(ACTORNAME).elf: $(LDFILES)

ACTORLDFLAGS += $(addprefix -T , $(LDFILES))

include ../../toolchain/make/object.mk
include ../../toolchain/make/actor.mk
