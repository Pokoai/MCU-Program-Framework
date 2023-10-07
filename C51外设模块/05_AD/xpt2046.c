#include "xpt2046.h"

// SPI写数据，即通过 DIN 传入控制字节
void SPI_Write(u8 dat)
{
    u8 i;
    CLK = 0;
    for ( i = 0; i < 8; i++ ) {
        DIN = dat >> 7;    // 先送最高位

        CLK = 0;           // 写数据：先把数据放到IO口，再送跳变沿
        CLK = 1;           // 上升沿传送数据

        dat <<= 1;         // 次高位升到最高位，待下一次传送
    }
}

// SPI读数据
u16 SPI_Read(void)
{
    u8 i;
    u16 dat = 0;

    CLK = 0;
    for ( i = 0; i < 12; i++ ) {
        dat <<= 1;         // 这一句必须放在 dat |= DOUT 之前，因为接受完最后一位时就不用再移位了   
        
        CLK = 1;
        CLK = 0;           // 下降沿传送数据
        
        dat |= DOUT;       // 读数据：先送跳变沿，再接收数据
        // dat <<= 1;      // 错误！最初放在后面的，输出值为8096，多移了一次
    }

    return dat; 
}

// 获取 AD 转换后的数据
u16 Read_AD_Data(u8 cmd)
{
    u8 i;
    u16 AD_Value;

    CS = 0;
    CLK = 0;
    SPI_Write(cmd);

    for ( i = 0; i < 6; i++ );  // 延时等待转换结束

    CLK = 1;    // 发送一个时钟周期，清除BUSY
    _nop_();
    _nop_();
    CLK = 0;
    _nop_();
    _nop_();

    AD_Value = SPI_Read();
    CS = 1;

    return AD_Value;
}