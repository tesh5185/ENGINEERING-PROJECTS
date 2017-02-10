#ifndef _RECEIVECIRBUF_H
#define _RECEIVECIRBUF_H
#include <MKL25Z4.H>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cirbuf.h"
#include "memory.h"
#include "data.h"
#define DEBUG
//#define FRDM
//#define CIRBUFFER
void UART0_init(void);
void delayMs(int n);
void LED_init(void);
void LED_set(int value);
void UART00_init(void);
int tx =0;
uint32_t count=0, j=0;

uint32_t time=0;

int tx_start=0;
char a[100]="";
char *str= a;
int t=0,k=0,o=0;
#endif
