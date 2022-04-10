#ifndef _APDS_9960_H_
#define _APDS_9960_H_

#include "HT66F2390.h"
#include "I2C_GPIO.h"
//#include "UART_v2.0.h"
	
	void test_APDS_9960();	//read id

	//ProximityDetection   "int during time so short , don't use , shoud add wait"
	void initProximityDetection();
	//void initProximityDetection_int();
	void enableProximityDetection();
	//void enableProximityDetection_int();
	
	//void clearProximity_int();
	
	void readProximityDetection();
	//void readProximityDetection_int();
	
#endif