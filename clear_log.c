#include <xc.h>
#include "main.h"
#include "clcd.h"

extern char lap,overflow;
extern char main_f;
void clear_log(char key)
{
    lap= 0,overflow = 0;
    clcd_print("LOGS ARE CLEARED",LINE1(0));
    clcd_print("SUCCESSFULLY",LINE2(2));
if(key==16)
{
    main_f=MENU;
}    
}