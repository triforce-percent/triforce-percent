include ../../toolchain/make/main.mk

SCENEDIR=../../build-romhack/scene/44
ROOM0ORIGMD5=05720407b5fc24c343926d8b6446862b

.PHONY: default clean

default: room_0.zmap
	echo "${ROOM0ORIGMD5} ${SCENEDIR}/room_0.zmap.orig" | md5sum -c
	cp room_0.zmap ${SCENEDIR}/
	touch $(SCENEDIR)/../../update.txt

${SCENEDIR}/room_0.zmap.orig:
	cp ${SCENEDIR}/room_0.zmap ${SCENEDIR}/room_0.zmap.orig

room_0.zmap: ${SCENEDIR}/room_0.zmap.orig shop1_room_0.pat
	${PYTHON3} ../../toolchain/apply_patch.py ${SCENEDIR}/room_0.zmap.orig shop1_room_0.pat room_0.zmap

clean:
	rm -f *.zscene *.zmap
