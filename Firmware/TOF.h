#ifndef _TOF_H_
#define _TOF_H_


#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_i2c.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_int.h"
#include "i2c.h"




#define SLAVE_TOF 0x29<<1
uint8_t flag2,data1,rangeint,devrdy;
void GPIO_TOF();

uint8_t readTOF(int address);
void writeTOF(int address,int value);
void workTOF(void);




typedef enum address_TOF{
	MEASURE_PERIOD=0x1B,
	INT_MODE=0x11,
	INT_CONFIG=0x14,
	LOW_THRES=0x1A,
	SYSRANGE_START=0x18
}address_tof;

typedef enum value_TOF{
	measure_time=0x10,
	gpio1=0x30,
	range=0x10,
	low_value=0x01,
	start_stop=0x01

}value_tof;


#endif
