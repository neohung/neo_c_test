PREFIX ?= 
CC = $(PREFIX)gcc
AR = $(PREFIX)ar
#CFLAGS		+= -Os -g -Wall -Wextra $(INCDIR)  -mmcu=msp430g2553
CFLAGS		+= -Os -g -Wall -Wextra $(INCDIR)
ARFLAGS		 = rcs
# where to search for headers
INCDIR      += -I./include -I$(HOME)/msp430/include
# where to put generated libraries to
LIBDIR		 = ../lib
# doxygen executable
DOXYGEN = doxygen
# doxygen flags
DOXYGENFLAGS = ../doxygen.conf
# styler to use
STYLER = astyle
# which c-style to use
# - see man astyle
STYLERFLAGS = --style=stroustrup --indent=spaces=2 --indent-switches --indent-preprocessor
# cpp checker
CHECKER = cppcheck
# flags for checker
# CHECKERFLAGS = --error-exitcode=1 --enable=all
CHECKERFLAGS = --enable=all --error-exitcode=1
.SUFFIXES: .elf .bin .hex .srec .list .images
.SECONDEXPANSION:
.SECONDARY:

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

SRC = $(wildcard *.c)
HDR = $(wildcard include/*.h)

all: target

target: prepare $(LIBNAME).a


$(LIBNAME).a: $(OBJS)
	@#printf "  AR      $(subst $(shell pwd)/,,$(@))\n"
	$(AR) $(ARFLAGS) $@ $^ && cp $(LIBNAME).a $(LIBDIR)/.

prepare:
	test -d $(LIBDIR) || mkdir $(LIBDIR)

%.o: %.c Makefile
	@$(CC) -c $(CFLAGS) $< -o $@ 2> $@.log; RESULT=$$?; if [ $$RESULT -ne 0 ]; then \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
	printf "$(ERROR_COLOR)=======================================================\n"; \
	cat $@.log; \
	printf "=======================================================$(NO_COLOR)\n"; \
	elif [ -s $@.log ]; then \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"; \
	printf "$(WARN_COLOR)=======================================================\n"; \
	cat $@.log; \
	printf "=======================================================$(NO_COLOR)\n"; \
	else  \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
	fi ;\
	rm -f $@.log; \
	exit $$RESULT

%.o: %.cpp Makefile
	@$(CC) -c $(CFLAGS) $< -o $@ 2> $@.log; RESULT=$$?; if [ $$RESULT -ne 0 ]; then \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
	elif [ -s $@.log ]; then \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"; \
	else  \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
	fi ;\
	printf "$(WARN_COLOR)===========================\n"; \
	cat $@.log; \
	printf "===========================$(NO_COLOR)\n"; \
	rm -f $@.log; \
	exit $$RESULT

style:
	@if [ "X$(SRC)" != "X" ]; then $(STYLER) $(STYLERFLAGS) $(SRC); fi
	@if [ "X$(HDR)" != "X" ]; then $(STYLER) $(STYLERFLAGS) $(HDR); fi

check: 
	@if [ "X$(SRC)" != "X" ]; then \
	$(CHECKER) $(CHECKERFLAGS) $(SRC) 2> $@.log; RESULT=$$?; if [ $$RESULT -ne 0 ]; then \
	printf "$(ERROR_COLOR)===========================\n"; \
        cat $@.log; \
        printf "===========================$(NO_COLOR)\n"; \
	fi;\
        rm -f $@.log; \
	fi

clean:
	rm -f *.o
	rm -f *.a

.PHONY: clean

