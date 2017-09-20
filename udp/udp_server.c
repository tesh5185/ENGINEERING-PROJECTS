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
	FILE *fp=NULL;
	int sock;                           //This will be our socket
	struct sockaddr_in serv, remote;     //"Internet socket address structure"
	socklen_t remote_length = sizeof(remote);       //length of the sockaddr_in structure
	int nbytes;                        //number of bytes we receive in our message
	unsigned char buffer[MAXBUFSIZE];             //a buffer to store our received message
	DIR *d;
	char delimiter[]=":";
	struct dirent *dir;
	char list[MAXBUFSIZE]; 
	char *list_ptr=&list[0];
	char num=0;
	int readbyte=0;
	d = opendir(".");
	unsigned char filedata[chunk];
	unsigned char *buffer_ptr=malloc(MAXFILESIZE*sizeof(char));
	int sent;
	int err;
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
	//nbytes = nbytes = **** CALL RECVFROM() HERE ****;
	printf("The client says %s\n", buffer);
	char *cmp, *token1,*token2;
	cmp=strstr(buffer,delimiter);
	if(cmp)
	{
		token1=strtok(buffer,delimiter);
		buffer_ptr=strtok(NULL,delimiter);
		printf("The strings are %s and %s\n",token1,buffer_ptr);
		num = strcmp(token1,"get");
		if(num==0)
		{ 
			//buffer_ptr=token2;			
			printf("Sending file %s\n",buffer_ptr);
			//fopen(buffer_ptr,"rb");
		
	
	//if(buffer=="apple\n")
	/*num = strcmp(buffer,"ls");
	memset(list,0,sizeof(list));
	if (num == 0)
	{
		printf("listing the files");	
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
	printf("List is\n %s\n",list);
	closedir(d);
	}*/

	bzero(filedata,sizeof(filedata));
	printf("filename is %s\n", buffer_ptr);
	fp=fopen(buffer_ptr,"rb");
	//if (fp!=NULL)
	//{
	//printf("Start : %p\n", fp);
	fseek(fp, 0 , SEEK_END);	
	int fsize = ftell(fp);
	printf("End : %p\n", fp);
	printf("File size is %d\n", fsize);
	fseek(fp, 0, SEEK_SET);

	//char msg[] = "orange";
	//err=fread(filedata,1,fsize, fp);
		
	/*if (ferror(fp))
	perror("Error Reading File");
	*/
	
	//}
	//else
	//printf("Error Opening file");
	rem=fsize;
	//printf("chunk=%d and remainder is %d",chunk,rem);
	//char message[MAXFILESIZE];
	//strncpy(message, filedata, fsize);
	while(rem>0)
	{	
		if(rem>chunk)
			readbyte=chunk;
		else
			readbyte=rem;
	
		size_t bytes_read=fread(filedata, sizeof(char),readbyte, fp);			
		if (bytes_read!=readbyte*sizeof(char))
		printf("Incomplete read. Read : %d, Expected : %ld\n", (int)bytes_read,(readbyte*sizeof(char)));

		printf("Sending %d bytes to client\n", chunk);
		/*if(rem>chunk)
		nbytes=sendto(sock,filedata,chunk,0,(struct sockaddr *)&remote,sizeof(remote));
		else*/
		nbytes=sendto(sock,filedata,readbyte,0,(struct sockaddr *)&remote,sizeof(remote));
		
		printf("sent size is %d\t",readbyte);
		rem-=chunk;
		printf("rem=%d\n ",rem);
		//filedata_ptr=filedata_ptr+nbytes;
		sent+=nbytes;
	}
	fclose(fp);
}
}
	if(buffer_ptr!=NULL)	
	free(buffer_ptr);

	/*printf("Sending %d bytes to client\n", strlen(filedata));
	nbytes=sendto(sock,filedata,fsize,0,(struct sockaddr *)&remote,sizeof(remote));
	*///nbytes = **** CALL SENDTO() HERE ****;
//	printf("Total byes sent=%d\n",sent);
	close(sock);
}

