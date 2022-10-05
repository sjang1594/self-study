%include "io64.inc"

section .text
global CMAIN
CMAIN:
    mov rbp, rsp; for correct debugging
    ; 8 bit = 1 byte
    ; 16 bit = 2 byte = 1 word
    ; 32 bit = 4 byte = 2 word = 1 dword(double-word)
    ; 64 bit = 8 byte = 4 word = 1 qword (quad-word)
    
    ; move reg1, cst
    ; move reg1, reg2
    mov eax, 0x1234
    mov rbx, 0x12345678
    mov cl, 0xff
    
    mov al, 0x00
    ;mov rax, rdx
    
    ; Memory <-> Register
    ;mov rax, a ; copy the address of a.
    ;mov rax, [a] ; copy the value of an a.
    mov al, [a] ; size of a into 1 byte
    
    mov [a], byte 0x55
    mov [a], word 0x6666
    mov [a], cl
    
    xor rax, rax
    ret
 
    ; variable declaration and usage
    ; variable is just the placeholder to hold the data.
    ; - declare that placeholder is going to be used (its name & size)
    
    ; memory has distinguishable address
    ; initialzed data
    ; [Variable name] [size] [initiailzed value]
    ; [size] db(1) dw(2) dd(4) dq(8) 
    
section .data
    a db 0x11  ; [0x11]
    b dw 0x2222
    c dd 0x333333
    d dq 0x444444444444
    
    ; uninitialized data
    ; [variable name] [its size] [the number of its value]
    ; [size] resb(1) resw(2) resd(4) resq(8)
section .bss
    e resb 10
    