VERSION  = 0.1
TARGET   = neo-test_v$(VERSION)
BINARY	 = $(TARGET)
BINDIR   = ../bin
OBJS	+= main.o 
INCDIR  += -I../../../libneo/src/include \
	   -I../../../libudp/src/include
LIBDIR  += -L../../../libneo/lib \
	   -L../../../libudp/lib
LIBS	+= -lpthread -lneo -ludp

include ../../../common.mk

gen-docs: $(SRC) 
	$(DOXYGEN) $(DOXYGENFLAGS)
