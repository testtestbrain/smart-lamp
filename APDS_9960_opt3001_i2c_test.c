#include "HT66F2390.h"
#include "OPT3001.h"
#include "UART_v2.0.h"
#include "I2C_GPIO_v2.0.h"
#include "APDS_9960.h"
#include "Delay.h"
#include "PTM_PWM_v2.0.h"
////all document will use same define//////////////////
//i2C no init can run?!////////////////////////////////

#define period 600		//PWM ~=200Hz  0.005s


void System_config();
void STM0_config();
unsigned char determineBtValue(int value);

int counter=0;
//int distanceLux=0;
//unsigned char startCount=0,endCount=1,orphan=0;

void __attribute((interrupt(0x14))) ISR_time (void)
{
	//_stm0af=0;
	counter++;
	
	_stm0pf=0;		//should manual clear
} 


void main()
{
	unsigned char i,j=0;
	//unsigned char distance=0;
	unsigned char lockStart=0,lockStartRead=0,lockChangeRead=0;
	unsigned char btValue=0,btValueTemp=0;
	
	int distanceLux=0,distanceLux_F[2],distanceLux_pwm[5];
	
	unsigned char lightColor=2;
	int illuminance[3]={0,300,600};
	
	unsigned char mode=0;
	
	int lux1,lux2,lux_all;

	System_config();
	Initial_UART(0,9600,16000000);
	STM0_config();
	PTM_PWM_config(2,0); 				//pin 03	PD2
	PTM_PWM_config(3,1);				//pin 02	PB2
	i2c_init();

	//test_APDS_9960();
	
	initProximityDetection();
	enableProximityDetection();
	opt3001_init(adrr2gnd);
	opt3001_init(adrr2vdd);
	
	while(1){
		for(i=0;i<2;i++){
			distanceLux_F[i]=(((int)readProximityDetection())*40)/17;
		}
		distanceLux=(distanceLux_F[0]+distanceLux_F[1])/2;
	//	if(distanceLux<=17) distanceLux=0;
	
	
		//not complete start read
		if(distanceLux<50){		//40//
			_st0on=0;
			counter=0;	
			
			//String(0,"not complete\r\n");
		}	
		
		//start read debounce
		if((distanceLux>=50) && (lockStart==0)){	//40//start value
			_st0on=1;
			
			//String(0,"start\r\n");
			
			if(counter>=23){//start read debounce counter
				_st0on=0;
				
				//String(0,"counter >=30 ");
				//Int_to_String(0,counter);
				//String(0,"\r\n");
				
				counter=0;
				lockStart=1;
			}
		}
		

		
		if(lockStart==1){
			
			//String(0,"read\r\n");
			
			//only read once
			if(lockStartRead==0){
				btValue=determineBtValue(distanceLux);
				
				if((mode<=1)){
					if((btValue!=5) && (btValue!=1)){
						PTM_PWM_period_duty(lightColor,period,illuminance[btValue-2]);
						PTM_PWM_period_duty(lightColor,period,illuminance[btValue-2]);
					}
				}
				
				//change mode
				if(btValue==1){
					mode++;			//0 -> Y; 1 -> W; 2 ->autoY; 3 -> autoW; 4 ->turnOff; 5 -> turnOn
					
					if(mode==0)lightColor=2;
					else if(mode==1)lightColor=3;
					else if(mode==2){	//auto light
						PTM_PWM_period_duty(2,period,0);
						PTM_PWM_period_duty(2,period,0);
						PTM_PWM_period_duty(3,period,0);
						PTM_PWM_period_duty(3,period,0);
					}
					else if(mode==4){		//shout down
						PTM_PWM_period_duty(2,period,0);
						PTM_PWM_period_duty(2,period,0);
						PTM_PWM_period_duty(3,period,0);
						PTM_PWM_period_duty(3,period,0);
					}
					else if(mode==5) {
						mode=0;		//turn on
						lightColor=2;
					}
					
					String(0,"mode ");
					Int_to_String(0,(int)mode);
					String(0,"\r\n");
				}
				
				lockStartRead=1;
				
				//String(0,"read data\r\n");
			}
			
			//end
			if(lockStartRead==1){		//exit 33
			
				if(distanceLux<33){
					lockStart=0;
					lockStartRead=0;
					
					_st0on=0;
					counter=0;
					lockChangeRead=0;
					
					//String(0,"end\r\n");
				}
				/*else{	//change btValue
					btValueTemp=determineBtValue(distanceLux);
					
					if((btValueTemp!=1) && (btValueTemp!=btValue) && (lockChangeRead==1)){
						_st0on=1;
						lockChangeRead=1;
					}
					if((lockChangeRead==1) && (counter>20)){
						_st0on=0;
						counter=0;
						lockChangeRead=0;
						lockStartRead=0;
					}
				}*/
			}
		}
		
		
		//auto light
		if((mode==2) || (mode==3)){
			lux1=(int)opt3001_readLight(adrr2gnd);
			lux2=(int)opt3001_readLight(adrr2vdd);
			lux_all=(lux1+lux2)/2;
				
			Int_to_String(0,lux1);
			String(0,"  ");
				
			Int_to_String(0,lux2);
			String(0,"  ");
				
			Int_to_String(0,lux_all);
			String(0,"\r\n");
			
			if(btValue==2){
				PTM_PWM_period_duty(mode,period,0);
				PTM_PWM_period_duty(mode,period,0);
			}
			else if(btValue==3){
				lux_all=lux_all+100;
				PTM_PWM_period_duty(mode,period,600-lux_all);
				PTM_PWM_period_duty(mode,period,600-lux_all);
			}
			else if(btValue==4){
				lux_all=lux_all-100;
				
				PTM_PWM_period_duty(mode,period,600-lux_all);
				PTM_PWM_period_duty(mode,period,600-lux_all);
			}			
		}
	
		//determineBtValue(distanceLux);
		//Int_to_String(0,distanceLux);
		//String(0,"\r\n");
		
		//PTM_PWM_period_duty(2,period,distanceLux);
		//Delay100ms(3);
		
	}
}

void System_config(){
	//disable watch dog
	_wdtc=0xA8;	
	//system clock set 16Mhz
	_scc=0x04;
	_hircc=0x09;
}

void STM0_config(){
	_stm0c0=0x00;	//Run, fSYS/4, STMn Counter "OFF"
	_stm0c1=0xc0;	//Counter Mode,Comparator P match
	_stm0rp=0xff;	//~1/60s	16M/4/255/255 ~= 61		//CCRP 8-bit register
	//_st0on=1;
	
	//form CCRA
	_stm0pe=1;		//STM0 Comparator P match Interrupt control
	_mf0e=1;		//Multi-function 0 interrupt control
	_emi=1;			//Global interrupt control
	
	//_stm0pf=1;
}

unsigned char determineBtValue(int value){
/*	if((value>=40) && (value<=60)){
		String(0,"1\r\n");
		return 1;
	}
	else if((value>=61) && (value<=132)){
		String(0,"2\r\n");
		return 2;
	}
	else if((value>=133) && (value<=350)){
		String(0,"3\r\n");
		return 3;
	}
	else if((value>=351) && (value<=600)){
		String(0,"4\r\n");
		return 4;
	}
	else {
		String(0,"none\r\n");
		return 4;
	}
	*/
	
	if((value>=50) && (value<=68)){
		String(0,"1\r\n");
		return 1;
	}
	else if((value>=69) && (value<=123)){
		String(0,"2\r\n");
		return 2;
	}
	else if((value>=124) && (value<=330)){
		String(0,"3\r\n");
		return 3;
	}
	else if((value>=331) && (value<=600)){
		String(0,"4\r\n");
		return 4;
	}
	else {
		String(0,"none\r\n");
		return 4;
	}
}

/*
		lux1=(int)opt3001_readLight(adrr2gnd);
		lux2=(int)opt3001_readLight(adrr2vdd);
		lux_all=(lux1+lux2)/2;
		
		Int_to_String(0,lux1);
		String(0,"  ");
		
		Int_to_String(0,lux2);
		String(0,"  ");
		
		Int_to_String(0,lux_all);
		String(0,"\r\n");
		
		PTM_PWM_period_duty(2,period,600-lux_all);
		
		//Int_to_String(0,(int)readProximityDetection());
		//String(0,"\r\n");
		*/
		
		