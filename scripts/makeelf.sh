ld -m elf_i386 -T linker/linker.ld -o iso/boot/kernel build/vga.o build/kernel.o build/entry.asm.o build/serial.o build/io.asm.o build/idt.o build/idt.asm.o
