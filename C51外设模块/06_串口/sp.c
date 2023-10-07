#include <REG52.H>

unsigned char flag;
unsigned char temp;

// 定时器初始化-方式2：8位自动重装
void Timer1_init()
{
    TMOD = 0x20;

    TH1 = 0xFD;
    TL1 = 0xFD;

    EA = 1;
    // ET1 = 1;   // 这里要注意：定时器1的 ET1千万不能置1，否则 ES 将失效，这两个中断允许有冲突
    TR1 = 1;       
}

// 串口初始化
void SP_init()
{
    // SCON = 0x50;
    SM0 = 0;
    SM1 = 1;
    REN = 1;

    PCON &= 0x7F;

    ES = 1;     // 开串口中断允许
}

// 串口中断服务程序
void sp() interrupt 4
{
    RI = 0;     // 软件清标志位
    flag = 1;

    // P0 = SBUF;
    temp = SBUF;
}  


// 串口控制
void sp_control()
{
    switch (SBUF) {
        case 0x01: P0 = 0xFF; break;
        case 0xFF: P0 = 0x00; break;   
    }
}


void main()
{
    P0 = 0x00;

    Timer1_init();
    SP_init();

    while (1) {
        sp_control();
    
        if ( 1 == flag ) { 
            flag = 0;
            ES = 0;     // 防止中断死循环，故发送数据时关闭串口中断，待发送完毕再打开中断允许
            SBUF = temp;
            // SBUF = 'V';

            // if ( 1 == TI ) {  // 这里的 if 语句块有问题的，如果执行到 if 语句的时候，  
            //     TI = 0;       // TI 还未被置1的话，那么后续 TI 就一直为 1，没有清零，那么就一直进入串口中断
            //     ES = 1;       // 所以这里应该采用 while (!TI); 让程序阻断在这，直到 TI 为1，再接着执行后续代码
            // }                 // 或者将 if 语句块放到 if(1 == flag) 外面也行，这样就会不断的执行 if(1==TI)，而非之前的仅检测一次
            
            while (!TI);
            TI = 0;
            ES = 1;
        }

        // if ( 1 == TI ) {  // 或者将 if 语句块放到 if(1 == flag) 外面也行，这样就会不断的执行 if(1==TI)，而非之前的仅检测一次
        //     TI = 0;       
        //     ES = 1;       
        // }
    }
    

}

