#include "vga.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>



void VGA::Term::Init(void) 
{
	for (size_t y = 0; y < VGA::HEIGHT; y++) {
		for (size_t x = 0; x < VGA::WIDTH; x++) {
			const size_t index = y * VGA::WIDTH + x;
			VGA::Term::Buffer[index] = VGA::Term::Entry(' ', terminal_color);
		}
	}
}
