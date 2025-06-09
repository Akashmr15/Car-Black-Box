#include<xc.h>
#include"main.h"
#include"clcd.h"
#include"matrix_keypad.h"
#include"timer0.h"
#include "eeprom.h"

unsigned char j;
unsigned char ent_pass[4];
unsigned char oe_pass[4];
unsigned char atmpt = 3;
extern char main_f;
char cp_f = 0;
extern unsigned int sec;
extern char new_password[4];
void password(char key)
{
    static unsigned long int count = 0;
    static unsigned int delay=0;
    if(cp_f == 0)
    {
        write_external_eeprom(101,0);
        write_external_eeprom(102,1);
        write_external_eeprom(103,0);
        write_external_eeprom(104,1);
    }
    else
    { 
        char k = 0;
        for(char i =101;i<105;i++)
            {
                write_external_eeprom(i,new_password[k]);
                k++;
            }    
    }
    char k = 0;
    for(int i=101;i<105;i++)
    {
      oe_pass[k] = read_external_eeprom(i);
            k++;
    }
    unsigned pass_f = 0;
    if(j<4)
    {
    clcd_print("ENTER PASSWORD",LINE1(0));
    if(delay++ <25)
    {
        clcd_print("_",LINE2(j));
    }
    else if(delay++ > 25&& delay < 50)
    {
        clcd_print(" ",LINE2(j));
    }
    else
        delay = 0;
    if(count++ == 250)
    {
        count = 0;
        j = 0;
        CLEAR_DISP_SCREEN;
        main_f = DASHBOARD;
    }
    if(key == MK_SW5 )
    {
        count = 0;
        ent_pass[j] = 0;
        clcd_print("*",LINE2(j));
        j++;
    }
    if(key == MK_SW6 )
    {
        count = 0;
        ent_pass[j] = 1;
        clcd_print("*",LINE2(j));
        j++;
    }
    
    for(int i =0;i<4;i++)
    {
        if(ent_pass[i] != oe_pass[i])
        {
            pass_f = 1;
            break;
        }
    }
    if(pass_f && j == 4)
    {
        if(atmpt > 0)
        {
           
            clcd_print("WRONG PASSWORD",LINE1(0));
            clcd_putch(atmpt+48,LINE2(0));
            clcd_print("Attempt Left",LINE2(1));
            for(unsigned long int i = 500000;i--;);
            CLEAR_DISP_SCREEN;
            
            atmpt--;
            j = 0;
        }
        else
        {
            GIE = PEIE = 1;
            init_timer0();
            sec = 5;
            while(1)
            {
                clcd_print("YOU ARE BLOCKED",LINE1(0));
                clcd_print("FOR ",LINE2(0));
                clcd_putch((sec%10)+48,LINE2(7));
                clcd_putch((sec/10)%10+48,LINE2(6));
                clcd_putch((sec/100)+48,LINE2(5));
                clcd_print("SECONDS",LINE2(9));
                if(sec == 0)
                {
                    GIE = 0;
                    PEIE = 0;
                    CLEAR_DISP_SCREEN;
                    atmpt = 3;
                    j=0;
                    pass_f = 0;
                    break;
                }
            }
        }
    }
    else if(j==4 && pass_f == 0)
    {
        CLEAR_DISP_SCREEN;
        j = 0;
        main_f = MENU;     
    }
}
}
    


        
    


