%include "io64.inc"

section .text
global CMAIN
CMAIN:
    
    ; practice) sum all up to 100
    mov eax, 100
    xor ebx, ebx ; mov ebx, 0 ebx: result
    xor ecx, ecx
    
LABEL_SUM:
    inc ecx ;add ecx, 1
    add ebx, ecx ; ebx = ebx + ecx
    cmp ecx, eax
    jne LABEL_SUM
    
    PRINT_DEC 4, ebx
    NEWLINE
    
    
    xor rax, rax
    ret