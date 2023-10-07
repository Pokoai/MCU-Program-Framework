/*
 * date: 2023-05-18
 * author: Guyue
 * describe: 洗碗机上水控制
 */


#include "head.h"

u16 water_hight = 0;
u8 IR_cmd = 0;
char * UART_cmd;
bool key_is_on;
bool key_is_off;

u8 water_disp[4];

bool water_is_full = false;
bool relay_is_on = false;


void data_process()
{
    water_disp[0] = water_hight / 1000 + 48;
    water_disp[1] = water_hight % 1000 / 100 + 48;  // 百位
	water_disp[2] = water_hight % 1000 % 100 / 10 + 48;  // 十位
	water_disp[3] = water_hight % 1000 % 100 % 10 + 48;  // 个位
}

void data_display()
{
    LCD_write_str(0, 0, "water hight:");
    LCD_write_str(12, 0, water_disp);
    
    // 向上位机发送水位值
    uart_send_str("water hight:");
    uart_send_str(water_disp);
    uart_send_ch(' ');
}

void main()
{
    led_off();
    relay_off();
    LCD_init();
    Ir_init();
    timer_init();
    uart_init();

    while(1) {
        if ( water_hight > 2200 && water_hight < 2600 ) {  // < 2600：排除洗完后水蒸气干扰
            // relay_off();  // 关闭阀门
            water_is_full = true;  // 水满后打个标记，不马上关闭阀门

            if ( water_hight > 2500 ) {  // 暂时用此方法限制报警，洗完后的水蒸气会使其大于2X00
				beep_on();		 // 蜂鸣器报警
			}
        }
        if ( key_is_on || IR_cmd == 71 || !strcmp(UART_cmd, "on") ) {  // 实际发送的应该是"on$"
            relay_on();
            relay_is_on = true;
            // *IR_cmd = 0; // 按一次遥控触发中断，才会更新 IR_cmd 的值，否则就会一直保持上次的值，故只能手动清零
            UART_cmd[0] = '\0';  // 原理同上，清空串口命令 
        } else if ( key_is_off || IR_cmd == 69 || !strcmp(UART_cmd, "off") ) {  // 实际发送的应该是"off$"
            relay_off();
            relay_is_on = false;
            TIMER0_CNT3 = 0;  // 若关闭阀门，则2min重新计算
            // *IR_cmd = 0;
            UART_cmd[0] = '\0'; 
        }
    }
}

void timer0() interrupt 1
{
    TH0 = TH0_VAL;
    TL0 = TL0_VAL;

    // 50ms更新一次
    water_hight = get_water_hight();  // 读取水位值
    IR_cmd = Ir_read();               // 读取红外命令
    // UART_cmd = uart_read(UART_cmd);   // 读取串口命令
    UART_cmd = uart_read2();

    // 100ms更新一次
    if ( 2 == ++TIMER0_CNT ) {
        TIMER0_CNT = 0;
        key_is_on = key_on();         // 读取两个按键状态
        key_is_off = key_off();
    }

    // 1s更新一次
    if ( 20 == ++TIMER0_CNT2 ) {
        TIMER0_CNT2 = 0;
        data_process();  // 显示程序没有必要快速刷新，1s刷新一次即可
        data_display();

        // 液位传感器检测到水后，延时1秒再关闭阀门
        if ( water_is_full ) {
            water_is_full = false;
            relay_off();  
            relay_is_on = false;
            TIMER0_CNT3 = 0;  // 若关闭阀门，则2min重新计算
        }
    }

    // 保险起见，继电器导通上水后开始计时2min，超过此时间则强制关闭电磁阀
	// 实际上水时间：1min33s
    if ( relay_is_on ) {
        if ( 2000 == ++TIMER0_CNT3 ) {
            TIMER0_CNT3 = 0;
            relay_off();
            relay_is_on = false;
        }

    }
    

}
