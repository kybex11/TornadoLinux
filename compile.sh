# Компиляция C-кода
gcc -m32 -ffreestanding -c kernel.c -o kernel.o

# Компиляция Multiboot заголовка
nasm -felf32 multiboot_header.asm -o multiboot_header.o

# Линковка
ld -m elf_i386 -T linker.ld multiboot_header.o kernel.o -o kernel.elf
