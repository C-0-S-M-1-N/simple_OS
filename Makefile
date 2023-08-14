CXX		 	:= g++ #C++ compiler path
CXXLINKER 	:= ld  #linker path
NASM 	 	:= nasm			#nasm path
CXXFLAGS   	:= -c -m32 -O0 \
			   -ffreestanding -fno-exceptions -fno-rtti \
			   -I./src/incl/ \
			   -nostdinc -nostdinc++
CXXLINK  	:= -Ttext 0x1000 --oformat binary -m32

ASM 	:= ./asm
ASMS 	:= $(shell find ./asm -name "*.asm")

BIN		:= ./bin
BINS	:= boot.bin kernel.bin zero.bin
BINS 	:= $(addprefix $(BIN)/,$(BINS))

SRC 	:= ./src
SRCS 	:= $(shell find ./src -name '*.cpp' -or -name '*.c')

OBJ 	:= ./link
OBJS 	:= $(patsubst $(SRC)/%.cpp,$(OBJ)/%.cpp.o,$(filter %.cpp,$(SRCS))) \
		   $(patsubst $(SRC)/%.c,$(OBJ)/%.c.o,$(filter %.c,%(SRCS)))

.PHONY: all clean run
all: OS.bin | $(BIN) $(OBJ)
# all: 
# 	@echo "ASMS: $(ASMS)"
# 	@echo "SRCS: $(SRCS)"
# 	@echo "OBJS: $(OBJS)"
# 	@echo "BINS: $(BINS)"


OS.bin: $(BINS) | $(BIN) $(OBJ)
	cat $^ > OS.bin	
	dd if=OS.bin of=OS.img

# $(BIN)/%.bin: $(ASM)/%.asm | $(BIN)
# 	@touch $@
# 	$(NASM) $^ -o $@ -f bin

$(BIN)/boot.bin: $(ASM)/boot.asm | $(BIN)
	-touch $@
	@$(NASM) $^ -o $@ -f bin

$(BIN)/kernel.bin: $(OBJS) $(OBJ)/kernel.asm.o | $(BIN)
	@$(CXXLINKER) $^ -o $@ $(CXXLINK)

$(BIN)/zero.bin: $(ASM)/zero.asm | $(BIN)
	@$(NASM) $^ -o $@ -f bin 
# $(BIN)/kernel.bin: $(OBJS) $(OBJ)/kernel.o | $(BIN)
# 	@$(CL) $^ -o $@ $(LFLAGS)

$(OBJ)/kernel.asm.o: $(ASM)/kernel.asm | $(OBJ)
	@$(NASM) $^ -o $@ -f elf

# $(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
# 	@$(CC) $^ -o $@ $(CFLAGS)
$(OBJ)/%.cpp.o: $(SRC)/%.cpp | $(OBJ)
	@mkdir -p $(@D)
	@$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJ)/%.c.o: $(SRC)/%.c | $(OBJ)
	@mkdir -p $(@D)
	@$(CXX) $^ -o $@ $(CXXFLAGS)

$(OBJ):
	-mkdir -p $@
$(BIN):
	-mkdir -p $@

clean:
	@rm -rf $(OBJ)
	@rm -rf $(BIN)

# all: compile 
# 
# compile: boot kernelo maino link
# 
# boot: asm/boot.asm
# 	nasm asm/boot.asm -o bin/boot.bin -f bin
# kernelo: asm/kernel.asm
# 	nasm asm/kernel.asm -o link/kernel.o -f elf 
# maino: src/main.cpp src/include/stdio.cpp 
# 	i386-elf-g++ src/main.cpp -c -m32 -g -o link/main.o -O0 -ffreestanding -fno-exceptions -fno-rtti
# link: link/kernel.o link/main.o link/stdio.o
# 	i386-elf-ld link/kernel.o link/main.o -Ttext 0x1000 -o bin/kernel.bin --oformat binary
# 	cat bin/boot.bin bin/kernel.bin bin/zero.bin > OS.bin 
run:
# 	qemu-system-x86_64 -fda OS.fld
# 	qemu-system-x86_64 -drive format=raw,file="OS.bin",index=0 -m 1000
	qemu-system-i386 -hda OS.img
	
