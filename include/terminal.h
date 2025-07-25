#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum vga_color;
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg);
static inline uint16_t vga_entry(unsigned char uc, uint8_t color);
size_t strlen(const char* str);
void terminal_initialize(void);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_print(const char* data);
void terminal_clear();
void terminal_prompt(const char* prompt);
void terminal_moveCursor(uint8_t row, uint8_t col);
void terminal_erase();
void terminal_incCursor();
void terminal_decCursor();
void terminal_updateCursor();
const char* terminal_readLine(uint8_t row, uint8_t offset);
