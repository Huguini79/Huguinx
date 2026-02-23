// Author: Huguini79
// GDT Implementation
#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define MAX_GDT_SEGMENTS 3

struct Gdt {
	uint16_t limit;
	uint16_t base_first_0_15_bits;
	uint8_t base_16_23_bits;
	uint8_t access_byte;
	uint8_t flags;
	uint8_t base_24_31_bits;
}__attribute__((packed));

struct Gdtr {
	uint16_t limit;
	uint32_t base;

}__attribute__((packed));

static struct Gdt gdt[MAX_GDT_SEGMENTS];

static struct Gdtr gdtr = {
	.limit = sizeof(gdt) - 1,
	.base = (uint32_t)&gdt
};

void gdt_load(struct Gdtr* Gdtr);

struct Gdt* CreateNullSegment(struct Gdt* Gdt);
struct Gdt* CreateCodeSegment(struct Gdt* Gdt);
struct Gdt* CreateDataSegment(struct Gdt* Gdt);

#endif
