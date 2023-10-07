#ifndef __KEY_H__
#define __KEY_H__

/*
 * module：4*4矩阵按键
 * author：Guyue
 * 
 * api：
 * u8 key_polling()   轮询模式读取 4*4 按键，成功返回 1 - 16，失败返回 0
 * u8 key_blocking()  阻塞模式读取 4*4 按键，成功返回 1 - 16，失败返回 0
 */

#include "main.h"

extern u8 duli_key();

extern u8 key_polling();
extern u8 key_blocking();



#endif