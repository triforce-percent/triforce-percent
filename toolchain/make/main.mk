SELF_PATH := $(shell echo "$(MAKEFILE_LIST)" | sed -e "s/.*Makefile //")
PROJECT_DIR := $(dir $(SELF_PATH))../..

ifeq ("$(wildcard $(PROJECT_DIR)/local.mk)","")
    $(error You have not read README.md, please do so)
endif

ifeq ("$(and $(wildcard $(PROJECT_DIR)/build-shortcut/oot_1.0U_comp.z64), $(wildcard $(PROJECT_DIR)/build-romhack/oot_1.0U_uncomp.z64))","")
    $(error Original ROMs not found, please read README.md)
endif

ifeq ("$(wildcard $(PROJECT_DIR)/toolchain/ZAPD/Makefile)","")
    $(error ZAPD not found; try git submodule update --init --recursive)
endif
ifeq ("$(wildcard $(PROJECT_DIR)/toolchain/novl/src/main.c)","")
    $(error novl not found; try git submodule update --init --recursive)
endif
ifeq ("$(wildcard $(PROJECT_DIR)/include/z64hdr/z64hdr.h)","")
    $(error z64hdr not found; try git submodule update --init --recursive)
endif
ifeq ("$(wildcard $(PROJECT_DIR)/toolchain/AudiobankToC/audiobank.ld)","")
    $(error AudiobankToC not found; try git submodule update --init --recursive)
endif
ifeq ("$(wildcard $(PROJECT_DIR)/toolchain/z64audio/Makefile)","")
    $(error z64audio not found; try git submodule update --init --recursive)
endif
ifeq ("$(wildcard $(PROJECT_DIR)/toolchain/ExtLib/ExtLib.h)","")
    $(error ExtLib not found; try git submodule update --init --recursive)
endif
ifeq ("$(wildcard $(PROJECT_DIR)/toolchain/z64convert/wowlib/wow.h)","")
    $(error wowlib within z64convert not found; try git submodule update --init --recursive)
endif
ifeq ("$(wildcard $(PROJECT_DIR)/toolchain/ExtLib/zip/src/zip.h)","")
    $(error zip within ExtLib not found; try git submodule update --init --recursive)
endif

include $(PROJECT_DIR)/local.mk

ifeq ($(PYTHON3),"")
	$(error Python3 command definition missing from local.mk)
endif

# Disables built-in rules (e.g. how to make .o from .c)
.SUFFIXES:
#empty

# Paths

MAININCLUDEDIR := $(PROJECT_DIR)/include
Z64HDRMAINDIR := $(PROJECT_DIR)/include/z64hdr
Z64HDRINCLUDEDIR := $(PROJECT_DIR)/include/z64hdr/include
OOTMAINH := $(PROJECT_DIR)/include/ootmain.h
OOTMAINLD := $(PROJECT_DIR)/include/ootmain.ld
ACTORLD := $(PROJECT_DIR)/include/z64hdr/common/z64hdr_actor.ld
STATICDATADIR := $(PROJECT_DIR)/build-romhack/staticdata


# Main tools

CC = $(MIPS64PREFIX)gcc
AS = $(MIPS64PREFIX)as
LD = $(MIPS64PREFIX)ld
OC = $(MIPS64PREFIX)objcopy

# Main flags

CCOPTFLAGS := -mips3 -mabi=32 -mtune=vr4300 -mfix4300 -mno-gpopt -fomit-frame-pointer \
	-mno-check-zero-division -mno-explicit-relocs -mno-split-addresses -mno-memcpy \
	-fno-toplevel-reorder -fno-reorder-blocks -fno-builtin \
	--std=gnu99 -Wall -Werror -Wno-main \
	-Wbuiltin-declaration-mismatch -Wbuiltin-macro-redefined \
	-G 0 -Os
CCFLAGS := $(CCOPTFLAGS) -I $(MAININCLUDEDIR) -I $(Z64HDRMAINDIR) -I $(Z64HDRINCLUDEDIR)

LDFLAGS := --emit-relocs -L $(MAININCLUDEDIR) -T $(OOTMAINLD)
OCFLAGS := -R .MIPS.abiflags -O binary

# Other tools

NOVL := $(PROJECT_DIR)/toolchain/novl/novl
ZAPD := $(PROJECT_DIR)/toolchain/ZAPD/ZAPD.out
YAZ0 := $(PROJECT_DIR)/toolchain/yaz0/yaz0_encode
Z64CONVERT := $(PROJECT_DIR)/toolchain/z64convert/z64convert-cli
CREATE_PATCH := $(PYTHON3) $(PROJECT_DIR)/toolchain/create_patch.py
PATCHINSTR := $(PYTHON3) $(PROJECT_DIR)/toolchain/patchinstr.py
