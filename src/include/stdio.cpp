#ifndef _STDIO_H_
#define _STDIO_H_

typedef unsigned int size_t;

unsigned char *BASE = 0;
namespace std{


int _X_ = 0, _Y_ = 0;

//FREE MEMORY: 0x90001 -> 4GB
void* malloc(size_t bytes){
	
}

void printf(const char *str, int color = 0x0f){	
	BASE[_Y_*80*2+--_X_] = 0x00;
	BASE[_Y_*80*2+--_X_] = 0;
	while(*str != '\0'){
		switch (*str){
			case '\n':
				_X_ = 0;
				_Y_++;
				break;
			case '\t':
				_X_ += 4;
				break;
			case '\b':
				if(_X_ <= 0 && _Y_ == 0) break;
				_X_ -= 2;
				if(_X_ < 0) _X_ = 79*2, _Y_--;
				while(BASE[_Y_*80*2+_X_] == 0) _X_ -=2;	
				BASE[_Y_*80*2+_X_++] = 0;
				BASE[_Y_*80*2+_X_++] = color;
				_X_ -=2;
				break;
			default:
				BASE[_Y_*80*2+_X_++] = *str;
				BASE[_Y_*80*2+_X_++] = color;
				break;
		}
		str++;	
		if(_X_ > 80*2) _X_ = 0, _Y_++;
	}
	BASE[_Y_*80*2+_X_++] = 0;
	BASE[_Y_*80*2+_X_++] = 0xff;
	return;
}
void printf(int x, int color = 0x0f){
	char str[10], buff[10];
	int p = 0;
	while(x > 0){
		str[p++] = (x%10)+'0';
		x /= 10;
	}
	str[p--] = '\0';
	int p2 = 0;
	while(p >= 0){
		buff[p2++] = str[p--];
	}
	printf(buff, color);
}
void printf(unsigned char x, int color = 0x0f){
	char str[2];
	str[0] = x;
	str[1] = 0;
	printf(str, color);
}


};
#endif
