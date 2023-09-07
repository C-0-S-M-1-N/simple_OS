#ifndef __STRING_H
#define __STRING_H
#define NULL 0

extern bool strcmp(const char*, const char*);

extern int Cstrcmp(const char*, const char*);

extern void strcpy(char*, const char*);
extern void strcpy(char*, char*);
extern void strcpy(const char*, const char*);

extern void strchr(const char*, const char*);

#endif
