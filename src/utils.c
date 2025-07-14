#include "utils.h"

void utils_wait(unsigned int ticks)
{
    for (unsigned int i = 0; i < ticks * 100000; i++){
        __asm__ volatile("nop");
    }
}

void utils_outb(uint16_t port, uint8_t val)
{
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}