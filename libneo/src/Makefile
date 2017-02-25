
#common_lib.mk need assign LIBNAME
LIBNAME	 = libneo
OBJS	+= neo.o

include ../../common_lib.mk

gen-docs: $(HDR) $(SRC)
	$(DOXYGEN) $(DOXYGENFLAGS)
