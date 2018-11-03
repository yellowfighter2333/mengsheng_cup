#include"reg52.h"
typedef unsigned char u8;
typedef unsigned int u16;
sbit buzzer=P2^1;

void delayms(unsigned int xms)   //延时函数 ，延时xms
{
      unsigned int i , j;
          for(i = 0; i < xms; i++)
              for(j = 0; j < 110; j++);
}

void fengming()    //蜂鸣函数，脉宽t = 1ms 周期T = 2ms 频率f = 0.5khz 实际发现延时1ms的时候效果最好
{
        buzzer = 0; //给P1.5口送低电平
        delayms(1);   //延时1ms
        buzzer = 1;   //给P1.5口送高电平
        delayms(1);   //延时1ms
}

void main()
{
       while(1)
      {
            fengming();
       }
}




