#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

sbit ENLED = P1^4;
sbit ADDR3 = P1^3;
sbit ADDR2 = P1^2;
sbit ADDR1 = P1^1;
sbit ADDR0 = P1^0;
sbit LED0 = P0^0;
sbit LED1 = P0^1;
sbit LED2 = P0^2;
sbit LED3 = P0^3;
sbit LED4 = P0^4;
sbit LED5 = P0^5;
sbit LED6 = P0^6;
sbit LED7 = P0^7;

uchar code LEDnum[] = {
    0xC0,
    0xF9,
    0xA4,
    0xB0,
    0x99,
    0x92,
    0x82,
    0xF8,
    0x80,
    0x90,
    0x88,
	0x83,
	0xC6,
	0xA1,
	0x86,
	0x8E
};

uchar code KeyCode[] = {
	0xE7,0xD7,0xB7,0x77,
	0xEB,0xDB,0xBB,0x7B,
	0xED,0xDD,0xBD,0x7D,
	0xEE,0xDE,0xBE,0x7E

};

uchar key = 0;
uchar num = 0;
uchar i = 0, k = 0;
uchar flag = 0;


void Delay_ms(unsigned int cnt);
void LED_show();
uchar KeyBoard_Scan();
void Digital_show();

void main(){
	ENLED = 0;

	while(1){
		key = KeyBoard_Scan();
		switch (k){
			case 0:
				Digital_show();
				k = 1;
				break;
			case 1:
				LED_show();
				k = 0;
				break;
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

uchar KeyBoard_Scan(){
	static uchar j = 0;
	uchar scan1, scan2, keyboard;

	P2 = 0xf0;
	scan1 = P2;
	if((scan1 & 0xf0) != 0xf0){
		Delay_ms(10);
		P2 = 0xf0;
		scan1 = P2;
		if((scan1 & 0xf0) != 0xf0){
			P2 = 0x0f;
			scan2 = P2;
			keyboard = scan1 | scan2;
			while((P2 & 0x0f) != 0x0f);
			P2 = 0xf0;
			if(flag >= 99){
				flag = 0;
			}
			flag++;
			for(i = 0; i < 16; i++){
				if(keyboard == KeyCode[i]){
					j = i;
					return i;
				}
			}
			return j;
		}
	}
	else{
		return j;
	}
	return j;
}

void LED_show(){
	ADDR0 = 0;
	ADDR1 = 1;
	ADDR2 = 1;
	ADDR3 = 1;
	P0 = 0xff;
	switch(key){
		case 0:
			LED0 = 1;
			LED1 = 1;
			LED2 = 1;
			LED3 = 1;
			break;
		case 1:
			LED0 = 0;
			LED1 = 1;
			LED2 = 1;
			LED3 = 1;
			break;
		case 2:
			LED0 = 1;
			LED1 = 0;
			LED2 = 1;
			LED3 = 1;
			break;
		case 3:
			LED0 = 0;
			LED1 = 0;
			LED2 = 1;
			LED3 = 1;
			break;
		case 4:
			LED0 = 1;
			LED1 = 1;
			LED2 = 0;
			LED3 = 1;
			break;
		case 5:
			LED0 = 0;
			LED1 = 1;
			LED2 = 0;
			LED3 = 1;
			break;
		case 6:
			LED0 = 1;
			LED1 = 0;
			LED2 = 0;
			LED3 = 1;
			break;
		case 7:
			LED0 = 0;
			LED1 = 0;
			LED2 = 0;
			LED3 = 1;
			break;
		case 8:
			LED0 = 1;
			LED1 = 1;
			LED2 = 1;
			LED3 = 0;
			break;
		case 9:
			LED0 = 0;
			LED1 = 1;
			LED2 = 1;
			LED3 = 0;
			break;
		case 10:
			LED0 = 1;
			LED1 = 0;
			LED2 = 1;
			LED3 = 0;
			break;
		case 11:
			LED0 = 0;
			LED1 = 0;
			LED2 = 1;
			LED3 = 0;
			break;
		case 12:
			LED0 = 1;
			LED1 = 1;
			LED2 = 0;
			LED3 = 0;
			break;
		case 13:
			LED0 = 0;
			LED1 = 1;
			LED2 = 0;
			LED3 = 0;
			break;
		case 14:
			LED0 = 1;
			LED1 = 0;
			LED2 = 0;
			LED3 = 0;
			break;
		case 15:
			LED0 = 0;
			LED1 = 0;
			LED2 = 0;
			LED3 = 0;
			break;
		default:
			break;
	}
}

void Digital_show(){
	Delay_ms(1);
	uchar a, b;
	a = flag / 10;
	b = flag % 10;

	P0 = 0xff;
	ADDR0 = 0;
	ADDR1 = 0;
	ADDR2 = 0;
	ADDR3 = 1;
	P0 = LEDnum[b];
	Delay_ms(1);

	P0 = 0xff;
	ADDR0 = 1;
	ADDR1 = 0;
	ADDR2 = 0;
	ADDR3 = 1;
	P0 = LEDnum[a];
	Delay_ms(1);
}
