#include"reg52.h"
typedef unsigned char u8;
typedef unsigned int u16;
sbit buzzer=P2^1;

void delayms(unsigned int xms)   //��ʱ���� ����ʱxms
{
      unsigned int i , j;
          for(i = 0; i < xms; i++)
              for(j = 0; j < 110; j++);
}

void fengming()    //��������������t = 1ms ����T = 2ms Ƶ��f = 0.5khz ʵ�ʷ�����ʱ1ms��ʱ��Ч�����
{
        buzzer = 0; //��P1.5���͵͵�ƽ
        delayms(1);   //��ʱ1ms
        buzzer = 1;   //��P1.5���͸ߵ�ƽ
        delayms(1);   //��ʱ1ms
}

void main()
{
       while(1)
      {
            fengming();
       }
}




