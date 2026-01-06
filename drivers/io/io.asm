global insb
global insw
global outb
global outw

; 16 bit function (WORD)
insb:
	push ebp
	mov ebp, esp
	
	xor eax, eax
	mov edx, [ebp + 8] ; PORT
	in al, dx
	
	pop ebp
	ret
	
; 32 bit function (DWORD)
insw:
	push ebp
	mov ebp, esp
	
	xor eax, eax
	mov edx, [ebp + 8] ; PORT
	in ax, dx
	
	pop ebp
	ret

; 16 bit function (WORD)
outb:
	push ebp
	mov ebp, esp
	
	xor eax, eax
	mov eax, [ebp + 12] ; DATA
	mov edx, [ebp + 8] ; PORT
	out dx, al
	
	pop ebp
	ret

; 32 bit function (DWORD)
outw:
	push ebp
	mov ebp, esp
	
	xor eax, eax
	mov eax, [ebp + 12] ; DATA
	mov edx, [ebp + 8] ; PORT
	out dx, ax
	
	pop ebp
	ret
