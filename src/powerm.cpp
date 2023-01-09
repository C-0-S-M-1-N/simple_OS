#ifndef __POWH__
#define __POWH__
#include "include/stdio.cpp"
#include "kbd.cpp"
#include "kbd_map.h"


void reboot()
{
	stdinElement = 0;
	_Y_ = 0;
	_X_ = 0;
	while(hs_s){
		free(hs[0].ptr);
	}



    uint8_t good = 0x02;
    while (good & 0x02)
        good = ioport_in(0x64);
    ioport_out(0x64, 0xFE);
    halt();
}

void keyDebug(){
	for(int i = 1; i <= 12; i++){
		printf("F%d : %d\n", i, Fs[i]);
	}
	printf("capsLock : %d", capsLock);
}

#endif
