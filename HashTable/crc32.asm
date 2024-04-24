
global HashCRC32Asm

section .text
HashCRC32Asm:
   
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


