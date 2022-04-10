#ifndef _PTM_PWM_H_
#define _PTM_PWM_H_

#include "HT66F2390.h"

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef long s32;
typedef unsigned long u32;
/*
//PTP0  1:PC2; 0:PF5
#define PTP0_pin(x) ( (x)?(_pcs05=1 _pcs04=0 ):(_pfs13=1 _pfs12=0) )
//PTP1  1:PC4; 0:PE3	
#define PTP1_pin(x) ( (x)?(_pcs11=1 _pcs10=0 ):(_pes07=1 _pes06=0) )
//PTP2	1:PB3; 0:PD2
#define PTP2_pin(x) ( (x)?(_pbs07=1 _pbs06=1 ):(_pds05=0 _pds04=1) )
//PTP3	1:PD4; 0:PB2
#define PTP3_pin(x) ( (x)?(_pbs05=1 _pbs04=1 ):(_pds11=1 _pds10=0) )
*/

#define offset 0x08

extern void PTP0_pin(char x);//PTP0  1:PC2; 0:PF5
extern void PTP1_pin(char x);//PTP1  1:PC4; 0:PE3
extern void PTP2_pin(char x);//PTP2	 1:PB3; 0:PD2
extern void PTP3_pin(char x);//PTP3	 1:PD4; 0:PB2

extern void PTM_PWM_config(u8 ModuleNum,u8 pin);		//ModuleNum rang 0-3, pin 0,1
extern void PTM_PWM_period_duty(u8 ModuleNum, u16 period, u16 duty);	//ModuleNum rang 1-3
//extern void PTM2_PWM16bit_testconfig();

#endif