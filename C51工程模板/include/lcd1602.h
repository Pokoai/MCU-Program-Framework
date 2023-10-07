#ifndef __LCD1602_H__
#define __LCD1602_H__

/*
 * module: LCD1602
 * author: Guyue
 
 * api:
 * void LCD_init()
 * void void LCD_write_char(u8 x, u8 y, char ch)
 * void LCD_write_str(u8 x, u8 y, char *str)
 * void LCD_clear()
 *
 */
 
#include "config.h"


extern void LCD_init();
extern void LCD_write_char(u8 x, u8 y, u8 ch);
extern void LCD_write_str(u8 x, u8 y, u8 *str);
extern void LCD_clear();
// #define LCD_clear()     (LCD_write_cmd(0x01))     //清屏


#endif