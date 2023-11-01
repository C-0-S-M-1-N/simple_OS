#ifndef KBD_MAP_HPP_
#define KBD_MAP_HPP_
#include <types.hpp>

extern int8_t _codeToASCII[];
extern uint8_t extraNUM[];
extern bool R_SHIFT, R_CTRL, R_ALT,
	   		L_SHIFT, L_CTRL, L_ALT;
extern bool Fs[13];

extern bool capsLock, numLock, scrollLock;

extern bool kbd_keys[256], keyPress;

char toUpper(char);

uint8_t getChar(uint32_t);

#endif
