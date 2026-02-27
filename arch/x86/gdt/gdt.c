#include "gdt.h"
// #include "drivers/vga/vga.c"
// #include "libc/stdio.h"

struct Gdt DescriptorGdt[MAX_GDT_SEGMENTS];
struct Gdtr gdtr;

struct Gdt* CreateNullSegment(struct Gdt* Gdt) {
	Gdt->limit = 0x00;
	Gdt->base_first_0_15_bits = 0x00;
	Gdt->base_16_23_bits = 0x00;
	Gdt->access_byte = 0x00;
	Gdt->flags = 0x00;
	Gdt->base_24_31_bits = 0x00;
	return Gdt;
}

struct Gdt* CreateCodeSegment(struct Gdt* Gdt) {
	Gdt->limit = 0xFFFF;
	Gdt->base_first_0_15_bits = 0x00;
	Gdt->base_16_23_bits = 0x00;
	Gdt->access_byte = 0x9A;
	Gdt->flags = 0b11001111;
	Gdt->base_24_31_bits = 0x00;
	return Gdt;
}

struct Gdt* CreateDataSegment(struct Gdt* Gdt) {
	Gdt->limit = 0xFFFF;
	Gdt->base_first_0_15_bits = 0x00;
	Gdt->base_16_23_bits = 0x00;
	Gdt->access_byte = 0x92;
	Gdt->flags = 0b11001111;
	Gdt->base_24_31_bits = 0x00;
	return Gdt;
}

void SetUpGdtr(struct Gdtr* gdtr) {
	gdtr->limit = sizeof(DescriptorGdt) - 1;
	gdtr->base = (uint32_t)DescriptorGdt;
}

void LoadGdt(struct Gdtr* gdtr) {
    asm volatile (
        "lgdt %0"
        :
        : "m"(*gdtr)
    );
}
