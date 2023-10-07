#ifndef __XPT2046_H__
#define __XPT2046_H__

// 头文件
#include <REG52.H>
#include <INTRINS.H>  // _nop_()

// 类型重定义
#ifndef u8
#define u8 unsigned char 
#endif

#ifndef u16
#define u16 unsigned int
#endif

#ifndef u32 
#define u32 unsigned long
#endif

// 定义使用的 IO 口
sbit CLK  = P2^7;    // 时钟
sbit CS   = P2^6;    // 片选
sbit DIN  = P2^5;    // 控制输入
sbit DOUT = P2^4;    // 数字量输出

// 外部函数
extern void SPI_Write(u8 dat);
extern u16 SPI_Read(void);
extern u16 Read_AD_Data(u8 cmd); 

#endif