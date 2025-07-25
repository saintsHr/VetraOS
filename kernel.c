#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "include/terminal.h"
#include "include/utils.h"
#include "include/keyboard.h"

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This OS needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void)
{
	terminal_initialize();
	terminal_prompt("VetraOS> ");

	while (1)
	{
		keyboard_loop();
	}
}
