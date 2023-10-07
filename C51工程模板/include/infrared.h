#ifndef __INFRARED_H__
#define __INFRARED_H__

/*
 * module: 红外线
 * author: Guyue
 * 
 * api:
 * void Ir_init()
 * u8 Ir_read()
 * 
 * 红外线值分别为：
 * 45, 46, 47
 * 44, 40, 43
 * 07, 15, 09
 * 16, 19, 0D
 * 0C, 18, 5E
 * 08, 1C, 5A
 * 42, 52, 4A
 */

#include "config.h"


static idata u8 IrValue[4];  // 存储红外数据，4个字节，分别为用户码、用户码、数据码、数据反码
static u8 Time;              // 存储高电平的持续时间

extern void Ir_init();
extern u8 Ir_read();


#endif

