#include "kbd.cpp"
#include "include/init.cpp"
#include "include/stdio.cpp"
#include "include/cppStuff.cpp"
#include "include/string.cpp"
#include "powerm.cpp"
#include "include/micell.cpp"

bool writeToScreen = 0, getkey = 0;
extern char* stdin;
extern size_t stdinElement;
//z+5
extern "C" void start(){
	init();
	writeToScreen = 1;
	char* commandInput = (char*)malloc(1000*sizeof(char));
	int a, b;
	
	scanf("%d %d", &a, &b);
	printf("%d", a/b);

	return;
	//printf("%p", malloc);
	while("false"){
		printf(">");
		scanf("%s", commandInput);

		if(strcmp(commandInput, "exit")) break;
		else if(strcmp(commandInput, "reboot")) reboot();
		else if(strcmp(commandInput, "memmap")) memoryMap();
		else printf("Unknown command, use help for commands");

		printf("\n");
	}
	printf("exiting...");
	//free(commandInput);
	ioport_outw(0x604, 0x2000);


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
			if(pr == '\b'){
				stdinElement--;
			}
			else stdin[stdinElement++] = pr;
			if(stdinElement >= 8000000) stdinElement = 0;
			BASE[78*2] = pr;
			BASE[78*2+1] = 0xf0;
		
		}

	}
}

