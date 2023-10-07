/* 题目：https://img.arctee.cn/one/202205201824051.png */


#include <REG52.H>
#include <intrins.h>

typedef unsigned int u16;
typedef unsigned char u8;

// 138译码器
sbit LSA = P2^0;
sbit LSB = P2^1;
sbit LSC = P2^2; 

// 数码管段选表
u8 code SmgDuanTable[] = {
    0x3f, 0x06, 0x5b, 0x4f,
    0x66, 0x6d, 0x7d, 0x07,
	0x7f, 0x6f, 0x77, 0x7c,
    0x39, 0x5e, 0x79, 0x71,
    0x76, 0x79, 0x38, 0x3f,  // hello
};

// 全局变量
long number = 799;
u8 temp;
u8 cnt01;
u8 cnt02;
u8 cnt11;
u8 flag = 0;   // 计数停止时标志位
u8 flag2 = 0;  // 3s计数标志位


void delay_ms(u16 n)
{
    u8 n1 = 23;
    n *= n1;
    
    while ( n-- );
}


// 数码管显示
void smg_display(u16 number)
{
    u8 ge = number % 10;
    u8 shi = number / 10 % 10;
    u8 bai = number / 100;

    // 显示百位
    LSC = 0, LSB = 0, LSA = 0; 
    P0 = SmgDuanTable[bai];
    delay_ms(5);
    P0 = 0x00;
    
    // 显示十位
    LSA = 1;  // LSC = 0, LSB = 0, LSA = 1;
    P0 = SmgDuanTable[shi];
    delay_ms(5);
    P0 = 0x00;

    // 显示个位
    LSB = 1, LSA = 0;  // LSC = 0, LSB = 1, LSA = 0;
    P0 = SmgDuanTable[ge];
    delay_ms(5);
    P0 = 0x00;

}

// 数码管显示 HELLO
void smg_display_str()
{
    LSC = 0, LSB = 0, LSA = 0; 
    P0 = SmgDuanTable[16];
    delay_ms(5);
    P0 = 0x00;
    
    LSA = 1;  // LSC = 0, LSB = 0, LSA = 1;
    P0 = SmgDuanTable[17];
    delay_ms(5);
    P0 = 0x00;

    LSB = 1, LSA = 0;  // LSC = 0, LSB = 1, LSA = 0;
    P0 = SmgDuanTable[18];
    delay_ms(5);
    P0 = 0x00;

    LSA = 1;  // LSC = 0, LSB = 1, LSA = 1;
    P0 = SmgDuanTable[18];
    delay_ms(5);
    P0 = 0x00;

    LSC = 1, LSB = 0, LSA = 0;  // LSC = 1, LSB = 0, LSA = 0;
    P0 = SmgDuanTable[19];
    delay_ms(5);
    P0 = 0x00;
}

// 定时器初始化
void init_timer()
{
    TMOD = 0x11;  // T0、T1 均工作在方式1，16位定时器
    TH0 = (65535 - 50000) / 256;   // T0: 50ms
    TL0 = (65535 - 50000) % 256;
    TH1 = (65535 - 50000) / 256;   // T1: 50ms
    TL1 = (65535 - 50000) % 256;
    EA = 1;
    ET0 = 1, ET1 = 1;
    TR0 = 1, TR1 = 1;
}

void timer0() interrupt 1
{
    TH0 = (65535 - 50000) / 256;   // T0: 50ms
    TL0 = (65535 - 50000) % 256;

    cnt01++;
    // 流水灯
    if ( !flag ) {
        if ( 10 == cnt01 ) {
            cnt01 = 0; 
            temp = _crol_(temp, 1);
            P3 = temp; 
        }
    } else {
        // 200ms 闪烁
        if ( cnt01 % 4 == 0 ) {
            P3 = ~P3;
        }
        // 3s 计时
        if ( 60 == cnt01 ) {
            P3 = 0x00;  // 关闭LED
            TR0 =  0;   // 为了 P3 = ~P3; 这一句不再执行，关闭定时器
            flag2 = 1;  // 3s 已到标志位
        }
    }
}

void timer1() interrupt 3
{
    TH1 = (65535 - 50000) / 256;   // T0: 50ms
    TL1 = (65535 - 50000) % 256;

    cnt11++;
    // 数字递减
    if ( 2 == cnt11 ) { // 100ms
        cnt11 = 0;
        number--;
        if ( number <= 775 ) {
            TR0 = 0;    // 流水灯不再流动
            P3 = 0x00;  // 关闭LED
            flag = 1;   // T0停止标志位
            TR1 = 0;    // 数码管不再递减

            // T0 再次开启前先初始化
            cnt01 = 0; 
            TH0 = (65535 - 50000) / 256;   // T0: 50ms
            TL0 = (65535 - 50000) % 256;
            TR0 = 1;
        }
    }
}

void main()
{   
    temp = 0x01;  // LED
    P3 = temp;

    init_timer();
    

    while (1) {
        if ( !flag2 ) {
            smg_display(number);
        } else {
            smg_display_str();
        }
    }

}