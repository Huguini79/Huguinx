global pit_irq_handler_asm

pit_irq_handler_asm:
    pusha
    call pit_irq_handler
    popa
    mov al, 0x20
    out 0x20, al
    iret