#ifndef _I2C_H_
#define _I2C_H_


#include "em_i2c.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_int.h"
#include "em_gpio.h"

void I2C0_setup(void);  //initialize the I2C0
#define SDAport gpioPortC
#define SDApin 6
#define SCLport gpioPortC
#define SCLpin  7
#define I2C0_LOC 2
#define writebit 0
#define readbit  1

uint8_t *tactile_data;
typedef enum mux_t{
	SLAVE_MUX=0x70<<1,
	Channel_ACC=0x08,
	Channel_TOF=0x04,
	Channel_V2=0x02,
	Channel_V1=0x01
}mux;

#endif
