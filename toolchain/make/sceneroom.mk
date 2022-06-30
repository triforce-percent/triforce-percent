ORIG_TARGETS=${patsubst %,${SCENEDIR}/%.orig,${TARGETS}}
PATCH_FILES=${patsubst %.zmap,%.pat,${patsubst %.zscene,%.pat,${TARGETS}}}

.PHONY: default clean clean2

.PRECIOUS: ${ORIG_TARGETS}

default: ${TARGETS} ${PATCH_FILES} check_md5s
	cp ${TARGETS} ${SCENEDIR}/
	touch $(SCENEDIR)/../../update.txt

check_md5s: md5s.txt ${ORIG_TARGETS}
	cp md5s.txt ${SCENEDIR}
	cd ${SCENEDIR} && md5sum -c md5s.txt
	rm ${SCENEDIR}/md5s.txt

${SCENEDIR}/%.orig:
	cp ${SCENEDIR}/$* ${SCENEDIR}/$*.orig

room_%.zmap: ${SCENEDIR}/room_%.zmap.orig room%_patch.txt
	cp ${SCENEDIR}/room_$*.zmap.orig $@
	${PATCHINSTR} $@ room$*_patch.txt

scene.zscene: ${SCENEDIR}/scene.zscene.orig scene_patch.txt ${SCENEPATCHDEPS}
	cp ${SCENEDIR}/scene.zscene.orig $@
	${PATCHINSTR} $@ scene_patch.txt

room_%.pat: room_%.zmap
	${CREATE_PATCH} ${SCENEDIR}/room_$*.zmap.orig $< $@

scene.pat: scene.zscene
	${CREATE_PATCH} ${SCENEDIR}/scene.zscene.orig $< $@

%.elf: %.o ${PROJECT_DIR}/scene/room.ld
	$(LD) $(LDFLAGS) -T ${PROJECT_DIR}/scene/room.ld -o $@ $<

clean: clean2 cleandir

clean2:
	rm -f *.zscene *.zmap *.pat

include ../../toolchain/make/c.mk
