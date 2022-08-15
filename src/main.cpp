#include "kbd.cpp"
#include "include/init.cpp"
#include "include/stdio.cpp"
extern unsigned char *BASE;



//z+5
extern "C" void start(){
	
	init();
	//printf(10);
	
		

	//while("false");
	return;
}

extern "C" void handle_keyboard_int(){
	ioport_out(PIC1_COMMAND_PORT, 0x20);
	uint32_t status = ioport_in(KEYBOARD_STATUS_PORT);
	if(status & 0x1){
		uint8_t keycode = ioport_in(KEYBOARD_DATA_PORT);
		unsigned char pr = getChar(keycode);
		//printf(pr); 
		//if((keycode & 128) == 128) printf("Released\n");
		//else printf("Pressed\n"); 	
	}
}
