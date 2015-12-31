# Comment/uncomment the following line to disable/enable debugging
DEBUG = y

TOPDIR = $(shell pwd)
SRCDIR = $(TOPDIR)
INCDIR = $(TOPDIR)
BINDIR = $(TOPDIR)

# Add your debugging flag (or not) to CFLAGS
ifeq ($(DEBUG),y)
# Options for development - debug
  CFLAGS = -g -Wall
else
# Options for release
  CFLAGS = -O -Wall
endif

SRC2 = $(SRCDIR)/dev_easy_cert.c

EXE1 = $(BINDIR)/easy_dev_cert_19

EXE2 = $(BINDIR)/easy_dev_cert_1B

EXE3 = $(BINDIR)/easy_dev_cert_821

EXE4 = $(BINDIR)/easy_dev_cert_822

all: $(EXE1) $(EXE2) $(EXE3) $(EXE4) 

$(EXE1): $(SRC2)
	gcc $(CFLAGS) -DDAP_19 -I $(INCDIR) -o $(EXE1) -lpniousr $(SRC2)

$(EXE2): $(SRC2)
	gcc $(CFLAGS) -DDAP_1B -DIRTMOD -I $(INCDIR) -o $(EXE2) -lpniousr $(SRC2)

$(EXE3): $(SRC2)
	gcc $(CFLAGS) -DDAP_821 -I $(INCDIR) -o $(EXE3) -lpniousr $(SRC2)

$(EXE4): $(SRC2)
	gcc $(CFLAGS) -DDAP_822 -DIRTMOD -I $(INCDIR) -o $(EXE4) -lpniousr $(SRC2)

clean:
	rm -f $(EXE1) $(EXE2) $(EXE3) $(EXE4) 
