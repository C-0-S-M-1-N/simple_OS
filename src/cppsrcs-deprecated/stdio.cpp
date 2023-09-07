#include <stdio.hpp>
#include <string.hpp>
#include <types.hpp>
#include <stdmem.hpp>
#include <micell.hpp>


void ioport_outw(uint32_t port, uint16_t data){
	__asm__ volatile("outw %w0, %w1" : : "a" (data), "Nd" (port));	
}

uint32_t ioport_inw(uint32_t port){
    unsigned short data;
    __asm__ volatile("inw %w1, %w0" : "=a" (data) : "Nd" (port));
    return data;
}




uint8_t *BASE = nullptr;
bool BASE_mutex = 0;
extern char* stdin;
size_t stdinElement = 0;


int _X_ = 0, _Y_ = 0;
int xS, yS;

short memoryBuffer[100000];
int memoryBufferInt = 0;

void memoryWrite__(unsigned char s, int color = 0x0f){
	
	memoryBuffer[memoryBufferInt] = s;
	memoryBuffer[memoryBufferInt++] = color;

	while(BASE_mutex);
	BASE_mutex = 1;
	switch(s){
		case '\n':
			BASE[_Y_*80*2+_X_++] = 10;
			BASE[_Y_*80*2+_X_++] = 0;
			_X_ = 0;
			_Y_++;
			break;
		case '\t':
			BASE[_Y_*80*2+_X_++] = '\t';
			BASE[_Y_*80*2+_X_++] = 0;
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
			BASE[_Y_*80*2+_X_++] = s;
			BASE[_Y_*80*2+_X_++] = color;
			break;
	
	}
	if(_X_ > 79*2) _X_ = 0, _Y_++;
	if(_Y_ > 24){ //scroll
		_Y_ = 24;	
		for(int i = 0; i<24; i++){
			for(int j = 0; j<80*2; j += 2){
				BASE[i*80*2 + j] = BASE[(i+1)*80*2 + j];
				BASE[i*80*2 + j+1] = BASE[(i+1)*80*2 + j+1];
			}
		}
		for(int i = 0; i<80*2; i++) BASE[24*80*2 + i] = 0;
	}
	BASE_mutex = 0;
}

const char* itoa(int x){
	char *s;
	char *rev;
	char p1 = 0, p2 = 0;
	while(x){
		s[p1++] = (x%10)+'0';
		x /= 10;	
	}
	s[p1--] = '\0';
	while(p1){
		rev[p2++] = s[p1--];
	}
	rev[p2++] = 0;
	return rev;
}

void printfNum__(int x, int color = 0x0f){
	if(x == 0){
		memoryWrite__('0', color);
	}
	bool neg = x<0;
	if(neg) x *= -1;
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
	buff[p2] = 0;
	p2 = 0;;
	if(neg) memoryWrite__('-', color);
	while(buff[p2]){
		memoryWrite__(buff[p2++], color);
	}

}

extern "C" void printf(const char *str, ...){	
		
	BASE[_Y_*80*2+_X_] = 0;
	BASE[_Y_*80*2+_X_+1] = 0x00;
	va_list l;
	__builtin_va_start(l, str);
	while(*str){
		if(*str == '%' && *(str+1)){
			str++;
			switch(*str){
				case 'd':{
					int n = 0; 
					n = va_arg(l, int);
					printfNum__(n);
					break;}		 
				case 's':{
					char *s = va_arg(l, char*);
					printf(s);
					break;}
				case 'b':{
					int n = va_arg(l, int);
					char bn[64];
					int p = 0;
					while(n){
						bn[p++] = (n&1)+'0';
						n >>= 1;
					}
					bn[p] = 0;
					printf(bn); 
					break;}
				case 'B':{
					int n = va_arg(l, int);
					char bn[64];
					int p = __msb__(n, 1)-1;
					bn[p+1] = 0;
					while(n){
						bn[p--] = (n&1)+'0';
						n >>= 1;
					}
					printf(bn); 
					break;}
				case 'x':{
					int64_t n = va_arg(l, int64_t);
					char hn[9];
					int p = __msb__(n, 1)/8+2;
					hn[p+1] = '\0';
					while(n){
						hn[p--] = (n%16)>=10? 'A'+((n%16)-10) : (n%16)+'0';
						n >>= 4;
					}
					printf(hn);
					break;}
				case 'c':{
					char c = va_arg(l, int);
					memoryWrite__(c);
					break;}
				case 'p':{
					void* ptr = va_arg(l, void*);
					printf("%x", ptr);
					break;}

			}
			str++;
		}else memoryWrite__(*str++);
	}
	BASE[_Y_*80*2+_X_] = 0;
	BASE[_Y_*80*2+_X_+1] = 0xff;
	

}

//123
int stoi(char* s){
	int ret = 0;
	while(*s){
		ret = ret*10 + (*s - '0');
		s++;
	}
	return ret;
}

void flush_stdin(){
	stdinElement = 0;
}

void __scanf_str(char* str){
	flush_stdin();
	while(stdin[stdinElement-1] != '\n'){
		__asm__("hlt");
	}
	stdin[stdinElement-1] = 0;
	strcpy(str, stdin);
	flush_stdin();
}

#define SPCHR 1
extern "C" void scanf(const char* str, ...){
	flush_stdin();
	while(stdin[stdinElement-1] != '\n'){
		__asm__("hlt");
	}
	stdin[stdinElement-1] = 0;
	char* buff = stdin;
	
	va_list l;
	va_start(l, str);
	
	
	for(int i = 0; str[i]; i++){
		if(str[i] != '%') continue;
		i++;
		
		switch(str[i]){
		case 'd':{
			int* ret = va_arg(l, int*);
			char* tmp = (char*)malloc(21, "tmp");
			int i; for(i = 0; buff[i] != ' ' && buff[i]; i++){
				tmp[i] = buff[i];
			}
			buff += i+1;
			tmp[i] = 0;
			*ret = stoi(tmp);
			free(tmp);
		} break;
		case 's':{
			char* s = va_arg(l, char*);
			int i; for(i = 0; buff[i] != ' ' && buff[i]; i++){
				s[i] = buff[i];
			}
			s[i] = 0;
			buff += i + 1;
				 
		} break;
		case 'c':{
			char* c = va_arg(l, char*);
			*c = *(buff++);

		} break;
		}

	}
	flush_stdin();
}





//files:
