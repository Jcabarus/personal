%include <assembly.cpp>

segment .data

segment .bss

segment .text
    global asm_main

asm_main:
    mov eax, 10
    mov ax, -20
    
    call reg_dump