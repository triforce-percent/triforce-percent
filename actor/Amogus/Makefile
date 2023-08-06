include ../../toolchain/make/main.mk

ACTORNAME = Amogus
ACTORNUM = 127

OBJECTNAME = AmogusObj
OBJECTNUM = 132
OBJECTOBJS = \
	AmogusObj.o \
	AmogusObjIdleAnim.o
OBJECTHDRS = \
	AmogusObj.h \
	AmogusObjIdleAnim.h
LDFILES = \
	$(OBJECTNAME).out.ld

CCFLAGS += -Wno-missing-braces

default: copyactor copyobject

$(ACTORNAME).o: $(OBJECTHDRS)

$(ACTORNAME).elf: $(LDFILES)

ACTORLDFLAGS += $(addprefix -T , $(LDFILES))

include ../../toolchain/make/object.mk
include ../../toolchain/make/actor.mk

clean: clean2

clean2:
	rm -f zobj.zobj
