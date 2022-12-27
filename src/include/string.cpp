#ifndef __STRING_H
#define __STRING_H



bool strcmp(const char *s1, const char *s2){
	while(*s1 && *s2){
		if(*s1 != *s2) return false;
		s1++, s2++;
		if((*s1 && !*s2) || (!*s1 && *s2)) return false;
	}
	return true;
}

int Cstrcmp(const char* s1, const char* s2){
	while(*s1 && *s2){
		if(*s1 > *s2) return 1;
		else if(*s1 < *s2) return -1;
		s1++, s2++;
	}
	if(*s1 && !*s2) return 1;
	if(!*s1 && *s2) return -1;
	return 0;
}

void strcpy(char *to, const char *from){
	while(*from){
		*to++ = *from++;
	}
	*to = 0;
	return;
}

bool strchr(const char* str, const char chr){
	while(*str++){
		if(*str == chr) return 1;
	}
	return 0;
}

void strtok(char* str, const char* restrict){
	static char* inp;
}

#endif
