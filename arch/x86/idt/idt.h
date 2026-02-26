// Author: Huguini79
// IDT implementation
#ifndef IDT_H
#define IDT_H

#include <stdint.h>

struct Idt {
	uint16_t offset_first_0_15_bits;	// 0-15 bits (16 bits of offset)
	uint16_t selector;	// Code Segment Selector (0x08)
	uint8_t zero;	// Unused, set to 0
	uint8_t type_attributes;	// Gate Type, DPL, And P Fields
	uint16_t offset_16_31_bits;		// 16-31 bits (16 bits of offset)
}__attribute__((packed));

struct Idtr {
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));

#endif
