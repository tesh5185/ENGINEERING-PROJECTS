#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

struct CirBuf {
	uint8_t *buf;
	uint16_t size;		//as a power of 2
	uint16_t read;
	uint16_t write;	
};

typedef enum{
	BufferInvalid=0,	//used for buffer initialization
	BufferAvailable,
	BufferFull,
	BufferEmpty
}eBuffState;

eBuffState e_buffer_state = BufferInvalid;


uint16_t CBLengthData(struct CirBuf *cb);
void printBuf(struct CirBuf *cb);
eBuffState Bufferfull(struct CirBuf *cb);
eBuffState Bufferempty(struct CirBuf *cb);
eBuffState CBWrite(struct CirBuf *cb, uint8_t data);
eBuffState CBRead(struct CirBuf *cb, uint8_t *data);
eBuffState BufferState(struct CirBuf *cb);


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
	uint8_t lengthData = ((cb->write - cb->read) & (cb->size - 1));	
	printf("length of data in buffer is: %d\n", lengthData );
	return lengthData;
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



void main(void){
    struct timevak begin,end;
    double elapsed;
    uint8_t *g=malloc(1*sizeof(char));
    struct CirBuf cb1;

    memset(&cb1, 0, sizeof(cb1));

    cb1.buf=g;
    cb1.size=8;
    cb1.read=0;
    cb1.write=0;

    printBuf(&cb1);
   gettimeofday(&begin,NULL);
    CBWrite(&cb1, 01);    
    gettimeofday(&end,NULL);
  elapsed = (end.tv_sec - begin.tv_sec) +
              ((end.tv_usec - begin.tv_usec)/1000000.0);

  printf("\ntime(in microseconds) for printf(str, float, float, float)  %ld\n",((end.tv_sec * 1000000 + end.tv_usec)
                  - (begin.tv_sec * 1000000 + begin.tv_usec)));


   	
}






