; Author: Huguini79
; GDT Implementation

section .text

global gdt_load

gdt_load:
	mov eax, [esp + 4]
	lgdt [eax]
	ret
