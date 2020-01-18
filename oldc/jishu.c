//计数器,延时法
#include <reg51.h>

#define uint unsigned int
#define uchar unsigned char
sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;
uchar aa = 0xff;
uchar code table[] = {
	0x3f, 0x06, 0x5b, 0x4f,
	0x66, 0x6d, 0x7d, 0x07,
	0x7f, 0x6f, 0x77, 0x7c,
	0x39, 0x5e, 0x79, 0x71};
uint ge = 0, shi = 0, bai = 0, jishu = 1;
void delay(uint z)
{
	uint a1;
	z = z * 110;
	for (a1 = 0; a1 < z; a1++)
	{
		;
	}
}
int main()
{

	while (1)
	{
		jishu++;
		if (jishu == 115)
		{
			ge = ge + 1;
			jishu = 0;
		}
		if (ge == 10)
		{
			shi = shi + 1;
			ge = 0;
		}
		if (shi == 10)
		{
			bai = bai + 1;
			shi = 0;
		}//计算显示数字
		wela = 1;
		P0 = 0xfe;
		wela = 0;
		dula = 1;
		P0 = table[bai];
		dula = 0;

		delay(2);
		wela = 1;
		P0 = 0xfd;
		wela = 0;
		dula = 1;
		P0 = table[shi];
		dula = 0;
		delay(2);

		wela = 1;
		P0 = 0xfb;
		wela = 0;
		dula = 1;
		P0 = table[ge];
		dula = 0;
		delay(2);

		aa = aa << 1;
		P1 = aa;
		if (aa == 0x00)
		{
			aa = 0xff;
		}
	}
}
