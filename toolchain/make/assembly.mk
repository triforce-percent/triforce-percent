
%.o: %.s
	$(AS) -Os -o $@ $<

%.bin: %.o
	$(OC) -O binary -j .text -j .data $< $@
