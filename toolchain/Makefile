include make/main.mk

SUBDIRS = \
z64audio/ \
ZAPD/ \
yaz0/

.PHONY: default clean $(SUBDIRS) z64convert/

default: $(SUBDIRS) z64convert/ $(NOVL)

clean: export C_INCLUDE_PATH := ../ExtLib
clean: yaz0/
	rm -f $(NOVL)
	$(MAKE) -C z64convert/ clean
	$(MAKE) -C z64audio/ clean

z64audio/: export C_INCLUDE_PATH := ../ExtLib

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

z64convert/:
	$(MAKE) -C $@ lincli
	
$(NOVL): novl/src/novl.c novl/src/novl-conv.c novl/src/novl-reloc.c
	gcc -o $@ -s -Os -DNOVL_DEBUG=1 -flto novl/src/*.c `pkg-config --cflags --libs libelf glib-2.0`
