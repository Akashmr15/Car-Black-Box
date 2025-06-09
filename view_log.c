#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"
#include "main.h"
#include "eeprom.h"

extern char main_f, menu_f;
unsigned int i;
extern unsigned char lap;
extern unsigned char overflow;

void view_log(char key)
{
    static char i=0;
    if(lap==0 && overflow==0)
        clcd_print("NO LOGS FOUND", LINE1(1));
    
    if(key==MK_SW5)
    {
        if(overflow)
        {
            if(i<9)
                i++;
        }
        else if(i<lap-1)
            i++;
    }
    else if(key==MK_SW6)
    {
        if(i>0)
            i--;
    }
    if(key==16)
    {
        CLEAR_DISP_SCREEN;
        main_f=MENU;
    }
    
    if(lap || overflow)
    {  
    clcd_print("LOGS", LINE1(6));
    clcd_putch((i+1)+48, LINE2(0));
    clcd_print(".", LINE2(1));
    clcd_putch(read_external_eeprom(i*10+0), LINE2(2));
    clcd_putch(read_external_eeprom(i*10+1), LINE2(3));
    clcd_print(":", LINE2(4));
    clcd_putch(read_external_eeprom(i*10+2), LINE2(5));
    clcd_putch(read_external_eeprom(i*10+3), LINE2(6));
    clcd_print(":", LINE2(7));
    clcd_putch(read_external_eeprom(i*10+4), LINE2(8));
    clcd_putch(read_external_eeprom(i*10+5), LINE2(9));
    clcd_print(":", LINE2(10));
    clcd_putch(read_external_eeprom(i*10+6), LINE2(11));
    clcd_putch(read_external_eeprom(i*10+7), LINE2(12));
    clcd_print(":", LINE2(13));
    clcd_putch(read_external_eeprom(i*10+8), LINE2(14));
    clcd_putch(read_external_eeprom(i*10+9), LINE2(15));
    }
}