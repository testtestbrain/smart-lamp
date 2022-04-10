#include "HT66F2390.h"
#include "APDS_9960.h"
#include "I2C_GPIO.h"
#include "UART_v2.0.h"

void test_APDS_9960(){		//read id
	//test APDS_9960 read ID
	i2c_readData(0x39,0x92,1);
	if(i2c_data1==0xab) String(0,"APDS-9960\r\n");
	else String(0,"APDS-9960\r\n");
}

void initProximityDetection(){
	//Enable Register: power on, Proximity Enable
	i2c_writeData(0x39,0x80,0x05);
}

void initProximityDetection_int(){
	//Enable Register: power on, Proximity Enable, Proximity Interrupt Enable
	i2c_writeData(0x39,0x80,0x25);
}

void enableProximityDetection(){
	//Proximity Pulse Count Register: Proximity Pulse Length 8us, Proximity Pulse Count 1
	i2c_writeData(0x39,0x8e,0x40);
	
	//Control Register One: LED Drive Strength 100 mA, 
	i2c_writeData(0x39,0x8f,0x00);
	
	//Configuration Register Two: Additional LDR current increased of LED_BOOST 300%
	i2c_writeData(0x39,0x90,0x31);
	
	//Proximity Offset UP / RIGHT Register: Offset Correction Factor 0
	i2c_writeData(0x39,0x9c,0x00);	
	
	//Proximity Offset DOWN / LEFT Register: Offset Correction Factor 0
	i2c_writeData(0x39,0x9e,0x00);
	
	//Configuration Three Register : no mask
	i2c_writeData(0x39,0x9f,0x00);
}

void enableProximityDetection_int(){
	//Persistence Register: Every proximity cycle
	i2c_writeData(0x39,0x8c,0x00);
	
	//Proximity Pulse Count Register: Proximity Pulse Length 8us, Proximity Pulse Count 1
	i2c_writeData(0x39,0x8e,0x40);
	
	//Control Register One: LED Drive Strength 100 mA, 
	i2c_writeData(0x39,0x8f,0x00);
	
	//Configuration Register Two: Additional LDR current increased of LED_BOOST 300%
	i2c_writeData(0x39,0x90,0x31);
	
	//Proximity Offset UP / RIGHT Register: Offset Correction Factor 0
	i2c_writeData(0x39,0x9c,0x00);	
	
	//Proximity Offset DOWN / LEFT Register: Offset Correction Factor 0
	i2c_writeData(0x39,0x9e,0x00);
	
	//Configuration Three Register : no mask
	i2c_writeData(0x39,0x9f,0x00);
}

void clearProximity_int(){
	//Proximity Interrupt Clear
	addressWrite(0x39);
	i2c_write(0xE5);
	i2c_stop();
}

void readProximityDetection(){
	//Proximity Data Register PDATA
	i2c_readData(0x39,0x9c,1);
	Int_to_String(0,((int)i2c_data1));	
	String(0,"\r\n");
}

void readProximityDetection_int(){
	//Proximity Data Register PDATA
	i2c_readData(0x39,0x9c,1);
	
	//Proximity Interrupt Clear
	clearProximity_int();
	
	Int_to_String(0,((int)i2c_data1));	
	String(0,"\r\n");
}
