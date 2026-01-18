// Author: Huguini79
// I/O Driver implementation
#ifndef IO_H
#define IO_H

#include <stdint.h>
#include <stddef.h>

unsigned short insb(unsigned short port);
unsigned short insw(unsigned short port);
unsigned short inl(unsigned short port);

void outb(unsigned short port, uint8_t data);
void outw(unsigned short port, uint16_t data);
void outl(unsigned short port, uint32_t data);

#endif
