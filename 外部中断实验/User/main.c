#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;

sbit ENLED = P1^4;
sbit KeyOut1 = P2^3;
sbit KeyIn1 = P2^4;

void delay_ms(unsigned int cnt) reentrant;
unsigned char code LedChar[] = {
    0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
    0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e
};
volatile unsigned char count = 60;
volatile unsigned char run = 0;
volatile unsigned char cnt50ms = 0;

void main()
{
    unsigned char dat;
    ADDR3 = 1;
    ENLED = 0;
    KeyOut1 = 0;
    TMOD = 0x01;
    TH0 = 0x4C;
    TL0 = 0x00;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
    while(1)
    {
        dat = count % 10;
        ADDR0 = 0;
        ADDR1 = 0;
        ADDR2 = 0;
        P0 = LedChar[dat];
        delay_ms(2);
        P0 = 0xff;
        dat = count / 10;
        ADDR0 = 1;
        P0 = LedChar[dat];
        delay_ms(2);
        P0 = 0xff;
        ADDR0 = 0;
        if(KeyIn1 == 0)
        {
            delay_ms(10);
            if(KeyIn1 == 0)
            {
                if(run == 1)
                {
                    run = 0;
                }
                else
                {
                    if(count == 0)
                    {
                        count = 60;
                    }
                    run = 1;
                }
                while(KeyIn1 == 0);
            }
        }
    }
}

void Timer0() interrupt 1
{
    TH0 = 0x4C;
    TL0 = 0x00;
    cnt50ms++;
    if(cnt50ms >= 20)
    {
        cnt50ms = 0;
        if(run == 1)
        {
            if(count > 0)
            {
                count--;
            }
            else
            {
                run = 0;
            }
        }
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
