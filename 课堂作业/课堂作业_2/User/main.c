#include<reg52.h>
sbit ADDR0=P1^0;
sbit ADDR1=P1^1;
sbit ADDR2=P1^2;
sbit ADDR3=P1^3;
sbit ENLED=P1^4;
unsigned char cnt=0;          //50ms计数
unsigned char sec=0,min=0,hour=0;
unsigned char flag=0;         //1=正在整点报时
unsigned char led=0;          //1=LED亮 0=LED灭
unsigned char report_cnt=0;   //报时计时，200个50ms=10秒
unsigned char blink_cnt=0;    //闪烁计时，10个50ms=0.5秒
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
    temp=sec%10;   //sec=45,个位是5
    P0=LedChar[temp];     // P0=0x92
    delay(2);

    ADDR2=0;
    ADDR1=0;
    ADDR0=1;
    temp=sec/10;   //sec的十位
    P0=LedChar[temp];     // P0=0x92
    delay(2);
    
    ADDR2=0;
    ADDR1=1;
    ADDR0=0;
    temp=min%10;   //min的个位
    P0=LedChar[temp]&0x7f;     // P0=0x92
    delay(2);

    ADDR2=0;
    ADDR1=1;
    ADDR0=1;
    temp=min/10;   //min的十位
    P0=LedChar[temp];     // P0=0x92
    delay(2);
    
    ADDR2=1;
    ADDR1=0;
    ADDR0=0;
    temp=hour%10;   //hour的个位
    P0=LedChar[temp]&0x7f;     // P0=0x92
    delay(2);

    ADDR2=1;
    ADDR1=0;
    ADDR0=1;
    temp=hour/10;   //hour的个位
    P0=LedChar[temp];     
    delay(2);
    if(led==1)              //整点报时：选中74HC138的Y6(S6)，LED亮
    {
      ADDR2 = 1;
      ADDR1 = 1;
      ADDR0 = 0;
      delay(2);
    }
  }
}
void timer0() interrupt 1
{
  TH0=0x4C;
  TL0=0x00;     //50毫秒初值

  cnt++;
  if(cnt==20)
  {     
     cnt=0;
       sec++;
    if(sec==60)
    {
         sec=0;
        min++;
        if(min==60)
        {
          min=0;
          hour++;
          if(hour==24)
           hour=0;
          flag=1;               //到整点，开始报时
          report_cnt=0;
          blink_cnt=0;
        }
    }
 }

  if(flag==1)                   //整点报时：闪10秒
  {
    report_cnt++;
    if(report_cnt==200)         //200个50ms=10秒，报时结束
    {
      flag=0;
      led=0;
      report_cnt=0;
      blink_cnt=0;
    }
    else
    {
      blink_cnt++;
      if(blink_cnt==10)         //10个50ms=0.5秒，翻转一次
      {
        blink_cnt=0;
        if(led==0)
         led=1;
        else
         led=0;
      }
    }
  }
}