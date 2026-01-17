// Author: Huguini79
// IDT implementation
#include "idt.h"
#include "config.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "drivers/io/io.h"
#include "drivers/serial/serial.h"
#include "drivers/keyboard/keyboard.h"

/* Define total IDT Interrupts */
struct idt_descriptor idt_descriptors[HUGUINX_TOTAL_INTERRUPTS];
struct idtr_descriptor idtr_descriptor;

void idt_zero();
void idt_set(int interrupt_no, void* address);
void int21_handler();
void no_interrupt_handler();

extern void idt_load(struct idtr_descriptor* ptr);
extern void int21h();
extern void no_interrupt();

const char* divide_zero_error_message = "Divide by zero error\n";

void idt_zero() {
	huguinx_print(divide_zero_error_message);
}

void int21h_handler() {
	/* Our keyboard interrupt function will be implemented later */
	init_keyboard();
}

void no_interrupt_handler() {
	outb(0x20, 0x20);
}

/* Map an interrupt to an address */
/* This is very important for example in Linux, because in Linux if you call "int 80h or int 0x80", our idt is prepared to begin executing at the address provided*/

void idt_set(int interrupt_no, void* address) {
	/* We define the idt descriptor */
	struct idt_descriptor* descriptor = &idt_descriptors[interrupt_no];
	
	descriptor->offset_1 = (uint32_t) address & 0x0000ffff;
	descriptor->selector = KERNEL_CODE_SELECTOR;
	descriptor->zero = 0x00; /* This is the most easy thing I wrote in an idt implementation XD */
	descriptor->type_attr = 0xEE;
	descriptor->offset_2 = (uint32_t) address >> 16;
	
}

/* WE INIT THE IDT, YEEEEES BABY*/
void idt_init() {
	memset(idt_descriptors, 0, sizeof(idt_descriptors));
	
	/* This reminds me to GDT with .limit and .base values */
	
	/* This is the actual idt table size */
	idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
	
	/* OMG, this is where our IDT is stored (yes, idt it's an array in memory like GDT) */
	idtr_descriptor.base = (uint32_t) idt_descriptors;
	
	for(int i = 0; i < HUGUINX_TOTAL_INTERRUPTS; i++) {
		idt_set(i, no_interrupt);
	}
	
	/* Well well well, ladies and gentlemen, we set our first interrupt (it's an exception <- divide by zero error) */
	idt_set(0, idt_zero);
	
	/* NOW WE SET OUR SECOND INTERRUPT, THE KEYBOARD INTERRUPT */
	idt_set(0x09, int21h);
	
	/* YES YES YES, WE LOAD THE IDT */
	idt_load(&idtr_descriptor);
	
}
