#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"

char *logs[]={"VIEW LOG       ","DOWNLOAD LOG          ","CLEAR LOG         ","SET TIME        ","CHANGE PASSWORD         "};
unsigned int flag=0;
unsigned static int i=0;
extern char menu_f,main_f;
void menu(char key)
{   
    if(flag==0)
    {
        clcd_putch('*',LINE1(0)); 
        clcd_print("  ",LINE2(0));
    }
    else
    {
        clcd_print("  ",LINE1(0)); 
        clcd_putch('*',LINE2(0));
    }
    if(key == MK_SW5)
    {
        if(flag==1)
            flag=0;
        else if(i>0)
            i--;
    }
    if(key == MK_SW6)
    {
        if(flag==0)
            flag=1;
        else if(i<3)
            i++;     
    } 
    clcd_print(logs[i],LINE1(1));
    clcd_print(logs[i+1],LINE2(1));
    
    if(key==15)
    {
        CLEAR_DISP_SCREEN;
        main_f=MENU_ENTER;
        if(flag==0)
        {
            menu_f=i;
        }
        else
            menu_f=i+1;
    }
    
    if(key==16)
    {
        CLEAR_DISP_SCREEN;
        main_f=DASHBOARD;
    }
}