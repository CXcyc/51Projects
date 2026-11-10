#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;

sbit ENLED = P1^4;
sbit KeyOut1 = P2^3;
sbit KeyINT0 = P3^2;	// INT0按键引脚
sbit KeyINT1 = P3^3;	// INT1按键引脚

void delay_ms(unsigned int cnt);
unsigned char code LedChar[] = {
    0xc0,
	0xf9,
	0xa4,
	0xb0,
	0x99,
	0x92,
	0x82,
	0xf8,
    0x80,
	0x90,
	0x88,
	0x83,
	0xc6,
	0xa1,
	0x86,
	0x8e
};

unsigned char count = 0; 

void main()
{
    unsigned char dat;
    ADDR3 = 1;
    ENLED = 0;
    KeyOut1 = 0;      
    EA = 1;           
    EX0 = 1;
    IT0= 1;
    EX1 = 1;
    IT1 = 1;
    while(1)
    {
        ADDR0 = 0;
        ADDR1 = 0;
        ADDR2 = 0;
        P0 = LedChar[count % 10];
        delay_ms(5);
        ADDR0 = 1;
        P0 = LedChar[count / 10];
        delay_ms(5);
    }
}

void Int0() interrupt 0    
{
    delay_ms(10);
    if(KeyINT0 == 0)
    {
        count++;                 
        if(count == 100)        
        {
            count = 0;
        }
    }
}

void Int1() interrupt 2    
{
    delay_ms(10);
    if(KeyINT1 == 0)
    {
        count++;                 
        if(count == 100)        
        {
            count = 0;
        }
    }
}

void delay_ms(unsigned int cnt)    
{
    unsigned char i;
    while(cnt--)
    {
        for(i=0; i<=110; i++);
    }
}