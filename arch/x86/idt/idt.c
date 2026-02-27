#include "idt.h"
#include "kernel/kernel.h"

#include "libc/stdio.h"

#include "libc/stdlib.h"

#define CODE_SEGMENT_SELECTOR 0x08

struct Idt DescriptorIdt[256];

struct Idt* IdtSetGate(int num, void* address) {
	struct Idt* Idt = &DescriptorIdt[num];
	
	// (0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31)
	Idt->offset_first_0_15_bits = (uint32_t) address & 0xFFFF;	// Offset first 16 bits (0-15) (with use AND Operator with 0xFFFF to extract only the first 16 bits
	Idt->selector = CODE_SEGMENT_SELECTOR;	// Kernel code selector
	Idt->zero = 0x00000000;	// Unused, set to zero
	Idt->type_attributes = 0x8E; // 32 bit Interrupt Gate
	Idt->offset_16_31_bits = (uint32_t) address >> 16 & 0xFFFF; // Offset 16 bits (16-31) | 32 bits of offset in total
	
	// return Idt;
	
}

void IdtSetTrap(int num, void* address) {
	struct Idt* Idt = &DescriptorIdt[num];

	Idt->offset_first_0_15_bits = (uint32_t) address & 0xFFFF;
	Idt->selector = CODE_SEGMENT_SELECTOR;
	Idt->zero = 0x00000000;
	Idt->type_attributes = 0x8F; // 32 bit Trap
	Idt->offset_16_31_bits = (uint32_t) address >> 16 & 0xFFFF;

}

void syscall_80h() {
			syscall_option = 2;

	if (syscall_option == 2) {
		huguinx_print("0x80 called | Yo Contigo, Tú Conmigo - Alvaro Soler");
		
	} else {
		huguinx_print("0x80 called | Try the magic way");
	}
}

void zero_interrupt() {
	huguinx_print("DIVIDE BY ZERO ERROR");
}

void IdtInstall() {
	struct Idtr idtr;
	
	// Exception Error (Divide by zero error)
	IdtSetGate(0, zero_interrupt);
	
	// 0x80 system call
	IdtSetTrap(0x80, syscall_80h);
	
	idtr.limit = sizeof(DescriptorIdt) - 1;
	idtr.base = (uint32_t)DescriptorIdt;
	
	asm volatile (
		"lidt %0"
		: : "m"(idtr)
	);
	
}
