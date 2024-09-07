mkdir -p isodir/boot/grub
cp kernel.elf isodir/boot/kernel.elf

cat > isodir/boot/grub/grub.cfg << EOF
menuentry "My Kernel" {
    multiboot /boot/kernel.elf
}
EOF

grub-mkrescue -o mykernel.iso isodir
