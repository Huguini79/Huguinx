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
#include "drivers/mouse/mouse.h"
#include "pit/pit.h"
#include "drivers/memory/heap/heap.h"

#include "config.h"

/*

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
    huguinx_print("X86 OPERATING SYSTEM FROM SCRATCH\n\n");

    huguinx_print("[ OK ] KERNEL\n");
    
	memset(gdt_real, 0x00, sizeof(gdt_real));
	gdt_structured_to_gdt(gdt_real, gdt_structured, HUGUINX_TOTAL_GDT_SEGMENTS);

	gdt_load(gdt_real, sizeof(gdt_real));
	
huguinx_print("[ OK ] GDT\n");
huguinx_print("[ OK ] TSS\n");

memset(&tss, 0x00, sizeof(tss));
tss.esp0 = 0x600000;
tss.ss0 = KERNEL_DATA_SELECTOR;

tss_load(0x28);

  huguinx_print("[ OK ] VGA\n");
    idt_init();
   huguinx_print("[ OK ] IDT\n");
	disk_search_and_init();
	huguinx_print("[ OK ] DISK DRIVER\n");

	// enable_interrupts();

	// char disk_buf[512];
	// disk_read_sector(0, 1, disk_buf); // Reads 1 sector of the Hard drive

	// for (int i = 0; i < 512; i++) {
	//	huguinx_perfectchar(disk_buf[i], 15);
	// }

	init_serial();
		
	// huguinx_print("THIS IS JUST AN EXAMPLE OF A LOG IN Huguinx OPERATING SYSTEM");

	huguinx_print("[ OK ] KEYBOARD\n");
	huguinx_print("[ OK ] MOUSE\n");
	heap_init();
	huguinx_print("[ OK ] HEAP");
	row_plus();
	row_plus();
	huguinx_print("HELLO FROM Huguinx OPERATING SYSTEM\nBE CAREFULL WITH THE DISK DRIVER\n");
	huguinx_print("Type <help> to see all the available commands\n\n\n\n");
	huguinx_print("# ");
	write_serial_string("\n\n");
	write_serial_string("# ");

	// tss_load(0x28);
	// init_keyboard(); // WARNING: THIS FUNCTIONS USE MANUAL POLLING, THIS RUNS AN INFINITE LOOP THAT CHECKS THE STATUS OF THE KEYBOARD AND THE SCANCODE

	int divi = 40 / 0;
	
	mouse_install();

	row_plus();
	
	huguinx_print("# ");
	write_serial_string("# ");

	pit_init();

    // huguinx_xychar(50, 50, 'A', 15);

    /* init_keyboard(); */
        
	enable_interrumpts();

	while(1) {
		__asm__("hlt");
	}

}

/* TIP: Use row_plus() instead of \n */