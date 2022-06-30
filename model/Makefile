SUBDIRS = \
	object_gi_butterfly/ \
	SagesCharm/

.PHONY: default clean $(SUBDIRS)

default clean: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
