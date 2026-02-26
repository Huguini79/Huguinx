#include "idt.h"

#include "libc/stdio.h"

#include "libc/stdlib.h"

#define CODE_SEGMENT_SELECTOR 0x08

struct Idt DescriptorIdt[256];

struct Idt* IdtSetGate(int num, void* address) {
	struct Idt* Idt = &DescriptorIdt[num];
	
	Idt->offset_first_0_15_bits = (uint32_t) address & 0xFFFF;
	Idt->selector = CODE_SEGMENT_SELECTOR;
	Idt->zero = 0x00000000;
	Idt->type_attributes = 0x8E;
	Idt->offset_16_31_bits = (uint32_t) address >> 16 & 0xFFFF;
	
	// return Idt;
	
}

void zero_interrupt() {
	huguinx_print("ERROR DE DIVISION POR CERO");
}

void IdtInstall() {	
	struct Idtr idtr;
	
	IdtSetGate(0, zero_interrupt);
	
	idtr.limit = sizeof(DescriptorIdt) - 1;
	idtr.base = (uint32_t)DescriptorIdt;
	
	asm volatile (
		"lidt %0"
		: : "m"(idtr)
	);
	
}
