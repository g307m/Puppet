// 8-width tabs are used here



  // grantlmul@gmail.com, 25/02/2020

// multiboot spec stuff (leaving as soon as possible)
.set ALIGN,	1<<0		//
.set MEMINFO,	1<<1		//
.set FLAGS,	ALIGN | MEMINFO //
.set MAGIC,	0x1BADB002	// 'one bad boot'
.set CHECKSUM,	-(MAGIC+FLAGS)	// should equal unsigned zero
//	\\	//	\\	//

// This HAS to be aligned on a 32-bit boundary, within the first 8K of the file.
.section .multiboot  //
.align 4            // #########################################################
.long MAGIC        //  # Future note: feel fee to yeet all these extra slashes #
.long FLAGS       //   # and whatever, I just think they look cool.            #
.long CHECKSUM   //    #########################################################
//==============//

// We're responsible for our own stack, we'll make it 16384 bytes. \\
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

// linker says _start is the front door, and we're going to lock them in \\
.section	.text
.global		_start
.type		_start, @function
_start:
	// 32 bit protected mode. \\
	//No interupts, no paging. We're on our own now. \\
	
	// Set up the stack, and set esp to the top. \\
	mov $stack_top,	%esp

	// This is a good place for setup. \\

	// Time to go. \\
	call kernel_main

	// When the computer dies, freeze. \\
	cli
1:	hlt
	jmp 1b

// set the size of _start to here minus where it begins
.size _start, . - _start
