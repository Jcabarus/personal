%include <assembly.cpp>

segment .data

segment .bss

segment .text
    global asm_main

asm_main:
    mov eax, 0
    inc eax
    dec eax

    call print_int
    call print_nl