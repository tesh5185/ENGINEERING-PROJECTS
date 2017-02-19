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
#include "acc.h"


void I2C0_setup(void)
{
	CMU_ClockEnable(cmuClock_I2C0,true);  //enable clock for I2C0
	GPIO_PinModeSet(accSDAport,accSCLpin, gpioModeWiredAnd, 1);//enable SCLpin
	GPIO_PinModeSet(accSDAport,accSDApin, gpioModeWiredAnd, 1);//enable SDApin
    I2C0->ROUTE= I2C_ROUTE_SDAPEN |							   //route to the fixed location
                 I2C_ROUTE_SCLPEN |
                 (1<< _I2C_ROUTE_LOCATION_SHIFT);

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
	   GPIO_PinModeSet(accSCLport,accSCLpin, gpioModeWiredAnd, 0);//toggle multiple times

	       GPIO_PinModeSet(accSCLport,accSCLpin, gpioModeWiredAnd, 1);
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
	 while((I2C0->IF & I2C_IF_ACK) == 0);					//wait for acknowledgement
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;

	 I2C0->TXDATA = address;							// write register address
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;


	 I2C0->CMD  |= I2C_CMD_START;
	 I2C0->TXDATA =SLAVE_ADDRESS|readbit;				// write slave address with read bit
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

	writeacc(CTRL_REG1,standby);   //put device in standby mode while ODR=100hz
	writeacc(CTRL_REG2,lowpwrmode); // set device in low power mode
	writeacc(TRANSIENT_CONFIG,xaxis); //set the device to take interrupts in x direction
	writeacc(TRANSIENT_THS,threshold); //set threshold to 1g
	writeacc(DEBOUNCE_CNT,debounceval);//set debounce to 50ms
	writeacc(CTRL_REG4,transint);		// enable transient interrupt
	writeacc(CTRL_REG5,transintconfig); //enable transient configuration
    writeacc(CTRL_REG1,active); 		//set device in active mode

	GPIO_ExtIntConfig(accintport,accintpin,1,false,true,true);


}
void GPIOacc_setup()
{

	GPIO_PinModeSet(accintport, accintpin, gpioModeInput, 1);    //enable GPIO for pin and port for interrupts
	 NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
	 NVIC_EnableIRQ(GPIO_EVEN_IRQn);

}
