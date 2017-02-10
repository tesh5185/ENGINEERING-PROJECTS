/* UART0 interrupt handler */
#include "receivecirbuf.h"

#define echo 1
uint8_t transmit=1;
char b[100],d[100];
uint8_t *rdata=b;
uint8_t *ptr1=b;
void LOG_0(uint8_t *ptr1, uint8_t len1);
void LOG_1(uint8_t *ptr2, uint8_t len2, uint8_t *param2, uint8_t data_type_size);
char res[20];
uint8_t dts=0;
uint8_t *param=res;
float n =1234.567890;
uint8_t string1[100]="Unit_test_1:pass. Indicating buffer full~";
uint8_t string2[100]="Unit_test_2:pass. Indicating buffer empty~";
uint8_t transmit_data[100]="CIRBUF_UNIT_TEST_SUITE:fail.(1/2 PASS)~";
uint8_t *transmit_ptr = transmit_data;
uint32_t *g=0;
uint32_t *p=0;
uint32_t *u=0;
struct CirBuf cb1;
struct CirBuf cb2;

void UART0_IRQHandler(void) {
char c;
if(echo==1){
if (tx==0 && tx_start ==0)
	{
		c=UART0->D;
	   if  (c != '0')
     {
		*(str+t) = c; /* read the char received */
	*(rdata+t)=*(str+t);
	 CBWrite(&cb1, *(str+t));
	 CBWrite(&cb2, *(str+t));
   t++;
	}
	else {
		tx_start=1;

	}

	}
//UART00_init();
else if(tx == 1)
{
#ifdef DEBUG
UART0->D= *(ptr1+k);
#endif

#ifdef CIRBUFFER


//CBRead(&cb2, u );

UART0->D= *(p+k);
#endif
  // delayMs(2);
   k++;
  tx=0;
}
//LED_set(c); /* and use it to set LEDs */
}

else if(echo==0){
	if(transmit==1){
		if(*(p+k)=='~')
			transmit=0;
		else{
			UART0->D= *(p+k);
			k++;
		}
	}

}
}
/* initialize UART0 to receive at 115200 Baud */
void UART0_init(void) {
SIM->SCGC4 |= 0x0400; /* enable clock for UART0 */
SIM->SOPT2 |= 0x04000000; /* use FLL output for UART Baud rate
generator */
UART0->C2 = 0; /* turn off UART0 while changing configurations */
UART0->BDH = 0x00;
UART0->BDL = 0x17; /* 115200 Baud */
UART0->C4 = 0x0F; /* Over Sampling Ratio 16 */
UART0->C1 = 0x00; /* 8-bit data */
UART0->C2 = 0x24; /* enable receive and receive interrupt*/
NVIC->ISER[0] |= 0x00001000; /* enable INT12 (bit 12 of ISER[0]) */
SIM->SCGC5 |= 0x0200; /* enable clock for PORTA */
PORTA->PCR[1] = 0x0200; /* make PTA1 UART0_Rx pin */
tx=0;
}
/* initialize all three LEDs on the FRDM board */

void UART00_init(void)
  {
	  SIM->SCGC4|=0x0400;
	  SIM->SOPT2|=0x04000000;
	  UART0->C2=0;
	  UART0->BDH=0x00;
	  UART0->BDL=0x17;
	  UART0->C4=0x0F;
	  UART0->C1=0x00;
	  UART0->C2=0x88;
	  NVIC->ISER[0] |= 0x00001000;
	  SIM->SCGC5|=0x0200;
	  PORTA->PCR[2]=0x0200;

  }


// reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007

        fpart = fpart * pow(10,afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }

}

void LOG_0(uint8_t *ptr1, uint8_t len1){
	#ifdef BBB
	for(int i=0; i<len1; i++){
		printf("%c", *(ptr1+i));
		}
	printf("\n");
	#endif
//	k=0;
#ifdef FRDM
	*(ptr1+len1)=10;
		len1+=1;
	for (int l=0;l<len1;l++){
		tx=1;
	__enable_irq();
	while(tx==1);

}
	__disable_irq();
#endif
}

void LOG_1(uint8_t *ptr1, uint8_t len2, uint8_t *param2, uint8_t data_type_size){
	*(ptr1+len2)=':';
	len2+=1;
	k=0;


	if(data_type_size==8){
		dts=2;
	}
	else if(data_type_size==16){
		dts=4;
	}
	else if(data_type_size==32){
		dts=8;
	}
	else if(data_type_size==0){
		dts=32;
	}

	#ifdef BBB
	for(int i=0; i<len2+dts; i++){
		if(*(ptr2+i)=='\0'){
			break;
		}
		printf("%c", *(ptr2+i));
		}
	printf("\n");
	#endif
   #ifdef FRDM
	dts=len2+dts;
	 for (int m=len2;m<dts+100;m++)
	   {
		   if((res[m]<48||res[m]>57)&&res[m]!=46)
		     res[m]=48;

		 }
	 for(int j=0; j<dts; j++){
	 		*(ptr1+len2+j)=*(param2+j);
	 		}
	for (int l=0;l<dts;l++)
	  {
			tx=1;
		__enable_irq();
		while(tx==1);
		__disable_irq();

      }
#endif
	//__disable_irq();
}

/*cirbuf functions*/

eBuffState BufferState(struct CirBuf *cb){

	if(CBLengthData(cb) == (cb->size - 1))
	{
		e_buffer_state = BufferFull;
                //printf("BufferFull\n");
	}
	else if(CBLengthData(cb) == 0)
	{
		e_buffer_state = BufferEmpty;
              // printf("BufferEmpty\n");
	}
	else
	{
		e_buffer_state = BufferAvailable;
                //printf("BufferAvailable\n");
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
	//printf("length of data in buffer is: %d\n", lengthData );
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
                e_buffer_state = BufferEmpty;
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
		cb->write = (cb->write + 1) & (cb->size-1);
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
	*(data+cb->read) = cb->buf[cb->read];
	cb->read = (cb->read + 1) & (cb->size - 1);
	printf("Data Read at index %d is %d\n", cb->read, *data);
	}
	else
	{
		printf("Pointer is null\n");
	}
}

void CirBuf_Transmit(uint8_t *ptrBuf, uint8_t lenBuf){
	#ifdef BBB
	for(int i=0; i<lenBuf; i++){
		printf("%c", *(ptrBuf+i));
		}
	printf("\n");
	#endif
//	k=0;
#ifdef FRDM
	*(ptrBuf+lenBuf)=10;
		lenBuf+=1;
	for (int l=0;l<lenBuf;l++){
		tx=1;
	__enable_irq();
	while(tx==1);

}
	__disable_irq();
#endif
}

/*cirbuf function ends*/
void TPM0_IRQHandler(void){
	TPM0->SC|=0x80;				//clear TOF
	count+=1;
}

void TIMER0_init(){
		__disable_irq();

		SIM->SOPT2|=0x01000000;		//use mcgfllclk
		SIM->SCGC6|=0x01000000;		//enable clock to tpm0
		TPM0->SC=0;					//disable timer
		TPM0->SC=0x06; 				//prescaler to 64
		TPM0->MOD=0xFFFF;
		TPM0->SC|=0x80;				//clear TOF
		TPM0->SC|=0x40;				//enable timeout interrupt
		NVIC->ISER[0]|=0x00020000;
		__enable_irq();
}

void UART_transmit_message(uint8_t string[]){
	p=string;
	UART00_init();
	__enable_irq();
	while(transmit==1);
}

void UART_transmit(){
	int i=0;
	for(i=0; i<strlen(transmit_data);i++){
		if(CBWrite(&cb2, *(transmit_ptr+i))==BufferFull){
			UART_transmit_message(string1);
			//transmit=0;
			break;
		}
		}
	UART00_init();
	__enable_irq();
}


void main(){
	g=malloc(128*sizeof(char));
	p=malloc(128*sizeof(char));
  u=malloc(128*sizeof(char));
	 memset(&cb1, 0, sizeof(cb1));
	 memset(&cb2, 0, sizeof(cb2));
	/*uint32_t ga[1000];
	ga[1000]=0;
	uint32_t ua[1000];
	ua[1000]=0;
	 g=ga;
	 u=ua;
for(int il=0;il<1000;il++)
{
	*(g+il)=0;
	}*/
	    cb1.buf=g;
	    cb1.size=128;
	    cb1.read=0;
	    cb1.write=0;

	    cb2.buf=p;
	   	    cb2.size=128;
	   	    cb2.read=0;
	   	    cb2.write=0;
	   	  for(int i=0;i<100;i++)
	   	  {
	   	      *(g+i)=31+i;

	   	  }

	    ftoa(n, res, 6);
if(echo==1){
#ifdef FRDM
	__disable_irq(); /* global disable IRQs */
	 UART0_init();
 	__enable_irq();
 	                     /* global enable IRQs */
while (tx_start==0);
__disable_irq();
 UART00_init();
#endif
	//LOG_0(rdata,t);


   // printf("\n\"%s\"\n", res);
   // return 0;
//char str1[5]="Hello";
//char str2[2]="12";
//uint8_t *ptr=str1;
#ifdef CIRBUFFER
CirBuf_Transmit(p, t);
#endif

#ifdef DEBUG
TIMER0_init();
TPM0->SC|=0x08;				//enable timer
//LOG_0(g, 4);
//LOG_0(time_ptr, 5);

//ftoa(n,res,6);
//  LOG_0(rdata, t);
my_memmove(g,u,10);
//my_memzero(u,10);
  TPM0->SC=0;					//disable timer
   time=3*((count*65536)+TPM0->CNT);	//time(in microseconds) 3us is the time required by TMP0 counter to increment by 1
LOG_1(rdata, t, param, 0);		//pass 0 if it is a float type
#endif
}

else if(echo==0)
	if(transmit==1){
		if(Bufferempty(&cb1)==BufferEmpty)
			UART_transmit_message(string2);
		else UART_transmit_message(string1);
	}
while (1) {
	/* UART0 receive is moved to interrupt handler*/
	}

}
