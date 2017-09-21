#include <sys/types.h>
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
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#define chunk 512
/* You will have to modify the program below */

#define MAXBUFSIZE 500
#define MAXFILESIZE 10000
int main (int argc, char * argv[] )
{

	//printf("start\n");
	FILE *fget=NULL,*fput=NULL;
	int sock;                           //This will be our socket
	struct sockaddr_in serv, remote;     //"Internet socket address structure"
	socklen_t remote_length = sizeof(remote);       //length of the sockaddr_in structure
	int nbytes;                        //number of bytes we receive in our message
	unsigned char buffer[MAXBUFSIZE];             //a buffer to store our received message
	DIR *d;
	char delimiter[]=":";
	struct dirent *dir;
	char list[MAXBUFSIZE],recbuf[chunk]; 
	char *list_ptr=&list[0];
	char num,num1,num2,num3;
	int readbyte=0;
	d = opendir(".");
	unsigned char filedata[chunk];
	unsigned char *buffer_ptr=malloc(MAXFILESIZE*sizeof(char));
	int sent;
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
	

	//waits for an incoming message
	bzero(buffer,sizeof(buffer));
	nbytes=recvfrom(sock,buffer,MAXBUFSIZE,0,(struct sockaddr *)&remote,&remote_length);
	printf("The client says %s\n", buffer);
	char *cmp, *token1, *token2;
	cmp=strstr(buffer,delimiter);
	if(cmp)
	{
		token1=strtok(buffer,delimiter);
		token2=strtok(NULL,delimiter);
		strcpy(buffer_ptr,token2);
		printf("The strings are %s and %s\n",token1,token2);
		//printf("not here");
		num=strcmp(token1,"get");
		num1=strcmp(token1,"delete");
		num2=strcmp(token1,"put");
		num3=strcmp(buffer,"ls");
		if(num==0)		//if(strcmp(token1,"get")==0);
		{ 	
				
			printf("Sending file %s\n",buffer_ptr);
			bzero(filedata,sizeof(filedata));	
			printf("filename is %s\n", buffer_ptr);
			fget=fopen(buffer_ptr,"rb");
			fseek(fget, 0 , SEEK_END);	
			int fsize = ftell(fget);
			printf("End : %p\n", fget);
			printf("File size is %d\n", fsize);
			fseek(fget, 0, SEEK_SET);
			rem=fsize;
			while(rem>0)
			{	
				if(rem>chunk)
					readbyte=chunk;
				else
					readbyte=rem;
	
				size_t bytes_read=fread(filedata, sizeof(char),readbyte, fget);			
				if (bytes_read!=readbyte*sizeof(char))
					printf("Incomplete read. Read : %d, Expected : %ld\n", (int)bytes_read,(readbyte*sizeof(char)));

				printf("Sending %d bytes to client\n", chunk);
				nbytes=sendto(sock,filedata,readbyte,0,(struct sockaddr *)&remote,sizeof(remote));
		
				printf("sent size is %d\t",readbyte);
				rem-=chunk;
				printf("rem=%d\n ",rem);
				sent+=nbytes;
			}
			fclose(fget);
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
			printf("please send");
			//num=strcmp(token1,"put");
			nbytes=chunk;
			fput=fopen(token2,"wb");
			while(nbytes>=chunk)
				{	
					nbytes=recvfrom(sock,recbuf,chunk,0,(struct sockaddr *)&remote,&remote_length);
					//strncpy(buffer,recbuf,nbytes);
					printf("bytes recieved=%d\n",nbytes);
					recd+=nbytes;
					fwrite(recbuf,1,nbytes, fput);
			
				}	
				printf("received size is %d\n",recd);
				fclose(fput);
		}
	
	}	
	else if(num3==0)
	{
		//num=strcmp(buffer,"ls");
		//printf("num=%d",num);
		//if(strcmp(buffer,"ls")==0);
		//if(num==0)
		//{	
		//printf("buffer is %s\n",buffer);
		memset(list,0,sizeof(list));
		printf("listing the files\n");	
		if (d)
		{
			while ((dir = readdir(d)) != NULL)
			{
				//printf("Directory entry : %s\n",dir->d_name);
				//printf("%p\n",list);
				strncpy(list_ptr,dir->d_name,strlen(dir->d_name));
				//printf("%p\n",list);
				list_ptr+= strlen(dir->d_name);
				strncpy(list_ptr,"\n",strlen("\n"));
				list_ptr+= strlen("\n");
			}
			nbytes=sendto(sock,list,strlen(list),0,(struct sockaddr *)&remote,sizeof(remote));
		}
		printf("List is\n %s\n string size=%d\n",list,(int)strlen(list));
		closedir(d);
	}

		if(buffer_ptr!=NULL)	
		free(buffer_ptr);

	/*printf("Sending %d bytes to client\n", strlen(filedata));
	nbytes=sendto(sock,filedata,fsize,0,(struct sockaddr *)&remote,sizeof(remote));
	*///nbytes = **** CALL SENDTO() HERE ****;
//	printf("Total byes sent=%d\n",sent);
	close(sock);
}


