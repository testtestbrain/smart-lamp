#ifndef _I2C_GPIO_V2.0_H_
#define _I2C_GPIO_V2.0_H_


#include "HT66F2390.h"


//-----------define---------------

#define Bit_delay GCC_DELAY(1025) //1:0.26ns  

#define PULLUP_SDA _papu4
#define PULLUP_SCL _papu5

#define SDA_PORT  _pa4
#define SCL_PORT  _pa5

#define SDA_PORT_ioset _pac4	//0: Output  1: Input
#define SCL_PORT_ioset _pac5	//0: Output  1: Input

#define I2C_DELAY_TIME 200
#define I2C_START_STOP_DELAY_TIME 100

#define ACK   1
#define NO_ACK   0

//-------------------------------------------------

extern unsigned char i2c_data1,i2c_data2;

void i2c_init();
void i2c_start();
void i2c_stop();

void i2c_write(unsigned char data);
unsigned char i2c_read(unsigned char send_ack);	//0 -> remaining data; 1 -> no data

void addressWrite(unsigned char addr);
void addressRead(unsigned char addr);

//void i2c_writeData(unsigned char, unsigned char);
void i2c_writeData(unsigned char addr, unsigned char Reg, unsigned char data);
void i2c_readData(unsigned char addr, unsigned char Reg, unsigned char readRegNum);


#endif


//see SHT20 , go to V1.0

//void wait_SHT20();

// unsigned int SHT20_ReadTemperature_hold();
// unsigned int SHT20_RelativeHumidity_hold();

//void decode2temp_SHT20(unsigned int ans);
//void decode2RH_SHT20(unsigned int ans);