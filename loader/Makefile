include ../toolchain/make/main.mk

.PHONY: default clean

default: fast_loader/fast_loader.bin debugger/debugger.bin dma_patcher/dma_patcher.map dma_patcher/dma_patcher.bin

#Dependencies

debugger/debugger.o: fast_loader/fast_loader.h

debugger/debugger.elf: fast_loader/fast_loader.out.ld

dma_patcher/dma_patcher.o: debugger/debugger.h

dma_patcher/dma_patcher.elf: debugger/debugger.out.ld

%.elf %.map: %.o %.ld $(OOTMAINLD)
	$(LD) $(LDFLAGS) -T $*.ld -Map $*.map -o $*.elf $*.o 

clean: cleansubdirs

include ../toolchain/make/c.mk
