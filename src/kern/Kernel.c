#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

/* Hardware text mode color constants. */
enum vga_color {
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

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
char terminal_readentry(size_t index)
{
	return terminal_buffer[index];
}
void terminal_scroll(void)
{
	for (size_t y = 0; y < VGA_HEIGHT-1; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
			terminal_buffer[y*VGA_WIDTH+x] = terminal_buffer[(y+1)*VGA_WIDTH+x];
}
void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_scroll();
	}
	if (c == '\n')
	{
		terminal_row++;
		terminal_column = 0;
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();

	/* Newline support is left as an exercise. */
	terminal_writestring("Hello, Puppet user! I'm line one, and I'm going to kill myself!\n");
	terminal_writestring("lmao imagine using C++\n");
	terminal_writestring("um line 3 can be a long line to test if the auto newline whatever works like it should\n");
	terminal_writestring("hey what about never gonna give you up\n");
	terminal_writestring("ba doom ba dum da da doom ba doom da daa\n");
	terminal_writestring("*music plays in background*\n");
	terminal_writestring("We're no strangers to love\n");
	terminal_writestring("You know the rules, and so do I.\n");
	terminal_writestring("A full commitment's what I'm thinking of,\n");
	terminal_writestring("you wouldn't get this from any other guy.\n"); // line 11
	terminal_writestring("\nI just wanna tell you how I'm feeling\n"); //13
	terminal_writestring("Gotta make you understand\n\n"); //14,15
	terminal_writestring("Never gonna give you up,\n");//16
	terminal_writestring("never gonna let you down,\n");//17
	terminal_writestring("never gonna run around and desert you.\n");//18
	terminal_writestring("Never gonna make you cry,\n");//19
	terminal_writestring("never gonna say goodbye,\n");//20
	terminal_writestring("never gonna tell a lie, and hurt you.\n");//21
	terminal_writestring("\nEh, that's good enough.\n");//22,23
	terminal_writestring("This is line 24,\n");//24
	terminal_writestring("and this is line 25.\n");//25
	terminal_writestring("If all is well, that first line should have vanished. also line \\\"26\\\" btw\n");//"26"
}
