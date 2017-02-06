#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"



int8_t * my_itoa(int8_t *str,int32_t data,int32_t base)
{	
   int remainder,n; 
   long binary = 0, i = 1;
   int32_t len= strlen(str);
   for (i=0; i<len; i++)
   {
     char b =(char)*(str+i);
     printf("\n%c",b);
   }
   printf("\ndecimal value%x",data);
}

   
int32_t my_atoi(int8_t*src)
{
  int32_t *dst,x[100];
  dst=x; 
  int32_t len = strlen(src); 
  for(int i=0;i<len;i++)
  {
     *(dst+i)=(int32_t)*(src+i);
     printf("%d",*(dst+i));
  }
}


void dump_memory(uint8_t *start, uint32_t length)
   {
      for(int i=0;i<length;i++)
      printf("The hex output is %x\n", *(start+i));
   }
  

uint32_t big_to_little(uint32_t data)
{
   uint32_t m=100;
   uint32_t *z= NULL;
   z=&m;
   *z=(data & 0xff)<<24|(data & 0xff00)<<8|(data & 0xff0000)>>8|(data & 0xff000000)>>24;
   printf("CONVERSION IS %x",*z);
   

}


uint32_t little_to_big(uint32_t data)
{ 

   int m=100;
   uint32_t *y= NULL;
   y=&m;
   *y=(data & 0xff)<<24|(data & 0xff00)<<8|(data & 0xff0000)>>8|(data & 0xff000000)>>24;
   printf("CONVERSION IS %x",*y);


}



