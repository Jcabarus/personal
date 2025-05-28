%include <assembly.cpp>

segment .data

segment .bss

segment .text
    global asm_main

asm_main:
    mov ax, 10
    mov dx, 6
    sub ax, dx
    sub ax, dx
    
    movsx eax, ax

    call print_int
    call print_nl