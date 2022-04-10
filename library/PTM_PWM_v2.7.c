#include "HT66F2390.h"
#include "PTM_PWM_v2.0.h"

void PTP0_pin(char x){		//PTP0  1:PC2; 0:PF5
	if(x==1){
		_pcs05=1; 
		_pcs04=0; 
	}
	else {
		_pfs13=1; 
		_pfs12=0;
	}
}

void PTP1_pin(char x){		//PTP1  1:PC4; 0:PE3
	if(x==1){
		_pcs11=1; 
		_pcs10=0;
	}
	else {
		_pes07=1; 
		_pes06=0;
	}
}

void PTP2_pin(char x){		//PTP2	1:PB3; 0:PD2
	if(x==1){
		_pbs07=1; 
		_pbs06=1;
	}
	else {
		_pds05=0; 
		_pds04=1;
	}
}

void PTP3_pin(char x){		//PTP3	1:PB2; 0:PD4
	if(x==1){
		_pbs05=1; 
		_pbs04=1;
	}
	else {
		_pds11=1; 
		_pds10=0;
	}
}

void PTM_PWM_config(u8 ModuleNum,u8 pin){		//ModuleNum rang 1-3
	u8 modu=ModuleNum;
	
	if(ModuleNum==1 ||ModuleNum==2||ModuleNum==3){
		
		modu=modu-1;					//because form PTM1
	
		//PTMn Counter f_sys/4, enable PWM
		*(&_ptm1c0+modu*offset)=0x08;	
		
		//PWM Mode, PWM output mode, Active high
		*(&_ptm1c1+modu*offset)=0xa8;
		//CCRP <= Periodic ;CCRA <= Duty
	
		//pin should manual select
		if(ModuleNum==1) PTP1_pin(pin);
		else if (ModuleNum==2) PTP2_pin(pin);
		else if (ModuleNum==3) PTP3_pin(pin);
		
	}
	else if(ModuleNum==0){				//due to no logic
	
		//PTMn Counter f_sys/4, enable PWM
		_ptm0c0=0x08;
		
		//PWM Mode, PWM output mode, Active high
		_ptm0c1=0xa8;
		//CCRP <= Periodic ;CCRA <= Duty
	
		//pin should manual select
		PTP0_pin(pin);
	}
}

//so quite use will error output
void PTM_PWM_period_duty(u8 ModuleNum, u16 period, u16 duty){

	switch(ModuleNum){
		case 0:
			//Periodic CCRP
			_ptm0rph=period>>8;		
			period=period%256;
			_ptm0rpl=period;	
		
			//duty CCRA
			_ptm0ah=duty>>8;
			duty=duty%256;
			_ptm0al=duty;
		break;
			
		case 1:
			//Periodic CCRP
			_ptm1rph=period>>8;
			period=period<<8;
			period=period>>8;
			_ptm1rpl=period;
		
			//duty CCRA
			_ptm1ah=duty>>8;
			duty=duty<<8;
			duty=duty>>8;
			_ptm1al=duty;
		break;
			
		case 2:
			//Periodic CCRP
			_ptm2rph=period>>8;
			period=period<<8;
			period=period>>8;
			_ptm2rpl=period;
		
			//duty CCRA
			_ptm2ah=duty>>8;
			duty=duty<<8;
			duty=duty>>8;
			_ptm2al=duty;
		break;			
		
		case 3:
			//Periodic CCRP
			_ptm3rph=period>>8;
			period=period<<8;
			period=period>>8;
			_ptm3rpl=period;
		
			//duty CCRA
			_ptm3ah=duty>>8;
			duty=duty<<8;
			duty=duty>>8;
			_ptm3al=duty;
		break;	
	}
		
}
