section .multiboot
align 4
    dd 0x1BADB002             ; Magic number
    dd 0x0                    ; Flags
    dd -(0x1BADB002 + 0x0)    ; Checksum

section .text
global _start
_start:
    ; Call kernel_main defined in kernel.c
    extern kernel_main
    call kernel_main

    ; Infinite loop to keep the kernel running
hang:
    cli
    hlt
    jmp hang
