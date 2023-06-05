#ifndef _STDIO_HPP_
#define _STDIO_HPP_

extern char* stdin;
extern unsigned char* BASE;
extern bool BASE_mutex;
extern unsigned int stdinElement;

static inline void ioport_outw(unsigned int port, unsigned int data);
static inline unsigned short ioport_inw(unsigned int port);

void memoryWrite__(unsigned, int = 0x0f);
void printfNum__(int, int = 0x0f);

extern "C" void printf(const char*, ...);

extern "C" void scanf(const char*, ...);

void flush_stdin();
void __scanf_str(char*);

#endif
