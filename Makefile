all: target

lib: 
	make -C libneo

target: lib
	@echo "target"

clean:
	make -C libneo clean

#doxygen ../doxygen.conf
gen-docs: lib
	make -C libneo gen-docs 
