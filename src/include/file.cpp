#ifndef _FILESYSTEM__
#define _FILESYSTEM__
#include "stdio.cpp"

struct file{
	int c, h, s;
	size_t size;
	char *name;
};

class string{
	char* str;
	size_t s, allS = 0;;
public:
	string(){
		allS = 50;
		str = (char*)malloc(allS*sizeof(char));
		s = 0;
	}
	char& operator [](size_t i){return str[i];}
	void push_back(char c){
		if(s+1 > allS){
			allS += 50;
			str = (char*)realloc(str, allS*sizeof(char));
		}
		str[s++] = c;
	}
	void pop_back(){if(s) s--;}

	string& operator +(string a){
		while(s < a.s){ this->push_back(a[s]);}
		return *this;
	}

	string& operator +(const char* n){
		while(*n){ this->push_back(*n++);}
		return *this;
	}
	char back(){ return str[s-1];}
	char front(){ return *str;}

	char* c_str(){
		char *r = str;
		r[s] = 0;
		return r;
	}
};


class dir{
	const char*	name;
		int 	sd_s = 0, f_s = 0;
		dir**	subdir;
		file*	files;
public:

	dir*	prev;
	dir(const char* n): name{n}{
		subdir = (dir**)	malloc(5*sizeof(dir*));
		files  = (file*)	malloc(10*sizeof(file));
		prev = nullptr;	
	}

	dir(dir& d) = default;
	dir& operator =(const dir& d){
		name = d.name;
		sd_s = d.sd_s;
		f_s = d.f_s;
		subdir = d.subdir;
		files = d.files;
		prev = d.prev;	
		return *this;
	}

	//dir& operator =(const dir&) = default;

	void touch(file);
	bool rm(const char*);
	void mkdir(dir&);
	bool rmdir(const char*);
	
	dir* cd(const char*);

	const char* getName() const{ return name;}

	~dir(){
		free(subdir);
		free(files);
	}
};

file makeFile();
void freeFile();

void dir::touch(file f){
	if(f_s+1 > sizeof(files)){ files = (file*)realloc(files, sizeof(files)+sizeof(file)*5);}	
	files[f_s++] = f;
}

bool dir::rm(const char *n){
	for(size_t i = 0; i<f_s; i++){
		if(strcmp(n, files[f_s].name)){
			for(size_t j = i; j<f_s-1; j++) swap(files[j], files[j+1]);		
			f_s--;
			return true;
		}
	}
	return false;
}

void dir::mkdir(dir &d){
	if(sd_s+1 > sizeof(subdir)){ subdir = (dir**)realloc(subdir, sizeof(subdir)+sizeof(dir*)*5);}	
	subdir[sd_s++] = &d;
	subdir[sd_s-1]->prev = this;
}

bool dir::rmdir(const char *n){
	for(size_t i = 0; i<sd_s; i++){
		if(strcmp(n, subdir[i]->name)){
			for(size_t j = i; j<sd_s-1; j++) swap(subdir[j], subdir[j+1]);
			sd_s--;
			return true;
		}
	}
	return false;	
}

dir* dir::cd(const char* n){
	if(strcmp(n, "..")) {
				
		return prev;
	}
	for(size_t i = 0; i<sd_s; i++){ if(strcmp(n, subdir[i]->name)){
		return subdir[i];
	} }
	return this;
}


#endif
