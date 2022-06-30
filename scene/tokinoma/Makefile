include ../../toolchain/make/main.mk

SCENEDIR=../../build-romhack/scene/67
ROOM0ORIGMD5=b4ebf18440b266bebae77b5cab1bbddc

.PHONY: default clean

.PRECIOUS: ${SCENEDIR}/room_0.zmap.orig

default: room_0.zmap
	echo "${ROOM0ORIGMD5} ${SCENEDIR}/room_0.zmap.orig" | md5sum -c
	cp room_0.zmap ${SCENEDIR}/
	touch $(SCENEDIR)/../../update.txt

${SCENEDIR}/room_%.zmap.orig:
	cp ${SCENEDIR}/room_$*.zmap ${SCENEDIR}/room_$*.zmap.orig

room_%.zmap: ${SCENEDIR}/room_%.zmap.orig tokinoma_room_%.pat
	${PYTHON3} ../../toolchain/apply_patch.py ${SCENEDIR}/room_$*.zmap.orig tokinoma_room_$*.pat room_$*.zmap

clean:
	rm -f *.zscene *.zmap
