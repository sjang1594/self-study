%include "io64.inc"

section .text
global CMAIN
CMAIN:
    mov rbp, rsp
    ; function (Procedure subroutine)
    call PRINT_MSG
    
    xor rax, rax
    ret

PRINT_MSG:
    PRINT_STRING msg
    NEWLINE
    ret
    
    ; what if the number of parameter is 10? a b c d
    ; what if there is important value in 
    ; [!] use .data .bss
    ; then how many parameter do we have to use.
    
    ; 다른 메모리 구조가 필요하다
    ; - 꿈이 유효한 동안에는 그 꿈을 유지시켜야 함 (유효 범위의 개념이 있다)
    ; - 꿈이 끝나면 그 꿈을 부셔버려도 됨 (정리의 개념이 있다)
    ; - 꿈에서도 또 꿈을 꿀 수 있다는 것을 고려해야 함 (유동적으로 유효범위가 확장 가능)
    
    ; [!] use stack memory
    ; 함수가 사용하는 일종의 메모장
    ; - 매개 변수 전달
    ; - 돌아갈 주소 관리
    
section .data
    msg db 'Hello World', 0x00
    dd a 0
    dd b 0
    dd c 0