#include "timer.h"


// 定时器初始化
void timer_init()
{
    TMOD = TMOD_VAL;  
    TH0 = TH0_VAL;
    TL0 = TL0_VAL;

    // EA  = CONFIG_EA;  // uart_init() 中开启总中断
    ET0 = CONFIG_ET0;
    TR0 = CONFIG_TR0;
}
