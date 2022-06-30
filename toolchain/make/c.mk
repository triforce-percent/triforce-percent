%.o: %.c $(OOTMAINH)
	$(CC) $(CCFLAGS) -c $< -o $@

%.out.ld: %.map
	$(PYTHON3) $(PROJECT_DIR)/toolchain/ldout.py $< $@

%.bin: %.elf
	$(OC) $(OCFLAGS) $< $@

%.zmap: %.elf
	$(OC) $(OCFLAGS) $< $@

%.zscene: %.elf
	$(OC) $(OCFLAGS) $< $@
	
%.abnk: %.elf
	$(OC) $(OCFLAGS) $< $@

.PHONY: cleandir cleansubdirs

cleandir:
	rm -f *.i *.o *.map *.elf *.bin
	
cleansubdirs:
	rm -f */*.i */*.o */*.elf */*.map */*.bin */*.zscene */*.zmap
