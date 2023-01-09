
all: compile 

compile: boot kernelo maino link

boot: asm/boot.asm
	nasm asm/boot.asm -o bin/boot.bin -f bin
kernelo: asm/kernel.asm
	nasm asm/kernel.asm -o link/kernel.o -f elf 
maino: src/main.cpp src/include/stdio.cpp 
	i386-elf-g++ src/main.cpp -c -m32 -g -o link/main.o -O0 -ffreestanding -fno-exceptions -fno-rtti
link: link/kernel.o link/main.o link/stdio.o
	i386-elf-ld link/kernel.o link/main.o -Ttext 0x1000 -o bin/kernel.bin --oformat binary
	cat bin/boot.bin bin/kernel.bin bin/zero.bin > OS.bin 
run:
	qemu-system-x86_64 -drive format=raw,file="OS.bin",index=0 -m 1000
