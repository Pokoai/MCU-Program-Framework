/* 没有 DA 芯片，故采用 PWM 模拟模拟量输出*/

#include <REG52.H>

#define CYCLE 1000  // 一个周期时间
#define PWM_WD 600  // 高电平时间

typedef unsigned char u8;
typedef unsigned int u16;

sbit pwm = P2^1;

u16 t0, cnt;

void timer0_init()
{
    TMOD |= 0x01;

    TH0 = 0xFF;
    TL0 = 0xFF;

    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void timer0() interrupt 1
{
    TH0 = 0xFF;     // 1us
    TL0 = 0xFF;

    t0++;   // 一个周期
    cnt++;    
}

void main()
{
    timer0_init();

    pwm = 1;
    while (1) {
        if ( cnt > PWM_WD ) { 
            cnt = 0;
            pwm = 0;
        }

        if ( t0 > CYCLE ) {
            t0 = 0;
            cnt = 0;
            pwm = 1;
        }
    }
    
}