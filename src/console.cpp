#ifndef _CONSOLE__
#define _CONSOLE__
#include "stdio.hpp"
#include "include/file.cpp"



void ent(){
	dir root, *pth;
	rename(root, "-");	
	pth = &root;
	char* c = (char*)malloc(100*sizeof(char));
	while(!strcmp(c, "q") && !strcmp(c, "quit")){
		
	}
	free(c);
}

#endif
