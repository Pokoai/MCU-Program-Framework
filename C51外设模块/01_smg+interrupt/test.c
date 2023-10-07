#include <REG52.H>
#include <intrins.h>

typedef unsigned int u16;
typedef unsigned char u8;

// 数码管段选表
u8 code SmgDuanTable[] = {
    0x3f,0x06,0x5b,0x4f,
    0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
    0x39,0x5e,0x79,0x71
};

// 全局变量
u8 cnt = 0; 

// 位寄存器
sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit BEEP = P1^5;           // 蜂鸣器
sbit REALY = P1^6;          // 继电器
sbit LE = P1^0;             // 锁存器的锁存端
sbit SQUARE_WAVE = P1^0;   // 输出方波

   

// 毫秒延时函数
void delay_ms(u16 n)
{
    u8 n1 = 23;

	n *= n1;
    while ( n-- );
}

// 打开蜂鸣器
void beep_on(void)
{
    u8 i;

    for (i = 0; i < 10; i++ ) {
        BEEP = !BEEP;   // 无源蜂鸣器
        delay_ms(10);
    }
    
}

// 关闭蜂鸣器
void beep_off(void)
{
    BEEP = 0;
}

// 1. 第一个灯以间隔 200ms 闪烁
// void main(void)
// {
//     P0 = 0x00;

//     while(1){
//         LED1 = 1;
//         delay_ms(200);
//         LED1 = 0;
//         delay_ms(200);
//     }
// }

// 2. 1s流水灯，每个管亮 500ms，灭 500ms, 亮时蜂鸣器响，灭时关闭蜂鸣器
// void main(void)
// {   
//     u8 temp; 
//     P0 = 0x00;

//     temp = 0x01;
//     while(1){
//         P2 = 0x1f;
//         P0 = temp;
//         BEEP_on();
//         // REALY = 0;  // 打开继电器
//         delay_ms(500);

//         P0 = 0x00;
//         BEEP_off(); 
//         // REALY = 1;  // 关闭继电器
//         delay_ms(500);

//         temp = _crol_(temp, 1);
//         P0 = temp;
//     }
// }



// 定时器初始化
void timer0_init()
{
    TMOD = 0x01;    // 16位定时器工作方式1
    TH0 = 0x3C;     // 装初值 50ms
    TL0 = 0xB0;
    TR0 = 1;       // 启动定时器
    ET0 = 1;       // 允许定时器中断
    EA = 1;        // 开总中断
}



void main()
{
    // 定时器0初始化
    timer0_init();

    while(1) {
        // smg_display();
        // interrupt_init();
        

        }

    
}

// 定时器中断服务程序
void timer0() interrupt 1
{
    // 装初值
    TH0 = 0x3C;
    TL0 = 0xB0;

    cnt++;
	  if ( 2 == cnt ) {
				cnt = 0;  // 清零
				P0 = ~P0;  // 电平反向
		}
}
