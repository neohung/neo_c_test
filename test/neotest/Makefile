BASEDIR 	= .
SRCDIR  	= src
BINDIR		= bin
VERSION		= 0.1
TARGET		= libneo-test_v$(VERSION)

all: target

target:
	make -C $(SRCDIR)

clean:
	make -C $(SRCDIR) clean
	rm -fr doc/*
	#rm -f bin/firmware.*
