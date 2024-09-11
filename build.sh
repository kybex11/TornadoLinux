#!/bin/bash

# Assemble the multiboot header
nasm -f elf32 multiboot_header.asm -o multiboot_header.o

# Compile all C files with GCC
gcc -m32 -ffreestanding -fno-stack-protector -mno-sse -c kernel.c -o kernel.o
gcc -m32 -ffreestanding -fno-stack-protector -mno-sse -c io.c -o io.o
gcc -m32 -ffreestanding -fno-stack-protector -mno-sse -c commands.c -o commands.o
gcc -m32 -ffreestanding -fno-stack-protector -mno-sse -c keyboard.c -o keyboard.o

# Link all object files together into the kernel
ld -m elf_i386 -T linker.ld -o kernel.elf multiboot_header.o kernel.o io.o commands.o keyboard.o

# Create the ISO directory structure
mkdir -p isodir/boot/grub

# Copy the kernel binary to the ISO directory
cp kernel.elf isodir/boot/kernel.elf

# Create a GRUB configuration file
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "TornadoLinux" {
    multiboot /boot/kernel.elf
}
EOF

# Build the bootable ISO image with GRUB
grub-mkrescue -o mykernel.iso isodir
