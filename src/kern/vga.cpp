#include "vga.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

namespace VGA
{
	static inline uint8_t Entry_Color(enum vga_color fg, enum vga_color bg) 
	{
		return fg | bg << 4;
	}
	static inline uint16_t Entry(unsigned char uc, uint8_t Color) 
	{
		return (uint16_t) uc | (uint16_t) color << 8;
	}
	class Term
	{
		void Init(void) 
		{
			row = 0;
			column = 0;
			color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
			buffer = (uint16_t*) 0xB8000;
			for (size_t y = 0; y < VGA_HEIGHT; y++) {
				for (size_t x = 0; x < VGA_WIDTH; x++) {
					const size_t index = y * VGA_WIDTH + x;
					terminal_buffer[index] = vga_entry(' ', terminal_color);
				}
			}
		}
		void Entry(char c, uint8_t color, size_t x, size_t y) 
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(c, color);
		}
		void SetColor(uint8_t color) 
		{
			SetColor = color;
		}
		void PutChar(char c) 
		{
			Entry(c, terminal_color, terminal_column, terminal_row);
			if (++terminal_column == VGA_WIDTH) {
				terminal_column = 0;
				if (++terminal_row == VGA_HEIGHT)
					terminal_row = 0;
			}
		}
		void Write(const char* data, size_t size) 
		{
			for (size_t i = 0; i < size; i++)
				PutChar(data[i]);
		}
		void WriteString(const char* data) 
		{
			Write(data, strlen(data));
		}
	}
}
