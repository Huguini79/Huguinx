; Author: Huguini79
; TSS (Task State Segment) implementation

section .asm

global tss_load

tss_load:
	push ebp
	mov ebp, esp

	mov ax, [ebp + 8] ; TSS Segment (we define it in the GDT <- General Descriptors Table)
	ltr ax ; Load the TSS (Task State Segment) into the CPU
        pop ebp

	ret
