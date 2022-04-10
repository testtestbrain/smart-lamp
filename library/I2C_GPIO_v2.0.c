#include "HT66F2390.h"
#include "I2C_GPIO_v2.0.h"


unsigned char i2c_data1=0,i2c_data2=0;

void i2c_init()
{
	PULLUP_SDA = 1;
	PULLUP_SCL = 1;
	SCL_PORT_ioset = 0;
	SDA_PORT_ioset = 0;
	SCL_PORT = 1;
	SDA_PORT = 1;
}

void i2c_start()
{
	SCL_PORT_ioset = 0;
	SDA_PORT_ioset = 0;
	
	SDA_PORT = 1;
	SCL_PORT = 1;
	GCC_DELAY(I2C_DELAY_TIME-I2C_START_STOP_DELAY_TIME);
	SDA_PORT = 0;
	GCC_DELAY(I2C_START_STOP_DELAY_TIME);
	SCL_PORT = 0;
	GCC_DELAY(I2C_DELAY_TIME - I2C_START_STOP_DELAY_TIME);
}

void i2c_stop()
{
	SCL_PORT_ioset = 0;
	SDA_PORT_ioset = 0;
	
	SDA_PORT = 0;
	GCC_DELAY(I2C_START_STOP_DELAY_TIME);
	SCL_PORT = 1;
	GCC_DELAY(I2C_START_STOP_DELAY_TIME);
	SDA_PORT = 1;
	GCC_DELAY(I2C_DELAY_TIME - I2C_START_STOP_DELAY_TIME);
	SCL_PORT = 0;
	GCC_DELAY(I2C_DELAY_TIME);
}

void i2c_write(unsigned char data)
{
	unsigned char i;
	bit ackbit = 0;
	
	SCL_PORT_ioset = 0;
	SDA_PORT_ioset = 0;
	
	for(i=0;i<8;i++)
	{
		SDA_PORT = ((data&0x80)?1:0);
		data <<=1;
		GCC_DELAY(I2C_START_STOP_DELAY_TIME);
		SCL_PORT = 1;
		GCC_DELAY(I2C_DELAY_TIME);
		SCL_PORT = 0;
		GCC_DELAY(I2C_DELAY_TIME - I2C_START_STOP_DELAY_TIME);
	}
	//SDA_PORT = 1;
	
	SDA_PORT_ioset = 1;
	GCC_DELAY(I2C_START_STOP_DELAY_TIME);
	SCL_PORT = 1;
	GCC_DELAY(30);			//30
	ackbit = SDA_PORT;
	GCC_DELAY(I2C_DELAY_TIME-30);
	SCL_PORT = 0;
	GCC_DELAY(I2C_DELAY_TIME - I2C_START_STOP_DELAY_TIME);

	//return ackbit;
}

unsigned char i2c_read(unsigned char send_ack)	//0 -> remaining data; 1 -> no data
{
	SDA_PORT_ioset = 1;
	SCL_PORT_ioset = 0;
	
	unsigned char i,data;
	data = 0x00;	
	for(i=0;i<8;i++)
	{
		SCL_PORT = 1;
		GCC_DELAY(I2C_DELAY_TIME-I2C_START_STOP_DELAY_TIME);
		
		data <<= 1;
		data |= SDA_PORT;
		
		SCL_PORT = 1;
		GCC_DELAY(I2C_START_STOP_DELAY_TIME);
	
		SCL_PORT = 0;
		GCC_DELAY(I2C_DELAY_TIME);
	}
	
	SDA_PORT_ioset = 0;
	
	if(send_ack==0)
	{
		SDA_PORT = 0;
	}
	else
	{
		SDA_PORT = 1;
	}
	
	GCC_DELAY(I2C_START_STOP_DELAY_TIME);
	
	SCL_PORT = 1;
	GCC_DELAY(I2C_DELAY_TIME);
	SCL_PORT = 0;
	GCC_DELAY(I2C_DELAY_TIME);
	return data;
}	

void addressWrite(unsigned char addr)
{
	bit ack;
	i2c_init();
	i2c_start();
	i2c_write(addr<<1);
	//i2c_stop();
	
	//return  ack;
}

void addressRead(unsigned char addr)
{
	bit ack;
	i2c_init();
	i2c_start();
	i2c_write((addr<<1)+1);
	//i2c_stop();
	
	//return  ack;
}

void i2c_writeData(unsigned char addr, unsigned char Reg, unsigned char data)
{
	addressWrite(addr);
	i2c_write(Reg);
	i2c_write(data);
	i2c_stop();
}

void i2c_readData(unsigned char addr, unsigned char Reg, unsigned char readRegNum)
{
	unsigned char data;
	
	addressWrite(addr);
	i2c_write(Reg);
	i2c_stop();
	
	addressRead(addr);
	
	if(readRegNum==1) i2c_data1=i2c_read(1);
	else if(readRegNum==2){
		i2c_data1=i2c_read(0);	//remaining data 
		i2c_data2=i2c_read(1);
	}
	i2c_stop();
}
