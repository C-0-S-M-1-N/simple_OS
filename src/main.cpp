#include "kbd.cpp"
#include "include/init.cpp"
//#include "include/stdio.cpp"
#include "include/stdio.cpp"
#include "include/file.cpp"
#include "console.cpp"
#include "include/cppStuff.cpp"
#include "apic.cpp"

extern "C" void halt();
bool writeToScreen = 0, getkey = 0;
extern char* stdin;
extern size_t stdinElement;
//z+5
extern "C" void start(){
	init();

	writeToScreen = 1;
	
	char *s = (char*)malloc(100*sizeof(char));

	printf("%s\n", s);

	//for(int i = 0; i<16; i++){
	//	printf("%c %d\n", s[i], s[i]);
	//}

	//for(int i = 0; i<100-1; i++) printf("%c", s[i]);
}
extern "C" void handle_keyboard_int(){
	ioport_out(PIC1_COMMAND_PORT, 0x20);
	uint32_t status = ioport_in(KEYBOARD_STATUS_PORT);
	if(status & 0x1){
		keyPress = 1;
		uint8_t keycode = ioport_in(KEYBOARD_DATA_PORT);
		unsigned char pr = getChar(keycode);

		if((keycode & 128) != 128 && pr){
			if(writeToScreen) printf("%c", (char)pr);
			stdin[stdinElement++] = pr;
			if(stdinElement >= 8000000) stdinElement = 0;
		
		}

	}
}

