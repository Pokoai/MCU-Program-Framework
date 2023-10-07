#ifndef __I2C_H__
#define __I2C_H__

#include <REG52.H>

#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif

sbit EEPOM_SDA = P2^0;
sbit EEPOM_SCL = P2^1;

#endif