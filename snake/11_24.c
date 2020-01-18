#include "reg52.h"
sbit key = P3 ^ 6;
int num = 0;   // num模式计数,
int litp = 0;  // litp灯亮位数,
int pa = 0xff; // pa 16进制计数,
int flag = 0;  // flag循环标志,
int sgLit = 0;// sgLit 单组灯亮计数
int kmod = 0;               // 
int tick = 0; //循环次数
int p[] = {127, 191, 223, 239, 247, 251, 253, 254};
int p0[] = {1, 3, 7, 15, 31, 63, 127, 255};
void delay(int z) {
  int x, y;
  for (x = z; x > 0; x--)
    for (y = 110; y > 0; y--)
      ;
}
void keyscan() { //扫描
  if (key == 0) {
    delay(5);
    if (key == 0) {
      num++;
      num == 7 ? num = 0 : 0;
      P0 = 0xff, P2 = 0xff, litp = 0, pa = 0xff, sgLit = 0, flag = 0,
      tick = 0; //重置
      while (!key)
        ;
      delay(5);
      while (!key)
        ;
    }
  } else {
  }
}
void ledlit() { //点亮led
  switch (num) {
  case 0: //长亮
    P0 = ~P0;
    P2 = ~P2;
    delay(5);
    break;
  case 1: // rgb亮
    P0 = 0;
    P2 = 0;
    break;
  case 2: //单组组转圈
    sgLit == 0 ? P0 = p[litp] : 0;
    sgLit == -1 ? P2 = p[litp] : 0;
    delay(150);
    litp++;
    if (litp == 8) {
      P0 = 0xff;
      P2 = 0xff;
      litp = 0;
      sgLit = ~sgLit;
    }
    tick++;
    tick == 32 ? num++ : 0;
    break;
  case 3: //两组转圈
    P0 = p[litp];
    P2 = p[litp];
    delay(200);
    litp++;
    litp == 8 ? litp = 0 : 0;
    break;
  case 4: //二进制灯
    P0 = pa;
    P2 = pa;
    delay(100);
    pa--;
    pa < 0 ? pa = 0xff : 0;
    break;
  case 5: //渐变亮
    if (flag == 0) {
      litp = 0;
      P0 = pa;
      P2 = ~pa;
      pa = pa << 1;
      pa == 0 ? flag = 1 : 0;
    } else {
      pa = 0xff;
      P0 = p0[litp];
      P2 = ~p0[litp];
      litp++;
      litp == 8 ? flag = 0 : 0;
    }
    delay(150);
    break;
  default: //关机
    P0 = 0xff;
    P2 = 0xff;
    break;
  }
}
int main() {
  P3 = 0xff;
  while (1) {
    keyscan();
    ledlit();
  }
  return 0;
}


