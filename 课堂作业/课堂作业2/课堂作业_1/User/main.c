#include<reg52.h>

void delay_ms(unsigned int cnt);
void send_char(unsigned char dat);

unsigned char code str[11] = "hello world";

void main()
{
	unsigned char i;
	SCON = 0x50;
	PCON = 0x00;
	TMOD = 0x20;
	TH1 = 0xFD;
	TL1 = 0xFD;
	TR1 = 1;
	while(1)
	{
		for(i=0; i<11; i++)
		{
			send_char(str[i]);
		}
		delay_ms(1000);
	}
}
void send_char(unsigned char dat)
{
	SBUF = dat;
	while(TI == 0);
	TI = 0;
}
void delay_ms(unsigned int cnt)
{
	unsigned char i;
	while(cnt--)
	{
		for(i=0; i<=110; i++);
	}
}
