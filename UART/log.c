#include "log.h"

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