#include <reg51.h>
#define uint  unsigned int
unsigned char table0[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
char sec=5,min=0;att=24;
char m=0;
char Lakers_score=0;
char Warrior_score=0;

sbit HLA=P1^0;
sbit HLB=P1^1;
sbit HLC=P1^2;
sbit HHA=P1^4;
sbit HHB=P1^5;
sbit HHC=P1^6;
sbit BEEP=P2^7;
sbit LED=P2^0;
sbit Change=P2^1;
sbit key_att=P2^2;
sbit score_1=P2^3;
sbit score_2=P2^4;
sbit score_3=P2^5;


void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);

}

void display()
{
    unsigned char secshi,secge,minshi,minge,attge,attshi;
    secge=sec%10;
    secshi=sec/10;
    minge=min%10;
    minshi=min/10;
    attge=att%10;
    attshi=att/10;

    HLA=0;HLB=0;HLC=0; //第1位
    P0=table0[minshi];
    delayms(1);

    HLA=1;HLB=0;HLC=0;  //第2位
    P0=table0[minge];
    delayms(1);

    HLA=0;HLB=1;HLC=0;  //第3位
    P0=table0[secshi];
    delayms(1);

    HLA=1;HLB=1;HLC=0;  //第4位
    P0=table0[secge];
    delayms(1);

    HLA=0;HLB=0;HLC=1;  //第5位
    P0=table0[attshi];
    delayms(1);

    HLA=1;HLB=0;HLC=1;  //第6位
    P0=table0[attge];
    delayms(1);
    P0=0x00;          //消影

}

void display_score()
{
    unsigned char Lakers_scorege,Lakers_scoreshi,Warrior_scorege,Warrior_scoreshi;
    Lakers_scorege=Lakers_score%10;
    Lakers_scoreshi=Lakers_score/10;
    Warrior_scorege=Warrior_score%10;
    Warrior_scoreshi=Warrior_score/10;

    HHA=0;HHB=0;HHC=0; //第1位
    P3=table0[Lakers_scoreshi];
    delayms(1);

    HHA=1;HHB=0;HHC=0;  //第2位
    P3=table0[Lakers_scorege];
    delayms(1);

    HHA=0;HHB=1;HHC=0;  //第3位
    P3=table0[Warrior_scoreshi];
    delayms(1);

    HHA=1;HHB=1;HHC=0;  //第4位
    P3=table0[Warrior_scorege];
    delayms(1);
    P0=0x00;
}

void light_falsh()
{
    LED=~LED;
    delayms(50);
}

void speak()
{
    if (sec==0&&min==0)
    {
        att=0;
    }
    if (att==0)
    {
        BEEP=!BEEP;
    }
}

void keyscan()
{
    if (key_att==0)
    {
        delayms(5);
        if(key_att==0)
        att=24;
        while(!key_att);
    }
    if (Change==1)
    {
        if (score_1==0)
        {
            delayms(5);
            if (score_1==0)
            Lakers_score+=1;
            while(!score_1);
        }
        if (score_2==0)
        {
            delayms(5);
            if (score_2==0)
            Lakers_score+=2;
            while(!score_2);

        }
        if (score_3==0)
        {
            delayms(5);
            if (score_3==0)
            Lakers_score+=3;
            while(!score_3);
        }
    }
    else
    {
        if (score_1==0)
        {
            delayms(5);
            if (score_1==0)
            Warrior_score+=1;
            while(!score_1);
        }
        if (score_2==0)
        {
            delayms(5);
            if (score_2==0)
            Warrior_score+=2;
            while(!score_2);

        }
        if (score_3==0)
        {
            delayms(5);
            if (score_3==0)
            Warrior_score+=3;
            while(!score_3);
        }
    }
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
        sec--;
        att--;
        if (att<0)
        {
            att=0;
        }
        if(sec<=0)
        {
            min--;
            sec=59;
            if (min<0)
            {
            min=0;
            sec=0;
            light_falsh();
            }
        }
    }
}


void main()
{
    init();
    LED=1;
	while(1)
	{
	    display();
	    display_score();
	    keyscan();
	    speak();
	}
} 

