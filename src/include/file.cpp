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
	folder 	*next = nullptr;	//array
	file 	*files = nullptr;	//array
public:
	folder(const char *n): name{n}{
		next = (folder*)malloc(sizeof(folder));
		files = (file*)malloc(sizeof(file));
	}
	bool goDown(const char *n){
		for(size_t i = 0; i<folderPtr; i++){
			if(next[i].name)
		}
	}
	~folder(){
		free(next);
		free(files);
	}
};

#endif
