#include "test.h"

void UART0_IRQHandler(void) {
char c;
if(echo==1){
if (tx==0 && tx_start ==0)
	{
		c=UART0->D;
	   if  (c != '\0')
     {
		*(str+t) = c; /* read the char received */
	*(rdata+t)=*(str+t);
	 CBWrite(&cb1, *(str+t));
	 CBWrite(&cb2, *(str+t));
   t++;
	}
	else {
		tx_start=1;

	}

	}
//UART00_init();
else if(tx == 1)
{
#ifdef DEBUG
UART0->D= *(ptr1+k);
#endif

#ifdef CIRBUFFER


//CBRead(&cb2, u );

UART0->D= *(p+k);
#endif
  // delayMs(2);
   k++;
  tx=0;
}
//LED_set(c); /* and use it to set LEDs */
}

else if(echo==0){
	if(transmit==1){
		if(*(p+k)=='~')
			transmit=0;
		else{
			UART0->D= *(p+k);
			k++;
		}
	}

}
}


void main(){
	g=malloc(128*sizeof(char));
	p=malloc(128*sizeof(char));
	u=malloc(128*sizeof(char));
	 memset(&cb1, 0, sizeof(cb1));
	 memset(&cb2, 0, sizeof(cb2));


	    cb1.buf=g;
	    cb1.size=128;
	    cb1.read=0;
	    cb1.write=1;

	    cb2.buf=p;
	   	    cb2.size=128;
	   	    cb2.read=0;
	   	    cb2.write=1;

	    ftoa(n, res, 6);
if(echo==1){
#ifdef FRDM
	__disable_irq(); /* global disable IRQs */
	 UART0_init();
 	__enable_irq();
 	                     /* global enable IRQs */
while (tx_start==0);
__disable_irq();
 UART00_init();
#endif
	//LOG_0(rdata,t);


   // printf("\n\"%s\"\n", res);
   // return 0;
//char str1[5]="Hello";
//char str2[2]="12";
//uint8_t *ptr=str1;
#ifdef CIRBUFFER
CirBuf_Transmit(p, t);
#endif

#ifdef DEBUG
//TIMER0_init();
//TPM0->SC|=0x08;				//enable timer
//LOG_0(g, 4);
//LOG_0(time_ptr, 5);


  LOG_0(rdata, t);
//  TPM0->SC=0;					//disable timer
 //  time=3*((count*65536)+TPM0->CNT);	//time(in microseconds) 3us is the time required by TMP0 counter to increment by 1
LOG_1(rdata, t, param, 0);		//pass 0 if it is a float type
#endif
}

else if(echo==0)
	if(transmit==1){
	//	if(Bufferempty(&cb1)==BufferEmpty)
			UART_transmit_message(transmit_data);
	//	else UART_transmit_message(transmit_data);
	}
while (1) {
	/* UART0 receive is moved to interrupt handler*/
	}

}