#common_lib.mk need assign LIBNAME
LIBNAME	 = libpacket
OBJS	+= packet.o

include ../../common_lib.mk

gen-docs: $(HDR) $(SRC)
	$(DOXYGEN) $(DOXYGENFLAGS)
