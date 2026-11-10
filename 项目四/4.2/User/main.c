#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;

sbit ENLED = P1^4;

void delay_ms(unsigned int t);
unsigned char KeyScan();
void Timer0Init();

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
    1,  2,  3,  4,
    5,  6,  7,  8,
    9,  10, 11, 12,
    13, 14, 15, 16
};

unsigned char code Addr0Tab[] = {1, 0, 1, 0, 1, 0};
unsigned char code Addr1Tab[] = {0, 0, 1, 1, 0, 0};
unsigned char code Addr2Tab[] = {1, 1, 0, 0, 0, 0};

unsigned char hour = 12;
unsigned char minu = 0;
unsigned char sec  = 0;

unsigned char disp[6] = {0, 0, 0, 0, 0, 0};

unsigned int  ms_cnt   = 0;
unsigned char scan_i   = 0;
unsigned char set_mode = 1;

void main()
{
    unsigned char key;

    ADDR3 = 1;
    ENLED = 0;

    Timer0Init();

    while(1)
    {
        key = KeyScan();

        if(key == 16)
        {
            ms_cnt = 0;
            set_mode++;
            if(set_mode > 3)
            {
                set_mode = 1;
            }
        }
        else if(key == 4)
        {
            if(set_mode == 1)
            {
                hour++;
                if(hour >= 24)
                {
                    hour = 0;
                }
            }
            else if(set_mode == 2)
            {
                minu++;
                if(minu >= 60)
                {
                    minu = 0;
                }
            }
            else if(set_mode == 3)
            {
                sec++;
                if(sec >= 60)
                {
                    sec = 0;
                }
                ms_cnt = 0;
            }
        }
        else if(key == 12)
        {
            if(set_mode == 1)
            {
                if(hour == 0)
                {
                    hour = 23;
                }
                else
                {
                    hour--;
                }
            }
            else if(set_mode == 2)
            {
                if(minu == 0)
                {
                    minu = 59;
                }
                else
                {
                    minu--;
                }
            }
            else if(set_mode == 3)
            {
                if(sec == 0)
                {
                    sec = 59;
                }
                else
                {
                    sec--;
                }
                ms_cnt = 0;
            }
        }
    }
}

void Timer0Init()
{
    TMOD = 0x01;
    TH0 = 0xFC;
    TL0 = 0x66;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void Timer0Isr() interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x66;

    disp[0] = hour / 10;
    disp[1] = hour % 10;
    disp[2] = minu / 10;
    disp[3] = minu % 10;
    disp[4] = sec / 10;
    disp[5] = sec % 10;

    P0 = 0xff;
    ADDR0 = Addr0Tab[scan_i];
    ADDR1 = Addr1Tab[scan_i];
    ADDR2 = Addr2Tab[scan_i];

    if(scan_i == 1 || scan_i == 3)
    {
        P0 = LedChar[disp[scan_i]] & 0x7f;
    }
    else
    {
        P0 = LedChar[disp[scan_i]];
    }

    scan_i++;
    if(scan_i >= 6)
    {
        scan_i = 0;
    }

    ms_cnt++;
    if(ms_cnt >= 1000)
    {
        ms_cnt = 0;
        sec++;
        if(sec >= 60)
        {
            sec = 0;
            minu++;
            if(minu >= 60)
            {
                minu = 0;
                hour++;
                if(hour >= 24)
                {
                    hour = 0;
                }
            }
        }
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

    return 0;
}

void delay_ms(unsigned int t)
{
    unsigned char i;
    while(t--)
    {
        for(i = 0; i <= 110; i++);
    }
}
