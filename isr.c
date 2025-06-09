/*
 * File:   isr.c
 * Author: Admin
 *
 * Created on 27 May, 2024, 11:59 AM
 */


#include <xc.h>
#include "main.h"
#include "timer0.h"
unsigned int sec;
void __interrupt() isr(void)
{
	static unsigned long int count;
     
	if (TMR0IF)
	{
		TMR0 = TMR0 + 8;

		if (count++ == 20000)
		{
			count = 0;
            sec--;
		}
		TMR0IF = 0;
	}
}
    