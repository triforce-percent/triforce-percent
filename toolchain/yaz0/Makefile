.PHONY: default clean

default: yaz_encode
	
yaz_encode: yaz.c stretchy_buffer.h
	gcc -Wall -DYAZ_MAIN_TEST=1 yaz.c -o yaz0_encode

clean:
	rm -f yaz_encode
