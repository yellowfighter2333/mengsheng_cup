#include<reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;
//����ĺ���������ʼ��һЩ�趨

//��Ҫ����һ�µ�λ��
sbit echo = P2^0;
sbit buzzer = P2^1;
bit flag = 0;
bit sign = 0;
u16 count;
u16 time=0;
u16 distance;
void init()
{
	SCON=0X50;	 /*SCON�Ĵ����Ǵ��пڿ��ƼĴ���
				 ���÷�ʽ1���趨����ͨ��Ϊ10λ�첽�շ��������ʿɱ�(�ɶ�ʱ��������ʾ���)*/
	TMOD=0X21;		//��ʱ���ķ�ʽ���÷�ʽ2��8λ�����ļ�ʱ������ʱ��1��������ͨ��
					//����ʱ��0�������õ�����
	PCON=0X80;	 //�üĴ����ǵ�Դ����Ĵ��������һλ��SMOD
	TH1=0XF4;	 //��������ʼ�趨 ע�Ⲩ������4800
	TL1=0XF4;
	TH0=0;
	TL0=0;
	ES=1;	     //�򿪽����ж�
	ET0=1;        //����T0�ж�
	EA=1;		 //�����ж� 
	TR1=1;	  //�򿪼�ʱ��
	
}
void delayms(u16 n)//�ú�����������ʱ����nΪ1�ǣ���ʱΪ1ms
{
	u16 i,j;
	for(i=n;i>0;i--)
	{
		for(j=110;j>0;j--);
				  
	}

}
void calculate_distance()
{
	time=TH0*256+TL0;
	TH0=0;
	TL0=0;//����������

	distance=(time*1.7)/100;

}
void main(void)
{
	init();

	while(1)
	{
	   //���ڳ�ʼ����ʱ��2
	   RCAP2H=(65536-250)/256;//��T2�趨��ֵ
	   RCAP2L=(65536-250)%256;
	   for(count=500;count=0;count--)
	   {
	   		sign=0;
			while(!sign);
	   }
	   delayms(200);
	   while(!echo);
	   TR0=1;
	   while(echo);
	   TR0=0;
	   calculate_distance();
	   delayms(80);
	  
	}


}
void out_of_Range()	 interrupt 1
{
	flag=1;//�ж������־
	buzzer=~buzzer;
}
void usart() interrupt 4//�˴���ȷ���жϵĿ�
{
	  SBUF=distance;

	  while(!TI);	   //�ȴ������������
	  TI=0;				//���������ɱ�־λ

}


void Timer_Server(void)interrupt 5
{
	  TF2=0;
	  buzzer=~buzzer;
	  sign = 1;
}

