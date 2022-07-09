.PHONY: default clean

BUILDDIR = ../../build-shortcut
ACTORBASE = ../../actor/z_en_wonder_item/hack_wonder_item
ACTORZOVL = $(ACTORBASE).zovl
ACTORYAZ0 = $(ACTORBASE).yaz0
ORIGROM = $(BUILDDIR)/oot_1.0U_comp.z64
OUTROM = $(BUILDDIR)/tf-shortcut.z64

default: $(OUTROM)

# Check that the uncompressed actor size matches the original actor and that the beginning
# of the actor struct is in the right place.
# Also the dd clear count is clearing the compressed data, which is why it's shorter than the actor.

$(OUTROM): $(ACTORYAZ0)
	@dd if=$(ACTORZOVL) of=temp.dat bs=1 skip=$$((0xA9C)) count=4
	@if [ $$(wc -c < $(ACTORZOVL)) != "3152" ] || [ $$(hexdump -ve '1/1 "%.2x"' temp.dat) != "01120600" ] ; then echo; echo; echo "hack_wonder_item does not match original Wonder Item address / len (possible compiler change); adjust padding sizes in hack_wonder_item.c"; echo; echo; false; fi
	@rm -f temp.dat
	cp $(ORIGROM) $(OUTROM)
	dd if=/dev/zero of=$(OUTROM) conv=notrunc bs=1 seek=$$((0xC85010)) count=$$((0x8C0))
	dd if=$(ACTORYAZ0) of=$(OUTROM) conv=notrunc bs=1 seek=$$((0xC85010))

clean:
	find $(BUILDDIR) -mindepth 1 -maxdepth 1 ! -name 'oot_1.0U_comp.z64' -exec rm -rf {} +
