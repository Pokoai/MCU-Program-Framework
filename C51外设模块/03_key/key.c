/* 键盘 */

#include <REG52.H>
#include <intrins.h>

// 类型定义
typedef unsigned char u8;
typedef unsigned int u16;

#define GPIO_DIG P0
#define GPIO_KEY P2

// 管脚定义
sbit led1 = P0^0;
sbit key1 = P2^0;

// 数码管位选 - 138译码器
sbit LSA = P1^0;
sbit LSB = P1^1;
sbit LSC = P1^2;

// 数码管段选表
u8 code SmgDuanTable[] = {
    0x3f,0x06,0x5b,0x4f,
    0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
    0x39,0x5e,0x79,0x71
};

// 全局变量
u8 number = 0;


// 毫秒延时函数
void delay_ms(u16 n)
{
    u8 n1 = 23;

    n *= n1;
    while( n-- );
}

// 数码管显示
void smg_display(u16 num)
{
    LSC = 0, LSB = 0, LSA = 0;

    GPIO_DIG = SmgDuanTable[num];
}

// 独立键盘检测
void duli_key()
{
    if ( 0 == key1 ) {
        delay_ms(5);  // 消抖
        if ( 0 == key1 ) {
            number++;
            if ( 16 == number ) {
                number = 0;
            }
        }
        while (!key1); // 松手检测
    }
}

// 矩阵键盘检测 V1.0(代码有问题，原因没有找到，不采用这种方式了)
// u8 key_scan()
// {
//     u8 temp;
//     u8 key_num;
//     u8 i;  

//     // GPIO_KEY = 0xFE;  
//     // temp = GPIO_KEY & 0xF0;  // 只检测高四位
//     // if ( temp != 0xF0 ) {
//     //     delay_ms(5);    // 消抖
//     //     temp = GPIO_KEY & 0xF0;
//     //     if ( temp != 0xF0 ) {
//     //         switch ( temp ) {
//     //             case 0xE0: key_num = 1; break;
//     //             case 0xD0: key_num = 2; break;
//     //             case 0xB0: key_num = 3; break;
//     //             case 0x70: key_num = 4; break;
//     //         }
//     //     }
//     // }

//     // GPIO_KEY = 0xFD;  
//     // temp = GPIO_KEY & 0xF0;  // 只检测高四位
//     // if ( temp != 0xF0 ) {
//     //     delay_ms(5);    // 消抖
//     //     temp = GPIO_KEY & 0xF0;
//     //     if ( temp != 0xF0 ) {
//     //         switch ( temp ) {
//     //             case 0xE0: key_num = 5; break;
//     //             case 0xD0: key_num = 6; break;
//     //             case 0xB0: key_num = 7; break;
//     //             case 0x70: key_num = 8; break;
//     //         }
//     //     }
//     // }

//     // 用循环精简以上重复代码
//     u8 temGPIO_KEY = 0xFE;  // 从第一排开始扫描
    
//     for ( i = 0; i < 4; i++ ) {
//         GPIO_KEY = temGPIO_KEY;
//         temp = GPIO_KEY & 0xF0;  // 只检测高四位
//         if ( temp != 0xF0 ) {
//             delay_ms(5);    // 消抖
//             temp = GPIO_KEY & 0xF0;
//             if ( temp != 0xF0 ) {
//                 switch ( temp ) {
//                     case 0xE0: key_num = 4*i+1; break;
//                     case 0xD0: key_num = 4*i+2; break;
//                     case 0xB0: key_num = 4*i+3; break;
//                     case 0x70: key_num = 4*i+4; break;
//                 }
//             }
//         }
//         temGPIO_KEY = _cror_(temGPIO_KEY, 1); 
//         if ( 0xEF == temGPIO_KEY ) {
//             temGPIO_KEY = 0xFE;
//         }
//     }

//     return key_num;
// }


// 矩阵键盘检测 V2.0
u8 key_scan()
{
    u8 key_num = 0;
    u8 t = 0;

    GPIO_KEY = 0x0F;
    if ( GPIO_KEY != 0x0F ) {  // 按下
        delay_ms(5);           // 消抖
        if ( GPIO_KEY != 0x0F ) {   // 确实按下
            // 检测列
            GPIO_KEY = 0x0F;
            switch ( GPIO_KEY ) {
                case 0x07: key_num = 1; break;  // 第一列
                case 0x0B: key_num = 2; break;
                case 0x0D: key_num = 3; break;
                case 0x0E: key_num = 4; break;
            }
            // 检测行
            GPIO_KEY = 0xF0;
            switch ( GPIO_KEY ) {
                case 0x70: key_num += 0;  break;  // 第一行
                case 0xB0: key_num += 4;  break;
                case 0xD0: key_num += 8;  break;
                case 0xE0: key_num += 12; break;
            }
            // 松手检测
            while ( (t < 50) &&  GPIO_KEY != 0xF0 ) {
                t++;
                delay_ms(1);
            }  // 不会一直卡在这里面，50ms到了自动释放

            // while ( GPIO_KEY != 0xF0 );  // 如果不松按键，就会一直卡在这里
        } 
    }

    return key_num;
    
}


void main()
{
    GPIO_DIG = 0x00;  // 关闭 LED
    
    while (1) {
        smg_display( key_scan()-1 );

    }
}

