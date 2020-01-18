#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
extern char head;
extern void delay(uint x);
sbit dula = P2 ^ 6; //
sbit wela = P2 ^ 7; //数码管设置
sbit ukey = P3 ^ 4;
sbit dkey = P3 ^ 5;
sbit lkey = P3 ^ 6;
sbit rkey = P3 ^ 7;
uchar code numTable[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66,
                           0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 数字0-10
void keyscan() {                                          //扫描键盘
  if (ukey == 0) {
    delay(5);
    if (ukey == 0) {
      ////clearMatrix();
      head = 1;
      // xPoint++;
      while (!ukey)
        ;
      delay(5);
      while (!ukey)
        ;
    }
  }
  if (dkey == 0) {
    delay(5);
    if (dkey == 0) {
      // clearMatrix();
      head = 0;
      //  xPoint--;
      while (!dkey)
        ;
      delay(5);
      while (!dkey)
        ;
    }
  }
  if (rkey == 0) {
    delay(5);
    if (rkey == 0) {
      // clearMatrix();
      //  yPoint--;
      head = 3;
      while (!rkey)
        ;
      delay(5);
      while (!rkey)
        ;
    }
  }
  if (lkey == 0) {
    delay(5);
    if (lkey == 0) {
      // clearMatrix();
      // yPoint++;
      head = 2;
      while (!lkey)
        ;
      delay(5);
      while (!lkey)
        ;
    }
  }
}
void showPoint(/* a1, a2 */uint a) { //计分显示
  uint ten = 0, one = 0;
//  int a;
  if ((a % 100 - a % 10) > 0) {
    ten = (a % 100 - a % 10) / 10;
  }
  if (a % 10 > 0) {
    one = a % 10;
  }

  //ten = a1;
  //one = a2;
  wela = 1; //十位显示
  P0 = 0xfe;
  wela = 0;
  dula = 1;
  P0 = numTable[ten];
  dula = 0;
  delay(2);

  wela = 1; //个位显示
  P0 = 0xfd;
  wela = 0;
  dula = 1;
  P0 = numTable[one];
  dula = 0;
  delay(2);
}