; Author: Huguini79
; IDT implementation

section .text

extern int21h_handler
extern no_interrupt_handler
extern mouse_handler_c

global int21h
global idt_load
global no_interrupt
global enable_interrumpts
global disable_interrumpts

global mouse_handler
mouse_handler:
    pusha
    call mouse_handler_c
    popa
    iretd


enable_interrumpts:
	sti
	ret
	
disable_interrumpts:
	cli
	ret

idt_load:
	push ebp
	mov ebp, esp
	
	mov ebx, [ebp + 8]
	lidt [ebx]
	
	pop ebp
	ret


int21h:
	cli
	pushad
	call int21h_handler
	popad
	sti
	iret
	
no_interrupt:
	cli
	pushad
	call no_interrupt_handler
	popad
	sti
	iret
