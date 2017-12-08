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
#include <time.h>
#include <signal.h>
#include <sys/stat.h>

char *site="www.google.com";
int client_sock,c,server_sock,ssock;
char sock_data[5000],sock_data1[5000],final_data[1000];
char site_data[100000];
int nbytes=0;
char space[]=" ";
char *method, *url, *version, *hostname, *conn,*extra;
char header[100]= "http://";
int dsize,ssize;
void ISRP(int argumet)
{
	close(client_sock);
	close(server_sock);
	//printf("Gracefullly exiting\n");
	exit(0);
}
void makedir(char *path)
{
	struct stat st = {0};

	if (stat(path, &st) == -1) 
	{		
											
		if(mkdir(path, 0700)==-1)
			perror("File not made");
		else
			puts("mkdir successful");
			

	}

}
int main(int argc, char* argv[])
{
	//puts("start");

	if (argc<2)
	{
		puts("Need a port number");
		exit(0);
	}	

	signal(SIGINT,ISRP);
	struct sockaddr_in serv,websocket,client;
	//socklen_t socket_length = sizeof(websocket);
	//Create socket
	//make server socket
    server_sock = socket(AF_INET , SOCK_STREAM , 0);
    if (server_sock == -1)
    {
        printf("Could not create socket\n");
    }
	if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
    	perror("setsockopt(SO_REUSEADDR) failed");
    printf("Server Socket created\n");
    memset(&serv,0,sizeof(serv));
	serv.sin_family = AF_INET;
    serv.sin_addr.s_addr =INADDR_ANY;
    serv.sin_port = htons(atoi(argv[1]));
    //serv.sin_addr.s_addr = inet_addr("8.8.8.8");
    //serv.sin_port = htons(80);
	//Bind
    if( bind(server_sock,(struct sockaddr *)&serv , sizeof(serv)) < 0)
    {
        //print the error message
        perror("bind failed. Error\n");
        return 1;
    }
	puts("Bind done");
	
	
	listen(server_sock , 20);
	puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
	while(1)
	{
		/*
	    }*/
		//puts("Inside while");
		client_sock= accept(server_sock, (struct sockaddr *)&client, (socklen_t*)&c);
		//puts("New connection accepted");
		pid_t child =fork();
		if (child==0)
		{
			//close(server_sock);
			puts("Child socket created");
		    if (client_sock < 0)
		    {
		       	perror("accept failed\n");
		       	return 1;
		   	}
			else
			{
				//close(server_sock);
				bzero(sock_data , sizeof(sock_data));
				//printf(" New Connection accepted\n return value =%d\n",client_sock);
				nbytes=recvfrom(client_sock , sock_data , sizeof(sock_data),0,(struct sockaddr *)&client, (socklen_t*)&c);
				//printf("data is %s\n",sock_data);
				char *url_copy=malloc(70*sizeof(char));
				char *url_copy1=malloc(70*sizeof(char));
				char *url_copy2=malloc(70*sizeof(char));
				char *extra1=malloc(25*sizeof(char));
				//printf("HTTP client req: %s\n",sock_data);
				strcpy(sock_data1,sock_data);		
				method=strtok(sock_data,space);
				url=strtok(NULL,space);
				version=strtok(NULL,"\r\n");
				hostname=strtok(NULL,space);
				hostname=strtok(NULL,"\r\n");
				strcpy(url_copy,url);
				url_copy=strtok(url_copy,"/");
				//url_copy=strtok(NULL,"/");
				url_copy=strtok(NULL,"\0");
				url_copy+=1;
				strcpy(url_copy1,url_copy);
				strcpy(url_copy2,url_copy);
				//printf("URL asked:%s\n",url);
				printf("Diff datas are %s %s %s %s\n",method,url_copy1,version,hostname);
				conn=strstr(sock_data1,"Connection");
				if(conn)
					conn=strtok(conn,"\r\n");
				//printf("Conn is %s*\n",conn);
				bzero(final_data,sizeof(final_data));
				sprintf(final_data,"%s %s %s\r\nHost: %s\r\n%s\r\n\r\n",method,url,version,hostname,conn);
				//printf("sending data %s\n",final_data);
				//strcat(header,hostname);
				//printf("header is %s\n",header);
				if(strcmp(method,"GET")==0)
				{

					bzero(site_data,sizeof(site_data));
					extra=strrchr(url_copy2,'/');
					if(strlen(extra)==1)
						strcat(url_copy,"index.html");
					printf("path:%sand extra is %s\n",url_copy,extra );
					FILE *fp=fopen(url_copy,"rb");
					if(fp)
					{
						dsize=fread(site_data,sizeof(site_data),sizeof(char),fp);
						//printf("Read data is%s\n",site_data);
						if(dsize<0)
							perror("read failed");
						send(client_sock,site_data,dsize,0);
						printf("sending cached data\n" );


						fclose(fp);
					}
					else
					{	
						bzero(url_copy2,sizeof(url_copy2));
						
						strcpy(extra1,extra);
						
						printf("here %s and %s\n",extra,url_copy1 );
						url_copy1=strtok(url_copy1,"/");
						
						printf("url copy is %s\n",url_copy1 );
						strcpy(url_copy2,url_copy1);
						makedir(url_copy2);
						/*struct stat st = {0};

						if (stat(url_copy1, &st) == -1) 
						{		
											
							if(mkdir(url_copy1, 0700)==-1)
								perror("File not made");
							else
								puts("mkdir successful");
							//umask(mask);

						}*/
						//extra=strrchr(url_copy1,'/');
						if(strlen(extra1)==1)
							puts("index.html");
						else
						{
							while(url_copy1!=NULL)
							{
								url_copy1=strtok(NULL,"/");
								printf("url copy is %s\n",url_copy1 );
								if(url_copy1!=NULL)
								{
									if(strchr(url_copy1,'.')==NULL)
									{
										strcat(url_copy2,"/");
										strcat(url_copy2,url_copy1);
										makedir(url_copy2);
									}
								}


							}
						}
						
						struct hostent *hp = gethostbyname(hostname);

					    if (hp == NULL) 
					    {
					       perror("gethostbyname() failed\n");
					    } 
					    else
					    {
					       	//printf("%s = ", hp->h_name);
					       	unsigned int i=0;
					       	while ( hp -> h_addr_list[i] != NULL) 
					       	{
					       		char *ip;
					        	//ip= (( struct in_addr *)( hp -> h_addr_list[i]));
					        	//printf( "%s ", inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i])));
					        	//printf("%s %d\n",ip,inet_addr(ip) );
					        	i++;
					       	}
					       	printf("\n");
					       	ssock = socket(AF_INET , SOCK_STREAM , 0);

			    		   	if(ssock == -1)
			    		   	{
			        			printf("Could not create socket\n");
			    			}
			    			//puts("Remote socket created");
			    		   	websocket.sin_family = AF_INET;
			    			websocket.sin_addr.s_addr = inet_addr(inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i-1])));
			    			//websocket.sin_addr.s_addr=inet_addr("151.101.48.81");
			    			websocket.sin_port = htons(80);
			    			/*if( bind(ssock,(struct sockaddr *)&websocket , sizeof(websocket)) < 0)
			    			{
			      				//print the error message
			        			perror("bind failed. Error\n");
			        			return 1;
			    			}
							puts("Bind done");*/
							if (connect(ssock , (struct sockaddr *)&websocket , sizeof(websocket)) < 0)
							{
								perror("connect failed. Error");
							}
							//puts("website connected");
							//bzero(site_data,sizeof(site_data));
							//printf("Request Message: %s\n", sock_data1);

					       	dsize=send(ssock,final_data,strlen(final_data),0);
					       	sleep(1);
					       	ssize=recv(ssock, site_data , sizeof(site_data),0);
					       	strcat(url_copy2,extra1);
					       	if(strlen(extra1)==1)
					       		strcat(url_copy2,"index.html");

					       	//printf("the total path is %s\n",url_copy2);
					       	FILE *fw=fopen(url_copy2,"wb");
					       	if(fw)
					       	{
					       		fwrite(site_data,sizeof(char),ssize,fw);
					       		fclose(fw);
					       	}
					       	else
					       		puts("File open failed");
					       	//printf("size is %d and data is %s\n",ssize,site_data);
					       	send(client_sock,site_data,ssize,0);
					       	//printf("sent\n");
					       	
				       	}
				       
				   	}
				   	
			    }
			    
			}
			close(ssock);
					close(client_sock);
					exit(0);
		}
		else if(child>0)
		{
			//close(ssock);
			close(client_sock);
			//puts("parent");

		}		
	}

}
