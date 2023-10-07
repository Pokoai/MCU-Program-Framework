#include "lcd.h"

static u8 LCD_POS = 0;     // 指向接下去显示的位置

// 延时
static void delay_ms(u16 c)
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


// 初始化
void LCD_init(void)
{
    LCD_write_command(0x38);     // 显示模式设置：16x2显示，5x7点阵，8位数据接口
    LCD_write_command(0x0C);     // 开显示，不显示光标
	LCD_write_command(0x06);     // 设置读或写一个字符后地址指针加一
    // LCD_write_command(0x08);  // 显示 关闭
    LCD_write_command(0x01);     // 清屏
    LED_Write_command(0x80);     //  刚初始化完，指针指向首位置 

	LCD_POS = 0;
	delay(1);
}

// 写指令
void LCD_write_cmd(u8 cmd)
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

// 指定位置显示字符，x:0-15  y:0-1
void LCD_write_char(u8 x, u8 y, u8 ch)
{
    u8 pos = 0;

    (y == 0) ? pos = 0x80 + x : pos = 0x80 + 0x40 + x;
    
    LCD_write_cmd(pos);    // 数据指针位置
    LCD_write_data(ch);
}

// 指定位置显示字符串，x:0-15  y:0-1
void LCD_write_str(u8 x, u8 y, u8 str[])
{
	u8 pos = 0;  // 初始位置
	u8 str_len = strlen(str);
	u8 cnt = 0, 
	
	(y == 0) ? pos = 0x80 + x : pos = 0x80 + 0x40 + x;
	LCD_write_cmd(pos);    // 数据指针位置

	for ( cnt = 0; cnt < str_len; cnt++ ) {
		if ( (x+cnt) == 16) {
			LCD_write_cmd(0xc0);         // 换行
		}
		LCD_write_data( str[cnt] );
	}
}

void LCD_write_str_auto(u8 str[])
{
	u8 str_len = strlen(str);
	u8 cnt = 0;

	for ( cnt = 0; cnt < str_len; cnt++ ) {
		LCD_write_data(str[cnt]);
	}
}

void LCD_set_space(u8 x, u8 y)
{
	u8 pos = 0;

	(y == 0) ? pos = 0x80 + x : pos = 0x80 + 0x40 + x;
	LCD_write_cmd(pos);    // 数据指针位置

	LCD_write_char(' ');
	
}

void LCD_back_space()
{
	pos = ;  // 获取当前指针的位置

	// ( (pos - 1) < 16) ? LCD_write_cmd(0x80 + pos - 1) : LCD_write_cmd(0x80 + pos - 1);
	LCD_write_cmd(0x80 + pos -1);
	LCD_write_ch_auto(' ');
}
