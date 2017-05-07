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
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "i2c.h"
#include "acc.h"
#include "TOF.h"
#include "sleep.h"
#include "em_leuart.h"
/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/


int main(void)
{
  /* Chip errata */
  CHIP_Init();
  blockSleepMode(3);
  I2C0_setup();
  leuart0_setup();
  tactile_data=malloc(14*sizeof(uint8_t));
  GPIOacc_setup();
 //GPIO_TOF();
  //workTOF();
 /*

 	 while((I2C0->IF & I2C_IF_MSTOP) == 0);
 	 	 I2C0->IFC|=I2C_IFC_MSTOP;
 	 	*/

  workacc();

  //int x=readacc(0x2A);
  /*readTOF(0x14);
  readTOF(0x11);
  readTOF(0x1A);
  readTOF(0x18);
*/
/* GPIO_VCNL();
 workVCNL();*/
  /* Infinite loop */
  while (1) {
	  //EMU_EnterEM2(true);
	  sleep();
  }
}
