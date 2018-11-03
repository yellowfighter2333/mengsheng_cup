#include<reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;
//下面的函数用来初始化一些设定

//需要定义一下的位置
sbit echo = P2^0;
sbit buzzer = P2^1;
bit flag = 0;
bit sign = 0;
u16 count;
u16 time=0;
u16 distance;
void init()
{
	SCON=0X50;	 /*SCON寄存器是串行口控制寄存器
				 采用方式1，设定串行通信为10位异步收发，波特率可变(由定时器的溢出率决定)*/
	TMOD=0X21;		//计时器的方式采用方式2，8位自填充的计时器，计时器1用来串口通信
					//而计时器0是用来得到距离
	PCON=0X80;	 //该寄存器是电源管理寄存器，最后一位是SMOD
	TH1=0XF4;	 //计数器初始设定 注意波特率是4800
	TL1=0XF4;
	TH0=0;
	TL0=0;
	ES=1;	     //打开接收中断
	ET0=1;        //允许T0中断
	EA=1;		 //打开总中断 
	TR1=1;	  //打开计时器
	
}
void delayms(u16 n)//该函数是用来延时，当n为1是，延时为1ms
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
	TL0=0;//计数器清零

	distance=(time*1.7)/100;

}
void main(void)
{
	init();

	while(1)
	{
	   //用于初始化定时器2
	   RCAP2H=(65536-250)/256;//给T2设定初值
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
	flag=1;//中断溢出标志
	buzzer=~buzzer;
}
void usart() interrupt 4//此处不确定中断的口
{
	  SBUF=distance;

	  while(!TI);	   //等待发送数据完成
	  TI=0;				//清除发送完成标志位

}


void Timer_Server(void)interrupt 5
{
	  TF2=0;
	  buzzer=~buzzer;
	  sign = 1;
}

