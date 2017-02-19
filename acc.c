/**************************************************************************//**
 * @file
 * @brief Empty Project
 * @author Energy Micro AS
 * @version 3.20.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See 
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"  
 * for details. Before using this software for any purpose, you must agree to the 
 * terms of that agreement.
 *
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_i2c.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_timer.h"


#define SDAport gpioPortC
#define SDApin  4
#define SCLpin  5
#define LEDpin 2
#define LEDport gpioPortE
#define intpin 1
#define intport gpioPortD
#define powerport gpioPortD
#define powerpin 0
//#define slaveadd 0x39<<1
#define writebit 0
#define readbit  1
int data,flag1,dat,date;
#define SA0 1
#if SA0
#define SLAVE_ADDRESS 0x1D<<1  // SA0 is high, 0x1C if low
#else
#define SLAVE_ADDRESS 0x1C<<1
#endif


void powerup(void)

{
		CMU_ClockEnable(cmuClock_TIMER0,true);
        TIMER_Init_TypeDef timerInit0 =
		  {
		    .enable     = false,
		    .debugRun   = false,
		    .prescale   = timerPrescale1,
		    .clkSel     = timerClkSelHFPerClk,
		    .fallAction = timerInputActionNone,
		    .riseAction = timerInputActionNone,
		    .mode       = timerModeUp,
		    .dmaClrAct  = false,
		    .quadModeX4 = false,
		    .oneShot    = true,
		    .sync       = false,
		  };
		 TIMER_Init(TIMER0, &timerInit0);
		 TIMER0->CNT=0x0000;
		 TIMER_Enable(TIMER0,true);

		 while(TIMER0->CNT <= 28000);

		 TIMER_Enable(TIMER0,false);
}

void i2c1_setup(void)
{
	CMU_ClockEnable(cmuClock_HFPER,true);
	CMU_ClockEnable(cmuClock_CORELE,true);
	CMU_ClockEnable(cmuClock_GPIO,true);
	CMU_ClockEnable(cmuClock_I2C1,true);
	GPIO_PinModeSet(SDAport,SCLpin, gpioModeWiredAnd, 1);
	GPIO_PinModeSet(SDAport,SDApin, gpioModeWiredAnd, 1);
    I2C1->ROUTE= I2C_ROUTE_SDAPEN |
                 I2C_ROUTE_SCLPEN |
                 (0<< _I2C_ROUTE_LOCATION_SHIFT);

    I2C_Init_TypeDef i2cInit = {
    		  .enable = true,                    /* Enable when init done */
    		  .master = true,                    /* Set to master mode */
    		  .refFreq = 0,                       /* Use currently configured reference clock */
    		  .freq = I2C_FREQ_STANDARD_MAX,   /* Set to standard rate assuring being within I2C spec */
    		  .clhr = i2cClockHLRStandard      /* Set to use 4:4 low/high duty cycle */
    		};


    I2C_Init(I2C1, &i2cInit);
    int flag = I2C1->IF;
      I2C1->IFC=flag;
   if(I2C1->STATE & I2C_STATE_BUSY)
   {
	   I2C1->CMD=I2C_CMD_ABORT;
   }
   for(int i=0;i<=9;i++)
   {
	   GPIO_PinModeSet(gpioPortC, 5, gpioModeWiredAnd, 0);

	       GPIO_PinModeSet(gpioPortC, 5, gpioModeWiredAnd, 1);
   }
  // I2C1->IEN|=I2C_IEN_NACK;
   //I2C1->IEN|=I2C_IEN_ACK;
   //I2C1->IEN|=I2C_IEN_RXDATAV;
  // NVIC_ClearPendingIRQ(I2C1_IRQn);
   //NVIC_EnableIRQ(I2C1_IRQn);
}
void write(int address,int value)
{
	 I2C1->CMD  |= I2C_CMD_START;
	 I2C1->TXDATA =SLAVE_ADDRESS|writebit;     //write slave device address with write bit
	 while((I2C1->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C1->IF;
	 I2C1->IFC=flag1;

	 I2C1->TXDATA = address;					// write register address
	 while((I2C1->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C1->IF;
	 I2C1->IFC=flag1;

	 I2C1->TXDATA = value;						//value to be written
	 while((I2C1->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C1->IF;
	 I2C1->IFC=flag1;
	 I2C1->CMD  |= I2C_CMD_STOP;

}
int read(int address)
{
	 I2C1->CMD  |= I2C_CMD_START;						//write slave device address with write bit
	 I2C1->TXDATA =SLAVE_ADDRESS|writebit;
	 while((I2C1->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C1->IF;
	 I2C1->IFC=flag1;

	 I2C1->TXDATA = address;							// write register address
	 while((I2C1->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C1->IF;
	 I2C1->IFC=flag1;

	 I2C1->CMD  |= I2C_CMD_START;
	 I2C1->TXDATA =SLAVE_ADDRESS|readbit;				// write slave address with read bit
	 while(!(I2C1->STATUS & I2C_STATUS_RXDATAV));
	 data=I2C1->RXDATA;
	 I2C1->CMD |= I2C_CMD_NACK;
	 I2C1->CMD  |= I2C_CMD_STOP;
     return data;


}
void work()
{
	write(0x2A,0x18);
	write(0x1D,0x16);
	write(0x1F,0x0F);
	write(0x20,0x05);
	write(0x2D,0x20);
	write(0x2E,0x20);


	//dat=read(0x2A);
	//dat|=0x01;
	//for(int i=0;i<10000;i++);
	write(0x2A,25);
	for(int i=0;i<10000;i++);
	date =read(0x2A);
	GPIO_ExtIntConfig(intport,intpin,1,false,true,true);
	//NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
		// NVIC_EnableIRQ(GPIO_ODD_IRQn);

}
void GPIO2_setup()
{
	GPIO_PinModeSet(powerport, powerpin, gpioModePushPull, 1);    //enable GPIO for pin and port providing power
	GPIO_PinOutSet(powerport, powerpin);
	GPIO_PinModeSet(intport, intpin, gpioModeInput, 1);    //enable GPIO for pin and port for interrupts
	GPIO_PinModeSet(LEDport, LEDpin, gpioModePushPull, 0);
	//GPIO_ExtIntConfig(intport,intpin,1,true,false,true);


	 NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
	 NVIC_EnableIRQ(GPIO_ODD_IRQn);

    // GPIO->IEN=0x02;
}
void GPIO_ODD_IRQHandler(void)
{
  /* clear flag for PC9 interrupt */
  int flags8=GPIO->IF;
  GPIO->IFC=flags8;
 // GPIO_ExtIntConfig( gpioPortD, 1, 1,true,false, false );

  /*I2C1->TXDATA =slave_address<<1|writeslave;
      I2C1->CMD  |= I2C_CMD_START;
      while((I2C1->IF & I2C_IF_ACK) == 0);
      int flag3 = I2C1->IF;
      I2C1->IFC=flag3;
      write(data0low_add);
  read(slave_address<<1|readslave);
 int r= 256*cd+ab;
 if (r<0x000f)
	 GPIO_PinOutSet(gpioPortE,2);
 int s=256*gh+ef;
 if (s>0x0800)
	 GPIO_PinOutClear(gpioPortE,2);*/
}


/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  i2c1_setup();
  GPIO2_setup();
  powerup();
  work();

  /* Infinite loop */
  while (1) {
	  //GPIO_ExtIntConfig(intport,1,1,true,false,true);

  }
}