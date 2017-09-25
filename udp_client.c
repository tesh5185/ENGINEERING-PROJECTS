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
#define MAXFILESIZE 500000
#define RTT 1000000
/* You will have to modify the program below */
struct receivefile
{
   int packet_no;
   char recbuf[chunk];
};
int current_packet=0,ret;
int main (int argc, char * argv[])
{
	struct receivefile *getfile, *putfile;
	//getfile=malloc(sizeof(struct receivefile));
	int nbytes=1,rem,readbyte=0,sent,ack;                             // number of bytes send by sendto()
	int sock;                               //this will be our socket
	FILE *fget=NULL,*fput=NULL;
	char buffer[MAXFILESIZE];
	char recbuf[chunk];
	char direct[MAXBUFSIZE];
	char put[chunk];
	struct timeval timeout;
	timeout.tv_usec=RTT;

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
	nbytes=1;
	
	nbytes=sendto(sock,command,strlen(command),0,(struct sockaddr *)&remote,sizeof(remote));
	struct sockaddr_in from_addr;
	int addr_length = sizeof(struct sockaddr);
	char string[4];
	char *cmp,*token1,*token2;
	cmp=strstr(command,":");	//check if delimiter present
	printf("command is %s\n",command);
	num3=strcmp(command,"ls");
	if (cmp)
	{
		token1=strtok(command,":");
		token2=strtok(NULL,":");
		printf("cmd is %s & file is %s\n",token1,token2);
		num=strcmp(token1,"get");		//separate the command and filename
		num1=strcmp(token1,"delete");
		num2=strcmp(token1,"put");
		
		
		//num=strcmp(token1,"get");
		if(num==0)
		{	
			/*assign heap for put struct*/
			getfile=malloc(sizeof(struct receivefile));
			bzero(getfile->recbuf,sizeof(getfile->recbuf));	//set the structure as 0s
			nbytes=chunk+4;					//sum of bufffer and packet_no
			/*open file for writing*/			
			fget=fopen(token2,"wb");
			recd=0;
			setsockopt(sock,SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&timeout, sizeof(struct timeval));
			current_packet=0;
			while(nbytes>=chunk+4)
			{	
				/*receive data from client*/
				nbytes=recvfrom(sock,getfile,chunk+4,0,(struct sockaddr *)&remote,&remote_length);
				printf("packet number=%d\n",(int)getfile->packet_no);
				/*print packet number in string*/
				sprintf(string,"%d",(int)getfile->packet_no);
				/*send back acknowledgement*/
				sendto(sock,string,strlen(string),0,(struct sockaddr *)&remote,remote_length);				
				//strncpy(buffer,recbuf,nbytes);
				printf("bytes recieved=%d\tsequence number=%d\n",nbytes,getfile->packet_no);
				/*verify if we are getting the next packet*/
				if(getfile->packet_no==current_packet+1)
				{
					recd+=nbytes-4;				
					fwrite(getfile->recbuf,1,nbytes-4, fget);	
				}
				current_packet=getfile->packet_no;			
			}	
			printf("received size is %d\n",recd);
			fclose(fget);			//close file descriptor
			free(getfile);			//free getfile
		}
		else if(num2==0)
		{
			//num=strcmp(token1,"put");
			putfile=malloc(sizeof(struct receivefile));
			bzero(putfile->recbuf,sizeof(putfile->recbuf));
			/*open file for reading*/
			fput=fopen(token2,"rb");	
			fseek(fput, 0 , SEEK_END);	
			int fsize = ftell(fput);	//get end of file
			printf("File size is %d\n", fsize);
			fseek(fput, 0, SEEK_SET);
			rem=fsize;
			putfile->packet_no=1;
			while(rem>0)
			{	
				/*check if last byte*/
				if(rem>chunk)
					readbyte=chunk;
				else
					readbyte=rem;
	
				size_t bytes_read=fread(putfile->recbuf, sizeof(char),readbyte, fput);			
				if (bytes_read!=readbyte*sizeof(char))
					printf("Incomplete read. Read : %d, Expected : %ld\n", (int)bytes_read,(readbyte*sizeof(char)));

				/*read data and verify*/
				printf("Sending %d bytes to client\n", chunk);
				/*send data to receiver*/
				nbytes=sendto(sock,putfile,readbyte+4,0,(struct sockaddr *)&remote,remote_length);
				/*recieve ack no*/
				ret=recvfrom(sock,string,strlen(string),0,(struct sockaddr *)&remote,&remote_length);
				printf("ret=%d\n",ret);
				ack=atoi(string);	//convert string to integer
				printf("ACK NO =%d\n",ack);
				/*check if the same packet*/
				if(ack!=putfile->packet_no)
						nbytes=sendto(sock,putfile,readbyte+4,0,(struct sockaddr *)&remote,sizeof(remote));

				rem-=chunk;			//update chunk		
				printf("sent packet number =%d\n",putfile->packet_no);
				printf("sent size is %d\t",readbyte);
				
				printf("rem=%d\n ",rem);
				sent+=nbytes;
				putfile->packet_no+=1;	//update packet number
			}
			fclose(fput);
			free(putfile);
		}
	}
	
	else if(num3==0)	
	{	
		bzero(direct,sizeof(direct));
		//printf("command is %s\n",command);
		/*receive deirectory files from server*/
		nbytes=recvfrom(sock,direct,MAXBUFSIZE,0,(struct sockaddr *)&remote,&remote_length);
		printf("The list is %s\n",direct);		
	}
}
	//else
	//close(sock);

}


