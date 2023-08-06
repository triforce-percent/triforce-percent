include ../../toolchain/make/main.mk

ifneq ("$(MEMES)","")
BETAKOKIRIREPLACEMENT = room7_patch_memes.txt
else
BETAKOKIRIREPLACEMENT = room7_patch_betakokiri.txt
endif

SCENEDIR=../../build-romhack/scene/91
TARGETS=room_5.zmap room_7.zmap

include ../../toolchain/make/sceneroom.mk

room7_patch.txt:
	cp $(BETAKOKIRIREPLACEMENT) $@

clean:
	rm -f room7_patch.txt
