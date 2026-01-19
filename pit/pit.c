#include "pit.h"

#include "libc/stdio.h"

#include <stdint.h>

int counter_for_pit_s = 0;

bool we_call_pit = false;

void pit_init() {
    uint32_t divisor = 1193182 / 1000; // 1000 HZ

    __asm__ __volatile__("cli");

    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);

    __asm__ __volatile__("sti");
    
}

volatile uint64_t ticks = 0;
static uint32_t ms_counter = 0;

void pit_irq_handler() {
    ticks++;

    if (we_call_pit && ticks >= counter_for_pit_s) {
        huguinx_print("\nTimer finished\n# ");
        we_call_pit = false;
    }
}


void sleep(uint32_t ms) {
    counter_for_pit_s = ticks + ms;

    we_call_pit = true;

}