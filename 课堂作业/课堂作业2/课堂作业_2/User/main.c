#include<reg52.h>

void send_char(unsigned char dat);

void main()
{
	unsigned char dat;
	SCON = 0x50;
	PCON = 0x00;
	TMOD = 0x20;
	TH1 = 0xFD;
	TL1 = 0xFD;
	TR1 = 1;
	while(1)
	{
		while(RI == 0);
		RI = 0;
		dat = SBUF;
		send_char(dat);
	}
}
void send_char(unsigned char dat)
{
	SBUF = dat;
	while(TI == 0);
	TI = 0;
}
