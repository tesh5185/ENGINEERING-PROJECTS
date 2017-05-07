#include "sleep.h"
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
void sleep(void) //sleep routine
{
	if(sleep_block_counter[0]>0)
	{
		return;
	}
	else if(sleep_block_counter[1]>0)
	{
		EMU_EnterEM1();
	}
	else if(sleep_block_counter[2]>0)
	{
		EMU_EnterEM2(true);
	}
	else if(sleep_block_counter[3]>0)
	{
		EMU_EnterEM3(true);
	}
	else
	{
		EMU_EnterEM4();
	}

}
