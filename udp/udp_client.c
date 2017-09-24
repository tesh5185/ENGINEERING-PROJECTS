#include <sys/socket.h>
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
#include <errno.h>
#include <string.h>
#define chunk 1024
#define MAXBUFSIZE 25000
#define MAXFILESIZE 5000000
#define RTT 500000
/* You will have to modify the program below */
struct receivefile
{
   int packet_no;
   char recbuf[chunk];
};
int current_packet=0,ret;
int main (int argc, char * argv[])
{
	struct receivefile *getfile;
	getfile=malloc(sizeof(struct receivefile));
	int nbytes=1,rem,readbyte=0,sent;                             // number of bytes send by sendto()
	int sock;                               //this will be our socket
	FILE *fget=NULL,*fput=NULL;
	char buffer[MAXFILESIZE];
	char recbuf[chunk];
	char direct[MAXBUFSIZE];
	char put[chunk];
	struct timeval timeout;
	timeout.tv_usec=RTT;
	setsockopt(sock,SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&timeout, sizeof(struct timeval));
	/*char *pbuffer=malloc(MAXBUFSIZE*sizeof(char));
	if(pbuffer==NULL)
	{
		printf("malloc failed");
			
	}*/	

	//char buffer_ptr=buffer[0];
	char num,num1,num2,num3;
	struct sockaddr_in remote,dummy;              //"Internet socket address structure"
	socklen_t remote_length = sizeof(remote);
	//char get[MAXFILESIZE];
	//char *get_ptr=&get[0];
	int recd;
	if (argc < 3)
	{
		printf("USAGE:  <server_ip> <server_port>\n");
		exit(1);
	}

	/******************
	  Here we populate a sockaddr_in struct with
	  information regarding where we'd like to send our packet 
	  i.e the Server.
	 ******************/
	bzero(&remote,sizeof(remote));               //zero the struct
	remote.sin_family = AF_INET;                 //address family
	remote.sin_port = htons(atoi(argv[2]));      //sets port to network byte order
	remote.sin_addr.s_addr = inet_addr(argv[1]); //sets remote IP address

	//Causes the system to create a generic socket of type UDP (datagram)
	//if ((sock = **** CALL SOCKET() HERE TO CREATE A UDP SOCKET ****) < 0)
	if ((sock = socket(AF_INET,SOCK_DGRAM,0)) < 0)	
	{
		printf("unable to create socket");
	}
	printf("Socket successfully created\n");
	
	/******************
	  sendto() sends immediately.  
	  it will report an error if the message fails to leave the computer
	  however, with UDP, there is no error if the message is lost in the network once it leaves the computer.
	 ******************/
	char command[MAXBUFSIZE];
	while(1)
	{
	gets(command);

	//char command[]="ls";
	
	//nbytes = **** CALL SENDTO() HERE ****;
	nbytes=sendto(sock,command,strlen(command),0,(struct sockaddr *)&remote,sizeof(remote));
	struct sockaddr_in from_addr;
	int addr_length = sizeof(struct sockaddr);
	char string[4];
	char *cmp,*token1,*token2;
	cmp=strstr(command,":");
	//bzero(token1,sizeof(token1));
	//token1=command;
	//bzero(token1,sizeof(token1));
	printf("command is %s\n",command);
	num3=strcmp(command,"ls");
	if (cmp)
	{
		token1=strtok(command,":");
		token2=strtok(NULL,":");
		printf("cmd is %s & file is %s\n",token1,token2);
		num=strcmp(token1,"get");
		num1=strcmp(token1,"delete");
		num2=strcmp(token1,"put");
		
		
		//num=strcmp(token1,"get");
		if(num==0)
		{
			//printf("num=%d",num);
			bzero(getfile->recbuf,sizeof(getfile->recbuf));
			nbytes=chunk+4;
			fget=fopen(token2,"wb");
			while(nbytes>=chunk+4)
			{	
				nbytes=recvfrom(sock,getfile,chunk+4,0,(struct sockaddr *)&remote,&remote_length);
				printf("ret=%d\n",ret);
				sprintf(string,"%d",getfile->packet_no);
				sendto(sock,string,strlen(string),0,(struct sockaddr *)&remote,remote_length);				
				//strncpy(buffer,recbuf,nbytes);
				printf("bytes recieved=%d\tsequence number=%d\n",nbytes,getfile->packet_no);
				if(getfile->packet_no==current_packet+1)
				{
					recd+=nbytes-4;
					fwrite(getfile->recbuf,1,nbytes-4, fget);
				}
				current_packet=getfile->packet_no;			
			}	
			printf("received size is %d\n",recd);
			fclose(fget);
		}
		else if(num2==0)
		{
			//num=strcmp(token1,"put");
			fput=fopen(token2,"rb");	
			fseek(fput, 0 , SEEK_END);	
			int fsize = ftell(fput);
			printf("File size is %d\n", fsize);
			fseek(fput, 0, SEEK_SET);
			rem=fsize;
			while(rem>0)
			{	
				if(rem>chunk)
					readbyte=chunk;
				else
					readbyte=rem;
	
				size_t bytes_read=fread(put, sizeof(char),readbyte, fput);			
				if (bytes_read!=readbyte*sizeof(char))
					printf("Incomplete read. Read : %d, Expected : %ld\n", (int)bytes_read,(readbyte*sizeof(char)));

				printf("Sending %d bytes to client\n", chunk);
				nbytes=sendto(sock,put,readbyte,0,(struct sockaddr *)&remote,remote_length);
		
				printf("sent size is %d\t",readbyte);
				rem-=chunk;
				printf("rem=%d\n ",rem);
				sent+=nbytes;
			}
			fclose(fput);

		}
	}
	



	
	//num=strcmp(command,"ls");nbytes=0;
	//if(strcmp(command,"ls")==0);
	else if(num3==0)	
	{	
		bzero(direct,sizeof(direct));
		//printf("command is %s\n",command);
		nbytes=recvfrom(sock,direct,MAXBUFSIZE,0,(struct sockaddr *)&remote,&remote_length);
		printf("The list is %s\n",direct);		
	}
	}
	//else
	//close(sock);

}


