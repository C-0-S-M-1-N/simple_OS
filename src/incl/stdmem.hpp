#ifndef _STDMEM_HPP_
#define _STDMEM_HPP_

typedef unsigned long size_t;

//C-style allocation
void* malloc(size_t bytes, const char*);
void free(void*);
void* realloc(void* ptr, size_t newsize);

void* operator new(size_t);
void* operator new[](size_t);

void operator delete(void*);
void operator delete[](void*);

#endif
