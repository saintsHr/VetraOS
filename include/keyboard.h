#include <stdint.h>

uint8_t keyboard_inb(uint16_t port);
uint8_t keyboard_readScancode();
char keyboard_scancodeASCII(uint8_t scancode);
void keyboard_loop();