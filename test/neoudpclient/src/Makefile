VERSION  = 0.1
TARGET   = neo-udpclient_v$(VERSION)
BINARY	 = $(TARGET)
BINDIR   = ../bin
OBJS	+= main.o 
INCDIR  += -I../../../libneo/src/include \
	   -I../../../libudp/src/include
LIBDIR  += -L../../../libneo/lib \
	   -L../../../libudp/lib
LIBS	+= -lneo -ludp

include ../../../common.mk

gen-docs: $(SRC) 
	$(DOXYGEN) $(DOXYGENFLAGS)
