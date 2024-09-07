# Compile the C code and assembly to 32-bit object files
gcc -m32 -ffreestanding -c kernel.c -o kernel.o
nasm -felf32 multiboot_header.asm -o multiboot_header.o

# Link them together for a 32-bit architecture
ld -m elf_i386 -Ttext 0x100000 --oformat=elf32-i386 multiboot_header.o kernel.o -o kernel.elf

grub-mkrescue -o mykernel.iso isodir
