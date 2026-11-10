#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;

sbit ENLED = P1^4;
sbit KeyINT1 = P3^3;

void delay_ms(unsigned int cnt);

void main()
{
    ENLED = 0;
    ADDR3 = 1;
    ADDR2 = 1;
    ADDR1 = 1;
    ADDR0 = 0;
    P0 = 0xFF;

    EA = 1;
    EX0 = 1;
    IT0 = 1;

    while(1);
}

void Int0() interrupt 0
{
    delay_ms(10);
    if(KeyINT1 == 0)
    {
        P0 = 0xFF;
        P0 &= ~(0x01 << 1) & 0x07;
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
