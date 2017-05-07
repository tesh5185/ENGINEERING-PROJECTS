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
#include "sleep.h"

void writeacc(int address,int value)
{
	 INT_Disable();
	 I2C0->CMD  |= I2C_CMD_START;

	 I2C0->TXDATA =SLAVE_MUX|writebit;     //write slave device address with write bit
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;

	 I2C0->TXDATA = Channel_ACC;						//value to be written
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;
	 I2C0->CMD  |= I2C_CMD_STOP;

	 I2C0->CMD  |= I2C_CMD_START;
	 I2C0->TXDATA =SLAVE_ACC|writebit;     //write slave device address with write bit
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
	 INT_Enable();
}
int readacc(int address)
{
	INT_Disable();
	I2C0->CMD  |= I2C_CMD_START;						//write slave device address with write bit

	 I2C0->TXDATA =SLAVE_MUX|writebit;     //write slave device address with write bit
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;

	 I2C0->TXDATA = Channel_ACC;						//value to be written
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;
	 I2C0->CMD  |= I2C_CMD_STOP;

	 I2C0->CMD  |= I2C_CMD_START;
	 I2C0->TXDATA =SLAVE_ACC|writebit;
	 while((I2C0->IF & I2C_IF_ACK) == 0);					//wait for acknowledgement
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;

	 I2C0->TXDATA = address;							// write register address
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;


	 I2C0->CMD  |= I2C_CMD_START;
	 I2C0->TXDATA =SLAVE_ACC|readbit;				// write slave address with read bit
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag1 = I2C0->IF;
	 I2C0->IFC=flag1;

	 while(!(I2C0->STATUS & I2C_STATUS_RXDATAV));
	 data=I2C0->RXDATA;
	 I2C0->CMD |= I2C_CMD_NACK;
	 I2C0->CMD  |= I2C_CMD_STOP;
	 INT_Enable();
     return data;


}
void workacc()
{
	writeacc(CTRL_REG1,standby);   //put device in standby mode while ODR=12.5hz
	writeacc(CTRL_REG2,lowpwrmode); // set device in low power mode
	writeacc(TRANSIENT_CONFIG,allaxis); //set the device to take interrupts in all direction
	writeacc(TRANSIENT_THS,threshold); //set threshold to 1g
	writeacc(DEBOUNCE_CNT,debounceval);//set debounce to 80ms
	writeacc(CTRL_REG4,transint);		// enable transient interrupt
	writeacc(CTRL_REG5,transintconfig); //enable transient configuration
    writeacc(CTRL_REG1,active); 		//set device in active mode

	GPIO_ExtIntConfig(accintport,accintpin,1,false,true,true);


}
void GPIOacc_setup()
{

	GPIO_PinModeSet(accintport, accintpin, gpioModeInput, 1);    //enable GPIO for pin and port for interrupts
	GPIO_PinModeSet(gpioPortA, 3, gpioModePushPull, 0);    //enable GPIO for pin and port for interrupts
	GPIO_PinOutSet(gpioPortA,3);    //enable GPIO for pin and port for interrupts
	/*GPIO_PinModeSet(gpioPortA, 9, gpioModePushPull, 0);    //enable GPIO for pin and port for interrupts
	GPIO_PinOutSet(gpioPortA, 9);    //enable GPIO for pin and port for interrupts*/
	for(int i=10000;i>0;i--);
	NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);

}

void GPIO_EVEN_IRQHandler(void)
{
//	NVIC_DisableIRQ(GPIO_EVEN_IRQn);
	INT_Disable();

	int flags=GPIO->IF;
	GPIO->IFC=flags;

	dates= readacc(TRANSIENT_SRC);
	writeacc(CTRL_REG1,0x00);   //put device in standby mode while ODR=100hz
	writeacc(0x0E,0x02);  // 8g mode
	writeacc(CTRL_REG1,0x01);//active in ODR=800Hz
	while((status_acc & 0x08)!=0x08)
		{
	 status_acc= readacc(0x00);
		}
	status1= readacc(0x01);
	status2= readacc(0x02);
	status3= readacc(0x03);
	status4= readacc(0x04);
	status5= readacc(0x05);
	status6= readacc(0x06);
	 x= ((status1<<8)|status2);
	 y= ((status3<<8)|status4);
	 z= ((status5<<8)|status6);
	out_x();
	out_y();
	out_z();
	writeacc(0x0E,0x00);
	writeacc(CTRL_REG1,0x28);
	workTOF();
	GPIO_VCNL();
	workVCNL();

	INT_Enable();
	blockSleepMode(2);

	NVIC_EnableIRQ(LEUART0_IRQn);

}

void out_x(void)
{
	if (status1>0x7F)
		{
		*tactile_data=1;  //sign x
			x=~x|1;

		}
	else
		*tactile_data=0;

	*(tactile_data+1)=((status1 & 0x70)>>4); //integerof x:
		x=x>>4;

		*(tactile_data+2)=0;
		if ((x & 0x80 )==0x80)
			*(tactile_data+2)+=d0;

		if ((x & 0x40 )==0x40)
				*(tactile_data+2)+=d1;

		if ((x & 0x20 )==0x20)
				*(tactile_data+2)+=d2;

		if ((x & 0x10 )==0x10)
				*(tactile_data+2)+=d3;

		if ((x & 0x08 )==0x08)
				*(tactile_data+2)+=d4;

		if ((x & 0x04 )==0x04)
				*(tactile_data+2)+=d5;

		if ((x & 0x02 )==0x02)
				*(tactile_data+2)+=d6;

		if(*(tactile_data+2)>255)
			*(tactile_data+2)/=10;  //decimal of x:
}
void out_y(void)
{
	if (status3>0x7F)
		{
			*(tactile_data+3)=1;
			y=~y|1;

		}
	else
			*(tactile_data+3)=0;

		*(tactile_data+4)=((status3 & 0x70)>>4);
		y=y>>4;

		*(tactile_data+5)=0;
		if ((y & 0x80 )==0x80)
			*(tactile_data+5)+=d0;

		if ((y & 0x40 )==0x40)
				*(tactile_data+5)+=d1;

		if ((y & 0x20 )==0x20)
				*(tactile_data+5)+=d2;

		if ((y & 0x10 )==0x10)
				*(tactile_data+5)+=d3;

		if ((y & 0x08 )==0x08)
				*(tactile_data+5)+=d4;

		if ((y & 0x04 )==0x04)
				*(tactile_data+5)+=d5;

		if ((y & 0x02 )==0x02)
				*(tactile_data+5)+=d6;

		if(*(tactile_data+5)>255)
			*(tactile_data+5)/=10;
}
void out_z(void)
{
	if (status5>0x7F)
		{
			*(tactile_data+6)=1;
			z=~z|1;
		}
	else
		*(tactile_data+6)=0;

		 *(tactile_data+7)=((status5 & 0x70)>>4);
		z=z>>4;

		*(tactile_data+8)=0;
		if ((z & 0x80 )==0x80)
			*(tactile_data+8)+=d0;

		if ((z & 0x40 )==0x40)
				*(tactile_data+8)+=d1;

		if ((z & 0x20 )==0x20)
				*(tactile_data+8)+=d2;

		if ((z & 0x10 )==0x10)
				*(tactile_data+8)+=d3;

		if ((z & 0x08 )==0x08)
				*(tactile_data+8)+=d4;

		if ((z & 0x04 )==0x04)
				*(tactile_data+8)+=d5;

		if ((z & 0x02 )==0x02)
				*(tactile_data+8)+=d6;

		if(*(tactile_data+8)>255)
			*(tactile_data+8)/=10;
}
