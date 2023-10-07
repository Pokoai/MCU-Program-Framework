#include <intrins.h>  // _nop_()

#include "xpt2046.h"


// SPI 写数据，即通过 XPT2046_DIN 传入控制字节
void SPI_Write(u8 dat)
{
    u8 i;
    XPT2046_CLK = 0;

    for ( i = 0; i < 8; i++ ) {
        XPT2046_DIN = dat >> 7;    // 先送最高位
        // 或者 XPT2046_DIN = dat&0x80;

        XPT2046_CLK = 0;           // 写数据：先把数据放到IO口，再送跳变沿
        XPT2046_CLK = 1;           // 上升沿传送数据

        dat <<= 1;         // 次高位升到最高位，待下一次传送
    }
}

// SPI 读数据
u16 SPI_Read()
{
    u8 i;
    u16 dat = 0;
    XPT2046_CLK = 0;

    for ( i = 0; i < 12; i++ ) {
        dat <<= 1;         // 这一句必须放在 dat |= XPT2046_DOUT 之前，因为接受完最后一位时就不用再移位了   
        
        XPT2046_CLK = 1;
        XPT2046_CLK = 0;           // 下降沿传送数据
        
        dat |= XPT2046_DOUT;       // 读数据：先送跳变沿，再接收数据
        // dat <<= 1;      // 错误！最初放在后面的，输出值为8096，多移了一次
    }
    return dat; 
}

// 获取 AD 转换后的数据
// cmd -> 0x94:电位器、0xD4:NTC、0xA4:光敏、0xE4:外部模拟信号
u16 Read_AD_Data(u8 cmd)
{
    u8 i;
    u16 AD_Value;

    XPT2046_CLK = 0;
    XPT2046_CS = 0;
    
    SPI_Write(cmd);
    for ( i = 6; i > 0; i-- );  // 延时等待转换结束

    XPT2046_CLK = 1;    // 发送一个时钟周期，清除 BUSY
    _nop_();
    _nop_();
    XPT2046_CLK = 0;
    _nop_();
    _nop_();

    AD_Value = SPI_Read();

    XPT2046_CS = 1;

    return AD_Value;
}

// 获取水位高度
u16 get_water_hight()
{
    u16 temp = Read_AD_Data(0xE4);

    return temp;
}