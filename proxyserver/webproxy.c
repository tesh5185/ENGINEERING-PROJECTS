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
char site_data[1000000];
int nbytes=0;
char space[]=" ";
char *method, *url, *version, *hostname, *conn,*extra;
//char header[100]= "http://";
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
		//else
			//puts("mkdir successful");
			

	}

}

char blocked(char *host,char *ip)
{

	//printf("hostname is%s* and ip is %s*\n",host,ip );
	char hostname[50],ipaddr[50];
	strcpy(hostname,host);
	strcpy(ipaddr,ip);
	strcat(hostname,"\n");
	strcat(ipaddr,"\n");
	//printf("hostname is %s and ip is %s\n",hostname,ipaddr );
	FILE *b=fopen("blocked","r");
	//puts("inside");
	char * ptr;
	char *block=malloc(100);
	ptr=fgets(block,100,b);
	//printf("site is %s",block);
	if((strcmp(hostname,block)==0)||(strcmp(ipaddr,block)==0))
	{
		char error[]="HTTP/1.1 403 Bad Request\n\n<html><body>Error 403 Forbidden: Blocked :<<request method>></body></html>";			/*invalid Method*/
		send(client_sock,error,strlen(error),0);
				exit(0);	
	}
	//if(strcmp(host))
	while(ptr)
	{
		ptr=fgets(block,100,b);
		if(ptr)
		{
			//printf("site is %s",block);
			if((strcmp(hostname,block)==0)||(strcmp(ipaddr,block)==0))
			{
				char error[]="HTTP/1.1 403 Bad Request\n\n<html><body>Error 403 Forbidden: Blocked :<<request method>></body></html>";			/*invalid Method*/
				send(client_sock,error,strlen(error),0);
				exit(0);	
			}
		}
		
	}
	fclose(b);
	free(block);
	//printf("400 BAD Method\n");
	
}
int delete(char *path,long timeout)
{
	struct stat check;

	if(stat(path,&check)>=0)
	{
		time_t current_time;
		current_time=time(NULL);
		//printf("current time time %ld",current_time);
		//printf("Last modified time %ld",check.st_mtime);
		
		if((current_time-check.st_mtime)>timeout)
			remove(path);
	}
}
char *ipcache(char *host)
{

	char *ptr;
	char *cache=malloc(100);
	char *id; 
	bzero(cache,sizeof(cache));
	char *line=malloc(100);
	FILE *fc=fopen("cache","a");
	if(fc)
	{
		ptr=fgets(cache,100,fc);
		printf("first value is %s*\n",cache);
		while(ptr)
		{
			bzero(cache,sizeof(cache));
			ptr=fgets(cache,100,fc);
			printf("Next value is %s\n",cache);
			if(ptr)
			{
				id=strtok(ptr,space);
				id=strtok(NULL,"\n");
				printf("Hostname is %s and id is %s\n",ptr,id);
				if(strcmp(ptr,host)==0)
				{	
					printf("Hostname is %s and id is %s\n",ptr,id);
					return id;
				}
			}
		}
				//else
		struct hostent *hp = gethostbyname(host);
		bzero(line,sizeof(line));
		//printf("host is %s\n",host);
		if (hp == NULL) 
		{
		    perror("gethostbyname() failed\n");
		} 
		else
		{
				    	
			//printf("%s = ", hp->h_name);
			//printf(" is %s\n",host);
			unsigned int i=0;
			while ( hp -> h_addr_list[i] != NULL) 
			{
				char *ip;
				//ip= (( struct in_addr *)( hp -> h_addr_list[i]));
				//printf( "%s ", inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i])));
				//printf("%s %d\n",ip,inet_addr(ip) );
				i++;
			}
					    
			sprintf(line,"%s %s\n",hp->h_name,inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i-1])));
			if(strcmp(hp->h_name,host)!=0)
			{	
				fwrite(line,strlen(line),sizeof(char),fc);
			}
			
			//printf("Line is %s\n",line);
			return inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i-1]));				//{
				
					
		}   
				   

	fclose(fc);
				
	}			
	else
		perror("IP cache open failed");		//}	
			
			

		//}
		
	//}
	
	//free(cache);


}
int main(int argc, char* argv[])
{
	//puts("start");

	if (argc<3)
	{
		puts("Need a port number and a timeout");
		exit(0);
	}	
	long timm=atoi(argv[2]);
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
	//blocked();
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
			//puts("Child socket created");
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
				char *url_copy=malloc(100*sizeof(char));
				char *url_copy1=malloc(100*sizeof(char));
				char *url_copy2=malloc(100*sizeof(char));
				char *extra1=malloc(50*sizeof(char));

				//printf("HTTP client req: %s\n",sock_data);
				strcpy(sock_data1,sock_data);		
				method=strtok(sock_data,space);
				url=strtok(NULL,space);
				version=strtok(NULL,"\r\n");
				hostname=strtok(NULL,space);
				hostname=strtok(NULL,"\r\n");
				bzero(url_copy,sizeof(url_copy));
				strcpy(url_copy,url);
				url_copy=strtok(url_copy,"/");
				//url_copy=strtok(NULL,"/");
				url_copy=strtok(NULL,"\0");
				url_copy+=1;
				strcpy(url_copy1,url_copy);
				strcpy(url_copy2,url_copy);
				//printf("URL asked:%s\n",url);
				//printf("Diff datas are %s %s %s %s\n",method,url_copy1,version,hostname);
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
					/*check=time(NULL);
				    printf("checked time %ld",check);*/
					if(strlen(extra)==1)
						strcat(url_copy,"index.html");

					delete(url_copy,timm);
					/*struct stat abc;
					if(stat(url_copy,&abc)==-1)
					{
						perror("stat issue");
					}
					else
						printf("other time is %ld",abc.st_mtime);*/
					//printf("path:%sand extra is %s\n",url_copy,extra );
					FILE *fp=fopen(url_copy,"r");
					if(fp)
					{
						dsize=fread(site_data,sizeof(char),sizeof(site_data),fp);
						//printf("path:%sand extra is %s\n",url_copy,extra );
						//printf("Read data size is %d\n",dsize);
						if(dsize<0)
							perror("read failed");
						send(client_sock,site_data,dsize,0);
						printf("sent cached data\n" );
						fclose(fp);
						
						//close(client_sock);
						//exit(0);

					}
					else
					{	
						bzero(url_copy2,sizeof(url_copy2));
						
						strcpy(extra1,extra);
						
						//printf("here %s and %s\n",extra,url_copy1 );
						url_copy1=strtok(url_copy1,"/");
						
						//printf("url copy is %s\n",url_copy1 );
						//blocked(url_copy1);
						strcpy(url_copy2,url_copy1);
						makedir(url_copy2);
						
						if(strlen(extra1)==1)
							{}//puts("index.html");
						else
						{
							while(url_copy1!=NULL)
							{
								url_copy1=strtok(NULL,"/");
								//printf("url copy is %s\n",url_copy1 );
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
						char *abc =ipcache(hostname);
						printf("return value%s\n",abc);
						/*
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
					       	//printf("\n");
					       	*/
					       	blocked( hostname,abc);
					       	ssock = socket(AF_INET , SOCK_STREAM , 0);

			    		   	if(ssock == -1)
			    		   	{
			        			printf("Could not create socket\n");
			    			}
			    			//puts("Remote socket created");
			    		   	websocket.sin_family = AF_INET;
			    		   	websocket.sin_addr.s_addr = inet_addr(abc);
			    			//websocket.sin_addr.s_addr = inet_addr(inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i-1])));
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
					       	FILE *fw=fopen(url_copy2,"w");
					       	if(fw)
					       	{
					       		dsize=fwrite(site_data,sizeof(char),ssize,fw);
					       		fclose(fw);
					       		//printf("written size is %d\n",dsize);
					       	}
					       	else
					       		puts("File open failed");
					       	//printf("size is %d and data is %s\n",ssize,site_data);
					       	send(client_sock,site_data,ssize,0);
					       	//printf("sent\n");
					       	close(ssock);
					       	
				       //	}
				       
				   	}

					close(client_sock);
					exit(0);
				   	
			    }
			    else
			    {
				    printf("400 BAD Method\n");
					char error[]="HTTP/1.1 400 Bad Request\n\n<html><body>400 Bad Request Reason: Invalid Method :<<request method>></body></html>";			/*invalid Method*/
					send(client_sock,error,strlen(error),0);
					//continue;
				}
			    
			}

		}
		else if(child>0)
		{
			//close(ssock);
			close(client_sock);
			//puts("parent");

		}		
	}

}