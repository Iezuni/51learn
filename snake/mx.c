#include "reg52.h"
//????Max7219???
#define uchar unsigned char
#define uint unsigned int
sbit Max7219_pinCLK = P2 ^ 2; //点阵灯设置
sbit Max7219_pinCS = P2 ^ 1;  //
sbit Max7219_pinDIN = P2 ^ 0; //点阵灯设置

//--------------------------------------------
//功能：向MAX7219(U3)写入字节
//入口参数：DATA
//出口参数：无
//说明：
void Write_Max7219_byte(uchar DATA) {
  uchar i;
  Max7219_pinCS = 0;
  for (i = 8; i >= 1; i--) {
    Max7219_pinCLK = 0;
    Max7219_pinDIN = DATA & 0x80;
    DATA = DATA << 1;
    Max7219_pinCLK = 1;
  }
}
//-------------------------------------------
//功能：向MAX7219写入数据
//入口参数：address、dat
//出口参数：无
//说明：
void Write_Max7219(uchar address, uchar dat) {
  Max7219_pinCS = 0;
  Write_Max7219_byte(address); ///写入地址，即数码管编号
  Write_Max7219_byte(dat);     //写入数据，即数码管显示数字
  Max7219_pinCS = 1;
}

void Init_MAX7219(void) {
  Write_Max7219(0x09, 0x00); //译码方式：BCD码
  Write_Max7219(0x0a, 0x03); //亮度
  Write_Max7219(0x0b, 0x07); //扫描界限；8个数码管显示
  Write_Max7219(0x0c, 0x01); //掉电模式：0，普通模式：1
  Write_Max7219(0x0f, 0x00); //显示测试：1；测试结束，正常显示：0
}