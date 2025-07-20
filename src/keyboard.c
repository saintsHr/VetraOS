#include "keyboard.h"
#include "terminal.h"

uint8_t keyboard_inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

uint8_t keyboard_readScancode()
{
    return keyboard_inb(0x60);
}

char keyboard_scancodeASCII(uint8_t scancode)
{
    static const char map[128] = {
        0, 27, '1','2','3','4','5','6','7','8','9','0','-','=','\b',  //0x00
        '\t','q','w','e','r','t','y','u','i','o','p',0,0,'\n',        //0x0E
        0,'a','s','d','f','g','h','j','k','l','ç',0,0,0,              //0x1E
        0,'z','x','c','v','b','n','m',',','.',';',0,0,                //0x2E
        0,' ',0,0,0,0,0,0,0,0,                                      //0x3E
        0,0,0,0,0,0,0,0,0,0                                           //...
    };

    return scancode < 128 ? map[scancode] : 0;
}

void keyboard_loop()
{
    uint8_t sc;

    do {
        sc = keyboard_readScancode();
    } while (sc & 0x80);

    char c = keyboard_scancodeASCII(sc);
    if (c) {
        if (c == '\b') {
            terminal_erase();
            terminal_updateCursor();   
        } else if (c == '\n') {
            terminal_prompt("VetraOS> ");
        } else {
            terminal_putchar(c);
            terminal_updateCursor();
        }
    }

    do {
        sc = keyboard_readScancode();
    } while (!(sc & 0x80));
}
    