// IMPLEMENTAR FUNCIÓN DELETE EN MI DRIVER DEL TECLADO

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
#include "drivers/memory/paging/paging.h"

#include "config.h"

struct tss tss;

static struct paging* kernel_chunk_4gb = 0;
	
void kernel_main() {
    huguinx_init_screen();

    huguinx_print("Huguinx - 1.0 | Huguini79 (https://github.com/Huguini79/Huguinx)");
    row_plus();
    row_plus();
    huguinx_print("X86 OPERATING SYSTEM FROM SCRATCH\n\n");

    huguinx_print("[ OK ] KERNEL\n");
    
    CreateNullSegment(&gdt[0]);
    CreateCodeSegment(&gdt[1]);
    CreateDataSegment(&gdt[2]);

	gdt_load(&gdtr);

	huguinx_print("\n\n# ");

	init_keyboard();

    while (1) {
        __asm__("hlt");
    }
}	

/* TIP: Use row_plus() instead of \n */
