#include <REG52.H>
#include <string.h>
#include "LCD1602.h"

u8 code Disp[] = "pokeai.cn";

void main()
{
    u8 i;

    LCD_init();
    // while (1) {
    //    for ( i = 0; i < strlen(Disp); i++ ) {
    //        LCD_display_char(i, 0, Disp[i]);
    //    } 
    // }

    for ( i = 0; i < strlen(Disp); i++ ) {
           LCD_display_char(i+3, 0, Disp[i]);
           delay_ms(50);
    }
    while(1);
       
    
}