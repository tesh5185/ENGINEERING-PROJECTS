#include "acc.h"

/*void leuart0_setup(void)
{
	 CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);  //lfxo clock for em2

	 CMU_ClockEnable(cmuClock_LEUART0, true);

	LEUART_Init_TypeDef leuart0Init =
 {
   .enable   = leuartEnableTx,
   .refFreq  = 0,
   .baudrate = leuaert_baud,
   .databits = leuartDatabits8,
   .parity   = leuartNoParity,
   .stopbits = leuartstopbits,
  };
 LEUART_Reset(LEUART0);
 LEUART_Init(LEUART0, &leuart0Init);
 LEUART0->ROUTE = LEUART_ROUTE_TXPEN |
                  LEUART_ROUTE_LOCATION_LOC0;


 GPIO_PinModeSet(LEUARTport,
                   LEUARTpin,
                   gpioModePushPull,
                   1);
 LEUART0->IEN|=LEUART_IEN_TXBL;
 NVIC_ClearPendingIRQ(LEUART0_IRQn);
}
void LEUART0_IRQHandler(void)
{
	while((LEUART0->SYNCBUSY)!=0);
	int leuartif = LEUART_IntGet(LEUART0);  //clear flags
	LEUART_IntClear(LEUART0, leuartif);
    LEUART0->CTRL|=LEUART_CTRL_LOOPBK;  //enable loopback for verification
    LEUART0->CMD|=LEUART_CMD_RXEN;    //enable reception
    LEUART0->TXDATA=66;
    LEUART0->TXDATA=67;
    NVIC_DisableIRQ(LEUART0_IRQn);
}
*/

void I2C0_setup(void)
{
	CMU_ClockEnable(cmuClock_HFPER,true);
	CMU_ClockEnable(cmuClock_CORELE,true);
	CMU_ClockEnable(cmuClock_GPIO,true);
	CMU_ClockEnable(cmuClock_I2C0,true);
	GPIO_PinModeSet(SDAport,SCLpin, gpioModeWiredAnd, 1);
	GPIO_PinModeSet(SDAport,SDApin, gpioModeWiredAnd, 1);
    I2C0->ROUTE= I2C_ROUTE_SDAPEN |
                 I2C_ROUTE_SCLPEN |
                 (1<< _I2C_ROUTE_LOCATION_SHIFT);

    I2C_Init_TypeDef i2cInit = {
    		  .enable = true,                    /* Enable when init done */
    		  .master = true,                    /* Set to master mode */
    		  .refFreq = 0,                       /* Use currently configured reference clock */
    		  .freq = I2C_FREQ_STANDARD_MAX,   /* Set to standard rate assuring being within I2C spec */
    		  .clhr = i2cClockHLRStandard      /* Set to use 4:4 low/high duty cycle */
    		};


    I2C_Init(I2C0, &i2cInit);
    int flag = I2C0->IF;
      I2C0->IFC=flag;
   if(I2C0->STATE & I2C_STATE_BUSY)
   {
	   I2C0->CMD=I2C_CMD_ABORT;
   }
   for(int i=0;i<=9;i++)
   {
	   GPIO_PinModeSet(SCLport,SCLpin, gpioModeWiredAnd, 0);

	       GPIO_PinModeSet(SCLport,SCLpin, gpioModeWiredAnd, 1);
   }

}
void writeacc(int address,int value)
{
	 I2C0->CMD  |= I2C_CMD_START;
	 I2C0->TXDATA =SLAVE_ADDRESS|writebit;     //write slave device address with write bit
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;

	 I2C0->TXDATA = address;					// write register address
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;

	 I2C0->TXDATA = value;						//value to be written
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;
	 I2C0->CMD  |= I2C_CMD_STOP;

}
int readacc(int address)
{
	 I2C0->CMD  |= I2C_CMD_START;						//write slave device address with write bit
	 I2C0->TXDATA =SLAVE_ADDRESS|writebit;
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;

	 I2C0->TXDATA = address;							// write register address
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;


	 I2C0->CMD  |= I2C_CMD_START;
	 I2C0->TXDATA =SLAVE_ADDRESS|readbit;// write slave address with read bit
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;

	 while(!(I2C0->STATUS & I2C_STATUS_RXDATAV));
	 data=I2C0->RXDATA;
	 I2C0->CMD |= I2C_CMD_NACK;
	 I2C0->CMD  |= I2C_CMD_STOP;
     return data;


}
void workacc()
{

	    writeacc(CTRL_REG1,0x18);
		writeacc(CTRL_REG2,0x18);
		writeacc(DEBOUNCE_CNT,0x12);
		writeacc(TRANSIENT_THS,0x0F);
		writeacc(TRANSIENT_COUNT,0x05);
		writeacc(CTRL_REG4,0x20);
		writeacc(CTRL_REG5,0x20);
     	writeacc(0x2A,25);

	GPIO_ExtIntConfig(intport,intpin,1,false,true,true);


}
void GPIOacc_setup()
{

	GPIO_PinModeSet(intport, intpin, gpioModeInput, 1);    //enable GPIO for pin and port for interrupts
	GPIO_PinModeSet(LEDport, LEDpin, gpioModePushPull, 0);

	 NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
	 NVIC_EnableIRQ(GPIO_EVEN_IRQn);

}
void GPIO_EVEN_IRQHandler(void)
{
  /* clear flag for PC9 interrupt */
  int flags8=GPIO->IF;
  GPIO->IFC=flags8;
  NVIC_EnableIRQ(LEUART0_IRQn);
  dates= readacc(TRANSIENT_SRC);
  GPIO_PinOutToggle(LEDport,LEDpin);
 }