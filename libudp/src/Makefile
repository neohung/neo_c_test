
#common_lib.mk need assign LIBNAME
LIBNAME	 = libudp
OBJS	+= udp.o
#INCDIR  += -I../../../libneo/src/include 
#LIBDIR  += -L../../../libneo/lib 

LIBS    += -lpthread


include ../../common_lib.mk

gen-docs: $(HDR) $(SRC)
	$(DOXYGEN) $(DOXYGENFLAGS)
