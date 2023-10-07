#include "LCD1602.h"

// 延时
void delay_ms(u16 c)
{
    u8 a, b;
    
    for (; c > 0; c-- ) {
        for ( b = 199; b > 0; b-- ) {
            for ( a = 1; a > 0; a-- );
        }
    }
}

// 延时
// static void delay_us(u16 n)
// {
//     while(n--);
// }

// 写指令
void LCD_write_command(u8 cmd)
{
    LCD_E  = 0;
    LCD_RS = 0;
    LCD_RW = 0;

    LCD_DB = cmd;
    delay_ms(1);    // tsp1: 地址建立时间

    
    LCD_E = 1;
    delay_ms(1);    // tpw: E脉宽
    LCD_E = 0;
}

// 写数据
void LCD_write_data(u8 dat)
{
    LCD_E  = 0;
    LCD_RS = 1;
    LCD_RW = 0;

    LCD_DB = dat;
    delay_ms(1);    // tsp1: 地址建立时间

    
    LCD_E = 1;
    delay_ms(1);    // tpw: E脉宽
    LCD_E = 0;
}

// 初始化
void LCD_init(void)
{
    LCD_write_command(0x38);     // 显示模式设置
    LCD_write_command(0x0C);     // 开显示，不显示光标
    // LCD_write_command(0x08);      // 显示 关闭
    LCD_write_command(0x01);     // 清屏
    LCD_write_command(0x06);     // 坐标指针自动加1
    // LED_Write_command(0x80);     // 数据指针起点
}

// 指定位置显示，x:0-15  y:0-1
void LCD_display_char(u8 x, u8 y, u8 dat)
{
    u8 pos;

    if ( 0 == y ) {
        pos = 0x80 + x;
    } else {
        pos = 0x80 + 0x40 + x;
    }
    
    LCD_write_command(pos);    // 数据指针位置
    LCD_write_data(dat);
}

// 检查忙函数
// void LCD_check_busy(void)
// {

// }



