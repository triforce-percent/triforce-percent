include ../toolchain/make/main.mk
include ../toolchain/make/assembly.mk

RUNS = rta shortcut
OUTPUTS_M64 = $(patsubst %,../run/bootstrap%.m64,$(RUNS))
OUTPUTS_INPUTLOG = $(patsubst %,../run/bootstrap%-inputlog.txt,$(RUNS))
BOOTSTRAPPER_BINS = $(patsubst %,bootstrapper2%.bin,$(RUNS))
FAST_LOADER = ../loader/fast_loader/fast_loader.bin

.PHONY: default clean

.PRECIOUS: $(BOOTSTRAPPER_BINS)

default: $(OUTPUTS_M64) $(OUTPUTS_INPUTLOG)

../run/bootstrap%.m64: bootstrapper2%.bin bootstrapper4.bin $(FAST_LOADER)
	$(PYTHON3) ../toolchain/tas/ootbootstrap.py $* $^ $@

../run/%-inputlog.txt: ../run/%.m64
	$(PYTHON3) ../toolchain/tas/m642bk2.py $< $@

clean:
	rm -f *.o *.bin ../run/*.m64 ../run/*-inputlog.txt
