#ifndef _UART_H
#define _UART_H

#define echo 0
#define DEBUG
#define FRDM
//#define CIRBUFFER

#include <MKL25Z4.H>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cirbuf.h"

int tx =0;
uint32_t count=0, j=0;

uint32_t time=0;

int tx_start=0;
char a[100]="";
char *str= a;
int t=0,k=0,o=0;
uint8_t transmit=1;
char b[100],d[100];
uint8_t *rdata=b;
uint8_t *ptr1=b;
char res[20];
uint8_t dts=0;
uint8_t *param=res;
float n =1234.567890;
uint8_t string1[100]="Unit_test_1:pass. Indicating buffer full~";
uint8_t string2[100]="Unit_test_2:pass. Indicating buffer empty~";
uint8_t transmit_data[100]="CIRBUF_UNIT_TEST_SUITE:fail.(1/2 PASS)~";
uint8_t *transmit_ptr = transmit_data;
uint8_t *g=0;
uint8_t *p=0;
uint8_t *u=0;
struct CirBuf cb1;
struct CirBuf cb2;

void UART0_init(void);
void UART00_init(void);
void UART_transmit_message(uint8_t string[]);
void UART_transmit();

#endif