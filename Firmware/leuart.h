#ifndef _LEUART_H_
#define _LEUART_H_

#include "em_leuart.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_int.h"
#include "em_gpio.h"
#include "i2c.h"
void leuart0_setup(void);
void leuart0_setup1(void);
#define leuaert_baud 9600
#define leuart_databits  leuartDatabits8
#define leuartstopbits leuartStopbits1
#define LEUARTport gpioPortD
#define LEUARTpin 4
#define LETIMER0_ENERGY_MODE 2
uint8_t count=13;
#endif
