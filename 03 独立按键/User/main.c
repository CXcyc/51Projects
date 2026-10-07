#include <reg52.h>
#include <intrins.h>

sbit LED0 = P0^0;
sbit LED1 = P0^1;
sbit LED2 = P0^2;
sbit LED3 = P0^3;
sbit LED4 = P0^4;
sbit LED5 = P0^5;
sbit LED6 = P0^6;
sbit LED7 = P0^7;
sbit ADDR3 = P1^3;
sbit ADDR2 = P1^2;
sbit ADDR1 = P1^1;
sbit ADDR0 = P1^0;
sbit ENLED = P1^4;
sbit KeyIn1 = P2^4;
sbit KeyIn2 = P2^5;
sbit KeyIn3 = P2^6;
sbit KeyOu1 = P2^3;

bit flag = 0;

void Delay_ms(unsigned int cnt);

void main(){
	unsigned char led = 0x00;
	LED0 = 1;
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;
	LED4 = 1;
	LED5 = 1;
	LED6 = 1;
	LED7 = 1;
	ENLED = 0;
	ADDR3 = 1;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;
	KeyOu1 = 0;
	KeyIn1 = 1;
	KeyIn2 = 1;

	
	while(1){
		if(KeyIn1 == 0){
			Delay_ms(10);
			if(KeyIn1 == 0){
				while(KeyIn1 ==0){
					Delay_ms(5);
				}
				LED0 = 0;LED1 = 0;LED2 = 0;LED3 = 0;
			}
		}
		if(KeyIn2 == 0){
			Delay_ms(10);
			if(KeyIn2 == 0){
				while(KeyIn2 ==0){
					Delay_ms(5);
				}
				LED4 = 0;LED5 = 0;LED6 = 0;LED7 = 0;
			}
		}
		if(KeyIn3 == 0){
			Delay_ms(10);
			if(KeyIn3 == 0){
				while(KeyIn3 == 0){
					Delay_ms(5);
				}
				flag = !flag;
			}
		}
		while(flag == 1){
			P0 = ~led;
			led = (led << 1) | (led >> 7);
			Delay_ms(300);
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