BITS 32

section .asm

global paging_load_directory
global enable_paging

paging_load_directory:
    push ebp
    mov ebp, esp
    
    mov eax, [ebp + 8] ; The page directory
    mov cr3, eax ; Load the page directory
    
    pop ebp
    ret

enable_paging:
    push ebp
    mov ebp, esp

    mov eax, cr0
    or eax, 0x80000000 ; Enable a bit (bit 31)
    mov cr0, eax ; Mov the modified value of eax, to cr0
    pop ebp
    ret