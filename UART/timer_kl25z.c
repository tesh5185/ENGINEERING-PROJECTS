#include "timer_kl25z.h"


void TIMER0_init(){
		__disable_irq();

		SIM->SOPT2|=0x01000000;		//use mcgfllclk
		SIM->SCGC6|=0x01000000;		//enable clock to tpm0
		TPM0->SC=0;					//disable timer
		TPM0->SC=0x06; 				//prescaler to 64
		TPM0->MOD=0xFFFF;
		TPM0->SC|=0x80;				//clear TOF
		TPM0->SC|=0x40;				//enable timeout interrupt
		NVIC->ISER[0]|=0x00020000;
		__enable_irq();
}
