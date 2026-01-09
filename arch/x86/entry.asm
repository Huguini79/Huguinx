BITS 32

section .text

; GRUB MULTIBOOT
align 4
dd 0x1BADB002
dd 0x00
dd - (0x1BADB002 + 0x00)

global start
extern kernel_main

CODE_SEG equ 0x08
DATA_SEG equ 0x10

start:
	cli
	in al, 0x92
	or al, 2
	out 0x92, al
	call kernel_main
	
	mov al, 00010001b
	out 0x20, al
	
	mov al, 0x20
	out 0x21, al
	
	mov al, 00000001b
	out 0x21, al
	
	hlt

section .bss
stack_space: resb 65536 ; 64 KB of STACK
