#include<reg52.h>
sbit ADDR0=P1^0;
sbit ADDR1=P1^1;
sbit ADDR2=P1^2;
sbit ADDR3=P1^3;
sbit ENLED=P1^4;
unsigned char cnt=0;  //计数变量
unsigned char sec=99 , ms = 9;
unsigned char code LedChar[]={
    0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,
    0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e,
    0xff };
void delay(unsigned int k)                        // 软件延时子程序
{
unsigned int j;
 while(k--)
 {
 for(j=110;j>0;j--);                        
}                        

}
void main()
{
  ENLED=0;
  ADDR3=1;
  TMOD=0x01;
  TH0=0x4C;
  TL0=0x00;     //50毫秒初值
  EA=1;
  ET0=1;
  TR0=1;
  while(1)
  {
    unsigned char temp;
      ADDR2=0;
    ADDR1=0;
    ADDR0=0;
    temp=ms;   //十分位
    P0=LedChar[temp];
    delay(2);

    ADDR2=0;
    ADDR1=0;
    ADDR0=1;
    temp=sec%10;   //sec的个位
    P0=LedChar[temp]&0x7f;
    delay(2);
    
    ADDR2=0;
    ADDR1=1;
    ADDR0=0;
    temp=sec/10;   //sec的十位
    P0=LedChar[temp];
    delay(2);

  }
}
void timer0() interrupt 1
{
  TH0=0x4C;
  TL0=0x00;     //50毫秒初值
  cnt++;
  if(cnt==2)
  {     
    cnt=0;
    if(ms > 0){
      ms--;
    }
    else{
      ms = 9;
      if(sec > 0){
        sec--;
      }
      else{
        sec = 99;
      }
    }

  }
}