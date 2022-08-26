#include "kbd.cpp"
#include "include/init.cpp"
#include "include/stdio.cpp"
extern unsigned char *BASE;

bool writeToScreen = 0;

//z+5
extern "C" void start(){
	
	init();
	writeToScreen = 1;
	
	int *a = (int*)malloc(10*sizeof(int));
	int *b = (int*)malloc(5*sizeof(int));
	free(a);
	a = (int*)malloc(2*sizeof(int));
	//printf("%d", hs_s);
	for(int i = 0; i<hs_s; i++) printf("%x, %d; ", (int64_t)hs[i].ptr, hs[i].size);


	return;
}

extern "C" void handle_keyboard_int(){
	ioport_out(PIC1_COMMAND_PORT, 0x20);
	uint32_t status = ioport_in(KEYBOARD_STATUS_PORT);
	if(status & 0x1){
		keyPress = 1;
		uint8_t keycode = ioport_in(KEYBOARD_DATA_PORT);
		unsigned char pr = getChar(keycode);
		if((keycode & 128) != 128 && writeToScreen)
		printf("%c", (char)pr);
		//printf(pr); 
		//if((keycode & 128) == 128) printf("Released\n");
		//else printf("Pressed\n"); 	
	}
}
