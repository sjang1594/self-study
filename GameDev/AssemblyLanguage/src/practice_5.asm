%include "io64.inc"

section .text
global CMAIN
CMAIN:
    ;write a code that return max after comparing the two values
    mov eax, 10
    mov ebx, 5
    call MAX
    PRINT_DEC 4, ecx
    NEWLINE
    
    xor rax, rax
    ret

MAX:
    cmp eax, ebx
    jg L1
    mov ecx, ebx
    jmp L2

L1:
    mov ecx, eax

L2:
    ret