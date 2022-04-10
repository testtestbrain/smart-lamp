#include "HT66F2390.h"
#include "Delay.h"

void Delay10us(unsigned int num)  //0~65535
{
	unsigned int i;
	unsigned int j;
	for(i=0;i<num;i++)
		for(j=0;j<5;j++) GCC_NOP();	
}
void Delay100us(unsigned int num)  //0~65535
{
	unsigned int i,j;
	for(i=0;i<num;i++)
		for(j=0;j<52;j++) GCC_NOP();	
}
void Delay100ms(unsigned int num)  //0~65535
{
	unsigned int i,j;
	for(i=0;i<num;i++)
		for(j=0;j<52000;j++) GCC_DELAY(1);	
}