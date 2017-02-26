
#common_lib.mk need assign LIBNAME
LIBNAME	 = libudp
OBJS	+= udp.o

include ../../common_lib.mk

gen-docs: $(HDR) $(SRC)
	$(DOXYGEN) $(DOXYGENFLAGS)
