BINARY	 = firmware
BINDIR   = bin
OBJS	+= main.o 
INCDIR  += -I../../../libneo/src/include 
LIBDIR  += -L../../../libneo/lib
LIBS	+= -lneo

include ../../../common.mk

gen-docs: $(SRC) 
	$(DOXYGEN) $(DOXYGENFLAGS)
