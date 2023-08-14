#ifndef __STDIO_H
#define __STDIO_H
#include <types.hpp>
#include <init.hpp>

extern int8_t* stdin;
extern uint8_t* BASE;
extern size_t stdinElement;
extern int16_t memoryBuffer[];
extern int32_t memoryBufferInt;

extern "C" void printf(const char*, ...);
//__attribute__((optimize("O0")))void sleep(size_t);

extern "C" void scanf(const char*, ...);

extern int stoi(char *s);

extern void ioport_outw(uint32_t port, uint16_t data);

extern uint32_t ioport_inw(uint32_t port);

#endif
