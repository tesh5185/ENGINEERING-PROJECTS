#include  <stdio.h>
#include  <stdlib.h>
#include  <stdint.h>
#include  <string.h>
#include "project_1.h"
#include  "memory.h"

void project_1_report()
{ 
  int8_t a[32];
  int8_t *d;
  int8_t *e;
  int8_t *f;
  d=&a[0];
  e=&a[8];
  f=&a[17];
  for(int i=0;i<16;i++)
  {
      *(d+i)=31+i;
 
  }
  my_memzero(e,24);

  my_memmove(d,f,8);
 
  my_memmove(e,d,16);

  my_reverse(d,32);
  for(int i=0;i<32;i++)
  printf("\n%d",a[i]);
  }
 
