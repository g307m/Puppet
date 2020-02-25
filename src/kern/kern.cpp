#include <stdbool.h>
#include <stddef.h>  // Include them all!
#include <stdint.h>

#include "vga.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "you need an ix86-elf compiler"
#endif

// I'm basically minimizing the OSDev wiki barebones here, so *bare* with me


