#include "term.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga.h"
#include "string.h"

namespace Term
{
	void Write(const char c)
	{
		if (++Term::X == VGA::WIDTH)
		{
			Term::X = 0;
			Term::newline();
		}
		if (c == '\n')
			Term::newline();
		Term::Buffer[Term::Y][Term::X] = c;
	}
	void WriteString(const char* chx)
	{
		String::Numbers Numbers;
		for(size_t i = 0; i<Numbers.strlen(chx); i++)
			Term::Write(chx[i]);
	}
	void newline()
	{
		if (++Term::Y == VGA::HEIGHT)
			Term::shift();
	}
	void shift()
	{
		Term::Y--;
		for (size_t i = 0; i<VGA::HEIGHT-1;i++)
			Term::Buffer[i] = Term::Buffer[i+1];
	}
	void Print()
	{
		VGA::Text Text;
		VGA::Text::column = 0;
		VGA::Text::row = 0;
		for(size_t i = 0; i<VGA::HEIGHT;i++)
			Text.WriteString(Term::Buffer[i]);
	}
	void Clear()
	{
		for (size_t i = 0; i<VGA::HEIGHT;i++)
			for (size_t ii = 0; ii<VGA::WIDTH;ii++)
				Term::Buffer[i][ii]=' ';
	}
	void textclear()
	{
		char* yes = "";
		uint16_t no = 0;
		for (size_t i = 0; i<VGA::HEIGHT;i++)
		{
			for (size_t ii = 0; ii<VGA::WIDTH;ii++)
			{
				yes[ii] = ' ';
				no++;
			}
			yes[no+1] = '\n';
		}
		VGA::Text.WriteString(yes);
	}
}
