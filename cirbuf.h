#ifndef _CIRBUF_H
#define _CIRBUF_H
struct CirBuf {
	uint8_t *buf;
	uint16_t size;		//as a power of 2
	uint16_t read;
	uint16_t write;	
};
/*#ifndef NULL
#define NULL   ((void *) 0)
#endif
*/
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

//struct CirBuf cb1;
#endif
