#ifndef _KBD_H_
#define _KBD_H_
#include "../kbd.cpp"
#include "stdio.cpp"
extern unsigned char* BASE;
#define CURSOR '\n'


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
}
#endif
