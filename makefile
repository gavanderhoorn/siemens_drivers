all:
	make -C pniolib
	make -C layer2lib
	make -C servlib

clean:
	make -C pniolib clean
	make -C layer2lib clean
	make -C servlib clean

install:
	make -C pniolib install
	make -C layer2lib install
	make -C servlib install
