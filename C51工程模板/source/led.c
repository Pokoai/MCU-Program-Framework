#include "led.h"


// 1ms 延时函数
static void delay_ms(u16 n)
{
	u8 n1 = 23;
	
	n *= n1;
	while ( n-- );
}


// led亮
void led_on()
{
	GPIO_LED_1 = 1;
}

// led灭
void led_off()
{
	GPIO_LED_1 = 0;
}

// led闪烁
// 占用cpu时间，仅用来测试
void led_flashing()
{	
	int i;
	for ( i = 0; i < 6; i++ ) {
		led_on();
		delay_ms(500);
		led_off();
		delay_ms(500);
	}

	led_off();  // 闪烁结束后熄灭
}