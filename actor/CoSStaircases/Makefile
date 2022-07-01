include ../../toolchain/make/main.mk

ACTORNAME = cosstaircases
ACTORNUM = 26

OBJECTNAME = cosstaircasesobj
OBJECTNUM = 17
OBJECTOBJS = \
	RauruStair.o \
	RauruStairCollision.o \
	SariaStair.o \
	SariaStairCollision.o \
	SheikStair.o \
	SheikStairCollision.o \
	TriforceFadeWall.o \
	TriforceHallway.o \
	TriforceDoor.o
OBJECTHDRS = \
	RauruStair.h \
	RauruStairCollision.h \
	SariaStair.h \
	SariaStairCollision.h \
	SheikStair.h \
	SheikStairCollision.h \
	TriforceFadeWall.h \
	TriforceHallway.h \
	TriforceDoor.h

SCENEOUTLD = ../../scene/ChamberOfSages/ChamberOfSages_scene.out.ld

default: copyactor
#copyobject

$(ACTORNAME).o: $(OBJECTHDRS)

$(ACTORNAME).elf: $(OBJECTNAME).out.ld $(SCENEOUTLD)

ACTORLDFLAGS += -T $(OBJECTNAME).out.ld -T $(SCENEOUTLD)

#include ../../toolchain/make/object.mk
include ../../toolchain/make/actor.mk

