#!/bin/bash
nasm -f elf32 multiboot_header.asm -o multiboot_header.o
gcc -m32 -ffreestanding -fno-stack-protector -mno-sse -c kernel.c -o kernel.o
ld -m elf_i386 -T linker.ld -o kernel.elf multiboot_header.o kernel.o


mkdir -p isodir/boot/grub
cp kernel.elf isodir/boot/kernel.elf

grub-mkrescue -o mykernel.iso isodir
