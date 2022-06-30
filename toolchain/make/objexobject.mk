zobj.zobj $(OBJECTNAME).h $(OBJECTNAME).ld: $(OBJECTNAME).objex $(OBJEXSUBFILES)
	$(Z64CONVERT) --in $(OBJECTNAME).objex --out zobj.zobj $(OBJEXSETTINGS) --header $(OBJECTNAME).h --linker $(OBJECTNAME).ld

.PHONY: objexclean

clean: objexclean

objexclean:
	rm -f zobj.zobj $(OBJECTNAME).h $(OBJECTNAME).ld
