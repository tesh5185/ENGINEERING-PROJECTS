#include "i2c.h"
void I2C0_setup(void)
{
	CMU_ClockEnable(cmuClock_CORELE, true);
	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(cmuClock_I2C0,true);  //enable clock for I2C0
	CMU_ClockEnable(cmuClock_GPIO, true);

	GPIO_PinModeSet(SDAport,SCLpin, gpioModeWiredAnd, 1);//enable SCLpin
	GPIO_PinModeSet(SDAport,SDApin, gpioModeWiredAnd, 1);//enable SDApin
    I2C0->ROUTE= I2C_ROUTE_SDAPEN |							   //route to the fixed location
                 I2C_ROUTE_SCLPEN |
                 (I2C0_LOC<< _I2C_ROUTE_LOCATION_SHIFT);

    I2C_Init_TypeDef i2cInit = {
    		  .enable = true,                    /* Enable when init done */
    		  .master = true,                    /* Set to master mode */
    		  .refFreq = 0,                       /* Use currently configured reference clock */
    		  .freq = I2C_FREQ_STANDARD_MAX,   /* Set to standard rate assuring being within I2C spec */
    		  .clhr = i2cClockHLRStandard      /* Set to use 4:4 low/high duty cycle */
    		};



    I2C_Init(I2C0, &i2cInit);					//initialize the UART
    int flag = I2C0->IF;
      I2C0->IFC=flag;
   if(I2C0->STATE & I2C_STATE_BUSY)
   {
	   I2C0->CMD=I2C_CMD_ABORT;
   }
   for(int i=0;i<=9;i++)
   {
	   GPIO_PinModeSet(SCLport,SCLpin, gpioModeWiredAnd, 0);//toggle multiple times
	   GPIO_PinModeSet(SCLport,SCLpin, gpioModeWiredAnd, 1);
   }
   if(I2C0->STATE & I2C_STATE_BUSY)
     {
  	   I2C0->CMD=I2C_CMD_ABORT;
     }
}
