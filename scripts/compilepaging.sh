nasm -f elf32 drivers/memory/paging/paging.asm -o build/paging.asm.o
gcc -I./ -m32 -ffreestanding -nostdlib -c drivers/memory/paging/paging.c -o build/paging.o