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
FG++ = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -Wunused-parameter
FGCC = -ffreestanding -O2 -nostdlib -lgcc -Wunused-parameter

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
string.o:
	$(TARGET)-elf-g++ -c $(KERN)/string.cpp -o $(BUILD)/string.o $(FG++)
vga.o: string.o
	$(TARGET)-elf-g++ -c $(KERN)/vga.cpp -o $(BUILD)/vga.o $(FG++)
kern.o: vga.o
	$(TARGET)-elf-g++ -c $(KERN)/kern.cpp -o $(BUILD)/kld.o $(FG++)
	$(TARGET)-elf-ld -r -o $(BUILD)/kern.o $(BUILD)/string.o $(BUILD)/kld.o $(BUILD)/vga.o
default: kern.o boot.o
	mkdir $(BUILD)/$(VER) -p
	cd $(BUILD);\
	$(TARGET)-elf-gcc -T $(SRC)/linker.ld -o $(VER)/Puppet.bin $^ $(FGCC)

# 2 # stuff
iso:
	sh script/iso.sh $(BUILD)/$(VER)/Puppet.bin
	-mkdir -p $(BUILD)/iso/boot/grub
	cp $(BUILD)/$(VER)/kern.bin $(BUILD)/iso/boot/Puppet.bin
	cp script/grubiso.cfg $(BUILD)/iso/boot/grub/grub.cfg
	grub-mkrescue -o $(BUILD)/$(VER)/Puppet.iso $(BUILD)/iso
qemu-bin:
	qemu-system-i386 -kernel $(BUILD)/$(VER)/Puppet.bin
qemu-iso:
	qemu-system-i386 -cdrom $(BUILD)/$(VER)/Puppet.iso
qemu_iso: iso qemu-iso

