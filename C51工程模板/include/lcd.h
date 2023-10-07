#ifndef __LCD_H__
#define __LCD_H__

/*
 * module：LCD1602
 * author：Guyue
 * api：
 * void LCD_init()
 * void LCD_write_ch(uchar pos, uchar ch)
 * void LCD_write_ch_auto(uchar ch)
 * void LCD_write_str(uchar pos, uchar str[])
 * void LCD_write_str_auto(uchar str[])       |    LCD_write
 * void LCD_set_space(uchar pos)
 * void LCD_back_space()
 * void LCD_clear()
 *
 */
#include "main.h"

void LCD_write_cmd(uchar cmd);
void LCD_write_data(uchar dat);

//#define LCD_enter() (LCD_write_cmd(0xc0)) //换行
#define LCD_clear()           (LCD_write_cmd(0x01)) //清屏
#define LCD_write_ch_auto(ch) (LCD_write_data(ch))
#define LCD_write(str)        (LCD_write_str_auto(str))
void LCD_init();
void LCD_write_ch(uchar pos, uchar ch);
void LCD_write_str(uchar pos, uchar str[]);
void LCD_write_str_auto(uchar str[]);
void LCD_set_space(uchar pos);
void LCD_back_space();

#endif