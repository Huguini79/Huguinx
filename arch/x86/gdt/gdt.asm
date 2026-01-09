; Author: Huguini79
; GDT Implementation

section .text

global gdt_load

gdt_load:
	mov eax, [esp + 4] ; GDT Size
	mov [gdt_descriptor + 2], eax
	mov ax, [esp + 8] ; GDT Start Address
	mov [gdt_descriptor], ax
	lgdt [gdt_descriptor]
	ret

gdt_descriptor:
	dw 0x00 ; Size
	dd 0x00 ; Gdt Start address
