/*
 * File:   eeprom.c
 * Author: Admin
 *
 * Created on 29 May, 2024, 2:10 AM
 */


#include <xc.h>
#include "main.h"
#include "i2c.h"
#include "eeprom.h"

/* 
 * DS1307 Slave address
 * D0  -  Write Mode
 * D1  -  Read Mode
 */

/*void init_ds1307(void)
{
	unsigned char dummy;

	/* Setting the CH bit of the RTC to Stop the Clock */
	//dummy = read_ds1307(SEC_ADDR);
	//write_ds1307(SEC_ADDR, dummy | 0x80); 

	/* Seting 12 Hr Format */
	//dummy = read_ds1307(HOUR_ADDR);
	//write_ds1307(HOUR_ADDR, dummy | 0x40); 

	/* 
	 * Control Register of DS1307
	 * Bit 7 - OUT
	 * Bit 6 - 0
	 * Bit 5 - OSF
	 * Bit 4 - SQWE
	 * Bit 3 - 0
	 * Bit 2 - 0
	 * Bit 1 - RS1
	 * Bit 0 - RS0
	 * 
	 * Seting RS0 and RS1 as 11 to achive SQW out at 32.768 KHz
	 */ 
	//write_ds1307(CNTL_ADDR, 0x93); 

	/* Clearing the CH bit of the RTC to Start the Clock */
	//dummy = read_ds1307(SEC_ADDR);
	//write_ds1307(SEC_ADDR, dummy & 0x7F); 

//}

void write_external_eeprom(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(SLAVE_WRITE);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
    for(int i=3000;i--;);
}

unsigned char read_external_eeprom(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(SLAVE_WRITE);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(SLAVE_READ);
	data = i2c_read();
	i2c_stop();

	return data;
}