#ifndef _STDMEM_HPP_
#define _STDMEM_HPP_
#include <types.hpp>

struct mem_hld{
	void *ptr;
	size_t size{0};
	char deb_name[100];
};
extern mem_hld *hs;
extern size_t hs_s;


//C-style allocation
extern void* malloc(size_t bytes, const char*);
extern void free(void*);
extern void* realloc(void* ptr, size_t newsize);
extern void* memmove(void* src, void* dest, size_t s);


static inline void halt(){
	__asm__ volatile ("hlt");
}

#endif
