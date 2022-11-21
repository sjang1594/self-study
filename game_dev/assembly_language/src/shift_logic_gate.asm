%include "io64.inc"

section .text
global CMAIN
CMAIN:
    mov rbp, rsp; for correct debugging
    ; shift op, logical op
    
    mov eax, 0x12345678
    PRINT_HEX 4, eax
    NEWLINE
    shl eax, 8 ; move right
    PRINT_HEX 4, eax
    NEWLINE
    shl eax, 8 ; move right
    PRINT_HEX 4, eax
    NEWLINE
    ; Advantages : multiplication / division
    ; On game server, 64 bit is used for creating the Object ID
    
    ; not and or xor
    mov al, 0b10010101
    mov b1, 0b01111100
    
    and al, bl ; al = al and bl
    PRINT_HEX 1, al
    NEWLINE
    
    not al
    PRINT_HEX 1, al
    NEWLINE
    
    xor al, al
    PRINT_HEX 1, al ; xor op on itself returns 0
    xor rax, rax
    ret