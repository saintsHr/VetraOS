#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "terminal.h"
#include "utils.h"

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

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000 

size_t terminal_row;
size_t terminal_column;

uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	
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

void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++){
		if (data[i] == '\n'){
			terminal_row++;
			terminal_column = 0;
		}else{
			terminal_putchar(data[i]);
		}
	}
}

void terminal_print(const char* data)
{
	terminal_write(data, strlen(data));
}

void terminal_erase()
{
	if (terminal_column > 6)
	{
		terminal_putentryat(' ', 15, terminal_column - 1, terminal_row);
		terminal_column--;
	}
}

void terminal_moveCursor(uint8_t row, uint8_t col)
{
	uint16_t position = row * 80 + col;

	utils_outb(0x3D4, 0x0F);
	utils_outb(0x3D5, (uint8_t)(position & 0xFF));

	utils_outb(0x3D4, 0x0E);
	utils_outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));
}

void terminal_updateCursor()
{
	terminal_moveCursor(terminal_row, terminal_column);
}

void terminal_incCursor()
{
	terminal_moveCursor(terminal_row, terminal_column + 1);
}

void terminal_decCursor()
{
	terminal_moveCursor(terminal_row, terminal_column - 1);
}

void terminal_prompt(const char* prompt)
{
	terminal_setcolor(2);
	terminal_print("\n");
	terminal_print(prompt);
	terminal_setcolor(7);
	terminal_moveCursor((uint8_t)terminal_row, (uint8_t)strlen(prompt));
}

void terminal_clear()
{
	uint16_t *video_memory = (uint16_t*) VGA_MEMORY;
	for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++){
		video_memory[i] = (0x07 << 8) | ' ';
	}
	terminal_column = 0;
	terminal_row = 0;
}