include ../../toolchain/make/main.mk

SCENEDIR=../../build-romhack/scene/91
ROOM5ORIGMD5=7da61b9df96e1349cb92d5ba2b19fef0
ROOM7ORIGMD5=68dda44b12e80be04f79b0f243a495ef

.PHONY: default clean

.PRECIOUS: ${SCENEDIR}/room_7.zmap.orig ${SCENEDIR}/room_5.zmap.orig

default: room_7.zmap room_5.zmap
	echo "${ROOM7ORIGMD5} ${SCENEDIR}/room_7.zmap.orig" | md5sum -c
	echo "${ROOM5ORIGMD5} ${SCENEDIR}/room_5.zmap.orig" | md5sum -c
	cp room_7.zmap room_5.zmap ${SCENEDIR}/
	touch $(SCENEDIR)/../../update.txt

${SCENEDIR}/room_%.zmap.orig:
	cp ${SCENEDIR}/room_$*.zmap ${SCENEDIR}/room_$*.zmap.orig

room_%.zmap: ${SCENEDIR}/room_%.zmap.orig spot10_room_%.pat
	${PYTHON3} ../../toolchain/apply_patch.py ${SCENEDIR}/room_$*.zmap.orig spot10_room_$*.pat room_$*.zmap

clean:
	rm -f *.zscene *.zmap
