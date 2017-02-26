VERSION  = 0.1
TARGET   = packet_test_v$(VERSION)
BINARY	 = $(TARGET)
BINDIR   = ../bin
OBJS	+= main.o 

INCDIR  += -I../../../libneo/src/include \
	   -I../../../libudp/src/include \
	   -I../../../libpacket/src/include

LIBDIR  += -L../../../libneo/lib \
	   -L../../../libudp/lib \
	   -L../../../libpacket/lib

LIBS	+= -lneo -ludp -lpacket

include ../../../common.mk

gen-docs: $(SRC) 
	$(DOXYGEN) $(DOXYGENFLAGS)
