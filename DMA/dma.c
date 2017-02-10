
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
//#include "dma.h"
//static int i = 0;
void dma_init();
void dma_use();
char a[10]={1,2,3,4,5,6,7,8,5,5};
char b[10]={5,1,2,3,4,6,3,6,4,4};
void dma_memmove(char *src,char *dest,char length);
void dma_memmove(char *src,char *dest,char length)
{
	dma_init();
	DMA_DSR_BCR0|=length;            // total number of transfers
	DMA_SAR0=(uint32_t)src;  // source address
		DMA_DAR0=(uint32_t)dest;  //dest address

		DMA_DCR0|=DMA_DCR_START_MASK; // start transfer

}
void dma_init()
{

	SIM->SCGC6|=SIM_SCGC6_DMAMUX_MASK;   // Enable clock for dmamux
	SIM->SCGC7|=SIM_SCGC7_DMA_MASK;  // Enable clock for dma
	DMAMUX0_CHCFG0=0x39;       // give value for source while disabled
	DMAMUX0_CHCFG0|=DMAMUX_CHCFG_ENBL_MASK;  // enable chanel 0

    DMA_DCR0|=DMA_DCR_SINC_MASK|DMA_DCR_DINC_MASK;  // increment source and destination every transfer

    DMA_DCR0|=DMA_DCR_SSIZE(1)|DMA_DCR_DSIZE(1);  // size of src and dest bus cycle
	/*DMA_DSR_BCR0|=10;            // total number of transfers
	DMA_SAR0=(uint32_t)&a;  // source address
		DMA_DAR0=(uint32_t)&b;  //dest address
*/
}

int main(void)
{

    /* Write your code here */

    /* This for loop should be replaced. By default this loop allows a single stepping. */
    /*for (;;) {
        i++;
    }
    /* Never leave main */
dma_memmove(a,b,10);
	
	return 0;

}
////////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////
