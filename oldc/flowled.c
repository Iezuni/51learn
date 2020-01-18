//流水灯
#include <reg51.h>


sbit beep = P2 ^ 3;
char aa = 0xff;
void delay(int z){int a1, a2;for (a1 = 0; a1 < z; a1++){for (a2 = 0; a2 < 110; a2++){;}}}
void main()
{

	while (1)
	{
		delay(200);

		aa = aa << 1;
		P1 = aa;
		if (aa == 0x00)
		{
			aa = 0xff;
			beep = 0;
			delay(200);
			beep = 1;
		}
	}
}
