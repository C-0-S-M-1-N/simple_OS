#include <stdmem.hpp>
#include <micell.hpp>
#include <stdio.hpp>

void memoryMap(){
	for(int i = 0; i<hs_s; i++){
		printf("%p, %d, %s\n", hs[i].ptr, hs[i].size, hs[i].deb_name);
	}
	
}

extern "C" void div0Exception(){
	
	printf("Segfault, Core Dumped (div 0)\n");
}


 
//TODO: make a priority queue
__attribute__((optimize("O0")))void sleep(size_t time_ms){
	unsigned long long t = time_ms*5'000'000, i = 0;
	while(i < time_ms){
		asm("pause");
		i++;
	}
}


int __msb__(size_t n, bool pos){
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	n |= (n >> 16);
	n ++;
	n >>= 1;
	if(pos == 0) return n;
	int p = 0;
	while(n > 0) p++, n = n >> 1;
	return p;	
}

float ln(float y){
	int log2;
	float divisor, x, result;

	log2 = __msb__((int)y, 1);
	divisor = (float)(1 << log2);
	x = y / divisor;

	result = -1.7417939 + (2.8212026 + (-1.4699568 + (0.44717955 - 0.056570851 * x) * x) * x) * x;
	result += ((float)log2) * 0.69314718;
	
	return result;
}


float lg(float x){
	return ln(x)/ln(10);
}


float log2(float x){
	return ln(x)/ln(2);
}

