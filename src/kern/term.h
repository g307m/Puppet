#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga.h"

namespace Term
{
	void Write       (const char c);
	void WriteString (const char* chx);
	void Print	 ();
	void Clear	 ();
	
	// data
	uint8_t X = 0;
	uint8_t Y = 0;
	char* Buffer[VGA::WIDTH];

	namespace
	{
		void newline   ();
		void shift     ();
		void textclear ();
	}
}
