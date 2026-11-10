#include<reg52.h>
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
void delay_ms(unsigned int cnt);
unsigned char code LedChar[] = {
	0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 
	0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e
	};
unsigned char temp = 0;    //����ȫ�ֱ���temp������������յ�������
void main()
{
	unsigned char dat;
	ADDR3 = 1;
	ENLED = 0;
	EA = 1;
	ES = 1;
	SCON = 0x50;
	PCON = 0x00;
	TMOD = 0x20;
	TH1 = 0xFD;
	TL1 = 0xFD;
	TR1 = 1;
	while(1)
	{
	   dat = temp % 16;
	   ADDR0 = 0;
	   ADDR1 = 0;
	   ADDR2 = 0;
	   P0 = LedChar[dat];
	   delay_ms(2);
	   dat = temp / 16;
	   ADDR0 = 1;
	   P0 = LedChar[dat];
	   delay_ms(2);
	}
}
void uart() interrupt 4
{
	temp = SBUF;
	while(RI == 0);
	RI = 0;
}
void delay_ms(unsigned int cnt)
{
	unsigned char i;
	while(cnt--)
	{
		for(i=0; i<=110; i++);
	}
}