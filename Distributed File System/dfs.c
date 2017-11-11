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
#include <memory.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#define chunk 1024
#define partsize 1024*1024*1024
void ISRP(int argumet);
int sock,client_sock;
char pass[]="pass";
char fail[]="fail";
void parseconf(void);
int bytes_read,bytes=0;
char path[100],count;
char *method, *file,* file1, *username, *password,*ret,*user,*passw,*tempbuf,*tempbuf2,*partname;
char con[100];
FILE *fpp;
void ISRP(int argumet)
{
	close(client_sock);
	close(sock);
	free(user);
	free(passw);
	//printf("Gracefullly exiting\n");
	exit(0);
}

void parseconf(void)
{
	FILE *fp=fopen("dfs.conf","r");
	while(strcmp(user,username)!=0)
	{	
		//puts("in here");
		ret=fgets(con,100,fp);
		user=strtok(con," ");
		passw=strtok(NULL,"\n");
	}
	fclose(fp);	
}
int main(int argc, char *argv[])
{
	signal(SIGINT,ISRP);
	user=malloc(20*sizeof(char));
	passw=malloc(20*sizeof(char));
	partname=malloc(20*sizeof(char));
	int c,read_size;
	struct sockaddr_in serv,client;
	struct dirent *dir;
	DIR *d;
	if (argc !=3)
	{
		printf ("USAGE:  <port>\n");
		exit(1);
	}
	tempbuf=malloc(partsize*sizeof(char));
	tempbuf2=malloc(partsize*sizeof(char));
	bzero(&serv,sizeof(serv));                    //zero the struct
	serv.sin_family = AF_INET;                   //address family
	serv.sin_port = htons(atoi(argv[2]));        //htons() sets the port # to network byte order
	serv.sin_addr.s_addr = INADDR_ANY;           //supplies the IP address of the local machine
	file1=malloc(20*sizeof(char));
	if ((sock = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
	    printf("unable to create socket, sock : %d\n", sock);
	}
	printf("Socket successfully created\n");

	if( bind(sock,(struct sockaddr *)&serv , sizeof(serv)) < 0)
    {
        //print the error message
        perror("bind failed. Error\n");
        return 1;
    }
    printf("bind done on port %d\n",atoi(argv[2]));
	listen(sock , 10);
	c = sizeof(struct sockaddr_in);
	client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
	char client_message[chunk];
	
	
	//while(1)
	{
		 while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
		{
		    //Send the message back to client
		    
			printf("Read message is %s, %d\n",client_message,read_size);
			if(strncmp(client_message,"LIST",4)==0)
				method=strtok(client_message,"\n");
			else
			{
				method=strtok(client_message," ");
				file=strtok(NULL,"\n");
				strcpy(file1,file);
			}
			username=strtok(NULL," ");
			password=strtok(NULL,"\0");
			strcpy(user,fail);
			parseconf();
			printf("%s %s\n",user,passw);
			//printf("%s %s %s %s*\n",method,file,username,password);
			if (strcmp(passw,password)==0)
			{
				write(client_sock , pass ,sizeof(pass));
				if(strcmp(method,"PUT")==0)
				{
					printf("First here\n");
					bytes_read=chunk;	
					count=0;	
					while(bytes_read >= chunk)
					{
								
						bytes_read= recv(client_sock , client_message , chunk , 0);
						printf("then here\n");						
						strcpy(tempbuf,client_message);
						tempbuf+=chunk;
						bytes+=bytes_read;
						printf("bytes_read=%d\n",bytes_read);
						count++;
					}
			
					tempbuf-=count*chunk;
					printf("Message received is \n%s\n",tempbuf);				
					printf("Total bytes read are %d\n",bytes);
					write(client_sock , pass ,sizeof(pass));
					bzero(client_message,sizeof(client_message));
					bytes_read=recv(client_sock,client_message,sizeof(client_message),0);
					printf("message is %s\n",client_message);
			
			
					bzero(path,sizeof(path));
					strcpy(path,".");
					strcat(path,argv[1]);
					strcat(path,"/");
					strcat(path,user);
					//strcat(path,"/.");
					printf("file is %s\n",file1);
					//strcat(path,file1);
					//strcat(file1,client_message);
			
					strcpy(partname,".");
					strcat(partname,file1);
					strcat(partname,client_message);
					printf("Total path is %s and filename is %s\n",path,partname);
					struct stat st = {0};

					if (stat(path, &st) == -1) 
					{		
						//mode_t mask=umask(0);	
						//umask(mask);
						//printf("Mask %i\n",mask);				
						if(mkdir(path, 0700)==-1)
							perror("File not made");
						else
							puts("mkdir successful");
						//umask(mask);

					}
					strcat(path,"/");
					strcat(path,partname);
					printf("Total path is %s\n",path);
					fpp=fopen(path,"w");
					if(fpp)
					{
						fwrite(tempbuf,bytes,sizeof(char),fpp);
						fclose(fpp);
					}
					else
						perror("File open failed\n");
					bytes=0;
					bytes_read=chunk;
					//bzero(path,sizeof(path));
					count=0;
					while(bytes_read >= chunk)
					{
									
						bytes_read= recv(client_sock , client_message , chunk , 0);
						printf("then here\n");						
						strcpy(tempbuf2,client_message);
						tempbuf2+=chunk;
						bytes+=bytes_read;
						printf("bytes_read=%d\n",bytes_read);
						//printf("Message received is \n%s\n",client_message);
						count++;
					}
					tempbuf2-=count*chunk;
					printf("Message received is \n%s\n",tempbuf2);
					printf("Total bytes read are %d\n",bytes);
					write(client_sock , pass ,sizeof(pass));
			
					bytes_read=recv(client_sock,client_message,sizeof(client_message),0);
					printf("message is %s\n",client_message);
			
			
					bzero(path,sizeof(path));
					strcpy(path,".");
					strcat(path,argv[1]);
					strcat(path,"/");
					strcat(path,user);
					strcat(path,"/");
					strcat(path,".");
					printf("%s\n",file1);
					strcat(path,file1);
					strcat(path,client_message);
					printf("Total path is %s\n",path);
					fpp=fopen(path,"w");
					if(fpp)
					{	
						fwrite(tempbuf2,bytes,sizeof(char),fpp);
						fclose(fpp);
					}
					else
						perror("File open failed\n");

					bytes=0;
					bzero(path,sizeof(path));
					bzero(client_message,sizeof(client_message));
				}
				else if(strcmp(method,"LIST")==0)
				{
					bzero(path,sizeof(path));
					strcpy(path,".");
					strcat(path,argv[1]);
					strcat(path,"/");
					strcat(path,user);
					printf("Path uptill now is %s*\n",path);

	
				}
			}
			else
				write(client_sock , fail , sizeof(fail));
			
			bzero( client_message , sizeof(client_message));
			//printf("Total bytes read are %d\n",bytes);
		}
		 
		/*if(read_size == 0)
		{
		    puts("Client disconnected");
		    //fflush(stdout);
		}
		else if(read_size == -1)
		{
		    perror("recv failed");
		}*/
	}
	
}
