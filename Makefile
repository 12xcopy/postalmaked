
DEBUG ?= 0

# note: For whatever reason this doesnt work. i need to look at the postal1 makefile to figure out whats up

all:
	cd ./postal
	make all -f ./postal/makefile
	cd ../
	ln -s ./postal/bin/postal1-* ./postal1.elf

clean:
	cd ./postal
	make clean -f ./postal/makefile
	cd ../

.PHONY: all clean