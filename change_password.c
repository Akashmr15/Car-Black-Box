#include <xc.h>
#include "main.h"
#include "eeprom.h"
#include "clcd.h"
#include "matrix_keypad.h"

extern unsigned int i;
extern char main_f;
extern char cp_f;
char new_password[4],re_password[4];
void change_pass(char key)
{
    static char index1=0,index2=0,pass_f = 0;
    static unsigned int delay = 0;
    
    if(index1 < 4 && pass_f ==0)
    {
        clcd_print("ENTER NEW PASSWORD",LINE1(0));
        if(delay++ < 1000)
        {
            clcd_print("_",LINE2(index1));
        }
        else if(delay++ > 1000 && delay < 2000)
        {
            clcd_print(" ",LINE2(index1));
        }
        else
            delay = 0;
        if(key == MK_SW5)
        {
            new_password[index1] = 0;
            clcd_print("*",LINE2(index1));
            index1++;
        }
        if(key == MK_SW6)
        {
            new_password[index1] = 1;
            clcd_print("*",LINE2(index1));
            index1++;
        }
        if(index1 == 4)
        {
            CLEAR_DISP_SCREEN;
            pass_f = 1;
        }         
    }
    else if(index2 < 4  && pass_f == 1)
    {
        clcd_print("RE ENTER PASSWORD",LINE1(0));
        if(delay++ < 1000)
        {
            clcd_print("_",LINE2(index2));
        }
        else if(delay++ > 1000 && delay < 2000)
        {
            clcd_print(" ",LINE2(index2));
        }
        else
            delay = 0;
        if(key == MK_SW5)
        {
            re_password[index2]= 0;
            clcd_print("*",LINE2(index2));
            index2++;
        }
        if(key == MK_SW6)
        {
            re_password[index2] = 1;
            clcd_print("*",LINE2(index2));
            index2++;
        }
        if(index2 == 4)
            pass_f = 1;       
    }
    else if(index1 == 4 && index2 == 4)
    {
        for(int i =0;i<4;i++)
        {
            if(new_password[i] != re_password[i])
                pass_f = 2;
        }
        if(pass_f == 2)
        {
            clcd_print("CHANGE PASSWORD ",LINE1(0));
            clcd_print("    FAILURE     ",LINE2(0));
            pass_f = index1 = index2 = 0;
            for(unsigned long int i= 500000;i--;);
            main_f = MENU;           
        }
        else
        {
            clcd_print("CHANGE PASSWORD ",LINE1(0));
            clcd_print(" SUCCESSFULLY   ",LINE2(0));
            char k=0;
            cp_f = 1;
            char prev_i = i;
            i = 10;
            store_event();
            i = prev_i;
            pass_f = index1 = index2 = 0;
            for(unsigned long int i = 500000;i--;);
            main_f = MENU;    
        }
    }    
}