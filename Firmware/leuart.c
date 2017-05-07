#include "leuart.h"
#include "acc.h"
#include "sleep.h"
void leuart0_setup(void)
{

	 CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);  //lfxo clock for em2
	 CMU_ClockEnable(cmuClock_LEUART0, true);

	LEUART_Init_TypeDef leuart0Init =
 {
   .enable   = leuartEnable,     /* Activate data reception on LEUn_RX pin. */
   .refFreq  = 0,                  /* Inherit the clock frequenzy from the LEUART clock source */
   .baudrate = leuaert_baud,               /* Baudrate = 9600 bps */
   .databits = leuartDatabits8,    /* Each LEUART frame containes 8 databits */
   .parity   = leuartNoParity,     /* No parity bits in use */
   .stopbits = leuartstopbits,    /* Setting the number of stop bits in a frame to 2 bitperiods */
  };
 LEUART_Reset(LEUART0);
 LEUART_Init(LEUART0, &leuart0Init);
 LEUART0->ROUTE = LEUART_ROUTE_TXPEN |
                    LEUART_ROUTE_LOCATION_LOC0;

 LEUART0->CTRL|=LEUART_CTRL_LOOPBK;
 GPIO_PinModeSet(LEUARTport,            /* Port */
                   LEUARTpin,                    /* Port number */
                   gpioModePushPull,    /* Pin mode is set to input only, with pull direction given bellow */
                   1);                   /* Pull direction is set to pull-up */
 LEUART0->IEN|=LEUART_IEN_TXBL;
 NVIC_ClearPendingIRQ(LEUART0_IRQn);
 //NVIC_EnableIRQ(LEUART0_IRQn);
}
void leuart0_setup1(void)
{

	 CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);  //lfxo clock for em2

	 CMU_ClockEnable(cmuClock_LEUART0, true);

	LEUART_Init_TypeDef leuart0Init =
 {
   .enable   = leuartEnable,     /* Activate data reception on LEUn_RX pin. */
   .refFreq  = 0,                  /* Inherit the clock frequenzy from the LEUART clock source */
   .baudrate = leuaert_baud,               /* Baudrate = 9600 bps */
   .databits = leuartDatabits8,    /* Each LEUART frame containes 8 databits */
   .parity   = leuartNoParity,     /* No parity bits in use */
   .stopbits = leuartstopbits,    /* Setting the number of stop bits in a frame to 2 bitperiods */
  };
 /*LEUART_Reset(LEUART0);
 LEUART_Init(LEUART0, &leuart0Init);
 LEUART0->ROUTE = LEUART_ROUTE_TXPEN |
                    LEUART_ROUTE_LOCATION_LOC0;

 LEUART0->CTRL|=LEUART_CTRL_LOOPBK;
 GPIO_PinModeSet(LEUARTport,            /* Port */
   //                LEUARTpin,                    /* Port number */
     //              gpioModePushPull,    /* Pin mode is set to input only, with pull direction given bellow */
       //            1);                   /* Pull direction is set to pull-up */
// LEUART0->IEN|=LEUART_IEN_TXBL;
 //NVIC_ClearPendingIRQ(LEUART0_IRQn);
 //NVIC_EnableIRQ(LEUART0_IRQn);
}

void LEUART0_IRQHandler(void)
{
	CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);  //lfxo clock for em2
	while((LEUART0->SYNCBUSY)!=0);
	int leuartif = LEUART_IntGet(LEUART0);  //clear flags
	LEUART_IntClear(LEUART0, leuartif);
	//LEUART0->CMD|=LEUART_CMD_RXEN;    //enable reception
//	LEUART0->CTRL|=LEUART_CTRL_LOOPBK;  //enable loopback for verification

	LEUART0->TXDATA=*(tactile_data+count);
	while((LEUART0->IF & LEUART_IF_TXC)==0);
	count--;
	if(count==0)
	{
		NVIC_DisableIRQ(LEUART0_IRQn);
		unblockSleepMode(2);
		workacc();
		count=13;
	}

}
