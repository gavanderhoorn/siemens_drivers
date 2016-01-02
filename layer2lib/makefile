INSTALLDIR =/usr
INSTALLDIRLIB =$(INSTALLDIR)/lib
INSTALLDIRINC =$(INSTALLDIR)/include/dk16xx
ETC =/etc
LD = ld
CC =g++
AR =ar

LIB =libdk16xx_l2interface.so
LIBA =libdk16xx_l2interface.a
LIBOBJ = lnk/l2interface.lo \
	 ../pniolib/tracelib/lnk/tracelib.lo \
	 ../servlib/lnk/serv.lo

all:
	make -C csd
	make -C ../pniolib/tracelib/csd
	make -C ../servlib/csd
	$(AR) rc $(LIBA) $(LIBOBJ)
	$(CC) -shared -o $(LIB) $(LIBOBJ) -lpthread -lrt

clean:
	make -C csd clean
	make -C ../pniolib/tracelib/csd clean
	rm -f $(LIB) $(LIBA)

install: all
	install -d $(DESTDIR)$(INSTALLDIRLIB)
	install -d $(DESTDIR)$(INSTALLDIRINC)
	install -d $(DESTDIR)$(ETC)
	cp -p $(LIB) $(DESTDIR)$(INSTALLDIRLIB)/
	cp -p $(LIBA) $(DESTDIR)$(INSTALLDIRLIB)/
	cp -p inc/l2eth_defs.h $(DESTDIR)$(INSTALLDIRINC)/
	cp -p inc/l2eth_user.h $(DESTDIR)$(INSTALLDIRINC)/
	cp -p inc/l2eth_errs.h $(DESTDIR)$(INSTALLDIRINC)/
	cp -p inc/l2eth_config.h $(DESTDIR)$(INSTALLDIRINC)/
	cp -p inc/l2eth_trace.conf $(DESTDIR)$(ETC)/

deinstall:
	rm -f $(DESTDIR)$(INSTALLDIRLIB)/$(LIB) \
	      $(DESTDIR)$(INSTALLDIRLIB)/$(LIBA)
	rm -f $(DESTDIR)$(INSTALLDIRINC)/l2eth_defs.h
	rm -f $(DESTDIR)$(INSTALLDIRINC)/l2eth_user.h
	rm -f $(DESTDIR)$(INSTALLDIRINC)/l2eth_errs.h
	rm -f $(DESTDIR)$(INSTALLDIRINC)/l2eth_config.h
	rm -f $(DESTDIR)$(ETC)/l2eth_trace.conf

lint:
	make -C csd lint
	make -C ../pniolib/tracelib/csd lint

