include ../toolchain/make/main.mk

MAKESUBDIRS = \
	gerudoway \
	shop1 \
	spot00 \
	spot04 \
	spot07_scene \
	spot08 \
	spot09 \
	spot10 \
	spot11 \
	spot13 \
	spot15 \
	spot16 \
	spot20 \
	tokinoma \
	ydan

#OUTFILES = \
	#UnicornFountain/UnicornFountain_scene.zscene \
	#UnicornFountain/UnicornFountain_room_0.zmap \
	#UnicornFountain/UnicornFountain_scene.out.ld \
	#ChamberOfSages/ChamberOfSages_scene.zscene \
	#ChamberOfSages/ChamberOfSages_room_0.zmap \
	#ChamberOfSages/ChamberOfSages_scene.out.ld \
	#TriforceRoom/TriforceRoom_scene.zscene \
	#TriforceRoom/TriforceRoom_room_0.zmap \
	#TriforceRoom/TriforceRoom_scene.out.ld \
	#Ending/Ending_scene.zscene \
	#Ending/Ending_room_0.zmap \
	#Ending/Ending_scene.out.ld
#TITLEFILES = \
	#UnicornFountain/title.ia8 \
	#ChamberOfSages/title.ia8
#UNICORNFOUNTAINDIR = ../build-romhack/scene/78
#CHAMBEROFSAGESDIR = ../build-romhack/scene/68
#TRIFORCEROOMDIR = ../build-romhack/scene/46
#ENDINGDIR = ../build-romhack/scene/58

CCFLAGS += -Wno-incompatible-pointer-types -Wno-missing-braces -DNO_Z64HDR_GARBAGE

.PHONY: default clean $(MAKESUBDIRS)

default:
	@echo "No scenes to build"

#default: $(OUTFILES) $(TITLEFILES)
#	cp UnicornFountain/UnicornFountain_scene.zscene $(UNICORNFOUNTAINDIR)/scene.zscene
#	cp UnicornFountain/UnicornFountain_room_0.zmap $(UNICORNFOUNTAINDIR)/room_0.zmap
#	cp UnicornFountain/title.ia8.png $(UNICORNFOUNTAINDIR)/title.png
#	cp UnicornFountain/conf.txt $(UNICORNFOUNTAINDIR)/conf.txt
#	cp ChamberOfSages/ChamberOfSages_scene.zscene $(CHAMBEROFSAGESDIR)/scene.zscene
#	cp ChamberOfSages/ChamberOfSages_room_0.zmap $(CHAMBEROFSAGESDIR)/room_0.zmap
#	cp ChamberOfSages/title.ia8.png $(CHAMBEROFSAGESDIR)/title.png
#	cp ChamberOfSages/conf.txt $(CHAMBEROFSAGESDIR)/conf.txt
#	cp TriforceRoom/TriforceRoom_scene.zscene $(TRIFORCEROOMDIR)/scene.zscene
#	cp TriforceRoom/TriforceRoom_room_0.zmap $(TRIFORCEROOMDIR)/room_0.zmap
#	cp TriforceRoom/conf.txt $(TRIFORCEROOMDIR)/conf.txt
#	cp Ending/Ending_scene.zscene $(ENDINGDIR)/scene.zscene
#	cp Ending/Ending_room_0.zmap $(ENDINGDIR)/room_0.zmap

default clean: $(MAKESUBDIRS)

$(MAKESUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

%_room_0.elf: %_room_0.o room.ld
	$(LD) $(LDFLAGS) -T room.ld -o $@ $<

%_scene.elf %_scene.map: %_scene.o scene.ld
	$(LD) $(LDFLAGS) -T scene.ld -Map $*_scene.map -o $*_scene.elf $<

clean: cleansubdirs
	rm -f */title.ia8

include ../toolchain/make/textures.mk
include ../toolchain/make/c.mk
