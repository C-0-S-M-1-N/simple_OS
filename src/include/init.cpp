#ifndef _KBD_H_
#define _KBD_H_
#include "../kbd.cpp"
#include "../stdio.hpp"
extern unsigned char* BASE;
#define CURSOR '\n'

typedef short int16_t;
typedef unsigned short uint16_t;

#define inb(p) ioport_in(p)
#define outb(p, a) ioport_out(p, a)


extern bool writeToScreen;
uint32_t RAM_SIZE = 0;

extern char charGet;

void init(){
	hs[hs_s].ptr = (void*)0x91000;
	hs[hs_s++].size = 1;
	BASE = (unsigned char*)0xb8000;
	ioport_out(0x3D4, 0x0A);
	ioport_out(0x3D5, 0x20);
	for(int i = 0; i<=25; i++) for(int j = 0; j<=80*2; j++) BASE[i*80*2+j] = 0;
	idt_init();
	kbd_init();
	enable_interrupts();
	
	writeToScreen = 0;
	charGet = 0;

	//TODO
	uint8_t up, down;
	
	outb(0x70, 0x30);
	down = inb(0x71);

	outb(0x70, 0x31);
	up = inb(0x71);
	

	RAM_SIZE = down | up << 8;
}
#endif
