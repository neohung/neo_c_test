BASEDIR 	= .
SRCDIR  	= src
VERSION		= 0.1
TARGET		= libudp_v$(VERSION)

all: target

target:  
	make -C $(SRCDIR)

clean: 
	make -C $(SRCDIR) clean
	#rm -fr doc/gen	
	rm -f lib/*.a
style:
	make -C $(SRCDIR) style

check:
	make -C $(SRCDIR) check

gen-docs: target
	cd $(SRCDIR) && make gen-docs
