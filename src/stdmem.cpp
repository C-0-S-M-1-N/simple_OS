#include <stdmem.hpp>
#include <types.hpp>
#include <micell.hpp>
#include <string.hpp>

void* operator new(size_t bytes){
	return malloc(bytes, "NULL");
}
void* operator new[](size_t bytes){
	return malloc(bytes, "NULL");
}

void operator delete(void *ptr){
	free(ptr);
}
void operator delete[](void* ptr){
	free(ptr);
}

void* memmove(void* src, void* dest, size_t s){
	for(size_t i = 0; i<s; i++){
	 	*((uint8_t*)dest+i) = *((uint8_t*)src+i);
	}
	return dest;
}
//holder struct:
//	void* pointer to the block
//	size_t size of the block
//
//hs* = 0x90001(holder)
//
//malloc(){
//	sort(hs); //we can use bubble sort since it will only be one itteration
//	for(i : sorts){
//		if i+1.pointer - (i.pointer+i.size) >= size: allocate
//	}
//	allocate hs.last()+size
//
//}
mem_hld *hs = (mem_hld*)0x90001;


size_t hs_s = 0;


//start: 0x91000
// hs is a vector that has 0x91000 - 0x90001 elements
//
// eatch time malloc is called, we scan the whole free memory 
// until we find space for our malloc, witch is damn fast, 
// like we can have enough space inbetween the 3rd and 4th block, and we insert it there;
//
void* malloc(size_t bytes, const char* n){
	void* ret = nullptr;

	for(size_t i = 0; i<hs_s - 1; i++){
		
		if((uint8_t*)hs[i+1].ptr - ((uint8_t*)hs[i].ptr+hs[i].size) >= bytes){
			ret = (uint8_t*)hs[i].ptr+hs[i].size;
			
			//insert at i+1

			
			memmove(hs+i+1, hs+i+2, hs_s-i);
			
			hs[i+1].ptr = ret;
			hs[i+1].size = bytes;
			strcpy(hs[i+1].deb_name, n);
			hs_s++;

			return ret;
		}
		
	}

	ret = (uint8_t*)hs[hs_s-1].ptr+hs[hs_s-1].size;
	hs[hs_s].ptr = ret;
	hs[hs_s].size = bytes;
	strcpy(hs[hs_s++].deb_name, n); // debug only
	return ret;
}

void free(void* ptr){
	int i = 0, j = hs_s-1, m;
	while(i<j){
		m = (i+j)/2;
		if(ptr < hs[m].ptr) j = m-1;
		else if(ptr > hs[m].ptr) i = m+1;
		else break; 
	}
	for(i = m; i<hs_s-1; i++) swap(hs[i], hs[i+1]);
	hs_s--;
}

void* realloc(void* ptr, size_t rsize){
	size_t rh = 0, lf = hs_s-1, m;
	while(rh < lf){
		m = (rh + lf) / 2;
		if(ptr < hs[m].ptr) lf = m-1;
		if(ptr > hs[m].ptr) rh = m+1;
		else break;	
	}
	if((uint8_t*)hs[m+1].ptr - (uint8_t*)hs[m].ptr >= rsize){
		hs[m].size = rsize;
		return ptr;
	}
	
	void *buff = malloc(rsize, hs[m].deb_name);
	memmove(ptr, buff, hs[m].size);
	free(ptr);
	return buff;
}
