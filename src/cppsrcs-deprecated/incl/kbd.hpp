#ifndef _KBD_H_
#define _KBD_H_

#include <types.hpp>

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



extern void idt_init();
extern void kbd_init();
extern "C" char ioport_in(unsigned short port);
extern "C" void ioport_out(unsigned short port, unsigned char data);

extern "C" void load_idt(unsigned int* idt_address);
extern "C" void keyboard_handler();
extern "C" void enable_interrupts();
extern "C" void div0();



#endif
