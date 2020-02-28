#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "string.h"

namespace VGA
{
	static const size_t WIDTH  = 80;
	static const size_t HEIGHT = 25;
	enum Color {
		VGA_COLOR_BLACK = 0,
		VGA_COLOR_BLUE = 1,
		VGA_COLOR_GREEN = 2,
		VGA_COLOR_CYAN = 3,
		VGA_COLOR_RED = 4,
		VGA_COLOR_MAGENTA = 5,
		VGA_COLOR_BROWN = 6,
		VGA_COLOR_LIGHT_GREY = 7,
		VGA_COLOR_DARK_GREY = 8,
		VGA_COLOR_LIGHT_BLUE = 9,
		VGA_COLOR_LIGHT_GREEN = 10,
		VGA_COLOR_LIGHT_CYAN = 11,
		VGA_COLOR_LIGHT_RED = 12,
		VGA_COLOR_LIGHT_MAGENTA = 13,
		VGA_COLOR_LIGHT_BROWN = 14,
		VGA_COLOR_WHITE = 15,
	};
	
	inline uint8_t Entry(VGA::Color,VGA::Color);
	inline uint16_t EntryColor(unsigned char uc, uint8_t color);

	class Text
	{
		public:
			void Reset        (void);
			void SetColor     (uint8_t color);
			void WriteString  (const char* data);
			// Made available, but usage is discouraged.
			void Write        (const char* data, size_t size);
			// Either set to zero will continue like 'vanilla' Write.
			void bWrite       (const char* data, size_t size);
			// WriteString for scrolling
			void bWriteString (const char* data);
			// Refresh screen with buffer
			void bShow();
			//clear buffer
			void bClear();
			size_t    row    = 0;
			size_t    column    = 0;
		private:
			// better text handling + SCROLLING(!)
			char*   Buffer[VGA::HEIGHT];
			uint8_t BufferX = 0;
			uint8_t BufferY = 0;
			void    bScroll();
			//const char* OldBuffer[VGA::HEIGHT]; // may be necessary allow scrolling
			void PutChar(char c);
			uint8_t   color  = 7 | 0 << 4;
			uint16_t* vgabuffer = (uint16_t*) 0xB8000;
			void      Entry    (char c, uint8_t color, size_t x, size_t y);
			
	};
}
