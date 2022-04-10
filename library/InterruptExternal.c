#include "HT66F2390.h"

void InterruptExternal_0_config(){
//	01: Rising edge		10: Falling edge	11: Rising and falling edges	00: Disable
	_int0s1=1;
	_int0s0=0;

	_int0ps=1;			//PA6 INT0 input source		//0 PA1; 1 PA6 
	
//	_PAS03=0;			//PA1 INT0
//	_PAS02=0;
	_pas15=0;			//PA6 INT0
	_pas14=0;
	
	_int0e=1;			//Enable INT0 interrupt
	_emi=1;				//Enable Global interrupt
}

void InterruptExternal_1_config(){
//	01: Rising edge		10: Falling edge	11: Rising and falling edges	00: Disable
	_int1s1=0;
	_int1s0=1;

	_int1ps=1;			//PA6 INT1 input source		//0: PA3; 1: PA7 

//	_pas07=0;			//PA3 INT1
//	_pas06=0;
	_pas17=0;			//PA7 INT1
	_pas16=0;
	
	_int1e=1;			//Enable INT1 interrupt
	_emi=1;				//Enable Global interrupt
}

void InterruptExternal_2_config(){
	//	01: Rising edge		10: Falling edge	11: Rising and falling edges	00: Disable
	_int2s1=0;
	_int2s0=1;

	_int2ps=1;			//PA6 INT2 input source		//0: PA4; 1: PD0

//	_pas11=0;			//PA4 INT2
//	_pas10=0;
	_pds01=0;			//PD0 INT2
	_pds00=0;
	
	_int2e=1;			//Enable INT2 interrupt
	_emi=1;				//Enable Global interrupt
}

void InterruptExternal_3_config(){
	//	01: Rising edge		10: Falling edge	11: Rising and falling edges	00: Disable
	_int3s1=0;
	_int3s0=1;

	_int3ps=1;			//PA6 INT3 input source		//0: PA5; 1: PC7

//	_pas13=0;			//PA5 INT3
//	_pas12=0;
	_pcs17=0;			//PC7 INT3
	_pcs16=0;
	
	_int3e=1;			//Enable INT3 interrupt
	_emi=1;				//Enable Global interrupt
}