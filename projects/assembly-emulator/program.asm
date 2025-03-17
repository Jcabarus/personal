%include <assembly.cpp>

segment .data

segment .bss

segment .text
    global asm_main

asm_main:
    mov eax, 10
    mov ax, -20

    movsx eax, ax
    
    call print_int
    call print_nl