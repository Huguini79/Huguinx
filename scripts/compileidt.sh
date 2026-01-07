gcc -I./ -m32 -nostdlib -ffreestanding -c arch/x86/idt/idt.c -o build/idt.o
nasm -f elf32 arch/x86/idt/idt.asm -o build/idt.asm.o
