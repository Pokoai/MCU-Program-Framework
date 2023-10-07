#ifndef __CONFIG_H__
#define __CONFIG_H__

/*
 * module: config
 * function: 外设配置及端口分配
 * author: Guyue
 *
 */
 
#include <reg52.h>

 

 // 类型定义
typedef  unsigned char  uchar;  
typedef  unsigned int   uint;
typedef  unsigned long  ulong;

typedef  uchar    u8;
typedef  uint     u16;
typedef  ulong    u32;
typedef  char     int8;
typedef  int      int16;
typedef  long     int32;

typedef  char      bool;       
#define  true       1
#define  false      0
	


// 键盘
sbit GPIO_KEY_ON = P1^0;
sbit GPIO_KEY_OFF = P1^1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          // 独立按键
#define GPIO_KEY P3            // 矩阵键盘
                                                                                                                                 
// LED 
sbit GPIO_LED_1 = P1^4;

// 继电器                                                                                                           
sbit GPIO_RELAY = P1^2;

// 蜂鸣器
sbit GPIO_BEEP = P1^3;

// LCD 1602
sbit LCD_E   = P2^7;            // 使能信号
sbit LCD_RS  = P2^6;            // 数据/命令选择端  对应  1/0
sbit LCD_RW  = P2^5;            // 读/写选择端      对应  1/0
#define LCD_DB P0               // 数据总线

// Ifr
sbit IRIN = P3^2;       // 数据线接在外部中断P3.2口上
#define CONFIG_IT0   1  // 下降沿触发
#define CONFIG_EX0   1  // 打开外部中断0允许
#define CONFIG_EA    1  // 打开总中断
#define IRIN_VAL  1     // 端口初始化为高电平

// xpt2046 AD
sbit XPT2046_CLK  = P2^3;       // 时钟
sbit XPT2046_CS   = P2^2;       // 片选
sbit XPT2046_DIN  = P2^1;       // 模拟输入
sbit XPT2046_DOUT = P2^0;       // 数字量输出

// I2C
// sbit SCL = P1^4;
// sbit SDA = P1^5;

// PCF8591
#define AddWr 0x90   // 写数据地址
#define AddRd 0x91   // 读数据地址


/* ------------------------- timer options --------------------------*/
#define CONFIG_EA   1    // 总中断开关

#define TMOD_VAL  0x21   // 定时器工作方式设置，T0工作在方式1: 16位定时器, T1工作在方式2: 8位自动重装定时器

#define CONFIG_TR0  1    // 定时器0开关
#define CONFIG_ET0  1    // 中断允许
#define TH0_VAL  (65535-50000) / 256;   // T0: 50ms
#define TL0_VAL  (65535-50000) % 256;

#define CONFIG_TR1  1    // 定时器1开关
#define CONFIG_ET1  1    // 中断允许
// #define TH0_VAL  (65535-50000) / 256;   // 在 uart option 中根据选项有不同定义
// #define TL0_VAL  (65535-50000) % 256;
/* ------------------------- timer options --------------------------*/



/* ------------------------- uart option --------------------------*/
// #define UART_BLOCK      // 以阻塞方式读取数据

#define CONFIG_EA   1   // 总中断开关
#define CONFIG_ES   1   // 串口中断开关
// #define CONFIG_TR1  1   // 定时器1开关

//#define CONFIG_11_0592MHz_BAUDRATE_4800  // 通信波特率选择
#define CONFIG_11_0592MHz_BAUDRATE_9600
//#define CONFIG_11_0592MHz_BAUDRATE_57600
//#define CONFIG_12MHz_BAUDRATE_4800

#if defined   (CONFIG_11_0592MHz_BAUDRATE_4800)
// #define TMOD_VAL   0x20  // 已在 timer options 中定义
#define SCON_VAL   0x50
#define TH1_VAL    0xF4
#define TL1_VAL    0xF4
#define PCON_VAL   0x80
#elif defined (CONFIG_11_0592MHz_BAUDRATE_9600)
//#define TMOD_VAL   0x20  
#define SCON_VAL   0x50
#define TH1_VAL    0xFD
#define TL1_VAL    0xFD
#define PCON_VAL   0x00
#elif defined (CONFIG_11_0592MHz_BAUDRATE_57600)
// #define TMOD_VAL   0x20
#define SCON_VAL   0x50
#define TH1_VAL    0xFF
#define TL1_VAL    0xFF
#define PCON_VAL   0x80
#elif defined (CONFIG_12MHz_BAUDRATE_4800)
// #define TMOD_VAL   0x20
#define SCON_VAL   0x50
#define TH1_VAL    0xF3
#define TL1_VAL    0xF3
#define PCON_VAL   0x80
#endif
/* ------------------------- uart option --------------------------*/



#endif