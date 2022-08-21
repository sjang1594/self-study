%include "io64.inc"

section .text
global CMAIN
CMAIN:
    mov ax, 100
    mov b1, 2
    div b1
    cmp ah, 0
    je L1
    mov rcx, 0
    jmp L2

L1:
    mov rcx, 1
L2:
    PRINT_HEX 1, rcx
    NEWLINE
    xor rax, rax
    ret