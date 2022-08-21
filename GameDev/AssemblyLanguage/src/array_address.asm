%include "io64.inc"

section.text
global CMAIN
CMAIN:
  mov rbp, rsp; for correction debugging.

  ; Array and Address
  ; Array: 동일한 타입의 데이터의 묶음
  ; - 배열을 구성하는 각 값을 배열 요소 (element) 이라고 함
  ; - 배열의 위치를 가르키는 숫자를 인덱스(index)라고 함
  mov rax, a ; a 에 대한 value 가 들어가는게 아니라, 주소 값이 들어간다.

  PRINT_HEX 1, [a]
  NEWLINE
  PRINT_HEX 1, [a+1]
  NEWLINE
  PRINT_HEX 1, [a+2]
  NEWLINE

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
