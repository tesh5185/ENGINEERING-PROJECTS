#ifndef _SLEEP_H_
#define _SLEEP_H_

#include "em_emu.h"
#include "em_int.h"
void blockSleepMode(unsigned int sleepstate);
void unblockSleepMode(unsigned int sleepstate);
void sleep(void);

#define EM0 0
#define EM1 1
#define EM2 2
#define EM3 3
#define EM4 4
unsigned int sleep_block_counter[5];
#define LETIMER0_ENERGY_MODE EM2

#endif
