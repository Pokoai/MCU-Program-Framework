#include "relay.h"

// 继电器导通
void relay_on()
{
	GPIO_RELAY = 0;
}

// 继电器断开
void relay_off()
{
	GPIO_RELAY = 1;
}

