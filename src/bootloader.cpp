#include <init.hpp>
#include <stdio.hpp>

/**
 * TODO: MAKE BOOTING FROM DISK WORKING
 * TODO: LOAD KERNEL TO 0x10000*/
extern "C" void bootloader(){
	init();
	printf("DONE!\n");
	while(1);
}
