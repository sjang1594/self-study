%include "io64.inc"

section.text
global CMAIN
CMAIN:
    mov rbp, rsp; for correction debugging.

    mov rax, a ; a 에 대한 value 가 들어가는게 아니라, 주소 값이 들어간다.
    
    xor ecx, ecx

LABEL_PRINT_B:
    PRINT_HEX 2, [b+ecx*2] ; 2bytes 씩 가야하므로
    NEWLINE
    inc ecx
    cmp ecx, 5
    jne LABEL_PRINT_B
    
    ;0x00 0x01
    ; --> Little Radian 
    ; --> 0x0100
    ; --> 100
    xor rax, rax
    ret

section .data
  ; [Size] db(1), dw(2), dd(4) dq(8)
  msg db 'Hello World', 0x00
  a db 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 ; array, 5 * 1 = 5 bytes

  ; 0x01 0x00 (little redian) --> 0x0001 (word)
  b times 5 dw 1 ;5 개의 element 의 2 bytes 크기를, 초기갑은 1로 시킨다. --> 5 * 2 = 10 bytes

section .bss
  num resb 1
