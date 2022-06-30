include ../../toolchain/make/main.mk

SCENEDIR=../../build-romhack/scene/12
ROOM3ORIGMD5=06536420d24a0fba9795e78020f4f81c

.PHONY: default clean

default: room_3.zmap
	echo "${ROOM3ORIGMD5} ${SCENEDIR}/room_3.zmap.orig" | md5sum -c
	cp room_3.zmap ${SCENEDIR}/
	touch $(SCENEDIR)/../../update.txt

${SCENEDIR}/room_3.zmap.orig:
	cp ${SCENEDIR}/room_3.zmap ${SCENEDIR}/room_3.zmap.orig

room_3.zmap: ${SCENEDIR}/room_3.zmap.orig gerudoway_room_3.pat
	${PYTHON3} ../../toolchain/apply_patch.py ${SCENEDIR}/room_3.zmap.orig gerudoway_room_3.pat room_3.zmap

clean:
	rm -f *.zscene *.zmap
