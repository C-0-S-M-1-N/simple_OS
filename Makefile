all: boot kernelo maino link run



boot: asm/boot.asm
	nasm asm/boot.asm -o bin/boot.bin -f bin
kernelo: asm/kernel.asm
	nasm asm/kernel.asm -o link/kernel.o -f elf 
maino: src/main.cpp src/include/stdio.cpp 
	i386-elf-g++ src/main.cpp -c -m32 -g -o link/main.o -ffreestanding -O2 -fno-exceptions -fno-rtti
	i386-elf-g++ src/include/stdio.cpp -c -m32 -g -o link/stdio.o 
link: link/kernel.o 
	i386-elf-ld link/main.o link/stdio.o -o main.o
	i386-elf-ld link/kernel.o link/main.o -Ttext 0x1000 -o bin/kernel.bin --oformat binary
	cat bin/boot.bin bin/kernel.bin bin/zero.bin > OS.bin 
run:
	qemu-system-x86_64 -drive format=raw,file="OS.bin",index=0 -m 1G

