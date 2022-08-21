%include "io64.inc"

section .text
global CMAIN
CMAIN:
    mov rbp, rsp; for correct debugging
    
    ; if statement
    ; there are certain condition that we'd like to control.
    ; ex) if button for skill is clicked? yes -> use the skill.
    
    ; CMP dst, src (dst 기준)
    ; 비교를 한 결과물은 Flag Register 에 저장.
    
    ; JMP [label] series
    ; JMP : 무조건 jump
    ; JE  : JumpEquals 같으면 jump
    ; JNE : JumpNotEquals 다르면 jump
    ; JE  : JumpGreater 크면 jump
    ; JGE : JumpGreaterEquals 크거나 같으면 jump
    ; JL
    ; JLE 
    
    ; ex) if two number is same, return 1 otherwise 0.
    mov rax, 10
    mov rbx, 20
    
    cmp rax, rbx
    je LABEL_EQUAL
    
    ; je 에 의해 점프를 안했다면, 같지 않다는 의미
    mov rcx, 0
    jmp LABEL_EQUAL_END
    
LABEL_EQUAL:
    mov rcx, 1
LABEL_EQUAL_END:
    PRINT_HEX 1, rcx
    NEWLINE
    
    
    xor rax, rax
    ret