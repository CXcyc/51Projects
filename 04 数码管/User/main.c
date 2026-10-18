#include <reg52.h>
#include <intrins.h>

sbit ADDR3 = P1^3;
sbit ADDR2 = P1^2;
sbit ADDR1 = P1^1;
sbit ADDR0 = P1^0;
sbit ENLED = P1^4;
sbit KeyIn1 = P2^4;
sbit KeyIn2 = P2^5;
sbit KeyIn3 = P2^6;
sbit KeyOu1 = P2^3;

unsigned char code num[] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90, // 9
    0x88, // A
	0x83, // B
	0xC6, // C
	0xA1, // D
	0x86, // E
	0x8E  // F
};

void Delay_ms(unsigned int cnt);

void main(){
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int a = 0;
	unsigned int b = 0;
	unsigned int c = 0;

	unsigned char flag = 0;
	unsigned char flag_Key = 0;

	ENLED = 0;
	KeyOu1 = 0;

	while(1){
		if(c == 0){
			ADDR0 = 0;
			ADDR1 = 0;
			ADDR2 = 0;
			ADDR3 = 1;
			P0 = num[flag];
			c = 1;
		}
		else if(c == 1){
			ADDR0 = 1;
			ADDR1 = 0;
			ADDR2 = 0;
			ADDR3 = 1;
			P0 = num[flag_Key];
			c = 0;
			}
		Delay_ms(1);
			i++;
			if(i == 200){
				i = 0;
				flag++;
				if(flag >= 16){
					flag = 0;
				}
			}

		if(KeyIn1 == 0){
			Delay_ms(10);
			if(KeyIn1 == 0){	
				while(KeyIn1 == 0);
				if(flag_Key >= 3){
					flag_Key = 0;
				}
				flag_Key ++;
			}
		}
	}
}


void Delay_ms(unsigned int cnt){
	unsigned int i;
	unsigned int j;
	for(i = 0; i < cnt; i++){
		for(j = 0; j < 105; j++);
	}
}
