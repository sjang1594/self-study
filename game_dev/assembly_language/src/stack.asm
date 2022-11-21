%include "io64.inc"

section .text
global CMAIN
CMAIN:
    mov rbp, rsp; for correct debugging
    
    ; stack memory and stack frame
    
    ; 레지스터는 다양한 용도로 사용
    ; - a b c d 범용 레지스터
    ; - 포인터 레지스터 (포인터 = 위치를 가르키는~)
    ; -- ip (Instruction Pointer) : 다음 수행 명령어의 위치
    ; -- sp (Stack Pointer) : 현재 스택 top 위치 (일종의 cursor)
    ; -- bp (Base Pointer) : 스택 상대주소 계산용
    push rax
    push rbx
    push 1
    push 2
    call MAX
    PRINT_DEC 8, rax
    NEWLINE
    add rsp, 16
    pop rbx
    pop rax
    
    xor rax, rax
    ret

MAX:
    push rbp
    mov rbp, rsp
    mov rax, [rbp+16]
    mov rbx, [rbp+24]
    cmp rax, rbx
    jg L1
    mov rax, rbx

L1:
    pop rbp
    ret
section .data