#ifndef _UART_V2.0_H_
#define _UART_V2.0_H_

#include "HT66F2390.h"

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef long s32;
typedef unsigned long u32;

#define offset 0x05

	void Initial_UART(u8 ModuleNum,u32 BaudRate,u32 F_Sys);

	void String(u8 ModuleNum, char word[]);
	void chars(u8 ModuleNum, char word);
	
	//int	 Pow2(int num,int index);
	void Int_to_String(u8 ModuleNum, unsigned int num);
	
#endif