; Author: Huguini79
; I/O Driver implementation

global insb
global insw
global inl
global outb
global outw
global outl

; 8 bit function
insb:
	push ebp
	mov ebp, esp
	
	xor eax, eax
	mov edx, [ebp + 8] ; PORT
	in al, dx
	
	pop ebp
	ret
	
; 16 bit function (WORD)
insw:
	push ebp
	mov ebp, esp
	
	xor eax, eax
	mov edx, [ebp + 8] ; PORT
	in ax, dx
	
	pop ebp
	ret

; 8 bit function
outb:
	push ebp
	mov ebp, esp
	
	xor eax, eax
	mov eax, [ebp + 12] ; DATA
	mov edx, [ebp + 8] ; PORT
	out dx, al
	
	pop ebp
	ret

; 16 bit function (WORD)
outw:
	push ebp
	mov ebp, esp
	
	xor eax, eax
	mov eax, [ebp + 12] ; DATA
	mov edx, [ebp + 8] ; PORT
	out dx, ax
	
	pop ebp
	ret

; 32 bit function (DWORD)
inl:
	push ebp
	mov ebp, esp
	
	xor eax, eax
	mov edx, [ebp + 8]
	in eax, dx
	
	pop ebp
	ret
	
; 32 bit function (DWORD)
outl:
	push ebp
	mov ebp, esp
	
	xor eax, eax
	mov eax, [ebp + 12]
	mov edx, [ebp + 8]
	out dx, eax
	
	pop ebp
	ret
