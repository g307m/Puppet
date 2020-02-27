//vga.cpp
#include "vga.h"

#include "string.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
namespace VGA 
{
	inline uint8_t EntryColor(enum VGA::Color fg, enum VGA::Color bg) 
	{
		return fg | bg << 4;
	}
	inline uint16_t Entry(unsigned char uc, uint8_t color) 
	{
		return (uint16_t) uc | (uint16_t) color << 8;
	}
	void VGA::Term::Init(void) 
	{
		row = 0;
		column = 0;
		color = EntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
		buffer = (uint16_t*) 0xB8000;
		for (size_t y = 0; y < VGA::HEIGHT; y++) {
			for (size_t x = 0; x < VGA::WIDTH; x++) {
				const size_t index = y * VGA::WIDTH + x;
				buffer[index] = VGA::Entry(' ', color);
			}
		}
	}
	void VGA::Term::Entry(char c, uint8_t color, size_t x, size_t y) 
	{
		const size_t index = y * VGA::WIDTH + x;
		buffer[index] = VGA::Entry(c, color);
	}
	void VGA::Term::SetColor(uint8_t color) 
	{
		Term::color = color;
	}
	void VGA::Term::PutChar(char c) 
	{
		Entry(c, color, column, row);
		if (++column == VGA::WIDTH) {
			column = 0;
			if (++row == VGA::HEIGHT)
				row = 0;
		}
	}
	void VGA::Term::Write(const char* data, size_t size) 
	{
		for (size_t i = 0; i < size; i++)
			PutChar(data[i]);
	}
	void VGA::Term::WriteString(const char* data) 
	{
		String::Numbers instance;
		Write(data, instance.strlen(data));
	}
}
