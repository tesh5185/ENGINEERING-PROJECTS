#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include<string.h>
#include"cirbuf.h"

//gets the buffer state
eBuffState BufferState(struct CirBuf *cb){
		
	if(CBLengthData(cb) == (cb->size - 1)) 
	{
		e_buffer_state = BufferFull;
	}
	else if(CBLengthData(cb) == 0)
	{	
		e_buffer_state = BufferEmpty;
	}
	else 
	{	
		e_buffer_state = BufferAvailable;
	}
	return e_buffer_state;	
}

//prints the buffer

void printBuf(struct CirBuf *cb){
	int i;
	for(i=0;i<cb->size;i++){
		printf("[%d]\t",cb->buf[i]);
	}
	printf("\n");	
}

//gets the length of data in the buffer
uint16_t CBLengthData(struct CirBuf *cb){
	return ((cb->write - cb->read) & (cb->size - 1));	
}

//function to check if the buffer is full or no
eBuffState Bufferfull(struct CirBuf *cb){
	if(CBLengthData(cb) == (cb->size - 1)) 
	{
		e_buffer_state = BufferFull;
	}
	else 
	{	
		e_buffer_state = BufferAvailable;
	}
	return e_buffer_state;	
}

//function to verify if the buffer is empty or no

eBuffState Bufferempty(struct CirBuf *cb){
	if(CBLengthData(cb) == 0)
	{
                e_buffer_state = BufferFull;
        }
        else
        {
                e_buffer_state = BufferAvailable;
        }
        return e_buffer_state;
}


//function to write in the buffer
eBuffState CBWrite(struct CirBuf *cb, uint8_t data){

	if(BufferState(cb) == BufferFull) 
	{
		printf("BufferFull\n");	
		return BufferFull;
	}
	else 
	{	
		printf("Buffer is Available\n");
	}

	if (NULL != cb->buf)
	{
		cb->buf[cb->write] = data;
		cb->write = (cb->write + 1) & (cb->size - 1);
		printBuf(cb);
	}	
	else
	{
		printf("Write buffer pointer is null\n");
	}

	return BufferAvailable;		
}

//function to read from the buffer
eBuffState CBRead(struct CirBuf *cb, uint8_t *data){

	if(BufferState(cb) == BufferEmpty) {
		printf("BufferEmpty\n");			
		return BufferEmpty;
	}
	else
	{
		printf("Buffer is not empty\n");
	}
	if (NULL != cb->buf)
	{
	*data = cb->buf[cb->read];
	cb->read = (cb->read + 1) & (cb->size - 1);
	printf("Data Read at index %d is %d\n", cb->read, *data);
	}
	else
	{
		printf("Pointer is null\n");
	}
}




