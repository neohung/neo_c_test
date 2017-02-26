BASEDIR 	= .
VERSION		= 0.1
TARGET		= test_v$(VERSION)

all: target

target:  
	make -C neotest
	make -C neoudpclient

clean: 
	make -C neotest clean

style:
	make -C neotest style

check:
	make -C neotest check

gen-docs: target
	cd neotest && make gen-docs
