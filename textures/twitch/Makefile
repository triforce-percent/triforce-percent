include ../../toolchain/make/main.mk

default: icons.inc

icons.inc: icons.json icons.py $(PROJECT_DIR)/toolchain/ci4tool/ci4tool.py
	PYTHONPATH="$(PROJECT_DIR)/toolchain/ci4tool" $(PYTHON3) icons.py

clean:
	rm -f icons.inc
