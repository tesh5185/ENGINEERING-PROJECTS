#ifndef _ACC_H_
#define _ACC_H_


#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_i2c.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_int.h"
#include "i2c.h"
#include "TOF.h"
#include "vcnl.h"
#define accintpin 4
#define accintport gpioPortA


uint8_t data,flag1,dat,date,dates,status_acc;
void writetest(int address,int value);


//uint8_t *wr=malloc(1*sizeof(char));
//#define SA0 1
#if SA0
#define SLAVE_ACC 0x1D<<1  // SA0 is high, 0x1C if low
#else
#define SLAVE_ACC 0x1C<<1
#endif
typedef enum address_acc{
	CTRL_REG1=0x2A,
	CTRL_REG2=0x2B,
	TRANSIENT_CONFIG=0x1D,
	TRANSIENT_THS=0x1F,
	DEBOUNCE_CNT=0x20,
	CTRL_REG4=0x2D,
	CTRL_REG5=0x2E,
	TRANSIENT_SRC=0x1E
}address;

typedef enum value_acc{
	standby=0x28,
	lowpwrmode=0x18,
	allaxis=0x1F,
	threshold=0x10,
	debounceval=0x01,
	transint=0x20,
	transintconfig=0x20,
	active=0x29
}value;

#define d0 (1000*128)/1024
#define d1 d0/2
#define d2 d1/2
#define d3 d2/2
#define d4 d3/2
#define d5 d4/2
#define d6 d5/2
#define d7 d6/2

uint8_t status1,status2,status3,status4,status5,status6,signx,signy,signz,int_x,int_y,int_z,dec_x,dec_y,dec_z;
uint16_t x,y,z;
void writeacc(int address,int value); // takes the address and value to be written to that address
void GPIOacc_setup();  //setup GPIO pins for the I2C0
void workacc();  // all read write functions carried out here
int readacc(int address);  //reads data from a particular address given as the input and returns the data
void out_x(void);
void out_y(void);
void out_z(void);
#endif
