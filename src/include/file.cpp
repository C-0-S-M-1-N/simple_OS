#ifndef _FILESYSTEM__
#define _FILESYSTEM__
#include "../stdio.hpp"

struct file{
	int c, h, s;
	size_t size;
	char *name;
};
struct dir{
	char*		 name;
	int 		sd_s = 0, f_s = 0, sd_m = 5, f_m = 10;
	dir**		subdir;
	file*		files;
	dir*		prev = nullptr;
};


/*class dir{
public:
	char*	name;
	int 		sd_s = 0, f_s = 0, sd_m = 5, f_m = 10;
	dir** 		subdir;
	file* 		files;
	dir* 		prev = nullptr;

	dir(const char* n){
		strcpy(name, n);
		subdir = (dir**)malloc(5*sizeof(dir*));
		files = (file*)malloc(10*sizeof(file));
		prev = nullptr;
	}
	dir& operator =(const dir& a){
		strcpy(name, a.name);
		sd_s = a.sd_s;	sd_m = a.sd_m;
		f_s = a.f_s;	f_m = a.f_m;
		subdir = a.subdir;
		files = a.files;
		prev = a.prev;
		return *this;
	}
	dir(dir& a){
		strcpy(name, a.name);
		sd_s = a.sd_s;	sd_m = a.sd_m;
		f_s = a.f_s;	f_m = a.f_m;
		subdir = a.subdir;
		files = a.files;
		prev = a.prev;	
	}

	~dir(){
		free(subdir);
		free(files);
		free(prev);
	}
	
};*/
















//NON OOP
void rename(dir& d, const char* n){ strcpy(d.name, n);}

void touch(dir& d, file f){
	if(d.f_s + 1 > d.f_m){d.files = (file*)realloc(d.files, sizeof(file)*d.f_m*2); d.f_m *= 2;}
	d.files[d.f_s++] = f;
}

bool rm(dir& d, const char* n){
	for(size_t i = 0; i<d.f_s; i++){
		if(strcmp(n, d.files[i].name)){
			for(size_t j = i; j<d.f_s-1; j++) swap(d.files[j], d.files[j+1]);
			d.f_s--;
			return true;
		}
	}
	return false;
}

void mkdir(dir& d, dir& m){
	if(d.sd_s +1 > d.sd_m){d.subdir = (dir**)realloc(d.subdir, sizeof(dir*)*d.sd_m*2); d.sd_m *= 2;}
	d.subdir[d.sd_s++] = &m;
	d.subdir[d.sd_s-1]->prev = &d;
}
bool rmdir(dir& d, const char* n){
	for(size_t i = 0; i<d.sd_s; i++){
		if(strcmp(n, d.subdir[i]->name)){
			for(size_t j = i; j<d.sd_s-1; j++) swap(d.subdir[j], d.subdir[j+1]);
			d.sd_s--;
			return true;
		}
	}
	return false;
}

dir* cd(dir& d, const char* n){
	if(strcmp(n, "..")) return d.prev;
	for(size_t i = 0; i<d.sd_s; i++){
		if(strcmp(n, d.subdir[i]->name)) return d.subdir[i];
	}
	printf("no sutch dir\n");
	return &d;
}

#endif
