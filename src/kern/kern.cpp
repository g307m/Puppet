#include <stdbool.h>
#include <stddef.h>  // Include them all!
#include <stdint.h>

#include "vga.h"
#include "term.h"
#include "string.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "you need an ix86-elf compiler"
#endif

extern "C" void kernel_main(void)
{	
	Term::Write('a');
	Term::Write('\n');
	Term::Write('b');
	Term::Print();
}

