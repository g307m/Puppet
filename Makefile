# grantlmul@gmail.com,27/02/2020
# Puppet version 0.1.0a
# Makefile index
# 1. Compilation
#  a. 33 - default/general
# 2. Emulation

MAJ = 0
MIN = 1
REV = 0
BCH = a
VER = $(MAJ).$(MIN).$(REV)$(BCH)

#stuff
TARGET        = i686
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

# 1a # compilation default
boot.o:
	$(TARGET)-elf-as $(BOOT)/boot.s -o $(BUILD)/boot.o
kern.o:
	i686-elf-gcc -c $(KERN)/Kernel.c -o $(BUILD)/kern.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
default: kern.o boot.o
	-mkdir $(BUILD)/$(VER) -p
	cd $(BUILD);\
	$(TARGET)-elf-gcc -T $(SRC)/linker.ld -o $(VER)/Puppet.bin $^ $(FGCC)

# 2 # stuff
iso:
	sh script/iso.sh $(BUILD)/$(VER)/Puppet.bin
	-mkdir -p $(BUILD)/iso/boot/grub
	cp $(BUILD)/$(VER)/Puppet.bin $(BUILD)/iso/boot/Puppet.bin
	cp script/grubiso.cfg $(BUILD)/iso/boot/grub/grub.cfg
	grub-mkrescue -o $(BUILD)/$(VER)/Puppet.iso $(BUILD)/iso
qemu-bin:
	qemu-system-i386 -kernel $(BUILD)/$(VER)/Puppet.bin
qemu-iso:
	qemu-system-i386 -cdrom $(BUILD)/$(VER)/Puppet.iso
andiso: default iso
swore: andiso
	qemu-system-i386 -cdrom $(BUILD)/$(VER)/Puppet.iso -curses
