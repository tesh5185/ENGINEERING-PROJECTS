#ifndef __PWMLED_H
#define __PWMLED_H


#include "stdint.h"
void UART0_init_pwmled(void);
void delayMs(int n);
void LED_init(void);
void LED_set(char value);
//char a[20]="";
//char *str= a;
//int i=0;
//int x;
//uint16_t initial =100;

//void UART0_init_pwmled(void);
//void LED_init(void);
void LEDbright(char value);
void LEDON(char value, uint16_t intensity);


#endif
