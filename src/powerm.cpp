#include <powerm.hpp>
#include <stdio.hpp>
#include <stdmem.hpp>
#include <kbd.hpp>
#include <kbd_map.hpp>


void reboot(void){
	stdinElement = 0;
	while(hs_s){
		free(hs[0].ptr);
	}



    uint8_t good = 0x02;
    while (good & 0x02)
        good = ioport_in(0x64);
    ioport_out(0x64, 0xFE);
    halt();
}

void keyDebug(void){
	for(int i = 1; i <= 12; i++){
		printf("F%d : %d\n", i, Fs[i]);
	}
	printf("capsLock : %d", capsLock);
}

