#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "uart.h"
#include "eeprom.h"

extern char main_f,lap;
extern unsigned int i;
void download_log()
{ 
    char i = 0;
    init_uart();
    while(i<lap)
    { 
        for(char j = 0;j<10;j++)
        {
            putch(read_external_eeprom((i*10)+j)); 
            if(j == 1)
                putch(':');
            if(j== 3)
                putch(':');
            if(j == 5)
                putch(' ');
            if(j==7)
                putch(' ');
                
            
                
        }
        puts("\n\r");
        i++;
    }
    clcd_print(" LOGS DOWNLOADED  ",LINE1(0));
    clcd_print(" SUCCESSFULLY    ",LINE2(0));
    for(unsigned long int i= 1500000;i--;);
    char prev_i = i;
    i = 8;
    store_event();
    main_f = MENU;
}