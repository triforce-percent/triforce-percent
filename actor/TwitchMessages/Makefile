include ../../toolchain/make/main.mk

ACTORNAME = TwitchMessages
ACTORNUM = 116

CCFLAGS += -Wno-missing-braces -Wno-array-bounds

INCFILES = \
	../../textures/username_font.i4.inc \
	../../textures/tw_msg_case0.i4.inc \
	../../textures/tw_msg_case1.i4.inc \
	../../textures/tw_msg_case2.i4.inc \
	../../textures/tw_msg_case3.i4.inc \
	../../textures/tw_msg_exclam.i4.inc \
	../../textures/twitch/icons.inc

default: copyactor

$(ACTORNAME).o: ../../loader/fast_loader/fast_loader.h ../../loader/debugger/debugger.h ../../statics/statics.h $(INCFILES)

$(ACTORNAME).elf: ../../loader/fast_loader/fast_loader.out.ld ../../loader/debugger/debugger.out.ld ../../statics/statics.out.ld

ACTORLDFLAGS += -T ../../loader/fast_loader/fast_loader.out.ld -T ../../loader/debugger/debugger.out.ld -T ../../statics/statics.out.ld

include ../../toolchain/make/actor.mk
