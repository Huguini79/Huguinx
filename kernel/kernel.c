// Author: Huguini79
// KERNEL IMPLEMENTATION
#include "libc/stdio.h"
#include "drivers/vga/vga.h"
#include "kernel/kernel.h"
#include "drivers/io/io.h"
#include "drivers/serial/serial.h"

/*

#include "drivers/keyboard/keyboard.h"
#include "drivers/memory/heap/heap.h"
#include "drivers/memory/paging/paging.h"
#include "drivers/keyboard/keyboard.h"
#include "arch/x86/idt/idt.h"
#include "arch/x86/gdt/gdt.h"
#include "arch/x86/tss/tss.h"

*/

void kernel_main() {
    huguinx_init_screen();
    
    huguinx_print("Huguinx - 1.0 | Huguini79 (https://github.com/Huguini79/Huguinx)\n");

    huguinx_logs("KERNEL INITIALIZED WITH SUCCESS");
    huguinx_logs("VGA INITIALIZED WITH SUCCESS");

	init_serial();
	
	huguinx_logs("HELLO FROM Huguinx OPERATING SYSTEM"); // THIS WRITES IN SERIAL AND IN VGA
	
	huguinx_logs("THIS IS JUST AN EXAMPLE OF A LOG IN Huguinx OPERATING SYSTEM");

    // huguinx_xychar(50, 50, 'A', 15);

    /* init_keyboard(); */

}
