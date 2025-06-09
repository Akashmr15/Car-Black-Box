#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "ds1307.h"

int time_flag,t_flag;
static unsigned char dummy;
static unsigned int hrs,min,secs;
extern unsigned char time[9];
extern char main_f;

void settime(char key) 
{
    if (key == MK_SW6)
    {
        ++time_flag;
        if (time_flag > 2)
            time_flag = 0;
    }

    if (time_flag == 0) 
    {
        clcd_print("HH:MM:SS", LINE1(0));
        clcd_print(time, LINE2(0));
        if (t_flag >= 0 && t_flag < 100) 
        {
            clcd_print(time, LINE2(0));
            ++t_flag;
        }
        else if (t_flag >= 100 && t_flag < 200)
        {
            clcd_print("  ", LINE2(0));
            ++t_flag;
            if (t_flag >= 199)
                t_flag = 0;
        }

        if (key == MK_SW5)
        {
            
            if (time[1] < '9')
            {
                time[1]++;
                if(time[0] == '2' && time[1] == '4')
                {
                    time[0] = '0';
                    time[1]= '0';
                }
                
                
            }
            
            else
            {
                time[1] = '0';
                if (time[0] < '2')
                
                   ++time[0];
                else 
                {
                    time[0]='0';
                }
            }

        }
    }
    else if (time_flag == 1) {
        clcd_print("HH:MM:SS", LINE1(0));
        clcd_print(time, LINE2(0));
        if (t_flag >= 0 && t_flag < 100) {
            clcd_print(time, LINE2(0));
            t_flag++;
        } else if (t_flag >= 100 && t_flag < 200) {
            clcd_print("  ", LINE2(3));
            if (t_flag++ >= 199)
                t_flag = 0;
        }
        if (key == MK_SW5) {
            if (time[4] < '9') {
                ++time[4];
            } else {
                time[4] = '0';
                if (time[3] < '5')
                    ++time[3];
                else
                    time[3] = '0';
            }

        }
    } 
    else if (time_flag == 2) 
    {
        clcd_print("HH:MM:SS", LINE1(0));
        clcd_print(time, LINE2(0));
        if (t_flag >= 0 && t_flag < 100) 
        {
            clcd_print(time, LINE2(0));
            t_flag++;
        }
        else if (t_flag >= 100 && t_flag < 200)
        {
            clcd_print("  ", LINE2(6));
            if (t_flag++ == 199)
                t_flag = 0;
        }
        if (key == MK_SW5) 
        {
            if (time[7] < '9') {
                ++time[7];
            } else {
                time[7] = '0';
                if (time[6] < '5')
                    ++time[6];
                else
                    time[6] = '0';
            }

        }
        
        
       
    }
    if(key == 15)
        {
            save_exit(key);
            
            return;
        }
     if(key == 16)
        {
         main_f = MENU;
           return;
        }


}

void save_exit(char key)
{    
        hrs = (((time[0] - 48) * 10) + (time[1] - 48));
        min = (((time[3] - 48) * 10) + (time[4] - 48));
        secs = (((time[6] - 48) * 10) + (time[7] - 48));
        
         dummy = read_ds1307(SEC_ADDR);
        write_ds1307(SEC_ADDR, dummy | 0x80);
        
         write_ds1307(SEC_ADDR, (secs % 10) | ((secs / 10) << 4));
         write_ds1307(MIN_ADDR, (min % 10) | ((min / 10) << 4));
         write_ds1307(HOUR_ADDR, (hrs % 10) | ((hrs / 10) << 4));  

         dummy = read_ds1307(SEC_ADDR);
         write_ds1307(SEC_ADDR, dummy & 0x7F); 
         
         if(key == 15)
         {
             main_f = MENU;
         } 
         
         return;
}