#include "uart.h"

/* initialize UART0 to receive at 115200 Baud */
void UART0_init(void) {
SIM->SCGC4 |= 0x0400; /* enable clock for UART0 */
SIM->SOPT2 |= 0x04000000; /* use FLL output for UART Baud rate
generator */
UART0->C2 = 0; /* turn off UART0 while changing configurations */
UART0->BDH = 0x00;
UART0->BDL = 0x17; /* 115200 Baud */
UART0->C4 = 0x0F; /* Over Sampling Ratio 16 */
UART0->C1 = 0x00; /* 8-bit data */
UART0->C2 = 0x24; /* enable receive and receive interrupt*/
NVIC->ISER[0] |= 0x00001000; /* enable INT12 (bit 12 of ISER[0]) */
SIM->SCGC5 |= 0x0200; /* enable clock for PORTA */
PORTA->PCR[1] = 0x0200; /* make PTA1 UART0_Rx pin */
tx=0;
}
/* initialize all three LEDs on the FRDM board */

void UART00_init(void)
  {
	  SIM->SCGC4|=0x0400;
	  SIM->SOPT2|=0x04000000;
	  UART0->C2=0;
	  UART0->BDH=0x00;
	  UART0->BDL=0x17;
	  UART0->C4=0x0F;
	  UART0->C1=0x00;
	  UART0->C2=0x88;
	  NVIC->ISER[0] |= 0x00001000;
	  SIM->SCGC5|=0x0200;
	  PORTA->PCR[2]=0x0200;

  }

void UART_transmit_message(uint8_t string[]){
	p=string;
	UART00_init();
	__enable_irq();
	while(transmit==1);
}

void UART_transmit(){
	int i=0;
	for(i=0; i<strlen(transmit_data);i++){
		if(CBWrite(&cb2, *(transmit_ptr+i))==BufferFull){
			UART_transmit_message(string1);
			//transmit=0;
			break;
		}
		}
	UART00_init();
	__enable_irq();
}

