#ifndef __STDIO_H
#define __STDIO_H

typedef long unsigned int size_t;
typedef unsigned char uint8_t;
typedef unsigned long long uint64_t;

typedef __builtin_va_list va_list;

#define va_start(v, l)		__builtin_va_start(v, l);
#define va_arg(v, l)		__builtin_va_arg(v, l);

template <class T>void swap(T&, T&);
template <class T>void qsort(T*, size_t, size_t, bool (*)(T, T));
void* memmove(void*, void*, size_t);
int __msb__(size_t, bool = 0);
float log10(float);
float log2(float);
const char* itoa(int);
extern "C" void printf(const char*, ...);
//__attribute__((optimize("O0")))void sleep(size_t);

void* malloc(size_t);
void free(void*);
void* realloc(void*, size_t);

bool strcmp(const char*, const char*);
void strcpy(char*, const char*);
int stoi(char *s);

void* operator new(size_t);
void* operator new[](size_t);

void operator delete(void*);
void operator delete[](void*);

#endif
