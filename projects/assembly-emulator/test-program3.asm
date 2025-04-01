%include <assembly.cpp>

segment .data

segment .bss

segment .text
    global asm_main

asm_main:
    mov eax, 100
    mov ebx, 200

    add eax, 30
    add ebx, eax

    mov eax, ebx
    
    call print_int
    call print_nl
    call print_nl

    call reg_dump