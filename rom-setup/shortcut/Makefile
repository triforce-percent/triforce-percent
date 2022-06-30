.PHONY: default clean

BUILDDIR = ../../build-shortcut
ACTOR = ../../actor/z_en_wonder_item/hack_wonder_item.yaz0
ORIGROM = $(BUILDDIR)/oot_1.0U_comp.z64
OUTROM = $(BUILDDIR)/tf-shortcut.z64

default: $(OUTROM)
	
$(OUTROM): $(ACTOR)
	cp $(ORIGROM) $(OUTROM)
	dd if=/dev/zero of=$(OUTROM) conv=notrunc bs=1 seek=$$((0xC85010)) count=$$((0x8C0))
	dd if=$(ACTOR) of=$(OUTROM) conv=notrunc bs=1 seek=$$((0xC85010))

clean:
	find $(BUILDDIR) -mindepth 1 -maxdepth 1 ! -name 'oot_1.0U_comp.z64' -exec rm -rf {} +
