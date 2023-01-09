#ifndef _KEY_MAP_
#define _KEY_MAP_
#include "stdio.hpp"

char _codeToASCII[] = {
0, //NULL BIT
0, //esc
'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', //backspace
'\t', //tab
'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']','\n', /*return*/ 0, /*L-CTRL*/
'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, /*L-SHIFT*/ '\\',
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, //R-SHIFT
'*', // * keypad
0, //L-ALT
' ', //space
0, //capsLock pressed
0, //F1
0, //F2
0, //F3
0, //F4
0, //F5
0, //F6
0, //F7
0, //F8
0, //F9
0, //F10
0, //NUM LK pressed
0, //SCROLL LK pressed
//-----NUMPAD-----//
'7', '8', '9',
	 '-',
'4', '5', '6',
	 '+',
'1', '2', '3', 
'0', '.',
//---NUMPADEND----//
0,0,0, //NULL
0, //F11
0, //F12
};

unsigned char extraNUM[] = ")!@#$%^&*(";

//RIGHT
bool R_SHIFT = 0, R_CTRL = 0, R_ALT = 0;
//LEFT
bool L_SHIFT = 0, L_CTRL = 0, L_ALT = 0;

//F1, F2, ... , F11, F22
bool Fs[13] = {0,0,0,0,0,0,0,0,0,0,0,0};
//locks
bool capsLock = 0, numLock = 0, scrollLock = 0;

bool kbd_keys[256];
bool keyPress = 0;


char toUpper(char x){
	if(x >= 'a' && x<='z') return x-32;
	if(x >= '0' && x <= '9') return extraNUM[x-'0'];
   	if(x == '-') return '_';
	if(x == '=') return '+';
	if(x == '`') return '~';
	if(x == ';') return ':';
	if(x == '\'') return '"';
	if(x == ',') return '<';
	if(x == '.') return '>';
	if(x == '/') return '?';
	if(x == '\\') return '|'; 	
	if(x == '[') return '{';
	if(x == ']') return '}';
	return x;	
}

unsigned char getChar(unsigned int keycode){
	//Fs handle
	if(keycode <= 0x44 && keycode >= 0x3B){
		int Fnum = keycode - 0x3B + 1;
		Fs[Fnum] = 1;
	}else if(keycode == 0x57) Fs[11] = 1;
	else if(keycode == 0x58) Fs[12] = 1;
	else if(keycode <= 0xC4 && keycode >= 0xBB){
		int Fnum = keycode - 0xBB + 1;
		Fs[Fnum] = 0;
	}else if(keycode == 0xD7) Fs[11] = 0;
	else if(keycode == 0xD8) Fs[12] = 0;
	else{
	
	switch(keycode){
		case 0x1D:
			L_CTRL = 1;
			break;
		case 0x2A:
			L_SHIFT = 1;
			break;
		case 0x36:
			R_SHIFT = 1;
			break;
		case 0x38:
			L_ALT = 1;
			break;
		case 0x3A:
			capsLock = !capsLock;
			break;
		case 0x45:
			numLock = !numLock;
			break;
		case 0x46:
			scrollLock = !scrollLock;
			break;
		case 0x9D:
			L_CTRL = 0;
			break;
		case 0xAA:
			L_SHIFT = 0;
			break;
		case 0xB6:
			R_SHIFT = 0;
			break;
		case 0xB8:
			L_ALT = 0;
			break;
		case 0xE038: //ex
			R_ALT = 1;
			break;
		case 0xE0B8:
			R_ALT = 0;
			break;
		default:{
			if(keycode > 128){
				char c = _codeToASCII[keycode-0x80];
				if(L_SHIFT || R_SHIFT) c = toUpper(c);	
				if(capsLock){
					if(c >= 'a' && c <= 'z') c -= 32;
					else if(c >= 'A' && c <= 'Z') c += 32;
				}
				kbd_keys[c] = 0;
				//printf((unsigned char)c);
				//printf(" was released \0");
			}
			char c = _codeToASCII[keycode];
			if(L_SHIFT || R_SHIFT) c = toUpper(c);
			if(capsLock){
				if(c >= 'a' && c <= 'z') c -= 32;
				else if(c >= 'A' && c <= 'Z') c += 32;
			}
	
			kbd_keys[c] = 1;
			return c;
			break;	
		}
		
	}



	}
	return 0;
}

#endif
