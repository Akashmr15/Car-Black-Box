/* 
 * File:   eeprom.h
 * Author: Admin
 *
 * Created on 29 May, 2024, 2:11 AM
 */

#ifndef external_eeprom
#define external_eeprom

#define SLAVE_READ		0xA1
#define SLAVE_WRITE		0xA0


/*#define SEC_ADDR		0x00
#define MIN_ADDR		0x01
#define HOUR_ADDR		0x02
#define DAY_ADDR		0x03
#define DATE_ADDR		0x04
#define MONTH_ADDR		0x05
#define YEAR_ADDR		0x06
#define CNTL_ADDR		0x07
*/
//void init_ds1307(void);
void write_external_eeprom(unsigned char address1,  unsigned char data);
unsigned char read_external_eeprom(unsigned char address1);

#endif