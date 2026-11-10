#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;

sbit ENLED = P1^4;
sbit KeyOut1 = P2^3;
sbit KeyIn = P3^2;

void delay_ms(unsigned int cnt) reentrant;
unsigned char code LedChar[] = {
    0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
    0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e
};
volatile unsigned char count = 0; 

void main()
{
    unsigned char dat;
    ADDR3 = 1;
    ENLED = 0;
    KeyOut1 = 0;      
    EA = 1;           
    EX0 = 1;
    IT0= 1;           
    while(1)
    {
        dat = count % 10; 
        ADDR0 = 0;
        ADDR1 = 0;
        ADDR2 = 0;
        P0 = LedChar[dat];
        delay_ms(2);
        dat = count / 10; 
        ADDR0 = 1;
        P0 = LedChar[dat];
        delay_ms(2);
    }
}

void ExInt0() interrupt 0    
{
    delay_ms(10);
    if(KeyIn == 0)
    {
        count++;             
        if(count == 100)        
        {
            count = 0;
        }
        while(KeyIn == 0);
    }
}

void delay_ms(unsigned int cnt) reentrant   
{
    unsigned char i;
    while(cnt--)
    {
        for(i=0; i<=110; i++);
    }
}