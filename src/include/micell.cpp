#ifndef _MIC__H
#define _MIC__H
#include "stdio.cpp"

void memoryMap(){
	for(int i = 0; i<hs_s; i++){
		printf("%p, %d, %s\n", hs[i].ptr, hs[i].size, hs[i].deb_name);
	}
	
}

extern "C" void div0Exception(){
	
	printf("Seg Fault, Core Dumped (div 0)\n");
}

#endif
