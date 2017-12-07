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

char *site="www.google.com";
int client_sock,c,server_sock,ssock;
char sock_data[5000],sock_data1[5000],final_data[1000];
char site_data[100000];
int nbytes=0;
char space[]=" ";
char *method, *url, *version, *hostname, *conn;
char header[100]= "http://";
void ISRP(int argumet)
{
	close(client_sock);
	close(server_sock);
	//printf("Gracefullly exiting\n");
	exit(0);
}
int main(int argc, char* argv[])
{
	//puts("start");
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
	/*struct hostent *hp = gethostbyname(site);

    if (hp == NULL) {
       printf("gethostbyname() failed\n");
    } else {
       printf("%s = ", hp->h_name);
       unsigned int i=0;
       while ( hp -> h_addr_list[i] != NULL) {
          printf( "%s ", inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i])));
          i++;
       }
       printf("\n");
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
			//printf("HTTP client req: %s\n",sock_data);
			strcpy(sock_data1,sock_data);		
			method=strtok(sock_data,space);
			url=strtok(NULL,space);
			version=strtok(NULL,"\r\n");
			hostname=strtok(NULL,space);
			hostname=strtok(NULL,"\r\n");
			//printf("URL asked:%s\n",url);
			//printf("Diff datas are %s %s %s %s\n",method,url,version,hostname);
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
			       	int dsize=send(ssock,final_data,strlen(final_data),0);
			       	sleep(1);
			       	int ssize=recv(ssock, site_data , sizeof(site_data),0);
			       	//printf("size is %d and data is %s\n",ssize,site_data);
			       	send(client_sock,site_data,ssize,0);
			       	//printf("sent\n");
			       	close(ssock);
			       	close(client_sock);
			       	exit(0);
		       }
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
