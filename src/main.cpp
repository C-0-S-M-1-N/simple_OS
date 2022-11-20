#include "kbd.cpp"
#include "include/init.cpp"
#include "stdio.hpp"
#include "include/file.cpp"
#include "console.cpp"
#include "include/cppStuff.cpp"

extern unsigned char *BASE;
bool writeToScreen = 0;
char charGet;
//z+5
extern "C" void start(){
	init();
	writeToScreen = 1;
	printf("sdasd\n");
	
}

extern "C" void handle_keyboard_int(){
	ioport_out(PIC1_COMMAND_PORT, 0x20);
	uint32_t status = ioport_in(KEYBOARD_STATUS_PORT);
	if(status & 0x1){
		keyPress = 1;
		uint8_t keycode = ioport_in(KEYBOARD_DATA_PORT);
		unsigned char pr = getChar(keycode);
		if((keycode & 128) != 128 && writeToScreen && pr){
			printf("%c", (char)pr);
			charGet = pr;
		}
		//printf(pr); 
		//if((keycode & 128) == 128) printf("Released\n");
		//else printf("Pressed\n"); 	
	}
}

