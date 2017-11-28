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
#define partsize 5000000
void ISRP(int argumet);
int sock,client_sock;
char pass[]="pass";
char fail[]="fail";
void parseconf(void);
int bytes_read,bytes=0;
char path[100],path1[100],count;
char *method, *file,* file1, *username, *password,*ret,*user,*passw,*tempbuf,*tempbuf2,*partname,*sub,*sub1,*token,*token1;
char con[100];
FILE *fpp;
char delimiter[]=" ";

struct partt{
char partnum;
char tempbuf[partsize];
};


char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}
char content[500],more_cont[500];
void ISRP(int argumet)
{
	close(client_sock);
	close(sock);
	free(user);
	free(passw);
	//printf("Gracefullly exiting\n");
	exit(0);
}
void xor_encrypt(char *key, char *string, int n)
{
    int i;
    int keyLength = strlen(key);
	printf("keylength is %d\n",keyLength);
    for( i = 0 ; i < n ; i++ )
    {
		if(string[i] != key[i%keyLength])
        	string[i]=string[i]^key[i%keyLength];
		else
			printf("%c",string[i]^key[i%keyLength]);
    }
}

/*void xor_encrypt(char *key, char *string, int n)
{
    int i;char ptr[n];
    int keyLength = strlen(key)/sizeof(char);
	printf("keylength is %d\n",keyLength);
    for( i = 0 ; i < n ; i++ )
    {
        ptr[i]=string[i]^'p';
    }
	puts("Encrypting");
	strncpy(string,ptr,n);
	//free(ptr);
}*/

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
	printf("IN conf file username =*%s* and password=*%s*\n",user,passw);
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
	bzero(tempbuf,sizeof(tempbuf));
	bzero(tempbuf2,sizeof(tempbuf2));
	//content=malloc(chunk*sizeof(char));
	//content_ptr=content;
	bzero(&serv,sizeof(serv));                    //zero the struct
	serv.sin_family = AF_INET;                   //address family
	serv.sin_port = htons(atoi(argv[2]));        //htons() sets the port # to network byte order
	serv.sin_addr.s_addr = INADDR_ANY;           //supplies the IP address of the local machine
	file1=malloc(20*sizeof(char));
	sub=malloc(20*sizeof(char));

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
	/*client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");*/
	char client_message[chunk];
	
	
	while(1)
	{
		client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);
	    if (client_sock < 0)
	    {
	        perror("accept failed");
	        return 1;
	    }
	    puts("Connection accepted");
	
		pid_t child = fork();
		if (child == 0)
		{
		 	while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
			{
				//Send the message back to client
				/*client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);
				if (client_sock < 0)
				{
				    perror("accept failed");
   		 	   		 return 1;
   	 			}
	   		 	puts("Connection accepted");*/
				printf("Read message is %s, %d\n",client_message,read_size);
				if(strncmp(client_message,"LIST",4)==0)
				{
					method=strtok(client_message," ");
					sub1=strtok(NULL,"\n");
					strcpy(sub,sub1);
				}	
				else
				{
					method=strtok(client_message," ");
					file=strtok(NULL," ");
					sub1=strtok(NULL,"\n");
					strcpy(file1,file);
					strcpy(sub,sub1);
				}
				username=strtok(NULL," ");
				password=strtok(NULL,"\0");
				strcpy(user,fail);
				parseconf();
				printf("%s %s\n",user,passw);
				printf("%s %s *%s* *%s* %s\n",method,file,username,password,sub1);
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
							bzero(client_message,sizeof(client_message));		
							bytes_read= recv(client_sock , client_message , chunk , 0);
							//client_message^=password;
							//xor_encrypt(password,client_message,bytes_read);
							//printf("then here\n");						
							strcpy(tempbuf,client_message);
							tempbuf+=chunk;
							bytes+=bytes_read;
							//printf("bytes_read=%d\n",bytes_read);
							count++;
						}
			
						tempbuf-=count*chunk;
						xor_encrypt(passw,tempbuf,bytes);
						//xor_encrypt(passw,tempbuf,bytes);
						printf("Message received is \n%s\n",tempbuf);				
						printf("Total bytes read are %d\n",bytes);
						write(client_sock , pass ,sizeof(pass));
						bzero(client_message,sizeof(client_message));
						bytes_read=recv(client_sock,client_message,sizeof(client_message),0);
						printf("message is \n%s\n",client_message);
			
			
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
											
							if(mkdir(path, 0700)==-1)
								perror("File not made");
							else
								puts("mkdir successful");
							//umask(mask);

						}
						strcat(path,"/");
						strcat(path,sub);
						printf("Path here should be %s\n",path);
						struct stat st1={0};
						if (stat(path, &st1) == -1) 
						{					
							if(mkdir(path, 0700)==-1)
								perror("File not made");
							else
								puts("mkdir successful");

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
							bzero(client_message,sizeof(client_message));			
							bytes_read= recv(client_sock , client_message , chunk , 0);
							//client_message^=password;
							//printf("then here\n");
													
							strcpy(tempbuf2,client_message);
							tempbuf2+=chunk;
							bytes+=bytes_read;
							//printf("bytes_read=%d\n",bytes_read);
							//printf("Message received is \n%s\n",client_message);
							count++;
						}
						tempbuf2-=count*chunk;
						xor_encrypt(passw,tempbuf2,bytes);
						//xor_encrypt(passw,tempbuf2,bytes);
						printf("Message received is \n%s\n",tempbuf2);
					
						printf("Total bytes read are %d\n",bytes);
						write(client_sock , pass ,sizeof(pass));
						bzero(client_message,sizeof(client_message));
						bytes_read=recv(client_sock,client_message,sizeof(client_message),0);
						//printf("message is %s\n",client_message);
			
			
						bzero(path,sizeof(path));
						strcpy(path,".");
						strcat(path,argv[1]);
						strcat(path,"/");
						strcat(path,user);
						strcat(path,"/");
						strcat(path,sub);
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
						strcat(path,"/");
						strcat(path,sub);
						printf("Path is %s\n",path);
						d = opendir(path);
						while ((dir = readdir(d)) != NULL)
						{	
							strcat(content,dir->d_name);
							strcat(content," ");
						
						}
						printf("Content is %s\n",content);
						write(client_sock , content ,sizeof(content));
							
					}
					else if(strcmp(method,"GET")==0)
					{
						bzero(path,sizeof(path));
						bzero(more_cont,sizeof(more_cont));
						bzero(content,sizeof(content));
						strcpy(path,".");
						strcat(path,argv[1]);
						strcat(path,"/");
						strcat(path,user);
						strcat(path,"/");
						strcat(path,sub);
						printf("Path is %s\n",path);
						d = opendir(path);
						/*while ((dir = readdir(d)) != NULL)
						{	
							strcat(content,dir->d_name);
							strcat(content," ");
						
						}*/
						while ((dir = readdir(d)) != NULL)
						{	
							if(strlen(dir->d_name)>2)
							{
								strrev(dir->d_name);
								//token=strtok(dir->d_name,".");
								token=dir->d_name+strlen(dir->d_name)-1;
								memcpy(token,"\0",1);
								strrev(dir->d_name);
								//token+strlen(dir->d_name)-1=;
								strcat(more_cont,dir->d_name);
								strcat(more_cont," ");
							}
						
						}
						printf("More Content is %s\n",more_cont);
						token=strtok(more_cont,delimiter);
						printf("Token is %s\n",token);
						if(strncmp(token,file1,strlen(file1))==0)
						{
							printf("aajao\n");
							strcat(content,token);
							strcat(content,delimiter);
						}
						while(token!=NULL)
						{
							token=strtok(NULL,delimiter);
							printf("Token is %s\n",token);
							if(token!=NULL)
							{
								if(strncmp(token,file1,strlen(file1))==0)
								{
									strcat(content,token);
									strcat(content,delimiter);
								}
							}
	

						}
						printf("Content is %s\n",content);
						bzero(more_cont,sizeof(more_cont));
						token=strtok(content,delimiter);
						token1=strtok(NULL,"\0");
						strrev(token);
						token=strtok(token,".");
						printf("Token is %s\n",token);
						strcat(more_cont,token);
						//strcat(more_cont,delimiter);
						strrev(token1);
						//strrev(token);
						token1=strtok(token1,".");
						printf("Token is %s\n",token1);
						strcat(more_cont,token1);
						/*while(token!=NULL)
						{
							strcat(more_cont,delimiter);
							strrev(token);
							token=strtok(NULL,delimiter);
							if(token!=NULL)
							{
								
								token=strtok(token,".");
								printf("Token is %s\n",token);
								strcat(more_cont,token);
								strrev(token);
							}
						
						}*/
						printf("More Content is %s\n",more_cont);
						
						write(client_sock , more_cont ,sizeof(more_cont));
						bytes_read= recv(client_sock , client_message , chunk , 0);
						printf("received message is %s\n",client_message);
						token=strtok(client_message,delimiter);
						struct partt *part;
						part=malloc(sizeof(struct partt));
						bzero(part->tempbuf,sizeof(part->tempbuf));
						if(token!=NULL)
						{
							bzero(path1,sizeof(path1));
							strcpy(path1,path);
							strcat(path1,"/.");
							strcat(path1,file1);
							strcat(path1,".");
							strcat(path1,token);	
							
							part->partnum=atoi(token);
							printf("Whole path is %s and partnum is %d\n",path1,part->partnum);
							//struct partt part;
							fpp=fopen(path1,"r");
							if(fpp)
							{
								bytes_read=fread(part->tempbuf,sizeof(char),partsize,fpp);
								bytes_read=write(client_sock , part ,bytes_read+1);
								printf("buffer is \n%s*\n",part->tempbuf);
								printf("bytes sent are %d\n",bytes_read);
								fclose(fpp);
							}
							else
								perror("FILE open failed");
						}
						bzero(part->tempbuf,sizeof(part->tempbuf));
						//while (token!=NULL)
						{
							token=strtok(NULL,delimiter);
							if(token!=NULL)
							{
								bzero(path1,sizeof(path1));
								strcpy(path1,path);
								strcat(path1,"/.");
								strcat(path1,file1);
								strcat(path1,".");
								strcat(path1,token);	
								//struct partt *part;
								//part=malloc(sizeof(struct partt));
								part->partnum=atoi(token);
								printf("Whole path is %s and partnum is %d\n",path1,part->partnum);
								//struct partt part;
								fpp=fopen(path1,"r");
								if(fpp)
								{
									bytes_read=fread(part->tempbuf,sizeof(char),partsize,fpp);
									bytes_read=write(client_sock , part ,bytes_read+1);
									printf("buffer is \n%s*\n",part->tempbuf);
									printf("bytes sent are %d\n",bytes_read);
									fclose(fpp);
								}
								else
									perror("FILE open failed");
							}

						}

						//fclose(fpp);


					}
				}
				else
					write(client_sock , fail , sizeof(fail));
			
				bzero( client_message , sizeof(client_message));
				close(sock);
				//printf("Total bytes read are %d\n",bytes);
			}close(sock);
			close(client_sock);
		}
		else if(child>0)
		{
			close(client_sock);
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
