#include <reg51.h>
#define uint  unsigned int
unsigned char table0[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
static uint n,sec,min;
char m=0;

sbit HLA=P1^0;
sbit HLB=P1^1;
sbit HLC=P1^2;

void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);

}

void display()
{
    unsigned char secshi,secge,minshi,minge;
    secge=sec%10;
    secshi=sec/10;
    minge=min%10;
    minshi=min/10;
    HLA=0;HLB=0;HLC=0; //第1位
    P0=table0[minshi];
    delayms(10);

    HLA=1;HLB=0;HLC=0;  //第2位
    P0=table0[minge];
    delayms(10);

    HLA=0;HLB=1;HLC=0;  //第3位
    P0=table0[secshi];
    delayms(10);

    HLA=1;HLB=1;HLC=0;  //第4位
    P0=table0[secge];
    delayms(10);

}

void init()//初始化
{
    TMOD=0x01;
    TH0=0x3c;
    TL0=0xb0;
    EA=1;
    ET0=1;
    TR0=1;
}


void Time_0() interrupt 1  //定时器0
{
    TH0=0x3c;
    TL0=0xb0;
    m++;
    if (m>=20)
    {
        m=0;
        sec++;
        P2=~P2;
        if(sec==60)
        {
            sec=0;
            min++;
            if (min==60)
            {
            min=0;
            }
        }
    }
}


void main()
{
    init();
    P2=0x00;
	while(1)
	{
	    display();
	}
} 

