#include "HT66F2390.h"
#include "UART_v2.0.h"

void Initial_UART(u8 ModuleNum,u32 BaudRate,u32 F_Sys){
/*	
	name	pin		function
	-------------------------------
	PD4		59		Rx0
	PD5		60		Tx0
	PD1		52		RX1
	PD2		53		Tx1
	PG0		38		RX2
	PG1		37		TX2
	-------------------------------
*/	
	int N;
	char modu=ModuleNum;
	
	//step 1. set pin configure
	//should be manual set
	if(ModuleNum==0){
		if(0){
			_pds1 |= 0x09;	//pd5 tx0, pd4 rx0
			_rx0ps = 1;		//pd4 rx0 
		}
		else {
			_pas1 |= 0xf0;	//pa7 tx0, pa6 rx0
			_rx0ps = 0;		//pa6 rx0 
		}
	}
	else if(ModuleNum==1){
		_pds0=0x28;		//PD2, PD1 pin function TX1, RX1
		_rx1ps=0;		//RX1 input source PD1
	}
	else if(ModuleNum==2){
		if(1){
			_pgs0 |= 0x0f;		//pg1 tx2, pg0 rx2  
			_rx2ps = 1;			//rx2 pg0
		}
		else {
			_pbs0 |= 0x2c;		//pb1 tx2, rx2 pb2
			_rx2ps = 0;			//rx2 pb2
		}
	}
	
	//step 2. calculate UART baud rate
	//if BaudRate=115200 F_Sys=12M Hz N=8 ** Manual setting **
	N=F_Sys/(16*BaudRate)-1;
	
	//step 3. set UART configure
	
	if(modu==2) modu=-1;		//to meet register
/*	_u1cr1=0x80;
	_u1cr2=0xe0;
	_brg1=0x47;
*/	*(&_u0cr1+offset*modu)=0x80;	//Enable UART0
	*(&_u0cr2+offset*modu)=0xE0;	//Enable TXn, Enable RXn, High speed baud rate
	*(&_brg0+offset*modu)=N;		//11.0582MHZ/(16(1+"71"))=9600	//0x08
}

void String(u8 ModuleNum, char word[]){
	int i;
	char modu=ModuleNum;
	
	if(modu==2) modu=-1;		//to meet register
	for(i=0;i<strlen(word);i++){
		*(&_txr_rxr0+offset*modu)=word[i];
		while((*(&_u0sr+offset*modu) & 0x02)==0);	//data being transmitted
	}
}

void chars(u8 ModuleNum, char word){
	int i;
	char modu=ModuleNum;
	
	if(modu==2) modu=-1;		//to meet register

	*(&_txr_rxr0+offset*modu)=word;
	while((*(&_u0sr+offset*modu) & 0x02)==0);	//data being transmitted

}
/*
int	Pow2(int num,int index){
	int num2=num;
	
	if(index==0) return num=1;
	
	for(index;index>1;index--){
		num=num*num2;
	}
	return num;
}
*/
void Int_to_String(u8 ModuleNum, unsigned int num){
	
	char i=0;
	char modu=ModuleNum;
	unsigned char showNum[5]={0,0,0,0,0};
	
	//if 0 than output 0 and return
	if(num==0){
		if(modu==2) modu=-1;
		*(&_txr_rxr0+offset*modu)=0+0x30;
		while((*(&_u0sr+offset*modu) & 0x02)==0);
		return;
	}
	
	while(num>0){ 	//count Digits
		showNum[i]=num%10;
		num=num/10;
		i++;
	}
	
		//						             <- v
	i--;//backwards to now value  [0] [1] [2] [null] [null]
	
	//show number
	for(i;i>=0;i--){
		if(modu==2) modu=-1;
		*(&_txr_rxr0+offset*modu)=showNum[i]+0x30;
		while((*(&_u0sr+offset*modu) & 0x02)==0);
	}
}

/*
/////////////////////////////
[	Tx Rx select table		]
/////////////////////////////

PAS17~PAS16: PA7 	11: TX0		PAS1
PAS15~PAS14: PA6	11: RX0

PDS13~PDS12: PD5	10: TX0
PDS11~PDS10: PD4	01: RX0

RX0PS: RX0 		0: PA6  1: PD4


PDS05~PDS04: PD2	10: TX1
PDS03~PDS02: PD1 	10: RX1

PFS17~PFS16: PF7	01: TX1
PFS15~PFS14: PF6	10: RX1

RX1PS: RX1 		0: PD1  1: PF6


PBS03~PBS02: PB1 	11: TX2
PBS05~PBS04: PB2	10: RX2

PGS03~PGS02: PG1	11: TX2
PGS01~PGS00: PG0	11: RX2

RX2PS: RX2		0: PB2  1: PG0


*/
