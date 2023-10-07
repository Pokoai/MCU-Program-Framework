#include "beep.h"


// 大约延时10us
static void delay(u16 i)
{
	while(i--);	
}

// 蜂鸣器响
void beep_on()
{	
	u8 i;
	for ( i = 0; i < 100; i++ ) {
		GPIO_BEEP = ~GPIO_BEEP;
		delay(20);  // 延时100us，通过修改此时间实现不同的发声效果
	}
}

// 蜂鸣器停
void beep_off()
{	
	GPIO_BEEP = 0;
}
