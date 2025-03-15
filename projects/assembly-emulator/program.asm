%include <assembly.cpp>

segment .data

segment .bss

segment .text
    global asm_main

asm_main:
    mov ax, 10
    mov bx, 20

    movsx eax, ebx

    call reg_dump