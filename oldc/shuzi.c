//显示2019
#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char
sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;
uchar code table[] = {
	0x3f, 0x06, 0x5b, 0x4f,
	0x66, 0x6d, 0x7d, 0x07,
	0x7f, 0x6f, 0x77, 0x7c,
	0x39, 0x5e, 0x79, 0x71};
void delay(uint z)
{
	uint a1, a2;
	for (a1 = 0; a1 < z; a1++)
	{
		for (a2 = 0; a2 < 110; a2++)
		{
			;
		}
	}
}
int main()
{
	while (1)
	{
		wela = 1;
		P0 = 0xfe;
		wela = 0;
		dula = 1;
		P0 = table[1];
		dula = 0;
		delay(2);
		wela = 1;
		P0 = 0xfd;
		wela = 0;
		dula = 1;
		P0 = table[9];
		dula = 0;
		delay(2);
		wela = 1;
		P0 = 0xfb;
		wela = 0;
		dula = 1;
		P0 = table[0];
		dula = 0;
		delay(2);
		wela = 1;
		P0 = 0xf7;
		wela = 0;
		dula = 1;
		P0 = 0xdb;
		dula = 0;
		delay(2);
		wela = 1;
		P0 = 0xef;
		wela = 0;
		dula = 1;
		P0 = table[1];
		dula = 0;
		delay(2);
		wela = 1;
		P0 = 0xdf;
		wela = 0;
		dula = 1;
		P0 = table[7];
		dula = 0;
		delay(2);
	}
}
