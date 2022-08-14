#include "../kbd.cpp"
extern unsigned char* BASE;
#define CURSOR '\n'

int _X_ = 0, _Y_ = 0;


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

void init(){
	BASE = (unsigned char*)0xb8000;
	ioport_out(0x3D4, 0x0A);
	ioport_out(0x3D5, 0x20);
	for(int i = 0; i<=25; i++) for(int j = 0; j<=80*2; j++) BASE[i*80*2+j] = 0;
	idt_init();
	kbd_init();
	enable_interrupts();
}
