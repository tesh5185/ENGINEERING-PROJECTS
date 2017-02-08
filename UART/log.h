#ifndef _LOG_H
#define _LOG_H

#include <MKL25Z4.H>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cirbuf.h"

void LOG_0(uint8_t *ptr1, uint8_t len1);
void LOG_1(uint8_t *ptr2, uint8_t len2, uint8_t *param2, uint8_t data_type_size);

#endif