
 /*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include <stdlib.h>
void dma_init();
void dma_use();
#define length 10
#define wordsend 0
char *a,*b,*d;

char c[1]={0};

uint32_t k,l;
int flag,flag1;
int time=0,count=0;
void dma_memmove(char *src,char *dest,uint32_t len);
void dma_memzero(char *dest,uint32_t len);
void dma_memmove(char *src,char *dest,uint32_t len)
{
	if ((a>=b && a<(b+length))||(a<=b && (a+length)>b))
		       flag=1;

	else
			   flag=0;
	__disable_irq();
	DMA_DCR0|=DMA_DCR_SINC_MASK;
	DMA_DCR0|=DMA_DCR_DINC_MASK;  // increment source and destination every transfer
	dma_init();
	if (wordsend==1 && l!=0)
	{
       if (flag==0)
	   {
    	   DMA_DSR_BCR0|=k;            // total number of transfers
    	   DMA_SAR0=(uint32_t)src;  // source address
    	   DMA_DAR0=(uint32_t)dest;//dest address
    	   TPM0->SC|=0x08;
    	   DMA_DCR0|=DMA_DCR_START_MASK; // start transfer
    	   flag1=1;
    	   __enable_irq();
    	   while (flag1==1);
    	   DMA_DCR0|=DMA_DCR_SSIZE(1)|DMA_DCR_DSIZE(1);
    	   DMA_DSR_BCR0 =l;
    	   DMA_SAR0=(uint32_t)src+k;  // source address
    	   DMA_DAR0=(uint32_t)dest+k;  //dest address
    	   TPM0->SC|=0x08;
    	   DMA_DCR0|=DMA_DCR_START_MASK; // start transfer
    	   NVIC_EnableIRQ(DMA0_IRQn);
	   }
       else
       {
    	   DMA_DSR_BCR0|=k;            // total number of transfers
    	   DMA_SAR0=(uint32_t)src;  // source address
    	   DMA_DAR0=(uint32_t)d;//dest address
    	   TPM0->SC|=0x08;
    	   DMA_DCR0|=DMA_DCR_START_MASK; // start transfer
    	   flag1=1;
    	   __enable_irq();
    	   while (flag1==1);
    	   DMA_DCR0|=DMA_DCR_SSIZE(1)|DMA_DCR_DSIZE(1);
    	   DMA_DSR_BCR0 =l;
    	   DMA_SAR0=(uint32_t)src+k;  // source address
    	   DMA_DAR0=(uint32_t)d+k;  //dest address
    	   TPM0->SC|=0x08;
    	   DMA_DCR0|=DMA_DCR_START_MASK; // start transfer
    	   flag1=1;
    	   NVIC_EnableIRQ(DMA0_IRQn);
    	   while (flag1==1);

    	   DMA_DSR_BCR0|=k;            // total number of transfers
    	   DMA_SAR0=(uint32_t)d;  // source address
    	   DMA_DAR0=(uint32_t)dest;//dest address
    	   TPM0->SC|=0x08;
    	   DMA_DCR0|=DMA_DCR_START_MASK; // start transfer
    	   flag1=1;
    	   NVIC_EnableIRQ(DMA0_IRQn);
    	   while (flag1==1);
    	   DMA_DCR0|=DMA_DCR_SSIZE(1)|DMA_DCR_DSIZE(1);
    	   DMA_DSR_BCR0 =l;
    	   DMA_SAR0=(uint32_t)d+k;  // source address
    	   DMA_DAR0=(uint32_t)dest+k;  //dest address
    	   TPM0->SC|=0x08;
    	   DMA_DCR0|=DMA_DCR_START_MASK; // start transfer
    	   NVIC_EnableIRQ(DMA0_IRQn);
       }

	}
	else
	{
		if (flag==0)
	    {
			DMA_DSR_BCR0 =length;
	        DMA_SAR0=(uint32_t)src;  // source address
	        DMA_DAR0=(uint32_t)dest;  //dest address
	    }
	        else
	        {
	        	DMA_DSR_BCR0 =length;
	            DMA_SAR0=(uint32_t)src;  // source address
	            DMA_DAR0=(uint32_t)&d;  //dest address
	            TPM0->SC|=0x08;
	            DMA_DCR0|=DMA_DCR_START_MASK; // start transfer
	            flag1=1;
	            __enable_irq();
	            while (flag1==1);
	            DMA_SAR0=(uint32_t)&d;  // source address
	            DMA_DAR0=(uint32_t)dest;  //dest address
	            TPM0->SC|=0x08;
	            DMA_DCR0|=DMA_DCR_START_MASK; // start transfer
	            NVIC_EnableIRQ(DMA0_IRQn);
	        }

	   TPM0->SC|=0x08;
	    DMA_DCR0|=DMA_DCR_START_MASK; // start transfer
	    __enable_irq();

	}
}
void dma_memzero(char *dest,uint32_t len)
{
	__disable_irq();
	DMA_DCR0|=DMA_DCR_DINC_MASK;
	dma_init();
	if (wordsend==1 && l!=0)
	{
		DMA_DSR_BCR0|=k;
		DMA_SAR0=(uint32_t)&c;
		DMA_DAR0=(uint32_t)dest;
		TPM0->SC|=0x08;
		DMA_DCR0|=DMA_DCR_START_MASK;
		 flag1=1;
		__enable_irq();
		 while(flag1==1);
		DMA_DCR0|=DMA_DCR_SSIZE(1)|DMA_DCR_DSIZE(1);

		 DMA_DSR_BCR0 =l;
	     DMA_SAR0=(uint32_t)&c;  // source address
		 DMA_DAR0=(uint32_t)dest+k;  //dest address
		 TPM0->SC|=0x08;
		 DMA_DCR0|=DMA_DCR_START_MASK; // start transfer
		 NVIC_EnableIRQ(DMA0_IRQn);

	 }
	else
	{
		DMA_DSR_BCR0|=length;
		DMA_SAR0=(uint32_t)&c;
		DMA_DAR0=(uint32_t)dest;
		TPM0->SC|=0x08;
		DMA_DCR0|=DMA_DCR_START_MASK;
		__enable_irq();


	}
}
void dma_init()
{

	SIM->SCGC6|=SIM_SCGC6_DMAMUX_MASK;   // Enable clock for dmamux
	SIM->SCGC7|=SIM_SCGC7_DMA_MASK;  // Enable clock for dma
	DMAMUX0_CHCFG0=0x39;       // give value for source while disabled
	DMAMUX0_CHCFG0|=DMAMUX_CHCFG_ENBL_MASK;  // enable chanel 0
	DMA_DCR0|=DMA_DCR_EINT_MASK;
	NVIC_EnableIRQ(DMA0_IRQn);  //enable irq for dma0
    if (wordsend==0)
         DMA_DCR0|=DMA_DCR_SSIZE(1)|DMA_DCR_DSIZE(1);  // size of src and dest bus cycle
    else
    	 DMA_DCR0|=DMA_DCR_SSIZE(0)|DMA_DCR_DSIZE(0);

}

void DMA0_IRQHandler(void)
{

	NVIC_DisableIRQ(DMA0_IRQn);
	TPM0->SC=0;					//disable timer
	time=3*((count*65536)+TPM0->CNT);	//time(in microseconds) 3us is the time required by TMP0 counter to increment by 1
    flag1=0;
}
void TIMER0_init(){
		__disable_irq();

		SIM->SOPT2|=0x01000000;		//use mcgfllclk
		SIM->SCGC6|=0x01000000;		//enable clock to tpm0
		TPM0->SC=0;					//disable timer
		TPM0->SC=0x06; 				//prescaler to 64
		TPM0->MOD=0xFFFF;
		TPM0->SC|=0x80;				//clear TOF
		TPM0->SC|=0x40;				//enable timeout interrupt
		NVIC->ISER[0]|=0x00020000;
		__enable_irq();
}
void TPM0_IRQHandler(void){
	TPM0->SC|=0x80;				//clear TOF
	count+=1;
}


int main(void)
{
	a=malloc(length*sizeof(char));
	b=malloc(length*sizeof(char));
	d=malloc(length*sizeof(char));
	/*char arr[length];
	char *a,*b;
	 b=(arr+5);
    a=arr;
*/



	k=length/4;
	k=k*4;
	l=length%4;
	/*for(int i=0;i<length;i++)
	{
		a[i]=i+1;
	}*/
	TIMER0_init();

	dma_memmove(a,b,length);
	//dma_memzero(b,length);
	while(1){

	}
	return 0;

}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////



