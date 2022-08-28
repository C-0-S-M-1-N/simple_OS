#ifndef _STDIO_H_
#define _STDIO_H_

typedef unsigned int size_t;
typedef unsigned char uint8_t;
typedef unsigned long long uint64_t;
typedef long long int64_t;

typedef __builtin_va_list __gnuc_va_list;
typedef __builtin_va_list va_list;

#define va_start(v,l)	__builtin_va_start(v,l)
#define va_arg(v,l)		__builtin_va_arg(v,l)


unsigned char *BASE = 0;


int __msb__(size_t n, bool pos = 0){
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	n |= (n >> 16);
	n ++;
	n >>= 1;
	if(pos == 0) return n;
	int p = 0;
	while(n > 0) p++, n = n >> 1;
	return p;	
}

float __10__logs[] = {0, 0, 0.301, 0.477, 0.602, 0.698, 0.778, 0.845, 0.903, 0.954, 1};

float log10(float x){
	if(x == 10) return 1;
	if(x == 1 || !x) return 0;
	if(x > 10){
		return log10((float)(x/10) + 1);
	}else{
		float l = __10__logs[(int)x], l1 = __10__logs[(int)x+1];
		return (l1-l)*(x-(int)x)+l;
	}
}


float log2(float x){
	if(x > 2){
		return log2((float)x/__msb__(x)) + __msb__(x, 1) - 1;
	}else{
		return float(x-1);
	}
}

int _X_ = 0, _Y_ = 0;

void memoryWrite__(unsigned char s, int color = 0x0f){
	switch(s){
		case '\n':
			BASE[_Y_*80*2+_X_++] = 10;
			BASE[_Y_*80*2+_X_++] = 0;
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
			BASE[_Y_*80*2+_X_++] = 0x0f;
			_X_ -=2;
			break;
		default:
			BASE[_Y_*80*2+_X_++] = s;
			BASE[_Y_*80*2+_X_++] = 0x0f;
			break;
	
	}
	if(_X_ > 80*2) _X_ = 0, _Y_++;
	
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
	p2 = 0;
	if(neg) memoryWrite__('-', color);
	while(buff[p2]){
		memoryWrite__(buff[p2++], color);
	}

}
void printf(const char *str, ...){	
		
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

template <class T>void swap(T &a, T &b){
	T aux = a;
	a = b;
	b = aux;
}


//holder struct:
//	void* pointer to the block
//	size_t size of the block
//
//hs* = 0x90001(holder)
//
//malloc(){
//	sort(hs); //we can use bubble sort since it will only be one itteration
//	for(i : sorts){
//		if i+1.pointer - (i.pointer+i.size) >= size: allocate
//	}
//	allocate hs.last()+size
//
//}

struct mem_hld{
	void* ptr;
	size_t size{0};
} *hs = (mem_hld*)0x90001;

size_t hs_s = 0;

//start: 0x91000
void* malloc(size_t bytes){
	void* ret = nullptr;
//sort
	for(size_t i = 0; i<hs_s - 1; i++){
		if(hs[i].ptr > hs[i+1].ptr) swap(hs[i], hs[i+1]);
		if(!ret){
			if((uint8_t*)hs[i+1].ptr - ((uint8_t*)hs[i].ptr+hs[i].size) >= bytes){
				ret = (uint8_t*)hs[i].ptr+hs[i].size;
				hs[hs_s].ptr = ret;
				hs[hs_s++].size = bytes;
			}
		}
	}
	if(ret) return ret;	

	ret = (uint8_t*)hs[hs_s-1].ptr+hs[hs_s-1].size;
	hs[hs_s].ptr = ret;
	hs[hs_s++].size = bytes;	
	return ret;
}

void free(void* ptr){
	int i = 0, j = hs_s-1, m;
	while(i<j){
		m = (i+j)/2;
		if(ptr < hs[m].ptr) j = m-1;
		else if(ptr > hs[m].ptr) i = m+1;
		else break; 
	}
	for(i = m; i<hs_s-1; i++) swap(hs[i], hs[i+1]);
	hs_s--;
}

bool strcmp(const char *s1, const char *s2){
	while(*s1 && *s2){
		if(*s1 != *s2) return false;
		s1++, s2++;
		if((s1 && !s2) || (!s1 && s2)) return false;
	}
	return true;
}



#endif
