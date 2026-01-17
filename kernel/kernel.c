// Author: Huguini79
// KERNEL IMPLEMENTATION
#include "libc/stdio.h"
#include "drivers/vga/vga.h"
#include "kernel/kernel.h"
#include "drivers/io/io.h"
#include "drivers/serial/serial.h"
#include "arch/x86/idt/idt.h"
#include "arch/x86/gdt/gdt.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/disk/disk.h"
#include "arch/x86/tss/tss.h"

#include "config.h"

/*

#include "drivers/memory/heap/heap.h"
#include "drivers/memory/paging/paging.h"

*/

struct tss tss;

struct gdt gdt_real[HUGUINX_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[HUGUINX_TOTAL_GDT_SEGMENTS] = {
{.base=0x00, .limit=0x00, .type=0x00}, // NULL Segment
{.base=0x00, .limit=0xffffffff, .type=0x9a}, // Kernel code Segment
{.base=0x00, .limit=0xffffffff, .type=0x92}, // Kernel data Segment
{.base=0x00, .limit=0xffffffff, .type=0xf8}, // User
{.base=0x00, .limit=0xffffffff, .type=0xf2}, // User
{.base=(uint32_t)&tss, .limit=sizeof(tss) - 1, .type=0xE9} // TSS Segment
};
 
void kernel_main() {
    huguinx_init_screen();
    
    huguinx_print("Huguinx - 1.0 | Huguini79 (https://github.com/Huguini79/Huguinx)");
    row_plus();
    row_plus();
    huguinx_print("X86 OPERATING SYSTEM FROM SCRATCH");

    huguinx_logs("KERNEL INITIALIZED WITH SUCCESS\n\n");
    
	memset(gdt_real, 0x00, sizeof(gdt_real));
	gdt_structured_to_gdt(gdt_real, gdt_structured, HUGUINX_TOTAL_GDT_SEGMENTS);

	gdt_load(gdt_real, sizeof(gdt_real));
	
huguinx_logs("GDT INITIALIZED WITH SUCCESS");
huguinx_logs("TSS INITIALIZED WITH SUCCESS");

memset(&tss, 0x00, sizeof(tss));
tss.esp0 = 0x600000;
tss.ss0 = KERNEL_DATA_SELECTOR;

tss_load(0x28);

  huguinx_logs("VGA INITIALIZED WITH SUCCESS");
    idt_init();
   huguinx_logs("IDT INITIALIZED WITH SUCCESS");

	// enable_interrupts();

	// char disk_buf[512];
	// disk_read_sector(0, 1, disk_buf); // Reads 1 sector of the Hard drive

	// for (int i = 0; i < 512; i++) {
	//	huguinx_perfectchar(disk_buf[i], 15);
	// }

	init_serial();
	
	huguinx_logs("HELLO FROM Huguinx OPERATING SYSTEM"); // THIS WRITES IN SERIAL AND IN VGA
	
	// huguinx_logs("THIS IS JUST AN EXAMPLE OF A LOG IN Huguinx OPERATING SYSTEM");

	huguinx_logs("KEYBOARD INITIALIZED WITH SUCCESS");
	row_plus();
	row_plus();
	huguinx_logs("Type <help> to see all the available commands");
	row_plus();
	row_plus();
	row_plus();
	row_plus();
	huguinx_print("# ");
	write_serial_string("\n\n");
	write_serial_string("# ");

	// tss_load(0x28);
	// init_keyboard(); // WARNING: THIS FUNCTIONS USES MANUAL POLLING, THIS RUNS AN INFINITE LOOP THAT CHECKS THE STATUS OF THE KEYBOARD AND THE SCANCODE

	int divi = 40 / 0;
	
	row_plus();
	
	huguinx_print("# ");
	write_serial_string("# ");

    // huguinx_xychar(50, 50, 'A', 15);

    /* init_keyboard(); */
        
   while(1) {
	__asm__ __volatile__("sti");
   }

}
