INSTALLDIR =/usr
DEBIAN_VERSION_FILE =/etc/debian_version

LBITS := $(shell uname -m)

#64-Bit System?
ifeq ($(LBITS),x86_64)
	INSTALLDIRLIB =$(INSTALLDIR)/lib64
else
	#32-Bit System?
 	INSTALLDIRLIB =$(INSTALLDIR)/lib
endif

#check for ubuntu/debian
ifeq ($(shell ls $(DEBIAN_VERSION_FILE)),$(DEBIAN_VERSION_FILE))
  	#ubuntu and debian does not privide different pathes
 	INSTALLDIRLIB =$(INSTALLDIR)/lib
endif 

INSTALLDIRINC =$(INSTALLDIR)/include/dk16xx
ETC =/etc
LD = ld
CC =g++
AR =ar

LIB =libdk16xx_servusr.so
LIBA =libdk16xx_servusr.a
LIBOBJ = lnk/serv.lo \
	 ../pniolib/tracelib/lnk/tracelib.lo

all:
	make -C csd
	make -C ../pniolib/tracelib/csd
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
	cp -p inc/servusrx.h $(DESTDIR)$(INSTALLDIRINC)/
	cp -p ../pniolib/iobase/inc/pniobase.h $(DESTDIR)$(INSTALLDIRINC)/
	cp -p ../pniolib/iobase/inc/pnioerrx.h $(DESTDIR)$(INSTALLDIRINC)/
	cp -p ../pniolib/tracelib/inc/servtrace.conf $(DESTDIR)$(ETC)/

deinstall:
	rm -f $(DESTDIR)$(INSTALLDIRLIB)/$(LIB) \
	      $(DESTDIR)$(INSTALLDIRLIB)/$(LIBA)
	rm -f $(DESTDIR)$(INSTALLDIRINC)/servusrx.h

lint:
	make -C csd lint
	make -C ../pniolib/tracelib/csd lint
