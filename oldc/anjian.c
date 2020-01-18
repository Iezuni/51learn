#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;
//sbit key1 = P3 ^ 4;
uchar /*  code */ table[] = {
	0x3f, 0x06, 0x5b, 0x4f,
	0x66, 0x6d, 0x7d, 0x07,
	0x7f, 0x6f, 0x77, 0x7c,
	0x39, 0x5e, 0x79, 0x71, 0};
int disnum[6] = {1, 2, 3, 4, 4, 0};
uchar num, temp, zzs;
void delay(uint z)
{
	uint x, y;
	for (x = z; x > 0; x--)
		for (y = 110; y > 0; y--)
			;
}
int movenum(int zz)
{
	// if ((disnum[0] != zz) /* || (zzs ==40) */)
	// {
	disnum[5] = disnum[4];
	disnum[4] = disnum[3];
	disnum[3] = disnum[2];
	disnum[2] = disnum[1];
	disnum[1] = disnum[0];
	disnum[0] = zz;
	zzs = 0;
	// }
	// else
	// {
	// 	zzs++;
	// }
	return 0;
}
int clearx(int zz)
{
	disnum[5] = 0;
	disnum[4] = 0;
	disnum[3] = 0;
	disnum[2] = 0;
	disnum[1] = 0;
	disnum[0] = 0;
	return 0;
}
uchar keyscan();
void display(uchar aa);
void main()
{
	num = 17;
	dula = 1;
	P0 = 0;
	dula = 0;
	wela = 1;
	P0 = 0xc0;
	wela = 0;

	while (1)
	{
		display(keyscan());
	}
}
void display(uchar aa)
{

	wela = 1;
	P0 = 0xdf;
	wela = 0;
	dula = 1;
	P0 = table[disnum[0]];
	dula = 0;

	delay(2);
	wela = 1;
	P0 = 0xef;
	wela = 0;
	dula = 1;
	P0 = table[disnum[1]];
	dula = 0;
	delay(2);

	wela = 1;
	P0 = 0xf7;
	wela = 0;
	dula = 1;
	P0 = table[disnum[2]];
	dula = 0;
	delay(2);

	wela = 1;
	P0 = 0xfb;
	wela = 0;
	dula = 1;
	P0 = table[disnum[3]];
	dula = 0;
	delay(2);

	wela = 1;
	P0 = 0xfd;
	wela = 0;
	dula = 1;
	P0 = table[disnum[4]];
	dula = 0;
	delay(2);

	wela = 1;
	P0 = 0xfe;
	wela = 0;
	dula = 1;
	P0 = table[disnum[5]];
	dula = 0;
	delay(2);
}
uchar keyscan()
{
	P3 = 0xfe;
	temp = P3;
	temp = temp & 0xf0;
	while (temp != 0xf0)
	{
		delay(5);
		temp = P3;
		temp = temp & 0xf0;
		while (temp != 0xf0)
		{
			temp = P3;
			switch (temp)
			{
			case 0xee:
				movenum(0);
				num = 0;
				break;
			case 0xde:
				movenum(1);
				num = 1;
				break;
			case 0xbe:
				movenum(2);
				num = 2;
				break;
			case 0x7e:
				movenum(3);
				num = 3;
				break;
			}
			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
		}
	}

	P3 = 0xfd;
	temp = P3;
	temp = temp & 0xf0;
	while (temp != 0xf0)
	{
		delay(5);
		temp = P3;
		temp = temp & 0xf0;
		while (temp != 0xf0)
		{
			temp = P3;
			switch (temp)
			{
			case 0xed:
				movenum(4);
				num = 4;
				break;
			case 0xdd:
				movenum(5);
				num = 5;
				break;
			case 0xbd:
				movenum(6);
				num = 6;
				break;
			case 0x7d:
				movenum(7);
				num = 7;
				break;
			}
			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
		}
	}

	P3 = 0xfb;
	temp = P3;
	temp = temp & 0xf0;
	while (temp != 0xf0)
	{
		delay(5);
		temp = P3;
		temp = temp & 0xf0;
		while (temp != 0xf0)
		{
			temp = P3;
			switch (temp)
			{
			case 0xeb:
				movenum(8);
				num = 8;
				break;
			case 0xdb:
				movenum(9);
				num = 9;
				break;
			case 0xbb:
				clearx(1);
				num = 10;
				break;
			case 0x7b:
				num = 11;
				break;
			}
			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
		}
	}

	P3 = 0xf7;
	temp = P3;
	temp = temp & 0xf0;
	while (temp != 0xf0)
	{
		delay(5);
		temp = P3;
		temp = temp & 0xf0;
		while (temp != 0xf0)
		{
			temp = P3;
			switch (temp)
			{
			case 0xe7:
				num = 12;
				break;
			case 0xd7:
				num = 13;
				break;
			case 0xb7:
				num = 14;
				break;
			case 0x77:
				clearx(11);
				num = 15;
				break;
			}
			while (temp != 0xf0)
			{
				temp = P3;
				temp = temp & 0xf0;
			}
		}
	}

	return num;
}
