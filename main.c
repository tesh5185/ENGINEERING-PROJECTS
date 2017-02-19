/**************************************************************************//**
 * @file lesense_letouch_main.c
 * @brief LESENSE CAPACITIVE TOUCH code example
 * @author Silicon Labs
 * @version 2.05
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/

#include "em_device.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "lesense_letouch.h"
#include "lesense_letouch_config.h"
#define LED_PORT gpioPortE
#define LED_PIN  3
/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Bitmask for the currently touched channels */
  uint16_t channels_touched = 0;
    int  next =0;

    float sensitivity[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0};
  // Init GPIO for LED, turn LED off
  CMU_ClockEnable(cmuClock_GPIO, true);
  GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, 0);

  // Init Capacitive touch for channels configured in sensitivity array
  LETOUCH_Init(sensitivity);

  // If any channels are touched while starting, the calibration will not be correct.
  // Wait while channels are touched to be sure we continue in a calibrated state.
  while(LETOUCH_GetChannelsTouched() != 0);
  //i2c1_setup();
   // GPIO2_setup();
   // powerup();

  //  work();
    EMU_EnterEM2(true);
  // Enter infinite loop.
  while (1)
  {
    // Get channels that are pressed, result is or'ed together
    channels_touched = LETOUCH_GetChannelsTouched();

    // Check if any channels are in the touched state.
    if(channels_touched){
      // Turn on LED
       if (next ==0)
    	{
    	GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, 1);
         next=1;
         while(LETOUCH_GetChannelsTouched() != 0);

    }
    else{
      /* Turn off LED */
      GPIO_PinModeSet(LED_PORT, LED_PIN, gpioModePushPull, 0);
      next=0;
      while(LETOUCH_GetChannelsTouched() != 0);

    }
    }
    /* Enter EM2 */
    EMU_EnterEM2(true);
  }
}