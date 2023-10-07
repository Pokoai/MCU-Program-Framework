#include "smg.h"

// 数码管段选表，显示 0~F
u8 code SMG_DUAN_Table[] = {
    0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,
};      

// 内部辅助函数
static void delay(u16 n)
{
    while (n--);
}

// 数码管动态扫描
void dig_display(u16 num)
{
    u8 i;
    u8 disp[4];
    // 千百十个
    disp[0] = SMG_DUAN_Table[num / 1000];
    disp[1] = SMG_DUAN_Table[num % 1000 / 100];
    disp[2] = SMG_DUAN_Table[num % 1000 % 100 / 10];
    disp[3] = SMG_DUAN_Table[num % 1000 % 100 % 10];

    for ( i = 0; i < 4; i++ ) {
        switch(i) {
            case 0: LSC = 0; LSB = 0; LSA = 0; break;
            case 1: LSC = 0; LSB = 0; LSA = 1; break;
            case 2: LSC = 0; LSB = 1; LSA = 0; break;
            case 3: LSC = 0; LSB = 1; LSA = 1; break;
        }
        SMG_DUAN = disp[i];
        delay(100);
        SMG_DUAN = 0x00;    // 消隐
    }
}
