// Author: Huguini79
// KERNEL IMPLEMENTATION
#include "libc/stdio.h"
#include "drivers/vga/vga.h"
#include "kernel/kernel.h"
/*

#include "drivers/keyboard/keyboard.h"
#include "drivers/memory/heap/heap.h"
#include "drivers/memory/paging/paging.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/io/io.h"
#include "arch/x86/idt/idt.h"
#include "arch/x86/gdt/gdt.h"
#include "arch/x86/tss/tss.h"

*/

void kernel_main() {
    huguinx_init_screen();

    huguinx_print("KERNEL INITIALIZED WITH SUCCESS");

    // huguinx_xychar(50, 50, 'A', 15);

    /* init_keyboard(); */

}