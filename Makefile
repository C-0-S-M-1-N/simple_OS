## deprecated

CXX		 	:= i386-elf-g++ #C++ compiler path 
CXXFLAGS   	:= -c -m32 -O0 \
			   -ffreestanding \
			   -I./src/incl/ -g
CXXLINK  	:= -Ttext 0x1000 --oformat binary
# OBJS 	:= $(patsubst $(SRC)/%.cpp,$(OBJ)/%.cpp.o,$(filter %.cpp,$(SRCS)))

#end_deprecated

CC 			:= i386-elf-gcc
LD 		 	:= i386-elf-ld  #linker path
NASM 	 	:= nasm			#nasm path

CFLAGS 		 = -c -m32 -O0 \
			   -ffreestanding -nostdlib -nostartfiles \
			   -I./src/ 

LDFLAGS 	:= -Ttext 0x1000 --oformat binary -t

ASM 	:= ./asm
ASMS 	:= $(shell find ./asm -name "*.asm")

BIN		:= ./bin
BINS	:= boot.bin kernel.bin
BINS 	:= $(addprefix $(BIN)/,$(BINS))

SRC 	:= ./src
SRCS 	:= $(shell find ./src -name '*.c' -not -path './src/cppsrcs-deprecated')

OBJ 	:= ./link
OBJS 	:= $(patsubst $(SRC)/%.c,$(OBJ)/%.c.o,$(filter %.c,$(SRCS)))

.PHONY: all clean run compile

all: compile run

compile: OS.bin

OS.bin: $(BINS) | $(BIN) $(OBJ)
	cat bin/boot.bin bin/kernel.bin > /tmp/ostmp.bin
	dd if=/dev/zero of=OS.bin bs=512 count=30
	dd if=/tmp/ostmp.bin of=OS.bin conv=notrunc

$(BIN)/boot.bin: $(ASM)/boot.asm | $(BIN)
	@$(NASM) $^ -o $@ -f bin
	@echo "making $@"

$(BIN)/kernel.bin: $(OBJ)/kernel.asm.o $(OBJS) | $(BIN)
	@$(LD) $^ -o $@ $(LDFLAGS)
	@echo "making $@"

$(OBJ)/kernel.asm.o: $(ASM)/kernel.asm | $(OBJ)
	@$(NASM) $^ -o $@ -f elf
	@echo "making $@"

$(OBJ)/%.cpp.o: $(SRC)/%.cpp | $(OBJ) 	## deprecated
	@mkdir -p $(@D) 					## deprecated	
	@$(CXX) $^ -o $@ $(CXXFLAGS) 		## deprecated
	@echo "making $@" 					## deprecated

$(OBJ)/%.c.o: $(SRC)/%.c | $(OBJ)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(CFLAGS)

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
	
