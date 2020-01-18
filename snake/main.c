//#include <intrins.h>
#include "stdlib.h"
//#include "time.h"
#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int
#define uc uchar code
//????Max7219???
sbit Max7219_pinCLK = P2 ^ 2; //点阵灯设置
sbit Max7219_pinCS = P2 ^ 1;  //
sbit Max7219_pinDIN = P2 ^ 0; //点阵灯设置
extern void Write_Max7219_byte(uchar DATA);
extern void Write_Max7219(uchar address, uchar dat);
extern void Init_MAX7219(void);
extern void keyscan();
extern void showPoint(a1, a2 /* uint a */);
sbit dula = P2 ^ 6; //
sbit wela = P2 ^ 7; //数码管设置
sbit ukey = P3 ^ 4;
sbit dkey = P3 ^ 5;
sbit lkey = P3 ^ 6;
sbit rkey = P3 ^ 7;
sbit beep = P2 ^ 3;
uint snakePoint = 3; //分数
uint ticket = 0;
int xPoint = 0, yPoint = 0; // x轴,y轴
char head = 0;              //蛇头朝向 0;上,1:下,2:坐,3:右
uchar matrix[8][8] = {      //点阵点亮数组
    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
uchar showMatrix[8] = {0xff, 0, 0, 0, 0, 0, 0, 0}; //屏幕显示数组

char showSnake[][2] = { //蛇的身子
    {5, 5},   {3, 3},   {3, 4},   {-1, -1}, {-1, -1}, {-1, -1},
    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1},
    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1},
    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1},
    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
uchar code disp1[][8] = {
    {0xff, 129, 129, 129, 129, 129, 129, 0xff}, // 0//动画s
    {0, 126, 66, 66, 66, 66, 126, 0},           // 1
    {0, 0, 60, 36, 36, 60, 0, 0},               // 2
    {0, 0, 0, 24, 24, 0, 0, 0},                 // 3//动画e
    {0, 0xff, 0x24, 0xff, 0x24, 0x44, 0x84, 0}  //开	 //开局效果
};
void delay(uint x) {
  uint i, j;
  for (i = 0; i < x; i++)
    for (j = 0; j < 112; j++)
      ;
}
//-------------------------------------------------------------------------
void clearMatrix() { //清空8*8数组
  int a, b;
  for (a = 0; a < 8; a++) {
    for (b = 0; b < 8; b++) {
      matrix[a][b] = 0;
    }
    //  showMatrix[a] = 0;
  }
}
char twototen(char xz[8]) { //转化  将8*8数组转换到8行数组中
  char ret = 0;
  ret += xz[0] * 128;
  ret += xz[1] * 64;
  ret += xz[2] * 32;
  ret += xz[3] * 16;
  ret += xz[4] * 8;
  ret += xz[5] * 4;
  ret += xz[6] * 2;
  ret += xz[7] * 1;
  return ret;
}
void matrixtomx() { //继承上一个函数 进行转化
  int a;
  for (a = 0; a < 8; a++) {
    showMatrix[a] = twototen(matrix[a]);
  }
}
void trans() { //转化  将蛇身子的放置到8*8点阵中
  int a, /* b, */ p;
  p = snakePoint; // sizeof(showSnake) / sizeof(showSnake[0]);
  for (a = 0; a < 8; a++) {
    showSnake[a][0] != -1 && showSnake[a][1] != -1
        ? matrix[showSnake[a][0]][showSnake[a][1]] = 1
        : 0;
    // showSnake[a + 1][0];
  }
}

void moveSnake() { //蛇动
  int a;
 
  // srand(time(0)%1000);
  if (showSnake[0][0] == showSnake[1][0] &&
      showSnake[0][1] == showSnake[1][1]) {
    snakePoint++;
    beep = ~beep;
    // matrix[showSnake[a][0]][showSnake[a][1]] ;
  }
  switch (head) {
  case 0:
    xPoint--;
    break;
  case 1:
    xPoint++;
    break;
  case 2:
    yPoint++;
    break;
  case 3:
    yPoint--;
    break;
  default:
    head = 0;
    break;
  }
  for (a = snakePoint+1; a < 1; a--) {
    showSnake[a][0] = showSnake[a - 1][0];
     P1 = ~P1;
    showSnake[a][1] = showSnake[a - 1][1];
  }
  showSnake[1][0] = xPoint + 1;
  showSnake[1][1] = yPoint + 1;
 // P1 = ~P1;
}

void main(void) {
  uchar i, j /*, k */;
  TMOD = 0x01;
  TH0 = (65536 - 5000) / 256;
  TL0 = (65536 - 5000) % 256;
  EA = 1;
  ET0 = 1;
  TR0 = 1;
  ukey = 1, dkey = 1, lkey = 1, rkey = 1;
  delay(5);
  Init_MAX7219();           //初始化完毕
  for (j = 0; j < 4; j++) { //开幕Start
    for (i = 1; i < 9; i++)
      Write_Max7219(i, disp1[j][i - 1]);
    delay(75);
  };
  for (j = 3; j > 0; j--) {
    for (i = 1; i < 9; i++)
      Write_Max7219(i, disp1[j][i - 1]);
    delay(75);
  }
  for (i = 1; i < 9; i++) {
    Write_Max7219(i, disp1[4][i - 1]); //开
  }
  delay(300); ///开幕End

  //  for (i = 1; i < 9; i++)
  //    Write_Max7219(i, 0); //清理屏幕
  while (1) {
    //-------------------------------------------------------
    //   真正的主区
    matrixtomx(); //

    clearMatrix();
    for (i = 1; i < 9; i++)
      Write_Max7219(i, 0); //清理屏幕

    showPoint(/* showSnake[1][0], showSnake[1][0] */ snakePoint);
    if (ticket > 200) {
      moveSnake();
      ticket = 0;
    } //蛇动
    trans();
    for (i = 1; i < 9; i++) {
      Write_Max7219(i, showMatrix[i - 1]); //绘制蛇
    }
    //-------------------------------------------------------
  }
}

void timer0() interrupt 1 {
  TH0 = (65536 - 5000) / 256;
  TL0 = (65536 - 5000) % 256;
  keyscan();
  ticket++;
  snakePoint > 20 ? snakePoint = 0 : 0;
  xPoint > 7 ? xPoint = 0 : 0;
  yPoint > 7 ? yPoint = 0 : 0;
  xPoint < 0 ? xPoint = 7 : 0;
  yPoint < 0 ? yPoint = 7 : 0; //溢出设置
  // matrix[xPoint][yPoint] = 1;
}
