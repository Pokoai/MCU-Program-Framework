#ifndef __SMG_H__
#define __SMG_H__

// 头文件
#include <REG52.H>

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
sbit LSA = P1^0;  // 数码管位选
sbit LSB = P1^1; 
sbit LSC = P1^2;        

#define SMG_DUAN P0    // 数码管段选IO口

// 对外函数
extern void dig_display(u16 num);

#endif