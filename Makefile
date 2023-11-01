
CXX		 	:= i386-elf-g++ #C++ compiler path 
CXXFLAGS   	:= -c -m32 -O0 -g \
			   -ffreestanding -nostdlib -nostartfiles \
			   -I./src/incl/ 

CC 			:= i386-elf-gcc
LD 		 	:= i386-elf-ld  #linker path
NASM 	 	:= nasm			#nasm path

CFLAGS 		 = -c -m32 -O0 -g \
			   -ffreestanding -nostdlib -nostartfiles \
			   -I./src/ 

LDFLAGS 	:= -Ttext 0x1000 --oformat binary -t

ASM 	:= ./asm
ASMS 	:= $(shell find ./asm -name "*.asm")

BIN		:= ./bin
BINS	:= boot.bin kernel.bin
BINS 	:= $(addprefix $(BIN)/,$(BINS))

SRC 	:= ./src
SRCS 	:= $(shell find ./src -name '*.cpp' )

OBJ 	:= ./link
OBJS 	:= $(patsubst $(SRC)/%.cpp,$(OBJ)/%.cpp.o,$(filter %.cpp,$(SRCS)))

.PHONY: all clean run compile

all: compile run

compile: OS.bin

OS.bin: $(BINS) | $(BIN) $(OBJ)
	cat bin/boot.bin bin/kernel.bin > /tmp/ostmp.bin
	dd if=/dev/zero of=OS.bin bs=512 count=40
	dd if=/tmp/ostmp.bin of=OS.bin conv=notrunc

$(BIN)/boot.bin: $(ASM)/boot.asm | $(BIN)
	@echo "--- NASM ---"
	$(NASM) $^ -o $@ -f bin -g
	@echo "--- NASM END ---"

$(BIN)/kernel.bin: $(OBJ)/kernel.asm.o $(OBJS) | $(BIN)
	@echo "--- LD ---"
	$(LD) $^ -o $@ $(LDFLAGS)
	@echo "--- LD END ---"

$(OBJ)/kernel.asm.o: $(ASM)/kernel.asm | $(OBJ)
	@echo "--- NASM ---"
	$(NASM) $^ -o $@ -felf -g
	@echo "--- NASM END ---"

$(OBJ)/%.c.o: $(SRC)/%.c | $(OBJ)
	@echo "--- GCC ---"
	@mkdir -p $(@D)
	(CC) $^ -o $@ $(CFLAGS)
	@echo "--- GCC END ---"

$(OBJ)/%.cpp.o: $(SRC)/%.cpp | $(OBJ) 	
	@echo "--- G++ ---"
	@mkdir -p $(@D) 					
	$(CXX) $^ -o $@ $(CXXFLAGS) 		
	@echo "--- G++ END ---"

$(OBJ):
	-mkdir -p $@
$(BIN):
	-mkdir -p $@

clean:
	@rm -rvf $(OBJ)
	@rm -rvf $(BIN)
	@rm -rv OS.bin

debug: compile
	qemu-system-x86_64 -S -s -drive format=raw,file="OS.bin",index=0,if=floppy -m 512M

run:
	qemu-system-x86_64 -d cpu_reset -drive format=raw,file="OS.bin",index=0,if=floppy -m 128M
	



