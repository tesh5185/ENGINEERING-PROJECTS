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
#define chunk 512
#define MAXBUFSIZE 25000
#define MAXFILESIZE 50000
/* You will have to modify the program below */

int main (int argc, char * argv[])
{

	int nbytes=1;                             // number of bytes send by sendto()
	int sock;                               //this will be our socket
	FILE *fp;
	char buffer[MAXFILESIZE];
	char recbuf[chunk];
	/*char *pbuffer=malloc(MAXBUFSIZE*sizeof(char));
	if(pbuffer==NULL)
	{
		printf("malloc failed");
			
	}*/	

	//char buffer_ptr=buffer[0];
	int num=0;
	struct sockaddr_in remote,dummy;              //"Internet socket address structure"
	socklen_t dummy_length = sizeof(dummy);
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
	gets(command);
	//nbytes = **** CALL SENDTO() HERE ****;
	nbytes=sendto(sock,command,strlen(command),0,(struct sockaddr *)&remote,sizeof(remote));
	// Blocks till bytes are received
	
	struct sockaddr_in from_addr;
	int addr_length = sizeof(struct sockaddr);
	bzero(buffer,sizeof(buffer));
	//nbytes = **** CALL RECVFROM() HERE ****;  
	num=strcmp(command,"ls");
	if(num==0)
	{
		//nbytes=recvfrom(sock,buffer,MAXBUFSIZE,0,(struct sockaddr *)&dummy,&dummy_length);
		//printf("The list is %s\n", buffer);		
	}
	bzero(recbuf,sizeof(recbuf));
	//bzero(buffer,sizeof(buffer));	
	printf("reached here\n");
	nbytes=chunk;
	fp=fopen(command,"wb");
	while(nbytes>=chunk)
	{	
		nbytes=recvfrom(sock,recbuf,chunk,0,(struct sockaddr *)&dummy,&dummy_length);
		
		strncpy(buffer,recbuf,nbytes);
		printf("bytes recieved=%d\n",nbytes);
		//get_ptr=get_ptr+nbytes;
		//pbuffer+=nbytes;
		recd+=nbytes;
		fwrite(recbuf,1,nbytes, fp);
		//printf("received data is %s",buffer);
		//printf("Address f")
	}	
	//printf("%d",strlen(buffer));
	printf("received size is %d\n",recd);
	

	
	
	fclose(fp);
	//if(pbuffer)
	//free(pbuffer);
	
	close(sock);

}

