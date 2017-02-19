#ifndef _MYPROJECT_H
#define _MYPROJECT_H
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_int.h"
#include "em_cmu.h"
#include "em_acmp.h"
#include "em_emu.h"
#include "em_letimer.h"
#include "em_timer.h"
#include "em_gpio.h"
#include "em_adc.h"
#include "dmactrl.h"
#include  "em_dma.h"
#include "em_i2c.h"
#include "em_leuart.h"
#include "em_rtc.h"
#include "em_lesense.h"
#include "cirbuf.h"

#include "acc.h"
#include "lesense_letouch_config.h"
#include "lesense_letouch.h"

#define EM0 0
#define EM1 1
#define EM2 2
#define EM3 3
#define EM4 4
unsigned int sleep_block_counter[5];
#define LETIMER0_ENERGY_MODE EM2
#define LEDpin 2
#define LEDport gpioPortE
#define LEDpin2 3
#define LFXOcount 32768
#define ULFRCOcount 1000
#define totaltime 5
#define blinktime 0.004
#define dark_refrence 2
#define light_refrence 61
#define pos_ref acmpChannel6
#define neg_ref acmpChannelVDD
#define calibre 1  		//self calibration variable
#define DMA_CHANNEL_ADC       0
#define lowertemp 15
#define uppertemp 35
#define DMAuse
#define ADCprescale 1400000
#define LIGHTSENSE_EXCITE_PORT gpioPortD
#define LIGHTSENSE_EXCITE_PIN 6
#define LIGHTSENSE_SENSOR_PORT gpioPortC
#define LIGHTSENSE_SENSOR_PIN 6
#define adcinput adcSingleInputTemp
/* ADC Transfer Data */
#define ADCSAMPLES     500
#define dmaarbitrate dmaArbitrate1
#define Temp_Sense_Rate 10000
#define ADC_resolution adcRes12Bit
#define ADC_reference adcRef1V25
#define ADC_acq_time adcAcqTime1
#define ADC_rep true
#define ADC_warmup adcWarmupNormal

#define i2cuse
volatile bool transferActive;
volatile uint16_t ramBufferAdcData[ADCSAMPLES];
#define ADCSAMPLESPERSEC              100000
#define temp_calibration_address 0x0FE081B2
#define temp_input  CAL_TEMP_0
#define SDAport gpioPortC
#define SDApin  4
#define SCLpin  5
#define intpin 1
#define intport gpioPortD
#define powerport gpioPortD
#define powerpin 0
typedef enum TSL_add_t{
	slave_address =0x39,
	writeslave =0,
	readslave = 1,
	controladd=0x80,
	wordwrite =0x20,
	control =0x03,
	timing =0x01,
	ThreshLowLow =0x0f,
	ThreshLowHigh=0x01,
	ThreshHighLow=0x00,
	ThreshHighHigh=0x05,
	Threshlow = 0x010f,
	Threshlower =0x000f,
	ThreshHigh = 0x0500,
	ThreshHigher=0x0800,
	interrupt = 0x14,
	data0low_add= 0x8C,
	data0high_add =0x8D,
	data1low_add =0x8E,
	data1high_add =0x8F

}TSL_add;

int ab,cd,ef,gh;
void TIMER0_setup(void);
void TIMER1_setup(void);
void setupACMP(void);
void blockSleepMode(unsigned int sleepstate);
void unblockSleepMode(unsigned int sleepstate);
void sleep(void);
long LETIMERCAL_setup();
long LETIMERCAL1_setup();
void LETIMER0_setup(void);
void CMU_setup(void);
void GPIO_setup(void);
void LED_state(bool state);
void finaltemp();
float convertToCelcius(int32_t adcSample); // consverts the temperature to celciu
void i2c1_setup(void);  // gives clock to the i2c and initial setup on board
void work(void);// carries out all the read and write functions
void write(int z); // function to write to a particular address, takes data or address
void read(int y); // reads data from a particular register
void GPIO2_setup(void); //sets up the GPIO pins for the I2C1
void ClearTSLInterrupt(void); // clear interrupts
void leuart0_setup(void); //initialize the LEUART
void powerup(void);  // provide a certain amount of delay for powerpin to stabilise
DMA_CB_TypeDef cb; // callback
void transferComplete(unsigned int channel, bool primary, void *user);//callback function
int intflags;
int countADC=0;
float z;
int flags,ts=0,rx=0;
int32_t average;
int load_period;
char c=66;
char res[20];
int temp1,temp10,temp11,temp12,temp13;
#define leuaert_baud 9600
#define leuart_databits  leuartDatabits8
#define leuartstopbits leuartStopbits1
#define LEUARTport gpioPortD
#define LEUARTpin 4
#define LEDSetCMD 65
#define LEDResetCMD 66
#define cirbuf
struct CirBuf cb1;
uint8_t *rd;
uint8_t read1[1];

#endif