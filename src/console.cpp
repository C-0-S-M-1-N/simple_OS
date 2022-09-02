#ifndef _CONSOLE__
#define _CONSOLE__
#include "include/stdio.cpp"
#include "include/file.cpp"


char **history = (char**)malloc(50*sizeof(char*));
size_t hptr = 0;

bool exit = 0;
dir root("-");
dir *current = &root;

void ent(){
	dir aux("aux");
	current->mkdir(aux);
	current = current->cd("aux");

}

#endif
