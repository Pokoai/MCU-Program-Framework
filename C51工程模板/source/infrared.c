#include "infrared.h"


// 大约延时10us
static void delay(u16 i)
{
	while(i--);	
}


// 初始化红外线接收
void Ir_init()
{
	IT0 = CONFIG_IT0;   // 下降沿触发
	EX0 = CONFIG_EX0;   // 打开外部中断0允许
	EA  = CONFIG_EA;    // 打开总中断

	IRIN = IRIN_VAL;    // 初始化端口为1，一旦变为0，则触发外部中断
}

// 读取红外数值
// 存储到 IrValue[] 数组中
void Ir_receive() interrupt 0
{
	u8 j, k;
	u16 err;
	Time = 0;

	delay(700);	 		// 7ms
	if( IRIN == 0 )		// 确认是否真的接收到正确的信号
	{	 
		err = 1000;	    // 1000*10us=10ms，超过说明接收到错误的信号
		// 当两个条件都为真时循环，如果有一个条件为假的时候跳出循环，免得程序出错的时侯，程序死在这里	
		while( (IRIN==0) && (err>0) )	// 等待前面9ms的低电平过去  		
		{			
			delay(1);
			err--;
		} 
		if( IRIN == 1 )			// 如果正确等到9ms低电平
		{
			err = 500;
			while( (IRIN==1) && (err>0) )	// 等待4.5ms的起始高电平过去
			{
				delay(1);
				err--;
			}
			for( k = 0; k < 4; k++ )		// 共有4组数据，每组为1字节
			{				
				for( j = 0; j < 8; j++ )	//接收一组数据
				{
					err = 60;		
					while( (IRIN==0) && (err>0) )  // 等待信号前面的560us低电平过去
					{
						delay(1);
						err--;
					}

					err = 500;
					while( (IRIN==1) && (err>0) )	 // 计算高电平的时间长度
					{
						delay(10);	 // 0.1ms
						Time++;
						err--;
						if( Time > 30 )  // 信号0：高电平持续0.56ms  信号1：高电平持续1.69ms 
						{
							return;		 // 若高电平持续时间超过3ms，说明信号错误，直接结束中断服务程序
						}
					}
					IrValue[k] >>= 1;	 // k表示第几组数据
					if( Time >= 8 )	{		// 如果高电平出现大于565us，那么是信号1
						IrValue[k] |= 0x80;  // 字节最高位放入信号1
					}
					Time = 0;		// 时间清零							
				}
			}
		}
		if( IrValue[2] != ~IrValue[3] )  // 第2、3字节互为反码，作为校验方式
		{
			return;
		}
	}
}

// 专用的红外数据读取接口
// 之所以返回指针，是因为要在 main()中直接修改 IrValue[2]的值
// 在 main()中读取 IrValue[2]的值后，就要将其清空
u8 Ir_read()  
{
	u8 buf;

	buf = IrValue[2];
	IrValue[2] = 0;	 // 读完即清空，否则就会卡在 69 或者 71

	return buf;  
}

