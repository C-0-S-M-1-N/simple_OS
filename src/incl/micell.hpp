#ifndef _MICELL_HPP_
#define _MICELL_HPP_
#include <types.hpp>

extern void memoryMap();
extern "C" void div0Exception();

template <class T>
void swap(T& a, T& b){
	T aux = a; a = b; b = aux;
}

extern __attribute__((optimize("O0")))void sleep(size_t);

template <class T>void qsort(T *a, size_t r, size_t l, bool (*cmp)(T, T)){
	if(l < r){
		size_t m = (r+l) / 2;
		swap(a[l], a[m]);
		int i = l, j = r, d = 0;
		while(i < j){
			if(cmp(a[i], a[j])){
				swap(a[i], a[j]);
				d = 1 - d;
			}
			i += d;
			j -= 1 - d;
		}	
		qsort(a, r, i-1, cmp);
		qsort(a, i+1, l, cmp);
	}
}

extern int32_t __msb__(size_t, bool = 0);
extern float ln(float);
extern float lg(float);
extern float log2(float);

#endif
