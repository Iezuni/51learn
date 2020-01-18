//led 灯1亮灭
#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char

sbit a1 = P1 ^ 0;
sbit a2 = P1 ^ 1;
sbit a3 = P1 ^ 2;
sbit a4 = P1 ^ 3;
sbit a5 = P1 ^ 4;
sbit a6 = P1 ^ 5;
sbit a7 = P1 ^ 6;
sbit beep = P2 ^ 3;

void delay(uint z)
{
	int de1, de2;
	for (de1 = 0; de1 < z; de1++)
	{
		for (de2 = 0; de2 < 110; de2++)
			;
	}
}
void main()
{
	uint a = 1;
while(a<10)
	{
		a=a+1;
		a2 = 0;
		delay(100);
		a2 = 1;
		delay(100);
	}
	while(1);
}
