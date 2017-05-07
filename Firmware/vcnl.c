#include "vcnl.h"


void GPIO_VCNL(void)
{
	GPIO_PinModeSet(gpioPortA, 8, gpioModePushPull, 0);    //enable GPIO for pin and port for interrupts
	GPIO_PinOutSet(gpioPortA, 8);    //enable GPIO for pin and port for interrupts*/
	GPIO_PinModeSet(gpioPortA, 9, gpioModePushPull, 0);    //enable GPIO for pin and port for interrupts
	GPIO_PinOutSet(gpioPortA, 9);    //enable GPIO for pin and port for interrupts*/
	GPIO_PinModeSet(gpioPortA, 10, gpioModePushPull, 0);    //enable GPIO for pin and port for interrupts
	GPIO_PinOutSet(gpioPortA, 10);    //enable GPIO for pin and port for interrupts*/
	for(int i=10000;i>0;i--);
}
void writeVCNL(uint8_t IR,uint8_t address,uint8_t value)
{
	 INT_Disable();
	 I2C0->CMD  |= I2C_CMD_START;
	 I2C0->TXDATA =SLAVE_MUX|writebit;     //write slave device address with write bit
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag3 = I2C0->IF;
	 I2C0->IFC=flag3;

	 if(IR==1)
		 I2C0->TXDATA =Channel_V1;						//value to be written
	 else
		 I2C0->TXDATA =Channel_V2;

	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag3 = I2C0->IF;
	 I2C0->IFC=flag3;
	 I2C0->CMD  |= I2C_CMD_STOP;

	 I2C0->CMD  |= I2C_CMD_START;
	 I2C0->TXDATA =SLAVE_VCNL|writebit;     //write slave device address with write bit
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag3 = I2C0->IF;
	 I2C0->IFC=flag3;

	 I2C0->TXDATA = address;					// write register address
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag3 = I2C0->IF;
	 I2C0->IFC=flag3;

	 I2C0->TXDATA = value;						//value to be written
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag3 = I2C0->IF;
	 I2C0->IFC=flag3;
	 I2C0->CMD  |= I2C_CMD_STOP;
	 INT_Enable();
}
uint8_t readVCNL(uint8_t IR,uint8_t address)
{
	 INT_Disable();
	 I2C0->CMD  |= I2C_CMD_START;
	 I2C0->TXDATA =SLAVE_MUX|writebit;     //write slave device address with write bit
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag3 = I2C0->IF;
	 I2C0->IFC=flag3;

	 if(IR==1)
	 I2C0->TXDATA =Channel_V1;						//value to be written
	 else
	 I2C0->TXDATA =Channel_V2;

	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag3 = I2C0->IF;
	 I2C0->IFC=flag3;
	 I2C0->CMD  |= I2C_CMD_STOP;

	 I2C0->CMD  |= I2C_CMD_START;						//write slave device address with write bit
	 I2C0->TXDATA =SLAVE_VCNL|writebit;
	 while((I2C0->IF & I2C_IF_ACK) == 0);					//wait for acknowledgement
	 flag3 = I2C0->IF;
	 I2C0->IFC=flag3;

	 I2C0->TXDATA = address;							// write register address
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag3 = I2C0->IF;
	 I2C0->IFC=flag3;


	 I2C0->CMD  |= I2C_CMD_START;
	 I2C0->TXDATA =SLAVE_VCNL|readbit;				// write slave address with read bit
	 while((I2C0->IF & I2C_IF_ACK) == 0);
	 flag3 = I2C0->IF;
	 I2C0->IFC=flag3;

	 while(!(I2C0->STATUS & I2C_STATUS_RXDATAV));
	 data2=I2C0->RXDATA;
	 I2C0->CMD |= I2C_CMD_NACK;
	 I2C0->CMD  |= I2C_CMD_STOP;
	 INT_Enable();
     return data2;


}
void workVCNL(void)
{
	writeVCNL(1,0x80,0x08);
	writeVCNL(1,0x82,0x07);
	writeVCNL(2,0x80,0x08);
	writeVCNL(2,0x82,0x07);
	//writeVCNL(2,0x83,0x05);
	//uint8_t val=readVCNL(1,0x80);
	*(tactile_data+10)=readVCNL(1,0x87);  //high byte for VCNL1
	*(tactile_data+11)=readVCNL(1,0x88); //low byte for VCNL1
	*(tactile_data+12)=readVCNL(2,0x87); //high byte for VCNL2
	*(tactile_data+13)=readVCNL(2,0x88); //low byte for VCNL2
	uint16_t proximity_1 = ((*(tactile_data+10)<<8) | *(tactile_data+11));
	uint16_t proximity_2 = (*(tactile_data+12)<<8 | *(tactile_data+13));
}
