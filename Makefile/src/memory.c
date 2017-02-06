#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "memory.h"

int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length)
{ 
  int8_t ret_val =-1;
  
    for (int j=0;j<length;j++)
    {
        for (int k=0;k<length;k++)
	{
	    if((src+j) == (dst+k))
	    {
	       	printf("ERROR:OVERLAPPED MEMORY\n");

		ret_val=-1;
	    }
	    else
	    {
                for (int i=0;i<length;i++)
		{
		    *(dst+i)=*(src+i);
		   ret_val=0;
		}
	    }
	 }
    }	
	return ret_val;	
}

int8_t my_memzero(uint8_t *src, uint32_t length)
{
    int8_t ret_val =-1;
    for (int i=0; i<length;i++)
    {
        *(src+i)=0;
    }
    	
    for(int j=0;j<length;j++)
    {
        if((*(src+j))!=0) 
        {
	    ret_val=-1;
            break;
        } 
	else
	    ret_val=0;
    }
    
    return ret_val;
}

int8_t my_reverse(uint8_t *src, uint32_t length)
{  
    int8_t ret_val = -1;
    uint8_t *dest = NULL;
    uint8_t r[100];
    dest=r;
    int i;    
    int k=0;
    
    
    
    for ( i=length-1;i>=0;i--)
    {
       *(dest+k)=*(src+i);
	k++;
    }
    
    for(i=0;i<length;i++)
    { 
       *(src+i)=*(dest+i);
    }		
    
    for(i=1;i<=length;i++)
    {
       if((*(src+i))!=(*(src+length-i)))
	   ret_val=-1;
       else
           ret_val=0;
    }
    
   

    return ret_val;
}		


