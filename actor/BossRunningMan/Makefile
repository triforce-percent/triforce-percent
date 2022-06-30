include ../../toolchain/make/main.mk

ACTORNAME = BossRunningMan
ACTORNUM = 115

OBJECTNAME = BossRunningManObj
OBJECTNUM = 59
OBJEXSUBFILES = BossRunningManObj.anim BossRunningManObj.mtlex BossRunningManObj.skel
OBJEXSETTINGS = --address 0x06000000 --scale 10.0f

default: copyactor copyobject

$(ACTORNAME).o: BossRunningMan.h BossRunningManObj.h BossRunningManCutscenes.h BossRunningManCutscenes.c

$(ACTORNAME).elf: BossRunningManObj.ld

ACTORLDFLAGS += -T BossRunningManObj.ld

include ../../toolchain/make/actor.mk
include ../../toolchain/make/objexobject.mk
