%include "io64.inc"

section .text
global CMAIN
CMAIN:
    mov rbp, rsp; for correct debugging
    
    GET_DEC 1, al ; get decimal value into al (register)
    GET_DEC 1, num
    
    ;PRINT_DEC 1, al
    ;NEWLINE
    ;PRINT_DEC 1, num
    
    ; Add Operation
    ; add a, b ( a = a + b)
    ; a is register or memory
    ; b is register or memory or constant value
    ; but, a and b can't be memory
    
    ; sub operation
    ; sub a, b (a = a - b)
    add al, 1; register + b
    PRINT_DEC 1, al ; 1+1 = 2
    NEWLINE
    
    add al, [num] ; add al + the value of num (register + memory)
    PRINT_DEC 1, al ; 2+2=4
    NEWLINE
    
    mov b1, 3 ; register + register
    add al, bl ; 4+3=7
    PRINT_DEC 1, al
    NEWLINE
    
    add [num], byte 1 ; memory + constant
    PRINT_DEC 1, al ; 2+1=3
    NEWLINE
    
    add [num], al ; memory + register
    PRINT_DEC 1, al ; 3+7=10
    NEWLINE
    
    ; multiplication op
    ; mul reg
    ; - mul bl => al * bl
    ; -- save the result into ax
    ; - mul bx => ax * bx
    ; -- save the result into dx(상위 16 bits) ax(하위 16비트) 에 저장
    ; - mul ebx => eax + ebx
    
    ; ex) 5 * 8 ?
    mov ax, 0
    mov al, 5
    mov bl, 8
    mul bl 
    PRINT_DEC 2, ax
    NEWLINE
    
    ; division op
    ; div reg
    ; - div bl => ax / bl
    ; -- the quotient will save into al, remainder will save into ah
    mov ax, 100
    mov bl, 3
    div bl
    PRINT_DEC 1, al ; 100 / 3 = 33 * 3 + 1
    NEWLINE
    mov al, ah
    PRINT_DEC 1, al
    
    xor rax, rax
    ret

section .bss
    num resb 1