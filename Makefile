all: target

lib: 
	make -C libneo
	make -C libudp
	make -C libpacket

target: lib
	make -C test

clean:
	make -C libneo clean
	make -C libudp clean
	make -C libpacket clean
	make -C test clean

#doxygen ../doxygen.conf
gen-docs: lib
	make -C libneo gen-docs 
