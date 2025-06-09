#include <xc.h>
#include "eeprom.h"
#include "main.h"

extern char time[];
extern char *event[];
extern unsigned int speed;
unsigned char lap;
unsigned char arr[11];
extern unsigned int i;
unsigned char overflow;

void store_event()
{    
        arr[0]=time[0];
        arr[1]=time[1];
        arr[2]=time[3];
        arr[3]=time[4];
        arr[4]=time[6];
        arr[5]=time[7];
        arr[6]=event[i][0];
        arr[7]=event[i][1];
        arr[8]=((speed/10)+48);
        arr[9]=((speed%10)+48);
        
    for(unsigned int i=0;i<10;i++)
    {
        write_external_eeprom((lap*10)+i,arr[i]);
        if(i==9)
        {
            lap++;
        }
        else if(i>9)
        {
            lap=0;
            overflow++;
        }
    }
        
}