include ../toolchain/make/main.mk

.PHONY: default clean

TARGETS=\
	OvertureOfSages.aseq \
	OvertureOfSagesWarp.aseq \
	ChamberOfSages.aseq \
	ChamberOfSagesBank.abnk \
	triforce.aseq \
	PowerOfTheGoddesses.aseq \
	HereTogether1.aseq \
	HereTogether2.aseq \
	HereTogether3.aseq \
	HereTogetherBank.abnk


define procaudio
	mkdir -p $(STATICDATADIR)/$(1)
	cp $(5) $(STATICDATADIR)/$(1)/staticdata.bin
	echo "dtype $(2)\ndata1 0x$(3)020201\ndata2 0x$(4)0000" > $(STATICDATADIR)/$(1)/conf.txt
endef

	
default: $(TARGETS)
	$(call procaudio,6,1,6E,0900,OvertureOfSages.aseq)
	$(call procaudio,7,1,33,0900,OvertureOfSagesWarp.aseq)
	$(call procaudio,8,1,70,2600,ChamberOfSages.aseq)
	$(call procaudio,9,2,26,0B00,ChamberOfSagesBank.abnk)
	$(call procaudio,10,1,71,0300,triforce.aseq)
	$(call procaudio,11,1,72,0300,PowerOfTheGoddesses.aseq)
	$(call procaudio,12,1,73,2700,HereTogether1.aseq)
	$(call procaudio,13,1,74,2700,HereTogether2.aseq)
	$(call procaudio,14,1,75,2700,HereTogether3.aseq)
	$(call procaudio,15,2,27,1040,HereTogetherBank.abnk)
	$(call procaudio,16,1,76,0300,StaffRoll.aseq)
	$(call procaudio,17,1,77,0300,Trailer.aseq)

# %.pat: %.aseq
# 	$(CREATE_PATCH) --full $< $@

CCFLAGS := $(CCOPTFLAGS) -I ../toolchain/AudiobankToC/include
LDFLAGS += -T ../toolchain/AudiobankToC/audiobank.ld

%.elf: %.o
	$(LD) $(LDFLAGS) -o $@ $<

clean: cleandir
	rm -f *.pat *.abnk
	
include ../toolchain/make/c.mk
