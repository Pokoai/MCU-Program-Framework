#include "key.h"


// 1ms 延时函数
static void delay_ms(u16 n)
{
	u8 n1 = 23;
	
	n *= n1;
	while ( n-- );
}


// 独立键盘检测
u8 duli_key()
{
    if ( 0 == GPIO_KEY_1 ) {
        delay_ms(5);  // 消抖
        if ( 0 == GPIO_KEY_1 ) {
			return true
        }

        while ( !GPIO_KEY_1 ); // 松手检测
    } 
	else {
		return false;
	}
}


// 4*4矩阵键盘轮询模式
u8 key_polling()
{
    u8 key_num;  // 1~16
    u8 n = 0;  // 松手检测，时间计数变量

    GPIO_KEY = 0x0F;
    if ( GPIO_KEY != 0x0F ) {  // 按下
        delay_ms(5);           // 消抖
        if ( GPIO_KEY != 0x0F ) {   // 确实按下

            // 列扫描
            GPIO_KEY = 0x0F;
            switch ( GPIO_KEY ) {
                case 0x07: key_num = 1; break;  // 第一列
                case 0x0B: key_num = 2; break;
                case 0x0D: key_num = 3; break;
                case 0x0E: key_num = 4; break;
				default: return 0;  // 未按下直接返回 0
            }

            // 行扫描
            GPIO_KEY = 0xF0;
            switch ( GPIO_KEY ) {
                case 0x70: key_num += 0;  break;  // 第一行
                case 0xB0: key_num += 4;  break;
                case 0xD0: key_num += 8;  break;
                case 0xE0: key_num += 12; break;
				default: return 0;  // 未按下直接返回 0
            }

            // 松手检测
			// while ( GPIO_KEY != 0xF0 );  // 如果不松按键，就会一直卡在这里
            while ( n < 50 &&  GPIO_KEY != 0xF0 ) {  // 不会一直卡在这里面，50ms到了自动释放
                n++;
                delay_ms(1);
            }  
        } 
    }
    return key_num;
}


// 4*4矩阵键盘阻塞模式
u8 key_blocking()
{
	GPIO_KEY = 0x0F;
	while ( KEY == 0x0F );  // blocking
	
	return key_polling();
}

