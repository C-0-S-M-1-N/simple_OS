
void main(){
	*(char*) 0xb8000 = 'A';
	*(char*) 0xb8001 = 0x0f;
	while(1);
}
