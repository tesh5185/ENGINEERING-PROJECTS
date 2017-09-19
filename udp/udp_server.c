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
#define chunk 512
/* You will have to modify the program below */

#define MAXBUFSIZE 50000
#define MAXFILESIZE 50000
int main (int argc, char * argv[] )
{

	//printf("start\n");
	FILE *fp=NULL;
	int sock;                           //This will be our socket
	struct sockaddr_in serv, remote;     //"Internet socket address structure"
	socklen_t remote_length = sizeof(remote);       //length of the sockaddr_in structure
	int nbytes;                        //number of bytes we receive in our message
	char buffer[MAXFILESIZE];             //a buffer to store our received message
	DIR *d;
	struct dirent *dir;
	char list[MAXBUFSIZE]; 
	char *list_ptr=&list[0];
	char num=0;
	d = opendir(".");
	char filedata[MAXFILESIZE];
	int err;
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
	//if(buffer=="apple\n")
	num = strcmp(buffer,"ls");
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
	}

	bzero(filedata,sizeof(filedata));
	printf("filename is %s\n", buffer);
	fp=fopen(buffer,"rb");
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
	size_t bytes_read=fread(filedata, sizeof(char), fsize, fp);	
	if (bytes_read!=fsize*sizeof(char))
		printf("Incomplete read. Read : %d, Expected : %d\n", bytes_read, (fsize*sizeof(char)));	
	/*if (ferror(fp))
	perror("Error Reading File");
	*/
	fclose(fp);
	//}
	//else
	//printf("Error Opening file");

	
	//char message[MAXFILESIZE];
	//strncpy(message, filedata, fsize);
	
	printf("Sending %d bytes to client\n", strlen(filedata));
	nbytes=sendto(sock,filedata,fsize,0,(struct sockaddr *)&remote,sizeof(remote));
	
	
	//nbytes = **** CALL SENDTO() HERE ****;
	
	close(sock);
}

