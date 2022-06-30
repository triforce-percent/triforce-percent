include ../toolchain/make/main.mk

.PHONY: default clean

default: anim.bin anim.c
	mkdir -p                           $(STATICDATADIR)/0
	cp anim.bin                        $(STATICDATADIR)/0/staticdata.bin
	echo "dtype 0\ndata1 0\ndata2 0" > $(STATICDATADIR)/0/conf.txt

anim.bin anim.c: anim.txt ../toolchain/animcat.py linkcustomanim.objex
	$(PYTHON3) ../toolchain/animcat.py

clean:
	rm -f anim.bin anim.c
