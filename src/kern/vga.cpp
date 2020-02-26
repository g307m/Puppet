#include "vga.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

namespace VGA
{
	static inline uint8_t EntryColor(enum VGA:Color fg, enum VGA::Color bg) 
	{
		return fg | bg << 4;
	}
	static inline uint16_t Entry(unsigned char uc, uint8_t Color) 
	{
		return (uint16_t) uc | (uint16_t) color << 8;
	}
	void Term::Init(void) 
	{
		row = 0;
		column = 0;
		color = EntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
		buffer = (uint16_t*) 0xB8000;
		for (size_t y = 0; y < VGA::HEIGHT; y++) {
			for (size_t x = 0; x < VGA::WIDTH; x++) {
				const size_t index = y * VGA::WIDTH + x;
				buffer[index] = Entry(' ', color);
			}
		}
	}
	void Term::Entry(char c, uint8_t color, size_t x, size_t y) 
	{
		const size_t index = y * VGA::WIDTH + x;
		buffer[index] = vga_entry(c, color);
	}
	void Term::SetColor(uint8_t color) 
	{
		SetColor = color;
	}
	void Term::PutChar(char c) 
	{
		Entry(c, color, column, row);
		if (++column == VGA_WIDTH) {
			column = 0;
			if (++row == VGA_HEIGHT)
				row = 0;
		}
	}
	void Term::Write(const char* data, size_t size) 
	{
		for (size_t i = 0; i < size; i++)
			PutChar(data[i]);
	}
	void Term::WriteString(const char* data) 
	{
		Write(data, strlen(data));
	}

}
