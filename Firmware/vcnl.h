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

void writeVCNL(uint8_t IR,uint8_t address,uint8_t value);
uint8_t readVCNL(uint8_t IR,uint8_t address);
void workVCNL(void);
void GPIO_VCNL(void);

#define SLAVE_VCNL 0x13<<1
uint8_t flag3,data2;
#endif
