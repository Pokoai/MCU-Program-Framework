#ifndef __LCD1602_H__
#define __LCD1602_H__

#include <REG52.H>

#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif

#define LCD_DB P0
sbit LCD_RW = P2^5;
sbit LCD_RS = P2^6;
sbit LCD_E  = P2^7;

void LCD_init(void);
void LCD_Write_command(u8 cmd);
void LCD_Write_data(u8 dat);
void LCD_display_char(u8 x, u8 y, u8 dat);
void delay_ms(u16 n);

#endif