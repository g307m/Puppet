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
	void VGA::Text::Reset(void) 
	{
		row = 0;
		column = 0;
		color = EntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
		vgabuffer = (uint16_t*) 0xB8000;
		for (size_t y = 0; y < VGA::HEIGHT; y++) {
			for (size_t x = 0; x < VGA::WIDTH; x++) {
				const size_t index = y * VGA::WIDTH + x;
				vgabuffer[index] = VGA::Entry(' ', color);
			}
		}
	}
	void VGA::Text::Entry(char c, uint8_t color, size_t x, size_t y) 
	{
		const size_t index = y * VGA::WIDTH + x;
		vgabuffer[index] = VGA::Entry(c, color);
	}
	void VGA::Text::SetColor(uint8_t color) 
	{
		Text::color = color;
	}
	void VGA::Text::PutChar(char c) 
	{
		Entry(c, color, column, row);
		if (++column == VGA::WIDTH) {
			column = 0;
		}
		if(c=='\n') // newline support, boi
		{
			column=0;
			row++;
		}
	}
	void VGA::Text::Write(const char* data, size_t size) 
	{
		for (size_t i = 0; i < size; i++)
			PutChar(data[i]);
	}
	void VGA::Text::WriteString(const char* data) 
	{
		String::Numbers instance;
		Write(data, instance.strlen(data));
	}
}
