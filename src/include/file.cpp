#ifndef FILES__
#define FILES__
#include "stdio.cpp"

struct file{
	int c, h, s;
	const char *name;
};

class folder{
public:
	size_t folderPtr = 0, filePtr = 0;
	const char *name = "-";
	folder 	*prev = nullptr;	//pointer
	folder **next = nullptr;	//array
	file   **files = nullptr;	//array
public:
	folder(const char *n): name{n}{
		next = (folder**)malloc(sizeof(folder*)*5);
		files = (file**)malloc(sizeof(file*)*10);
	}
	folder* goDown(const char *n){
		for(size_t i = 0; i<folderPtr; i++){
			if(strcmp(n, next[i]->name)){
				next[i]->prev = this;
				return next[i];
			}
		}
		return nullptr;
	}
	folder* goUp(void){
		return this->prev;
	}

	void addFolder(folder& f){
		if(folderPtr+1 > sizeof(next)/sizeof(folder*))
		next[folderPtr++] = &f;
	}

	void addFile(file& f){
		files[filePtr++] = &f;
	}
	
	void listElem(){ //TODO: add color descriptions
		for(int i = 0; i<filePtr; i++) printf("%s\n", files[i]->name);
		for(int i = 0; i<folderPtr; i++) printf("%s\n", next[i]->name);
	}

	~folder(){
		free(next);
		free(files);
	}
};

#endif
