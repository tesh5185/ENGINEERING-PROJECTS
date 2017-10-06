#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#define chunk 1024
/* You will have to modify the program below */
#define RTT 1000000				// Define round trip time	
#define MAXBUFSIZE 50
#define MAXFILESIZE 500000
#define encryption
/*structure for reliability*/
struct sendfile
{
	int packet_no;
	char filedata[chunk];
};
   
int ret;int itr,encrypt;
char key='c';

int main (int argc, char * argv[] )
{
	struct sendfile *getfile, *putfile;
	FILE *fget=NULL,*fput=NULL;
	int sock,current_packet;                           //This will be our socket
	struct sockaddr_in serv, remote;    		 //"Internet socket address structure"
	socklen_t remote_length = sizeof(remote);       //length of the sockaddr_in structure
	int nbytes;                        		//number of bytes we receive in our message
	unsigned char buffer[MAXBUFSIZE];             //a buffer to store our received message
	
	char delimiter[]=":";			//delimiter for get and put
	/*Directory for ls*/	
	struct dirent *dir;
	char list[MAXBUFSIZE],recbuf[chunk]; 
	
	char num,num1,num2,num3,num4;
	int readbyte=0;
	DIR *d;
	//unsigned char filedata[chunk];
	int count;
	int sent;
	int ack;
	int err,recd=0;
	int rem;
	if (argc != 2)
	{
		printf ("USAGE:  <port>\n");
		exit(1);
	}
	
	/******************
	  This code populates the sockaddr_in struct with
	  the information about our socket
	 ******************/
	bzero(&serv,sizeof(serv));                    //zero the struct
	serv.sin_family = AF_INET;                   //address family
	serv.sin_port = htons(atoi(argv[1]));        //htons() sets the port # to network byte order
	serv.sin_addr.s_addr = INADDR_ANY;           //supplies the IP address of the local machine

	//printf("Creating socket\n");
	//Causes the system to create a generic socket of type UDP (datagram)
	//if ((sock = **** CALL SOCKET() HERE TO CREATE UDP SOCKET ****) < 0)
	
	if ((sock = socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
	    printf("unable to create socket, sock : %d\n", sock);
	}
	printf("Socket successfully created\n");


	/******************
	  Once we've created a socket, we must bind that socket to the 
	  local address and port we've supplied in the sockaddr_in struct
	 ******************/
	if (bind(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0)
	{
		perror("unable to bind socket\n");
		
	}
	printf("Socket successfully binded\n");
	struct timeval timeout;
	timeout.tv_usec=RTT;		//set timeout for receive function
	
	setsockopt(sock,SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&timeout, sizeof(struct timeval));
	while(1)
	{
	//waits for an incoming message
	bzero(buffer,sizeof(buffer));
	unsigned char *buffer_ptr=malloc(MAXFILESIZE*sizeof(char));
	nbytes=recvfrom(sock,buffer,MAXBUFSIZE,0,(struct sockaddr *)&remote,&remote_length);
	printf("The client says %s\n", buffer);
	num3=strcmp(buffer,"ls");
	num4=strcmp(buffer,"exit");
	char *cmp, *token1, *token2;
	cmp=strstr(buffer,delimiter);		//check if delimiter present
	char string[10];
	nbytes=0;	
	if(cmp)
	{
		token1=strtok(buffer,delimiter);		//separate the command and filename
		token2=strtok(NULL,delimiter);
		strcpy(buffer_ptr,token2);
		printf("The strings are %s and %s\n",token1,token2);
		//printf("not here");
		/*compare strings with various commands*/
		num=strcmp(token1,"get");
		num1=strcmp(token1,"delete");
		num2=strcmp(token1,"put");
		
		if(num==0)		
		{ 	
			getfile=malloc(sizeof(struct sendfile));
			printf("Sending file %s\n",buffer_ptr);
			bzero(getfile->filedata,sizeof(getfile->filedata));	
			printf("filename is %s\n", buffer_ptr);
			/*open file for reading*/
			fget=fopen(buffer_ptr,"rb");
			fseek(fget, 0 , SEEK_END);	
			int fsize = ftell(fget);		//get end of file
			printf("End : %p\n", fget);
			printf("File size is %d\n", fsize);
			fseek(fget, 0, SEEK_SET);
			rem=fsize;ack=0;
			getfile->packet_no=1;itr=0;
			bzero(string,sizeof(string));
			//setsockopt(sock,SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&timeout, sizeof(struct timeval));
			while(rem>0)
			{	
				/*check if last byte*/
				if(rem>chunk)
					readbyte=chunk;
				else
					readbyte=rem;
				
				/*read data and verify*/
				size_t bytes_read=fread(getfile->filedata, sizeof(char),readbyte, fget);			
				if (bytes_read!=readbyte*sizeof(char))						
					printf("Incomplete read. Read : %d, Expected : %ld\n", (int)bytes_read,(readbyte*sizeof(char)));
				/*Exor the data with a key for encryption*/				
				#ifdef encryption
				for(encrypt=0;encrypt<readbyte;encrypt++)
					getfile->filedata[encrypt]^=key;
				
				#endif
				
				//printf("Sending %d bytes to client\n", chunk);
				/*send data to receiver*/
				nbytes=sendto(sock,getfile,readbyte+4,0,(struct sockaddr *)&remote,sizeof(remote));
				printf("sent packet number =%d\n",getfile->packet_no);
				/*recieve ack no*/
				ret=recvfrom(sock,string,sizeof(string),0,(struct sockaddr *)&remote,&remote_length);
				printf("ret=%d\n",ret);
				printf("string is %s",string);
				ack=atoi(string);	//convert string to integer
				printf("ACK NO =%d\n",ack);
				//if(itr==0)	exit(0);
				/*check if the same packet*/
				if(ack!=getfile->packet_no)
				{		
					nbytes=sendto(sock,getfile,readbyte+4,0,(struct sockaddr *)&remote,sizeof(remote));
				}	
				else
				{
					rem-=readbyte;			//update chunk
					itr++;
				}
				printf("sent size is %d\tsequence number=%d\n",readbyte,getfile->packet_no);
				printf("remaining size=%d\n ",rem);
				sent+=nbytes-4;
				getfile->packet_no+=1; 	//update packet number
				//if(itr==99)	exit(0);

			}
			fclose(fget);
			free(getfile);
		}
		else if(num1==0)
		{	//num=strcmp(token1,"delete");(num==0)
			int delete=remove(token2);
			if(delete==0)
				printf("%s deleted successfully\n",token2);
			else
				printf("Delete unsuccessful");
			
		}
		else if(num2==0)
		{		
			/*assign heap for put struct*/
			putfile=malloc(sizeof(struct sendfile));
			bzero(putfile->filedata,sizeof(putfile->filedata));		//set the structure as 0s
			nbytes=chunk+4;						//sum of bufffer and packet_no
			/*open file for writing*/
			fput=fopen(token2,"wb");
			recd=0;ack=0;
			current_packet=0;
			bzero(string,sizeof(string));
			/*set timeout for receive function*/
			//setsockopt(sock,SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&timeout, sizeof(struct timeval));
			while(nbytes>=chunk+4)
				{	
					
					/*receive data from client*/
					nbytes=recvfrom(sock,putfile,chunk+4,0,(struct sockaddr *)&remote,&remote_length);
					//strncpy(buffer,recbuf,nbytes);
					printf("packet number=%d\n",(int)putfile->packet_no);
					/*print packet number in string*/
					sprintf(string,"%d",(int)putfile->packet_no);
					//printf("string is %s",string);
					/*send back acknowledgement*/
					sendto(sock,string,strlen(string),0,(struct sockaddr *)&remote,remote_length);
					printf("bytes recieved=%d\n",nbytes);
					//recd+=nbytes;
					printf("bytes recieved=%d\tsequence number=%d\n",nbytes,putfile->packet_no);
					/*verify if we are getting the next packet*/
					if(putfile->packet_no==current_packet+1)
					{
						recd+=nbytes-4;
						fwrite(putfile->filedata,1,nbytes-4, fput);
					}
				current_packet=putfile->packet_no;	
				}	
				printf("received size is %d\n",recd);
				ack=0;
				fclose(fput);		//close file descriptor
				free(putfile);		//free putfile
		}
	
	}	
	else if(num3==0)
	{
	
		bzero(list,sizeof(list));
		char *list_ptr=&list[0];
		/*Open directory*/
		d = opendir(".");
		printf("listing the files\n");	
		if (d)
		{	
			while ((dir = readdir(d)) != NULL)
			{	
				strncpy(list_ptr,dir->d_name,strlen(dir->d_name));	//copy the directory list in char array
				list_ptr+= strlen(dir->d_name);				//increment array
				strncpy(list_ptr,"\n",strlen("\n"));
				list_ptr+= strlen("\n");
			}
			//send to Client
			nbytes=sendto(sock,list,strlen(list),0,(struct sockaddr *)&remote,sizeof(remote));
		}
		printf("List is\n %s\n string size=%d\n",list,(int)strlen(list));
		closedir(d);
	}
	else if(num4==0)
	{
	/*close socket*/
	close(sock);
	printf("Socket Closed\n");
	break;
	}	
		
	if(buffer_ptr!=NULL)	
	free(buffer_ptr);
	}
	/*printf("Sending %d bytes to client\n", strlen(filedata));
	nbytes=sendto(sock,filedata,fsize,0,(struct sockaddr *)&remote,sizeof(remote));
	*///nbytes = **** CALL SENDTO() HERE ****;
//	printf("Total byes sent=%d\n",sent);
	
}


