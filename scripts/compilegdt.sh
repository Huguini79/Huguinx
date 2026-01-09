nasm -f elf32 arch/x86/gdt/gdt.asm -o build/gdt.asm.o
gcc -I./ -m32 -ffreestanding -nostdlib -c arch/x86/gdt/gdt.c -o build/gdt.o
