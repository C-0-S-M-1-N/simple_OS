#include <init.hpp>
#include <stdmem.hpp>
#include <types.hpp>
#include <kbd.hpp>
#include <string.hpp>
#include <stdio.hpp>

extern unsigned char* BASE;
#define CURSOR '\n'

#define inb(p) ioport_in(p)
#define outb(p, a) ioport_out(p, a)


extern bool writeToScreen;
char* stdin;
uint32_t RAM_SIZE = 0;


void init(){
	hs[hs_s].ptr = (void*)0x91000;
	strcpy(hs[hs_s].deb_name, "SYS_RES");
	hs[hs_s++].size = 1;


	BASE = (unsigned char*)0xb8000;
	
	ioport_out(0x3D4, 0x0A);
	ioport_out(0x3D5, 0x20);
	
	for(int i = 0; i<=25; i++) for(int j = 0; j<=80*2; j++) BASE[i*80*2+j] = 0;
	
	idt_init();
	kbd_init();
	enable_interrupts();
	
	writeToScreen = 0;

	//TODO
	uint8_t up, down;
	
	outb(0x70, 0x30);
	down = inb(0x71);

	outb(0x70, 0x31);
	up = inb(0x71);
	

	RAM_SIZE = down | (up << 8);

// 	stdin = (char*)malloc(8'000'000*sizeof(char), "STDIN");

}
