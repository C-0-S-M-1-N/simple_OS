nasm asm/boot.asm -o bin/boot.bin -f bin &&

nasm asm/kernel.asm -o link/kernel.o -f elf &&
nasm asm/zero.asm -o bin/zero.bin -f bin &&
i386-elf-g++ src/main.cpp -c -m32 -g -o link/main.o -ffreestanding &&

i386-elf-ld link/kernel.o link/main.o -Ttext 0x1000 -o bin/kernel.bin --oformat binary &&

cat bin/boot.bin bin/kernel.bin bin/zero.bin > OS.bin &&

qemu-system-x86_64 -drive format=raw,file="OS.bin",if=floppy,index=0
