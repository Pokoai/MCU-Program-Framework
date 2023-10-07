#include <stdlib.h>
#include <string.h>

#include "uart.h"


// 初始化
void uart_init()
{
	// 定时器1设置
	TMOD = TMOD_VAL;
	TH1  = TH1_VAL;
	TL1  = TL1_VAL;

	// 串口设置
	SCON = SCON_VAL;
	PCON = PCON_VAL;

	// 开中断
	EA   = CONFIG_EA;
	ES   = CONFIG_ES;
	TR1  = CONFIG_TR1;
#if 0
	// 波特率9600
	SCON = 0x50;   	// 串口工作在模式1（8位串口）、允许接收
	//PCON = 0x00;	// 波特率不加倍

	// 通信波特率相关的设置
	TMOD = 0x20;	// 设置T1为模式2
	TH1 = 0xfd;
	TL1 = 0xfd;	   	// 8位自动重装，意思就是TH1用完了之后下一个周期TL1会自动重装到TH1去

	EA = 1;			// 打开总中断
	ES = 1;			// 打开串口中断
	TR1 = 1;		// 开启T1让它开始工作
#endif
}

// 发送一个字符
void uart_send_ch(char ch)        
{
	TI = 0;  			// 发送前清除发送完成标志位
	SBUF = ch;			// 将字符装入发送寄存器
	while ( TI == 0 );	// 等待发送完成，发送完成 TI 自动置1
	TI = 0;				// 发送完成后手动清除标志位
}

// 发送字符串
void uart_send_str(char *str)	    
{
	TI = 0;
	while ( *str ) {
		SBUF = *(str++);
		while ( TI == 0 );
		TI = 0;
	}
}

// 串口中断接收数据
// 并将其存储到数组 USART_RX_BUF[]中
void uart_receive() interrupt 4 using 1
{
	char res = SBUF;  // 将接收寄存器中的外来数据保存起来

	// 外部数据到来 RI自动被置1，且 USART_FLAG 为0时，才将数据存储到 USART_RX_BUF[] 数组中
	if ( RI && !USART_FLAG ) {  
		if ( res == '$' ) {  // 本次字符传送结束标志
			USART_RX_BUF[USART_CUR] = '\0';
			USART_CUR = 0;  // 数组下标索引置 0，下次到来的数据从头开始存储
			USART_FLAG = 1;   // 表明本次数据接收完毕，将 USART_FLAG 置1
		} else if ( res != '\n' ) {
			USART_RX_BUF[USART_CUR++] = res;
		}
	}

	RI = 0;  // 清除接收中断标志位
}


// 从数组 USART_RX_BUF[]中读取数据
// 非阻塞：在往 USART_RX_BUF[]中写数据时，即使本次数据并未发送完毕，也可以随时读取数据
// 阻塞： 等待 USART_FLAG 置1才返回，即往 USART_RX_BUF[]中写数据时，无法从 USART_RX_BUF[] 中读取数据
char* uart_read(char *buf)  // 为了设置阻塞模式才设计了该函数，否则可以直接从USART_RX_BUF[]中读取数据
{
#ifdef UART_BLOCK
	while ( !USART_FLAG );   
	// 阻塞模式，只有本次数据传送完毕且将USART_RX_BUF[]中数据读走后，USART_FLAG清0，才可以在中断中接收下一次数据
#else
	// if ( !USART_FLAG ) {  // 这个if条件好像不对，USART_FLAG==1时无法读取数据，不符合现实0
	// 	return USART_RX_BUF;  // 非阻塞模式，可以直接返回 USART_RX_BUF[]中现存数据
	// }
	return USART_RX_BUF;
	
#endif

	// 将 USART_RX_BUF[] 中数据复制到 buf
	memset(buf, 0, sizeof(USART_RX_BUF));  // 初始化 buf 为全0字符串
	strcpy(buf, USART_RX_BUF);
	USART_FLAG = 0;  // USART_RX_BUF[] 中数据已经另存到buf中，现在可以开始接收下一次数据了

	// 为了配合 app.c ，读完 USART_RX_BUF[]就将其清空，否则就会一直卡在 on 或者 off 的状态下
	USART_RX_BUF[0] = '\0';

	// return buf;
}

char * uart_read2()
{
	USART_FLAG = 0; 
	
	return USART_RX_BUF;
}