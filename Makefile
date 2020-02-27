
# grantlmul@gmail.com,25/02/2020
#version 0.1.0a
MAJ = 0
MIN = 1
REV = 0
BCH = a
VER = $(MAJ).$(MIN).$(REV)$(BCH)

#stuff
TARGET        = i686-elf
BUILD         = build
.DEFAULT_GOAL:= default
ROOT = $(shell pwd)

#flags for programs
FG++ = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
FGCC = -ffreestanding -O2 -nostdlib -lgcc

# src stuff
SRC  = $(ROOT)/src
BOOT = $(SRC)/boot
KERN = $(SRC)/kern

init:
	-mkdir $(BUILD)
	-mkdir $(SRC)
	-mkdir $(BOOT)
	-mkdir $(KERN)

boot.o:
	$(TARGET)-as $(BOOT)/boot.s -o $(BUILD)/boot.o
vga.o:
	$(TARGET)-g++ -c $(KERN)/vga.cpp -o $(BUILD)/vga.o $(FG++)
kern.o: vga.o
	$(TARGET)-g++ -c $(KERN)/kern.cpp -o $(BUILD)/kld.o $(FG++)
	$(TARGET)-ld -r -o $(BUILD)/kern.o $(BUILD)/kld.o $(BUILD)/vga.o
default: kern.o boot.o
	mkdir $(BUILD)/$(VER) -p
	cd $(BUILD);\
	$(TARGET)-gcc -T $(SRC)/linker.ld -o $(VER)/kern.bin $^ $(FGCC)
