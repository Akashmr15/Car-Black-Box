/* 
 * File:   i2c.h
 * Author: Admin
 *
 * Created on 27 May, 2024, 3:49 PM
 */

#ifndef I2C_H
#define I2C_H


void init_i2c(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(void);

#endif