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

// 标准键码表：与 KeyCode[] 扫描码一一对应，0~15 号按键的标准键码 0~F
uchar code KeyVal[] = {
	0x00,0x01,0x02,0x03,
	0x04,0x05,0x06,0x07,
	0x08,0x09,0x0A,0x0B,
	0x0C,0x0D,0x0E,0x0F
};

uchar key = 0;
uchar num = 0;
uchar i = 0, k = 0;
uchar flag = 0;


void Delay_ms(unsigned int cnt);
void LED_show();
uchar KeyBoard_Scan();
void Digital_show();
void Digital_num(uchar dat);

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

// 用 switch 把键码值 0~F 翻译成数码管段码
void Digital_num(uchar dat){
	P0 = 0xff;
	switch(dat){
		case 0:
			P0 = 0xC0;
			break;
		case 1:
			P0 = 0xF9;
			break;
		case 2:
			P0 = 0xA4;
			break;
		case 3:
			P0 = 0xB0;
			break;
		case 4:
			P0 = 0x99;
			break;
		case 5:
			P0 = 0x92;
			break;
		case 6:
			P0 = 0x82;
			break;
		case 7:
			P0 = 0xF8;
			break;
		case 8:
			P0 = 0x80;
			break;
		case 9:
			P0 = 0x90;
			break;
		case 10:
			P0 = 0x88;
			break;
		case 11:
			P0 = 0x83;
			break;
		case 12:
			P0 = 0xC6;
			break;
		case 13:
			P0 = 0xA1;
			break;
		case 14:
			P0 = 0x86;
			break;
		case 15:
			P0 = 0x8E;
			break;
		default:
			P0 = 0xff;
			break;
	}
	Delay_ms(1);
}

void Digital_show(){
	uchar a, b;
	uchar val;
	val = KeyVal[key];
	a = val / 10;
	b = val % 10;

	ADDR0 = 0;
	ADDR1 = 0;
	ADDR2 = 0;
	ADDR3 = 1;
	Digital_num(b);

	ADDR0 = 1;
	ADDR1 = 0;
	ADDR2 = 0;
	ADDR3 = 1;
	Digital_num(a);
}
