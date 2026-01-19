#include "pit.h"

#include <stdint.h>

void pit_init() {
    uint32_t divisor = 1193182 / 1000; // 1000 HZ

    __asm__ __volatile__("cli");

    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);

    __asm__ __volatile__("sti");
    
}

volatile uint64_t ticks = 0;

void pit_irq_handler() {
    ticks++;
}

void sleep(uint32_t ms) {
    uint64_t target = ticks + ms;

    while(ticks < target) {
        __asm__ __volatile__("hlt");
    }

}