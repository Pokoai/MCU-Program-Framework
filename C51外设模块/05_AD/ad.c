/* AD模块：可结合热敏电阻、光敏电阻进行一系列控制
  该工程采用模块化编程，其中 XPT2046 AD芯片、数码管都采用单独文件编写驱动程序
*/

#include <REG52.H>
#include "xpt2046.h"
#include "smg.h"

// typedef unsigned char u8;
// typedef unsigned int u16;


void main()
{
    u8 i = 0;
    u16 dat;

    while (1) {
        if ( 50 == i++ ) {
            i = 0;
            // dat = Read_AD_Data(0x94);    // 电位器
            // dat = Read_AD_Data(0xD4);    // NTC
            dat = Read_AD_Data(0xA4);    // 光敏
            // dat = Read_AD_Data(0xE4);    // 外部
        }
        dig_display(dat);
    }
}