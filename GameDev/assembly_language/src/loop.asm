%include "io64.inc"

section .text
global CMAIN
CMAIN:
    ; Loop (while, for)
    ; if the specific condition met, loop
    
    ; ex) Hellow World 10 times
    mov ecx, 10

LABEL_LOOP:
    PRINT_STRING msg
    NEWLINE
    dec ecx ;sub ecx, 1 
    cmp ecx, 0
    jne LABEL_LOOP
    
    ; loop [label]
    ; - ecx 에 반복 횟수
    ; - loop 할때마다 ecx 1 감소 0 이면 빠져나감, 아니면 라벨로 이동
    mov ecx, 100
    xor ebx, ebx
LABEL_LOOP_SUM:
    add ebx, ecx
    loop LABLE_LOOP_SUM    
    
    PRINT_DEC 4, ebx
    NEWLINE
    
    xor rax, rax
    ret
section .data
    msg db 'Hello World', 0x00