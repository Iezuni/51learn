//计时器1,延时法
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
uint fs = 0, fg = 0, ms = 0, mg = 0, jishu = 1;
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
		if (jishu == 95)
		{
			mg = mg + 1;
			jishu = 0;
		} //秒计数

		if (mg == 10)
		{
			ms = ms + 1;
			mg = 0;
		} //秒个位进位

		if (ms == 6)
		{
			fg = fg + 1;
			ms = 0;
		} //秒十位进位

		if (fg == 10)
		{
			fs = fs + 1;
			fg = 0;
		} //分个位计数

		//		if (fs == 6)
		//		{
		//			fs = fs + 1;
		//			fs = 0;
		//		} //分十位计数

		wela = 1; //分十位
		P0 = 0xfe;
		wela = 0;
		dula = 1;
		P0 = table[fs];
		dula = 0;

		delay(2); //分个位
		wela = 1;
		P0 = 0xfd;
		wela = 0;
		dula = 1;
		P0 = table[fg];
		dula = 0;
		delay(2);

		if ((jishu > 5 && jishu < 35)||(jishu > 60 && jishu < 90))
		{
			wela = 1; //:号
			P0 = 0xfb;
			wela = 0;
			dula = 1;
			P0 = 0x86;
			dula = 0;
			delay(2);
		}

		wela = 1; //秒十位
		P0 = 0xf7;
		wela = 0;
		dula = 1;
		P0 = table[ms];
		dula = 0;
		delay(2);

		wela = 1; //秒个位
		P0 = 0xef;
		wela = 0;
		dula = 1;
		P0 = table[mg];
		dula = 0;
		delay(2);

		{
			aa = aa << 1;
			P1 = aa;
			if (aa == 0x00)
			{
				aa = 0xff;
			} //流水灯
		}
	}
}