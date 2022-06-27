rzy: rzy.c
	$(CC) rzy.c -o rzy
install:
		@cp -p rzy $(DESTDIR)$(PREFIX)/bin/rzy
		@chmod 755 $(DESTDIR)$(PREFIX)/bin/rzy
uninstall:
		@rm -rf $(DESTDIR)$(PREFIX)/bin/rzy
