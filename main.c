
#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "eeprom.h"
#include "matrix_keypad.h"
#include "timer0.h"
#include "ds1307.h"
#include "i2c.h"

void inti_config() {
    init_adc();
    init_clcd();
    init_matrix_keypad();
    init_i2c();
    init_ds1307();
}
char main_f = 0, menu_f = 0;
void main(void) {
    inti_config();

    char key;
    unsigned int prev_key, delay=0;
    while (1) {
        key = read_switches(LEVEL_CHANGE);

        if(key!=ALL_RELEASED)
        {
            prev_key=key;
            delay++;
        
        if(delay==1000)
        {
            key=key+10;
            delay=0;
        }
        else
            key=0;
        }
        else if(delay<1000 && delay>0)
        {
            key=prev_key;
            delay = 0;
        }
        
        if(main_f == DASHBOARD) 
        { 
            dashboard(key);
                      
        } 
        else if(main_f == PASSWORD) 
        {
            password(key);
        }
        else if(main_f == MENU)
        {
            menu(key);
        }
       else if(main_f == MENU_ENTER)
        {
            if(menu_f == VIEWLOG)
            {
                view_log(key);
            }
       else if(menu_f == DOWNLOADLOG)
        {
           download_log();
        }
       else if(menu_f == CLEARLOG)
        {
           clear_log(key);
        }
       else if(menu_f == SETTIME)
        {
           settime(key);
        }
       else if(menu_f == CHANGEPASS)
        {
            change_pass(key);
        }
       }
    }
}


