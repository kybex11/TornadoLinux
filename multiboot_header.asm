section .multiboot
align 4
    dd 0x1BADB002             ; Magic number (must be 0x1BADB002)
    dd 0x0                    ; Flags (no features required)
    dd -(0x1BADB002 + 0x0)    ; Checksum (magic + flags + checksum should equal 0)

section .text
global _start
_start:
    ; This is the entry point of the kernel
