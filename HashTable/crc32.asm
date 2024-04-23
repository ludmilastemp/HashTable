
global CRC32ASM

section .text
CRC32ASM:

;       movzx   edx, BYTE [rdi]      
        mov     eax, -1

.for
        movzx   edx, BYTE [rdi]
        test    dl, dl
        je      .ret
        
        crc32   eax, dl

        add     rdi, 1
        jmp     .for

.ret:
        not     eax
        ret


