/*
 * ENGG2800_Project_eeprom.c
 *
 * Created: 26-Aug-14 8:31:16 AM
 *  Author: Zakk
 */ 

#include <avr/io.h>
#define FOSC 1843200 // Clock Speed
#define BAUD 9600
#include <i2c>

void main(void){
	unsigned char aChar = '40';
	int aInt = aChar - '0';
	TWI_init_master();
	TWI_start();
	TWI_write_data(aChar);
	TWI_read_address(aChar);
	TWI_stop();
}

void TWI_init_master(void) // Function to initialize master
{
	TWBR=0x01;    // Bit rate
	TWSR=(0<<TWPS1)|(0<<TWPS0);    // Setting prescalar bits
	// SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
}

void TWI_start(void)
{
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT))); // Wait till start condition is transmitted
	while((TWSR & 0xF8)!= 0x08); // Check for the acknowledgement
}

void TWI_read_address(unsigned char data)
{
	TWDR=data;    // Address and read instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
	while((TWSR & 0xF8)!= 0x40);  // Check for the acknoledgement
}

void TWI_write_data(unsigned char data)
{
	TWDR=data;    // put data in TWDR
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
	while((TWSR & 0xF8) != 0x28); // Check for the acknoledgement
}

void TWI_stop(void)
{
	// Clear TWI interrupt flag, Put stop condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while(!(TWCR & (1<<TWSTO)));  // Wait till stop condition is transmitted
}