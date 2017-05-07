#include "TOF.h"
void GPIO_TOF()
{

	GPIO_PinModeSet(gpioPortA, 0, gpioModeInput, 1);
	NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);

}
/*void GPIO_EVEN_IRQHandler(void)
{
	int flags=GPIO->IF;
	GPIO->IFC=flags;
	int kls=readTOF(0x4F);
	writeTOF(0x15,0x1);
	//writeTOF(0x18,0x3);
}*/
void writeTOF(int address,int value)
{
	INT_Disable();
	I2C0->CMD  |= I2C_CMD_START;
	I2C0->TXDATA =SLAVE_MUX|writebit;     //write slave device address with write bit
	while((I2C0->IF & I2C_IF_ACK) == 0);
	flag2 = I2C0->IF;
	I2C0->IFC=flag2;

	I2C0->TXDATA =Channel_TOF;						//value to be written
	while((I2C0->IF & I2C_IF_ACK) == 0);
	flag2 = I2C0->IF;
	I2C0->IFC=flag2;
	I2C0->CMD  |= I2C_CMD_STOP;

	I2C0->CMD  |= I2C_CMD_START;
	I2C0->TXDATA =SLAVE_TOF|writebit;     //write slave device address with write bit
	while((I2C0->IF & I2C_IF_ACK) == 0);
	flag2 = I2C0->IF;
	I2C0->IFC=flag2;


	 I2C0->TXDATA = 0x0;					// write register address
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag2 = I2C0->IF;
	 I2C0->IFC=flag2;

	 I2C0->TXDATA = address;					// write register address
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag2 = I2C0->IF;
	 I2C0->IFC=flag2;

	 I2C0->TXDATA = value;						//value to be written
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag2 = I2C0->IF;
	 I2C0->IFC=flag2;
	 I2C0->CMD  |= I2C_CMD_STOP;
	 INT_Enable();
}
uint8_t readTOF(int address)
{
	 INT_Disable();
	 I2C0->CMD  |= I2C_CMD_START;
	 I2C0->TXDATA =SLAVE_MUX|writebit;     //write slave device address with write bit
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag2 = I2C0->IF;
	 I2C0->IFC=flag2;

	 I2C0->TXDATA = Channel_TOF;						//value to be written
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag2 = I2C0->IF;
	 I2C0->IFC=flag2;
	 I2C0->CMD  |= I2C_CMD_STOP;

	 I2C0->CMD  |= I2C_CMD_START;						//write slave device address with write bit
	 I2C0->TXDATA =SLAVE_TOF|writebit;
	 while((I2C0->IF & I2C_IF_ACK) == 0);					//wait for acknowledgement
	 flag2 = I2C0->IF;
	 I2C0->IFC=flag2;

	 I2C0->TXDATA = 0x0;								// write register address
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag2 = I2C0->IF;
	 I2C0->IFC=flag2;

	 I2C0->TXDATA = address;							// write register address
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag2 = I2C0->IF;
	 I2C0->IFC=flag2;


	 I2C0->CMD  |= I2C_CMD_START;
	 I2C0->TXDATA =SLAVE_TOF|readbit;				// write slave address with read bit
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag2 = I2C0->IF;
	 I2C0->IFC=flag2;

	 while(!(I2C0->STATUS & I2C_STATUS_RXDATAV));
	 data1=I2C0->RXDATA;
	 I2C0->CMD |= I2C_CMD_NACK;
	 I2C0->CMD  |= I2C_CMD_STOP;
	 INT_Enable();
     return data1;


}
void workTOF(void)
{
	writeTOF(MEASURE_PERIOD,measure_time); //set intermeasurement period
	//writeTOF(INT_MODE,gpio1); //setup GPIO1
	//writeTOF(INT_CONFIG,range); //range config interrupt
	writeTOF(0x31,0x1A);
	//for(int i=0;i<9000;i++);
	//writeTOF(LOW_THRES,low_value); // set low threshold
	//
	writeTOF(0x14,0x04); //range config interrupt
	while ((devrdy & 0x01) !=0x01)
		{
			devrdy = readTOF(0x4D);
		}
	writeTOF(SYSRANGE_START,start_stop);
	/*while (rangeint !=0x04)
		{
			rangeint =readTOF(0x4F);
		}*/

	//uint8_t range1=readTOF(0x4D);
	//uint8_t range2=readTOF(0x18);

	*(tactile_data+9)=readTOF(0x62);
	writeTOF(0x15,0x07); //start
		//GPIO_ExtIntConfig(gpioPortA,0,1,true,true,true);
}
