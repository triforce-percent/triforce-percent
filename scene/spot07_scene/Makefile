include ../../toolchain/make/main.mk

SCENEDIR=../../build-romhack/scene/88
SCENEORIGMD5=6f0fe11356db88532393c6b35ccd8be5
ROOM1ORIGMD5=77a71b992f9ff192ac4f99ec3a6063ff

.PHONY: default clean

default: scene.zscene room_1.zmap
	echo "${SCENEORIGMD5} ${SCENEDIR}/scene.zscene.orig" | md5sum -c
	echo "${ROOM1ORIGMD5} ${SCENEDIR}/room_1.zmap.orig" | md5sum -c
	cp scene.zscene room_1.zmap ${SCENEDIR}/
	touch $(SCENEDIR)/../../update.txt

${SCENEDIR}/scene.zscene.orig:
	cp ${SCENEDIR}/scene.zscene ${SCENEDIR}/scene.zscene.orig
	
${SCENEDIR}/room_1.zmap.orig:
	cp ${SCENEDIR}/room_1.zmap ${SCENEDIR}/room_1.zmap.orig

scene.zscene: ${SCENEDIR}/scene.zscene.orig zoras_scene.pat
	${PYTHON3} ../../toolchain/apply_patch.py ${SCENEDIR}/scene.zscene.orig zoras_scene.pat scene.zscene

room_1.zmap: ${SCENEDIR}/room_1.zmap.orig zoras_room1.pat
	${PYTHON3} ../../toolchain/apply_patch.py ${SCENEDIR}/room_1.zmap.orig zoras_room1.pat room_1.zmap

clean:
	rm -f *.zscene *.zmap
