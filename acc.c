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
#include "em_int.h"

unsigned int sleep_block_counter[5];
#define SDAport gpioPortD
#define SDApin  6
#define SCLport gpioPortD
#define SCLpin  7
#define LEDpin 2
#define LEDport gpioPortE
#define intpin 3
#define intport gpioPortD
#define powerport gpioPortD
#define powerpin 0
//#define slaveadd 0x39<<1
#define writebit 0
#define readbit  1
int data,flag1,dat,date,dates;
#define SA0 1
#if SA0
#define SLAVE_ADDRESS 0x1D<<1  // SA0 is high, 0x1C if low
#else
#define SLAVE_ADDRESS 0x1C<<1
#endif

void blockSleepMode(unsigned int sleepstate) //block sleep mode
{
	INT_Disable();
	sleep_block_counter[sleepstate]++;
	INT_Enable();
}
//disclaimer: I admit Ive taken this routine from simplicity studio
void unblockSleepMode(unsigned int sleepstate) // unblock sleep mode
{	INT_Disable();
	if(sleep_block_counter[sleepstate]>0)
	{
	sleep_block_counter[sleepstate]--;
	}
	else
		sleep_block_counter[sleepstate]=0;
	INT_Enable();
}
void sleep(void) //sleep routine
{
	if(sleep_block_counter[0]>0)
	{ return;
	}
	else if(sleep_block_counter[1]>0)
	{ EMU_EnterEM1();
	}
	else if(sleep_block_counter[2]>0)
	{ EMU_EnterEM2(true);
	}
	else if(sleep_block_counter[3]>0)
	{ EMU_EnterEM3(true);
	}
	else
	{EMU_EnterEM4();
	}

}
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
  // I2C0->IEN|=I2C_IEN_NACK;
   //I2C0->IEN|=I2C_IEN_ACK;
   //I2C0->IEN|=I2C_IEN_RXDATAV;
  // NVIC_ClearPendingIRQ(I2C0_IRQn);
   //NVIC_EnableIRQ(I2C0_IRQn);
}
void write(int address,int value)
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
int read(int address)
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
void work()
{
	write(0x2A,0x18);
	write(0x2B,0x18);
	write(0x1D,0x12);
	write(0x1F,0x0F);
	write(0x20,0x05);
	write(0x2D,0x20);
	write(0x2E,0x20);


//	dat=read(0x1D);
	//dat|=0x01;
	//for(int i=0;i<10000;i++);
	write(0x2A,25);
	//for(int i=0;i<10000;i++);
	//date =read(0x1F);

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
	//GPIO_ExtIntConfig(intport,intpin,1,false,true,false);


	 NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
	 NVIC_EnableIRQ(GPIO_ODD_IRQn);

    // GPIO->IEN=0x02;
}
void GPIO_ODD_IRQHandler(void)
{
  /* clear flag for PC9 interrupt */
  int flags8=GPIO->IF;
  GPIO->IFC=flags8;
 // date=read(0x0C);
  //if(date==0x20)
  //{
 // NVIC_DisableIRQ(GPIO_ODD_IRQn);
  dates= read(0x1E);
	 GPIO_PinOutToggle(LEDport,LEDpin);
  //}
 }


/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();
  //blockSleepMode(3);
  //EMU_EnterEM3(true);
  I2C0_setup();
  GPIO2_setup();
  powerup();

  work();
  EMU_EnterEM3(true);
  /* Infinite loop */
  while (1) {
	 // GPIO_ExtIntConfig(intport,1,1,false,true,true);
	//  NVIC_EnableIRQ(GPIO_ODD_IRQn);

	 EMU_EnterEM3(true);
	  //sleep();
  }
}