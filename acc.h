#ifndef _ACC_H_
#define _ACC_H_


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
#include "em_leuart.h"
unsigned int sleep_block_counter[5];

#define accSDAport gpioPortD
#define accSDApin  6
#define accSCLport gpioPortD
#define accSCLpin  7
#define LEDpin 2
#define LEDport gpioPortE
#define accintpin 6
#define accintport gpioPortC
#define leuaert_baud 9600
#define leuart_databits  leuartDatabits8
#define leuartstopbits leuartStopbits1
#define LEUARTport gpioPortD
#define LEUARTpin 4
#define LEDSetCMD 65
#define LEDResetCMD 66

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
typedef enum address_t{
	CTRL_REG1=0x2A,
	CTRL_REG2=0x2B,
	DEBOUNCE_CNT=0x18,
	TRANSIENT_THS=0x1F,
	TRANSIENT_COUNT=0x20,
	CTRL_REG4=0x2D,
	CTRL_REG5=0x2E,
	TRANSIENT_SRC=0x1E
}address;
void leuart0_setup(void);
void I2C0_setup(void);
void writeacc(int address,int value);
void GPIOacc_setup();
void workacc();
int readacc(int address);

#endif