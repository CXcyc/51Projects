#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;

sbit ENLED = P1^4;

void delay_ms(unsigned int t);
unsigned char KeyScan();
void DigShow();

unsigned char code LedChar[] = {
    0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
    0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e
};

unsigned char code KeyCode[] = {
    0xE7, 0xD7, 0xB7, 0x77,
    0xEB, 0xDB, 0xBB, 0x7B,
    0xED, 0xDD, 0xBD, 0x7D,
    0xEE, 0xDE, 0xBE, 0x7E
};

unsigned char code KeyNum[] = {
    1, 2, 3, 10,
    4, 5, 6, 10,
    7, 8, 9, 10,
    0, 10, 10, 10
};

unsigned char num[6] = {0, 0, 0, 0, 0, 0};
unsigned char cnt = 0;

void main()
{
    unsigned char key;

    ADDR3 = 1;
    ENLED = 0;

    while(1)
    {
        if(cnt < 6)
        {
            key = KeyScan();
            if(key < 10)
            {
                num[cnt] = key;
                cnt++;
            }
        }
        DigShow();
    }
}

unsigned char KeyScan()
{
    unsigned char scan1;
    unsigned char scan2;
    unsigned char i;

    P2 = 0xf0;
    scan1 = P2;
    if((scan1 & 0xf0) != 0xf0)
    {
        delay_ms(10);
        P2 = 0xf0;
        scan1 = P2;
        if((scan1 & 0xf0) != 0xf0)
        {
            P2 = 0x0f;
            scan2 = P2;
            scan1 = scan1 | scan2;
            while((P2 & 0x0f) != 0x0f);
            for(i = 0; i < 16; i++)
            {
                if(scan1 == KeyCode[i])
                {
                    return KeyNum[i];
                }
            }
        }
    }

    return 10;
}

void DigShow()
{
    P0 = 0xff;
    ADDR0 = 1;
    ADDR1 = 0;
    ADDR2 = 1;
    P0 = LedChar[num[0]];
    delay_ms(2);

    P0 = 0xff;
    ADDR0 = 0;
    ADDR1 = 0;
    ADDR2 = 1;
    P0 = LedChar[num[1]];
    delay_ms(2);

    P0 = 0xff;
    ADDR0 = 1;
    ADDR1 = 1;
    ADDR2 = 0;
    P0 = LedChar[num[2]];
    delay_ms(2);

    P0 = 0xff;
    ADDR0 = 0;
    ADDR1 = 1;
    ADDR2 = 0;
    P0 = LedChar[num[3]];
    delay_ms(2);

    P0 = 0xff;
    ADDR0 = 1;
    ADDR1 = 0;
    ADDR2 = 0;
    P0 = LedChar[num[4]];
    delay_ms(2);

    P0 = 0xff;
    ADDR0 = 0;
    ADDR1 = 0;
    ADDR2 = 0;
    P0 = LedChar[num[5]];
    delay_ms(2);
}

void delay_ms(unsigned int t)
{
    unsigned char i;
    while(t--)
    {
        for(i = 0; i <= 110; i++);
    }
}
