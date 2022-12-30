#ifndef KDB_TYPES__
#define KDB_TYPES__
#include "kbd_map.h"
#include "include/micell.cpp"

typedef unsigned short uint16_t;
typedef unsigned char uint8_t ;
typedef unsigned int uint32_t;
typedef char int8_t;
#define IDT_SIZE 256
#define KERNEL_CODE_SEGMENT_OFFSET 0x8
#define IDT_INTERRUPT_GATE_32BIT 0x8e
#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA2
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_TRAP_GATE_32BIT 0b10011111


/*

  idt attribute:

  7   6   5   4   3   2   1   0
+---+---+---+---+---+---+---+---+
| P |  DPL  | S |    GateType 	|
+---+---+---+---+---+---+---+---+
  7   6   5   4   3   2   1   0


(P)resent: 0 if is not used or paging

(D)escriptor (P)rivilage (L)evel: 00 -> 11

(S)torage segment: 0 for intterupts, 1 otherwise





Type:
 
+-BIN-+-HEX-+-DEC-+----------DESC----------+
|0101 |  5  |  5  |  32bit task gate	   |
|0110 |  6  |  6  |  16bit interrupt gate  |
|0111 |  7  |  7  |  16bit trap gate       |
|1110 |  E  | 14  |  32bit intterupt gate  |
|1111 |  F  | 15  |  32bit trap gate 	   |
+-----+-----+-----+------------------------+



*/

extern "C" void load_idt(unsigned int* idt_address);
extern "C" void keyboard_handler();
extern "C" char ioport_in(unsigned short port);
extern "C" void ioport_out(unsigned short port, unsigned char data);
extern "C" void enable_interrupts();
extern "C" void div0();


typedef struct{
	uint16_t isr_low;	//0..15 offset bits
	uint16_t kernel_cs;	//gdt/ldt code segment
	uint8_t  reserved; 	//just 0
	uint8_t	 attributes;//type of attributes
	uint16_t isr_high; 	//16..31 offset bits
} __attribute__((packed)) idt_entry_t;

typedef struct{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idtr_t;
__attribute__((aligned(0x10)))
static idt_entry_t idt[256]; //idt enteryes



void idt_init(){
	uint32_t offset = (uint32_t)keyboard_handler;
	idt[0x21].isr_low = offset & 0x0000FFFF;
	idt[0x21].kernel_cs = KERNEL_CODE_SEGMENT_OFFSET;
	idt[0x21].reserved = 0;
	idt[0x21].attributes = IDT_INTERRUPT_GATE_32BIT;
	idt[0x21].isr_high = (offset & 0xFFFF0000) >> 16;


	offset = (uint32_t)div0;
	idt[0x00].isr_low = offset & 0x0000FFFF;
	idt[0x00].kernel_cs = KERNEL_CODE_SEGMENT_OFFSET;
	idt[0x00].reserved = 0;
	idt[0x00].attributes = IDT_TRAP_GATE_32BIT;
	idt[0x00].isr_high = (offset & 0xFFFF0000) >> 16;



	ioport_out(PIC1_COMMAND_PORT, 0x11);
	ioport_out(PIC2_COMMAND_PORT, 0x11);

	ioport_out(PIC1_DATA_PORT, 0x20);
	ioport_out(PIC2_DATA_PORT, 0x28);

	ioport_out(PIC1_DATA_PORT, 0x0);
	ioport_out(PIC2_DATA_PORT, 0x0);

	ioport_out(PIC1_DATA_PORT, 0x1);
	ioport_out(PIC2_DATA_PORT, 0x1);

	ioport_out(PIC1_DATA_PORT, 0xff);
	ioport_out(PIC2_DATA_PORT, 0xff);

	idtr_t idt_ptr;
	idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
	idt_ptr.base = (uint32_t)&idt;
	load_idt((uint32_t*)&idt_ptr);
}

void kbd_init(){
	ioport_out(PIC1_DATA_PORT, 0xFD);
}
#endif
