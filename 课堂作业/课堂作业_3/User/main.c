#include<reg52.h>
sbit ADDR0=P1^0;
sbit ADDR1=P1^1;
sbit ADDR2=P1^2;
sbit ADDR3=P1^3;
sbit ENLED=P1^4;
unsigned char cnt=0;          //50ms计数
/*时、分、秒各用两位（十位、个位）分别计数*/
unsigned char sec_shi=0,sec_ge=0;     //秒十位、秒个位
unsigned char min_shi=0,min_ge=0;     //分十位、分个位
unsigned char hour_shi=0,hour_ge=0;   //时十位、时个位
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
    ADDR2=0;
    ADDR1=0;
    ADDR0=0;
    P0=LedChar[sec_ge];          //秒个位
    delay(2);

    ADDR2=0;
    ADDR1=0;
    ADDR0=1;
    P0=LedChar[sec_shi];         //秒十位
    delay(2);
    
    ADDR2=0;
    ADDR1=1;
    ADDR0=0;
    P0=LedChar[min_ge]&0x7f;     //分个位
    delay(2);

    ADDR2=0;
    ADDR1=1;
    ADDR0=1;
    P0=LedChar[min_shi];         //分十位
    delay(2);
    
    ADDR2=1;
    ADDR1=0;
    ADDR0=0;
    P0=LedChar[hour_ge]&0x7f;    //时个位
    delay(2);

    ADDR2=1;
    ADDR1=0;
    ADDR0=1;
    P0=LedChar[hour_shi];        //时十位
    delay(2);
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

    sec_ge++;                    //秒个位计数：0~9
    if(sec_ge>=10)
    {
      sec_ge=0;
      sec_shi++;                 //秒个位满10，秒十位进位：0~5
      if(sec_shi>=6)
      {
        sec_shi=0;
        min_ge++;                //秒满60，分个位进位
        if(min_ge>=10)
        {
          min_ge=0;
          min_shi++;             //分个位满10，分十位进位：0~5
          if(min_shi>=6)
          {
            min_shi=0;
            hour_ge++;           //分满60，时个位进位
            if(hour_shi==2)      //20~23时，时个位只能到3
            {
              if(hour_ge>=4)
              {
                hour_ge=0;
                hour_shi=0;      //时归零：00点
                flag=1;          //到整点，开始报时
                report_cnt=0;
                blink_cnt=0;
              }
            }
            else if(hour_ge>=10) //09、19时个位满10，时十位进位
            {
              hour_ge=0;
              hour_shi++;
            }
          }
        }
      }
    }
  }
}
