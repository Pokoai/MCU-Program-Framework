#ifndef __XPT2046_H__
#define __XPT2046_H__

/*
 * module：xpt2046 AD
 * author：Guyue
 * 
 * api：
 * u16 get_water_hight()       // 获取水位高度
 * u16 Read_AD_Data(u8 cmd)    // 获取 AD 转换后的数据
 * 其中 cmd -> 0x94:电位器；0xD4:NTC；0xA4:光敏；0xE4:外部模拟信号
 */

#include "config.h"


extern u16 Read_AD_Data(u8 cmd); 
extern u16 get_water_hight();

#endif