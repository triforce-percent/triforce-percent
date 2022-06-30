SUBDIRS = romhack/ shortcut/

.PHONY: default clean $(SUBDIRS)

default clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
