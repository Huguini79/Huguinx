#ifndef PIT_H
#define PIT_H

#include <stdint.h>

void pit_init();
void pit_irq_handler();
void sleep(uint32_t ms);

#endif