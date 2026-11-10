#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
sbit KeyOut1 = P2^3;
sbit KeyIn1 = P3^2;

void delay_ms(unsigned int cnt);
unsigned char code LedChar[] = {
    0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
    0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e
};

unsigned char led_dat = 0x01;

void main()
{
    ADDR3 = 1;
    ENLED = 0;
    KeyOut1 = 0;

    EA = 1;
    EX0 = 1;
    IT0 = 1;

    while(1)
    {
        P0 = ~led_dat;
        ADDR0 = 0;
        ADDR1 = 1;
        ADDR2 = 1;
        delay_ms(5);
    }
}

void ExInt0() interrupt 0
{
    delay_ms(20);

    if(KeyIn1 == 0)
    {
        led_dat = led_dat << 1;
        if(led_dat == 0x00)
        {
            led_dat = 0x01;
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