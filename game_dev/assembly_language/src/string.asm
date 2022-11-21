%include "io64.inc"

section .text
global CMAIN
CMAIN:
    mov rbp, rsp; for correct debugging
     
    xor rax, rax
    ret
 
section .data
    msg db 'Hello World', 0x00
    a db 0x11  ; [0x11]
    b dd 0x12345678
    
    ; Pros & Cons
    ; - big endian : fast to compare the number
    
    ; - little endian: fast for casting
    
section .bss
    e resb 10
    