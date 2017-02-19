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
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ******************************************************************************/
/*disclaimer: some functions are credited to silocon labs : blockSleepMode, unBlockSleepMode, sleep, converToCelcius*/
//disclaimer: I admit Ive taken this routine from simplicity studio

#include "myproject.h"
#include "cirbuf.h"
#include <stdlib.h>
#include <acc.h>
struct CirBuf cb1;
uint8_t *rd;
uint8_t read1[1];
void blockSleepMode(unsigned int sleepstate) //block sleep mode
{
	INT_Disable();
	sleep_block_counter[sleepstate]++;
	INT_Enable();
}
//disclaimer: I admit Ive taken this routine from simplicity studio
void unblockSleepMode(unsigned int sleepstate) // unblock sleep mode
{	INT_Disable();
	if(sleep_block_counter[sleepstate]>0)
	{
	sleep_block_counter[sleepstate]--;
	}
	else
		sleep_block_counter[sleepstate]=0;
	INT_Enable();
}
//disclaimer: I admit Ive taken this routine from simplicity studio
void sleep(void) //sleep routine
{
	if(sleep_block_counter[0]>0)
	{ return;
	}
	else if(sleep_block_counter[1]>0)
	{ EMU_EnterEM1();
	}
	else if(sleep_block_counter[2]>0)
	{ EMU_EnterEM2(true);
	}
	else if(sleep_block_counter[3]>0)
	{ EMU_EnterEM3(true);
	}
	else
	{EMU_EnterEM4();
	}

}
void GPIO_setup(void)
{
	GPIO_PinModeSet(LIGHTSENSE_EXCITE_PORT, LIGHTSENSE_EXCITE_PIN, gpioModePushPull, 0);
    GPIO_PinModeSet(LIGHTSENSE_SENSOR_PORT, LIGHTSENSE_SENSOR_PIN, gpioModeDisabled, 0);
	GPIO_PinModeSet(LEDport,LEDpin, gpioModePushPullDrive, 0);
	GPIO_PinModeSet(LEDport,LEDpin2,gpioModePushPullDrive,0);
	GPIO_DriveModeSet(LEDport,gpioDriveModeLowest);
}

void CMU_setup(void)
{

	   CMU_ClockEnable(cmuClock_HFPER,true);// high freq clock
		CMU_ClockEnable(cmuClock_LETIMER0, true);
	    CMU_ClockEnable(cmuClock_GPIO, true); // give clock to peripherals

	    CMU_ClockEnable(cmuClock_TIMER0,true);
	    CMU_ClockEnable(cmuClock_TIMER1,true);
	    CMU_ClockEnable(cmuClock_CORELE, true);
	    CMU_ClockEnable(cmuClock_DMA, true);
        CMU_ClockEnable(cmuClock_ADC0, true);




	if(LETIMER0_ENERGY_MODE==EM3)
    {
		if (calibre == 1)
        {
            TIMER0_setup();
	        TIMER1_setup();

	        CMU_OscillatorEnable(cmuOsc_LFXO,true,true);
	        CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);
            CMU_ClockEnable(cmuClock_CORELE, true);

	        long y=LETIMERCAL1_setup();//lfxo count

	        CMU_OscillatorEnable(cmuOsc_LFXO,false,false);
	        CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);
         	long x=LETIMERCAL_setup();
            z=y/(float) x;
	        z=z*1000; // calibrated clock
	        CMU_OscillatorEnable(cmuOsc_LFXO,false,false);
			CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);

            }
		    else
		    {
	        CMU_OscillatorEnable(cmuOsc_LFXO,false,false);

	        CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);
	        CMU_ClockEnable(cmuClock_TIMER0,false);
	       	    CMU_ClockEnable(cmuClock_TIMER1,false);

            }
         }
         else
         {
       	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);
         }
}


void setupACMP(void)
{
	CMU_ClockEnable(cmuClock_ACMP0, true);
  /* ACMP configuration constant table. */
  static const ACMP_Init_TypeDef acmp_init =
  {
    .fullBias = false,                 /* fullBias */
    .halfBias = true,                  /* halfBias */
    .biasProg =  0x0,                  /* biasProg */
    .interruptOnFallingEdge =  false,  /* interrupt on rising edge */
    .interruptOnRisingEdge =  false,   /* interrupt on falling edge */
    .warmTime = acmpWarmTime256,       /* 512 cycle warmup to be safe */
    .hysteresisLevel = acmpHysteresisLevel0, /* hysteresis level 5 */
    .inactiveValue = false,            /* inactive value */
    .lowPowerReferenceEnabled = false, /* low power reference */
    .vddLevel = 2,                  /* VDD level */
    .enable = false                   /* Don't request enabling. */
  };
  ACMP_Init(ACMP0, &acmp_init);

  ACMP_ChannelSet(ACMP0, neg_ref, pos_ref);

}

void LETIMER0_setup(void)
{
	int Comp0_init;
	int Comp1_init;
	float comp1_float_init;
	int Prescalar;
	const LETIMER_Init_TypeDef letimerInit =
	  {		  .enable         = false,// disable letimer
			  .debugRun       = false,
			  .rtcComp0Enable = false,
			  .rtcComp1Enable = false,
			  .comp0Top       = true,
			  .bufTop         = false,
			  .out0Pol        = 0,
			  .out1Pol        = 1,
			  .ufoa0          = letimerUFOANone,
			  .ufoa1          = letimerUFOANone,
			  .repMode        = letimerRepeatFree

			  };
	LETIMER_Init(LETIMER0, &letimerInit);
    if(LETIMER0_ENERGY_MODE ==EM3)
	    if ( calibre == 1) // if self calibration use updated value of ulfrco
	    Comp0_init=totaltime*z;
	 else
		Comp0_init=totaltime*ULFRCOcount;// self cal deactivated
    else
    {
        Prescalar= totaltime/2;  //prescalar
 	    CMU->LFAPRESC0 &= 0xfffff0ff;
 	    CMU->LFAPRESC0 |=Prescalar << 8;
 	    Prescalar = 1<< Prescalar;

	    Comp0_init= totaltime*LFXOcount/Prescalar;
    }
    LETIMER0->CNT=Comp0_init;
    LETIMER_CompareSet(LETIMER0,0,Comp0_init);

    if(LETIMER0_ENERGY_MODE ==EM3)
    {
	   if ( calibre == 1)
	   {
		  Comp1_init=blinktime*z;
          comp1_float_init=blinktime*z; // check for float value
	      if(comp1_float_init>Comp1_init)
		  Comp1_init++;                 // increment int if float is greater

	   }
	   else
       {
		  Comp1_init=blinktime*ULFRCOcount;}

     }
     else
     {
	      Comp1_init= blinktime*LFXOcount/Prescalar;
     }
	 LETIMER_CompareSet(LETIMER0,1,Comp1_init);
	 while((LETIMER0->SYNCBUSY) != 0);// check for syncbusy

	 intflags = LETIMER0->IF;
	 LETIMER0->IFC = intflags;

	 LETIMER0->IEN = LETIMER_IEN_UF
			| LETIMER_IEN_COMP1;

	  blockSleepMode(LETIMER0_ENERGY_MODE);

	  NVIC_EnableIRQ(LETIMER0_IRQn);

}

void LETIMER0_IRQHandler(void)
{
	/*INT_Disable();
	intflags=LETIMER_IntGet(LETIMER0);
	LETIMER_IntClear(LETIMER0,intflags);
	INT_Enable();*/

	int intflags = LETIMER0->IF;
	LETIMER0->IFC= intflags;
	if ((intflags & LETIMER_IF_COMP1) != 0)
	{    LETIMER0->IFC= intflags;
		if (i2cuse==0)  //check if i2c is used
		{
			ACMP0->CTRL|=ACMP_CTRL_EN; // enable acmp
		    while (!(ACMP0->STATUS & ACMP_STATUS_ACMPACT)) ;// wait for warmup
	        GPIO_PinOutSet(LIGHTSENSE_EXCITE_PORT, LIGHTSENSE_EXCITE_PIN);
	    }
	}
	else if((intflags & LETIMER_IF_UF) != 0)
	{  LETIMER0->IFC= intflags;
		if (i2cuse==0)
	   {
		  uint32_t x=ACMP0->STATUS;
          if((x & 0x00000002) == (0x00000002))//check output of acmp0
          {
        	 LED_state(false);
             ACMP0->INPUTSEL &= 0xffffc0ff;
             ACMP0->INPUTSEL |= dark_refrence << 8;// change vdd level to 2
          }
          else
          {
	      LED_state(true);
          ACMP0->INPUTSEL &=0xffffc0ff;
          ACMP0->INPUTSEL |=light_refrence << 8;//change vdd level to 61
          }
	    GPIO_PinOutClear(LIGHTSENSE_EXCITE_PORT, LIGHTSENSE_EXCITE_PIN);// disable excite
	    ACMP0->CTRL &= ~ACMP_CTRL_EN;                             // disable acmp
	    ADC_Start(ADC0,adcStartSingle);              // start single conversion
	    blockSleepMode(1);                     //enter blocksleepmode1
	   }
	   else
	   { // blockSleepMode(EM1);
		   if(load_period==0)
	      {
	      i2c1_setup(); //i2c setup
	      GPIO2_setup();// gpio pins for i2c
	      powerup();  //power for stabilization
	      work();
	      load_period++;  //increment period
	      }
	      else if (load_period==1)
	      {

	    	  load_period++;
	      }
	      else if(load_period==2)
	      {

	    	  GPIO->IFC = GPIO->IF; //clear flags
	    	  //GPIO_PinModeSet(SDAport,SCLpin, gpioModeDisabled, 1); //disable SCL pin
	    	  	//GPIO_PinModeSet(SDAport,SDApin, gpioModeDisabled, 1); //disable SDA pin
	    	  	GPIO_ExtIntConfig( intport, intpin, 1, false, true, false );//disable interrupts
	    	  GPIO_PinOutClear(powerport, powerpin); //clear power pin
	    	  load_period=0;
	    	  unblockSleepMode(EM1);  // unblock em1
	    	  blockSleepMode(EM3);    //block em3 for slave
	      }

	   }
		 ADC_Start(ADC0,adcStartSingle);              // start single conversion
			    blockSleepMode(1);                     //enter blocksleepmode1

	    if (DMAuse == 1)  // activate dma
			{
		      DMA_ActivateBasic(DMA_CHANNEL_ADC, //adc channel


			                    true,

			                    false,

			                    (void *)ramBufferAdcData, // store in buffer

			                    (void *)&(ADC0->SINGLEDATA), // single data enabled

			                    ADCSAMPLES - 1);
			}
	    else
	    {
	    	NVIC_ClearPendingIRQ(ADC0_IRQn);
	    	  NVIC_EnableIRQ(ADC0_IRQn);
	    	  ADC0->IEN |= 0x01;  // enable interrupts
	    	  ADC0->SINGLECTRL &= ~ADC_SINGLECTRL_REP;// repeat mode off
	    }



       /*ADC_Start(ADC0,adcStartSingle); //go to IRQ handler after conversion
       blockSleepMode(1);*/


  }
}

void ADC0_IRQHandler(void)
{// INT_Disable();
	int flagADC= ADC0->IF;
    ADC0->IFC=flagADC;  //disable flags

    if(countADC<ADCSAMPLES)
    {
       ramBufferAdcData[countADC] = ADC_DataSingleGet(ADC0); // store in buffer
       countADC+=1;
      // ADC0->CMD=0x2;

    }
	else
	{
		ADC0->CMD = 0x02;  //stop conversion after 1000 conversions
		unblockSleepMode(1);
		countADC=0;
		finaltemp(); // give final temp
		//CMU_ClockEnable(cmuClock_ADC0, false);
	}
   // INT_Enable();
}
long LETIMERCAL_setup()
{
	int comp0_init=ULFRCOcount;
	const LETIMER_Init_TypeDef letimerInit =
		  {		  .enable         = false, // disable letimer
				  .debugRun       = false, // disable counter value running
				  .rtcComp0Enable = false,// dont start rtc comp0
				  .rtcComp1Enable = false, // dont start rtc comp 1
				  .comp0Top       = true, //comp0 used as top
				  .bufTop         = false,// dont load comp1 into comp0
				  .out0Pol        = 0,
				  .out1Pol        = 1,
				  .ufoa0          = letimerUFOANone,
				  .ufoa1          = letimerUFOANone,
				  .repMode        = letimerRepeatOneshot,//enabled once then disabled

				  };
    LETIMER0->CNT=comp0_init;// put comp0 in cnt
	LETIMER_Init(LETIMER0, &letimerInit);
	while(LETIMER0->SYNCBUSY !=0);
	TIMER0->CNT=0;
	TIMER1->CNT=0;
    LETIMER_Enable(LETIMER0,true);
    TIMER_Enable(TIMER0,true);// enable timer 0
    TIMER_Enable(TIMER1,true);// enable timer 1

	while(LETIMER0->CNT != 0);// poll underflow flag
	LETIMER_Enable(LETIMER0,false);

	TIMER_Enable(TIMER0,false);// disable timers
    TIMER_Enable(TIMER1,false);

    long x = TIMER0->CNT | TIMER1->CNT << 16;// no. of counts in time
    return x;

}
long LETIMERCAL1_setup()
{
	int comp0_init;
	const LETIMER_Init_TypeDef letimerInit1 =
		  {		  .enable         = false,
				  .debugRun       = false,
				  .rtcComp0Enable = false,
				  .rtcComp1Enable = false,
				  .comp0Top       = true,
				  .bufTop         = false,
				  .out0Pol        = 0,
				  .out1Pol        = 1,
				  .ufoa0          = letimerUFOANone,
				  .ufoa1          = letimerUFOANone,
				  .repMode        = letimerRepeatOneshot,

				  };
	comp0_init=LFXOcount;
    LETIMER0->CNT=comp0_init;
	LETIMER_Init(LETIMER0, &letimerInit1);
	while(LETIMER0->SYNCBUSY !=0);


	TIMER0->CNT=0;
	TIMER1->CNT=0;
	LETIMER_CompareSet(LETIMER0,0,comp0_init);
	LETIMER_Enable(LETIMER0,true);
	TIMER_Enable(TIMER0,true);
	TIMER_Enable(TIMER1,true);

		//flags = LETIMER0->IF;
		//LETIMER0->IFC = flags;
	while(LETIMER0->CNT != 0);

	TIMER_Enable(TIMER0,false);
    TIMER_Enable(TIMER1,false);

    long y = TIMER0->CNT | TIMER1->CNT <<16;

    return y;  //no. of counts

}

void TIMER0_setup()
{
	TIMER_Init_TypeDef timerInit0 =
		  {
		    .enable     = false,
		    .debugRun   = false,
		    .prescale   = timerPrescale1,
		    .clkSel     = timerClkSelHFPerClk,
		    .fallAction = timerInputActionNone,
		    .riseAction = timerInputActionNone,
		    .mode       = timerModeUp,
		    .dmaClrAct  = false,
		    .quadModeX4 = false,
		    .oneShot    = false,
		    .sync       = false,
		  };
		 TIMER_Init(TIMER0, &timerInit0);
}
void TIMER1_setup()
{
	 TIMER_Init_TypeDef timerInit1 =
	  {
	    .enable     = false,
	    .debugRun   = false,
	    .prescale   = timerPrescale1,
	    .clkSel     = timerClkSelCascade,
	    .fallAction = timerInputActionNone,
	    .riseAction = timerInputActionNone,
	    .mode       = timerModeUp,
	    .dmaClrAct  = false,
	    .quadModeX4 = false,
	    .oneShot    = false,
	    .sync       = true,
	  };
	 TIMER_Init(TIMER1, &timerInit1);
}

void LED_state(bool state)
{
	if(state)
        {GPIO_PinOutSet(LEDport,LEDpin);
	c=LEDSetCMD;

	}
     else
     { GPIO_PinOutClear(LEDport,LEDpin);
     c=LEDResetCMD;
}

}
//disclaimer: I admit Ive refrenced this routine from simplicity studio
void setupDma(void)

{

  DMA_Init_TypeDef        dmaInit;

  DMA_CfgChannel_TypeDef  chnlCfg;

  DMA_CfgDescr_TypeDef    descrCfg;



  /* Initializing the DMA */

  dmaInit.hprot        = 0;   //protection not an issue

  dmaInit.controlBlock = dmaControlBlock;

  DMA_Init(&dmaInit); // initialize dma



  /* Setting up call-back function */

  cb.cbFunc  = transferComplete;

  cb.userPtr = NULL;



  /* Setting up channel */

  chnlCfg.highPri   = true;	//channel priority is high

  chnlCfg.enableInt = true; // enable interrupt

  chnlCfg.select    = DMAREQ_ADC0_SINGLE; // configure channel 0

  chnlCfg.cb        = &cb;  // callback routine

  DMA_CfgChannel(DMA_CHANNEL_ADC, &chnlCfg);

/* Setting up channel descriptor */

  descrCfg.dstInc  = dmaDataInc2; // dest incrememnt by 2

  descrCfg.srcInc  = dmaDataIncNone; // source doesnt increment

  descrCfg.size    = dmaDataSize2; // set data size

  descrCfg.arbRate = dmaarbitrate;// arbitrate level 1

  descrCfg.hprot   = 0;

  DMA_CfgDescr(DMA_CHANNEL_ADC, true, &descrCfg);



  /* Setting flag to indicate that transfer is in progress

   * will be cleared by call-back function. */

  transferActive = true;

}
void setupAdc(void)

{

  ADC_Init_TypeDef        adcInit       = ADC_INIT_DEFAULT;

  ADC_InitSingle_TypeDef  adcInitSingle = ADC_INITSINGLE_DEFAULT;


  adcInit.prescale = ADC_PrescaleCalc(ADCprescale, 0); //calculate and set prescaled adc clock
  ADC_Init(ADC0, &adcInit);



  adcInitSingle.input     =  adcinput;  /* temperature sensor */
  adcInitSingle.acqTime=2;

  ADC_InitSingle(ADC0, &adcInitSingle);
  ADC0->SINGLECTRL |=0x01;


}

void transferComplete(unsigned int channel, bool primary, void *user)

{

  (void) channel; //call-back routine iniatializations

  (void) primary;

  (void) user;

  ADC0->CMD |= 0x02;
  unblockSleepMode(1);
  /* Stopping ADC by stopping TIMER0 */

  /* Clearing flag to indicate that transfer is complete */
  transferActive = false; //transfer complete
  finaltemp();
}

void finaltemp()
{
    for (int i=0;i<ADCSAMPLES;i++)
    {
    	average += ramBufferAdcData[i];
    }
    average=average/ADCSAMPLES;

    //temperature= average%10;
    //temperature1=average/10;
    float temp = convertToCelcius(average);
   //float temp = -1.63;
    if(temp<0)   //check if temperature negative
	{
	   temp10=67;
	   temp=temp*(-1); // make positive
	}
   else
	   temp10=68;

     temp1=temp*10;
     temp11=temp1%10;
     temp13=temp1/10;
     temp12=temp13%10;
     temp13=temp13/10;
     CBWrite(&cb1,temp10);
     CBWrite(&cb1,temp11);
     CBWrite(&cb1,temp12);
     CBWrite(&cb1,temp13);
     CBWrite(&cb1,c);
     NVIC_EnableIRQ(LEUART0_IRQn);
     if (temp <lowertemp|| temp>uppertemp)
    	GPIO_PinOutSet(LEDport,LEDpin2);
     else
    	GPIO_PinOutClear(LEDport,LEDpin2);
}

//disclaimer: I admit Ive taken this routine from simplicity studio
float convertToCelcius(int32_t adcSample)
{
	float temp;
    float cal_temp_0 = (float)((DEVINFO->CAL &_DEVINFO_CAL_TEMP_MASK)
                 >>_DEVINFO_CAL_TEMP_SHIFT);
    float cal_value_0 = (float)((DEVINFO->ADC0CAL2
		          &_DEVINFO_ADC0CAL2_TEMP1V25_MASK)
		          >>_DEVINFO_ADC0CAL2_TEMP1V25_SHIFT);
    float t_grad = -6.27;
    temp = (cal_temp_0-((cal_value_0-adcSample)/t_grad));
    return temp;
}

void GPIO_ODD_IRQHandler(void)
{

  ClearTSLInterrupt(); //disable TSL interrupts
  int flags8=GPIO->IF;
  GPIO->IFC=flags8;
  I2C1->CMD  = I2C_CMD_START;
  I2C1->TXDATA =slave_address<<1|writeslave;
  while((I2C1->IF & I2C_IF_ACK) == 0);
  int flag3 = I2C1->IF;
  I2C1->IFC=flag3;
  write(data0low_add);
  read(slave_address<<1|readslave);
  int r= 256*gh+ef;
  if (r<Threshlow)   //compare
  LED_state(true);
  int s=256*cd+ab;
  if (s>ThreshHigh)
  LED_state(false);
}


void i2c1_setup(void)
{
	CMU_ClockEnable(cmuClock_I2C1,true);
	GPIO_PinModeSet(SDAport,SCLpin, gpioModeWiredAnd, 1);
	GPIO_PinModeSet(SDAport,SDApin, gpioModeWiredAnd, 1);
    I2C1->ROUTE= I2C_ROUTE_SDAPEN |
                 I2C_ROUTE_SCLPEN |
                 (0<< _I2C_ROUTE_LOCATION_SHIFT);

    I2C_Init_TypeDef i2cInit = {
    		  .enable = true,                    /* Enable when init done */
    		  .master = true,                    /* Set to master mode */
    		  .refFreq = 0,                       /* Use currently configured reference clock */
    		  .freq = I2C_FREQ_STANDARD_MAX,   /* Set to standard rate assuring being within I2C spec */
    		  .clhr = i2cClockHLRStandard      /* Set to use 4:4 low/high duty cycle */
    		};


    I2C_Init(I2C1, &i2cInit);
    int flag = I2C1->IF;
      I2C1->IFC=flag;
   if(I2C1->STATE & I2C_STATE_BUSY)
   {
	   I2C1->CMD=I2C_CMD_ABORT;
   }
   for(int i=0;i<=9;i++)
   {
	   GPIO_PinModeSet(SDAport, SCLpin, gpioModeWiredAnd, 0);

	       GPIO_PinModeSet(SDAport, SCLpin, gpioModeWiredAnd, 1);
   }

}
void GPIO2_setup()
{
	GPIO_PinModeSet(powerport, powerpin, gpioModePushPull, 1);
	GPIO_PinOutSet(powerport, powerpin);
	GPIO_PinModeSet(intport, intpin, gpioModeInput, 1);
	//GPIO_PinModeSet(LEDport, LEDpin, gpioModePushPull, 0);
	GPIO_ExtIntConfig(intport,
		 			            1,
		 			            1,
		 			            true,
		 			            false,
		 			            true);

	 NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
	 NVIC_EnableIRQ(GPIO_ODD_IRQn);

    // GPIO->IEN=0x02;
}
void write(int z)
{
	I2C1->TXDATA =  z;
		  while((I2C1->IF & I2C_IF_ACK) == 0);
		   int flag1 = I2C1->IF;
		  I2C1->IFC=flag1;


}
void work(void)
{   //ClearTSLInterrupt();
    //int l=slave_address<<1|writeslave;
	I2C1->TXDATA =slave_address<<1|writeslave;
    I2C1->CMD  |= I2C_CMD_START;
    //I2C1->TXDATA =slave_address<<1|writeslave;
    while(!(I2C1->IF & I2C_IF_ACK));
    int flag3 = I2C1->IF;
    I2C1->IFC=flag3;

    write(controladd|wordwrite);
    write(control);
    write(timing);
    write(ThreshLowLow);
    write(ThreshLowHigh);
    write(ThreshHighLow);
    write(ThreshHighHigh);
    write(interrupt);
    I2C1->CMD  |= I2C_CMD_STOP;
    flag3 = I2C1->IF;
        I2C1->IFC=flag3;

    if(I2C1->STATE & I2C_STATE_BUSY){

      I2C1->CMD = I2C_CMD_ABORT ;

       }
   // GPIO->IFC = 0x02;

     // GPIO->IEN = 0x02;
      GPIO_ExtIntConfig( intport, intpin, 1, false, true, true );
 	}
void read(int y)
{
	I2C1->CMD  |= I2C_CMD_START;
    I2C1->TXDATA =y;
    //I2C1->CMD |= I2C_CMD_ACK;
    while(!(I2C1->IF & I2C_IF_RXDATAV));
    ab = I2C1->RXDATA;
    I2C1->CMD |= I2C_CMD_ACK;
     while(!(I2C1->IF & I2C_IF_RXDATAV));
     cd = I2C1->RXDATA;
     I2C1->CMD |= I2C_CMD_ACK;
     while(!(I2C1->IF & I2C_IF_RXDATAV));
     ef = I2C1->RXDATA;
     I2C1->CMD |= I2C_CMD_ACK;
     while(!(I2C1->IF & I2C_IF_RXDATAV));
     gh = I2C1->RXDATA;
     I2C1->CMD |= I2C_CMD_NACK;
     I2C1->CMD  |= I2C_CMD_STOP;
	}
void ClearTSLInterrupt(void)

{

if(I2C1->STATE & I2C_STATE_BUSY)

 	  {

 	  I2C1->CMD = I2C_CMD_ABORT ;

 	  }
    I2C1->TXDATA =slave_address<<1|writeslave;
    I2C1->CMD  |= I2C_CMD_START;
    //I2C1->TXDATA =slave_address<<1|writeslave;
    while(!(I2C1->IF & I2C_IF_ACK));
    int flag3 = I2C1->IF;
    I2C1->IFC=flag3;
    write(0xC6);
    write(0x01);
    I2C1->CMD = I2C_CMD_STOP;

}

void powerup(void)
{
		CMU_ClockEnable(cmuClock_TIMER0,true); //enable timer


    TIMER_Init_TypeDef timerInit0 =
		  {
		    .enable     = false,
		    .debugRun   = false,
		    .prescale   = timerPrescale1,
		    .clkSel     = timerClkSelHFPerClk,
		    .fallAction = timerInputActionNone,
		    .riseAction = timerInputActionNone,
		    .mode       = timerModeUp,
		    .dmaClrAct  = false,
		    .quadModeX4 = false,
		    .oneShot    = true,
		    .sync       = false,
		  };
		 TIMER_Init(TIMER0, &timerInit0);
		 TIMER0->CNT=0x0000;
		 TIMER_Enable(TIMER0,true);

		 while(TIMER0->CNT <= 28000); //wait for 2ms

		 TIMER_Enable(TIMER0,false);
}

eBuffState BufferState(struct CirBuf *cb){

	if(CBLengthData(cb) == (cb->size - 1))
	{
		e_buffer_state = BufferFull;
                //printf("BufferFull\n");
	}
	else if(CBLengthData(cb) == 0)
	{
		e_buffer_state = BufferEmpty;
              // printf("BufferEmpty\n");
	}
	else
	{
		e_buffer_state = BufferAvailable;
                //printf("BufferAvailable\n");
	}
	return e_buffer_state;
}

//prints the buffer

void printBuf(struct CirBuf *cb){
	int i;
	for(i=0;i<cb->size;i++){
		printf("[%d]\t",cb->buf[i]);
	}
	printf("\n");
}

//gets the length of data in the buffer
uint16_t CBLengthData(struct CirBuf *cb){
	uint8_t lengthData = ((cb->write - cb->read) & (cb->size - 1));
	//printf("length of data in buffer is: %d\n", lengthData );
	return lengthData;
}

//function to check if the buffer is full or no
eBuffState Bufferfull(struct CirBuf *cb){
	if(CBLengthData(cb) == (cb->size - 1))
	{
		e_buffer_state = BufferFull;
	}
	else
	{
		e_buffer_state = BufferAvailable;
	}
	return e_buffer_state;
}

//function to verify if the buffer is empty or no

eBuffState Bufferempty(struct CirBuf *cb){
	if(CBLengthData(cb) == 0)
	{
                e_buffer_state = BufferFull;
        }
        else
        {
                e_buffer_state = BufferAvailable;
        }
        return e_buffer_state;
}


//function to write in the buffer
eBuffState CBWrite(struct CirBuf *cb, uint8_t data){

	if(BufferState(cb) == BufferFull)
	{
		printf("BufferFull\n");
		return BufferFull;
	}
	else
	{
		printf("Buffer is Available\n");
	}

	if (NULL != cb->buf)
	{
		cb->buf[cb->write] = data;
		cb->write = (cb->write + 1) & (cb->size-1);
		printBuf(cb);
	}
	else
	{
		printf("Write buffer pointer is null\n");
	}

	return BufferAvailable;
}

//function to read from the buffer
eBuffState CBRead(struct CirBuf *cb, uint8_t *data){

	if(BufferState(cb) == BufferEmpty) {
		printf("BufferEmpty\n");
		return BufferEmpty;
	}
	else
	{
		printf("Buffer is not empty\n");

	}
	if (NULL != cb->buf)
	{
	*data = cb->buf[cb->read];
	cb->read = (cb->read + 1) & (cb->size - 1);
	printf("Data Read at index %d is %d\n", cb->read, *data);
	}
	else
	{
		printf("Pointer is null\n");
	}
	return BufferAvailable;
}

void leuart0_setup(void)
{
   if(LETIMER0_ENERGY_MODE==EM2)
	 CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);  //lfxo clock for em2
   else
	CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFRCO); //lfrco clock for em3

	 CMU_ClockEnable(cmuClock_LEUART0, true);

	LEUART_Init_TypeDef leuart0Init =
 {
   .enable   = leuartEnableTx,     /* Activate data reception on LEUn_RX pin. */
   .refFreq  = 0,                  /* Inherit the clock frequenzy from the LEUART clock source */
   .baudrate = leuaert_baud,               /* Baudrate = 9600 bps */
   .databits = leuartDatabits8,    /* Each LEUART frame containes 8 databits */
   .parity   = leuartNoParity,     /* No parity bits in use */
   .stopbits = leuartstopbits,    /* Setting the number of stop bits in a frame to 2 bitperiods */
  };
 LEUART_Reset(LEUART0);
 LEUART_Init(LEUART0, &leuart0Init);
 LEUART0->ROUTE = LEUART_ROUTE_TXPEN |
                    LEUART_ROUTE_LOCATION_LOC0;


 GPIO_PinModeSet(LEUARTport,            /* Port */
                   LEUARTpin,                    /* Port number */
                   gpioModePushPull,    /* Pin mode is set to input only, with pull direction given bellow */
                   1);                   /* Pull direction is set to pull-up */
 LEUART0->IEN|=LEUART_IEN_TXBL;
 NVIC_ClearPendingIRQ(LEUART0_IRQn);
}



void LEUART0_IRQHandler(void)
{
	while((LEUART0->SYNCBUSY)!=0);
	int leuartif = LEUART_IntGet(LEUART0);  //clear flags
	LEUART_IntClear(LEUART0, leuartif);
    LEUART0->CTRL|=LEUART_CTRL_LOOPBK;  //enable loopback for verification
    LEUART0->CMD|=LEUART_CMD_RXEN;    //enable reception

if (ts==0)								//send data
	{CBRead(&cb1,rd);
        LEUART0->TXDATA=read1[0];
	}
if (ts==1)
	{
	CBRead(&cb1,rd);
	 LEUART0->TXDATA=read1[0];
	}
if (ts==2)
	{CBRead(&cb1,rd);
	 LEUART0->TXDATA=read1[0];
	}
if(ts==3)
	{CBRead(&cb1,rd);
	LEUART0->TXDATA=read1[0];
	}
if(ts==4)
	{
	CBRead(&cb1,rd);
	LEUART0->TXDATA=read1[0];
	}
while((LEUART0->IF & LEUART_IF_TXC)==0);
//unblockSleepMode(2);
ts++;
if (ts==5)
 {
	NVIC_DisableIRQ(LEUART0_IRQn);
    ts=0;
   cb1.write=0;
   cb1.read=0;
 }
}
int main(void){
	/**************************************************************************//**
	 * @brief  Main function
	 *****************************************************************************/

	CHIP_Init();
	blockSleepMode(3);
	if (i2cuse ==0) setupACMP();

	uint8_t *wr=malloc(1*sizeof(char));

	rd=read1;
	//struct CirBuf cb1;
	//memset(&cb1, 0, sizeof(cb1));
    cb1.buf=wr;
	cb1.size=8;
	cb1.read=0;
	cb1.write=0;

	CMU_setup();
	GPIO_setup();
	I2C0_setup();
	GPIOacc_setup();
	workacc();

	setupAdc();

	//leuart0_setup();
	if(DMAuse==1) setupDma();



    LETIMER0_setup();
    LETIMER_Enable(LETIMER0,true);

	while(1)
	{
		if (DMAuse==0 && countADC>0 && countADC<=ADCSAMPLES)//switch off if 1000 conversions done
		{
			   ADC_Start(ADC0,adcStartSingle);
		}
		sleep();
		//EMU_EnterEM2(false);
	}

	return 0;
}