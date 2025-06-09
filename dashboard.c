#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "adc.h"
#include "matrix_keypad.h"
#include "ds1307.h"
#include "i2c.h"

unsigned char on;
unsigned char time[9];
unsigned char clock_reg[3];
unsigned int speed;
unsigned int i=0;
char *event[]={"ON","GR","GN","G1","G2","G3","G4","-C"};

void dashboard(char key)
{
    clcd_print("TIME",LINE1(2));
    clcd_print("EV",LINE1(10));
    clcd_print("SP",LINE1(14));
    display_time();
    clcd_print(time,LINE2(0));
    display_event(key);
    display_speed();
    if(on==0)
    {
        store_event();
        on=1;
    }
    if(key==5)
    {
        extern char main_f;
        main_f=PASSWORD;
        CLEAR_DISP_SCREEN;
    }
}
// display the speed ADC
void display_speed() 
{
    unsigned  int adc_reg_val;
    adc_reg_val=read_adc(CHANNEL4);
    speed = adc_reg_val/10;
    clcd_putch((speed%10)+48,LINE2(15));
    clcd_putch((speed/10)+48,LINE2(14));
}
// display the events
unsigned char key;
unsigned int flag1=0;
void display_event(char key)
{
    if(key == MK_SW2 && flag1 == 0)
    {
        if(i<6)
        {
            i++;
            store_event();
        }
    }
    else if(key == MK_SW3 && flag1 == 0)
    {
        if(i>0)
        {
            i--;
            store_event();
        }
    }  
    else if(key == MK_SW1)
    {
        i=7;
        flag1=1;
        store_event();
    }
    else if(key == MK_SW2 || key == MK_SW3)
    {
        i=2;
        flag1=0;
        store_event();
    }
    clcd_print(event[i],LINE2(10)); 
}


void display_time()
{
   clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}



