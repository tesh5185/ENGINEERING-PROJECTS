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
char delimiter[]= " ";
size_t size=1024;
int dep;
char *method,*url,*url1,*version;
int main(int argc , char *argv[])
{
	int server_sock,client_sock,c,num,i=1,abc;
	struct sockaddr_in serv,client;
	char buffer[3000],base[1024],string1[5*1024],string2[5*1024];
	char conf[20];
	char *port,*port1;
	//char (*conf)[size];
	//conf=(char *)(size*sizeof(char));
	char *pstring=&string1[0];
	FILE *fp,*furl,*fcon;
	int nbytes=1, bytes_read=0;
 	//Create socket
    server_sock = socket(AF_INET , SOCK_STREAM , 0);
    if (server_sock == -1)
    {
        printf("Could not create socket\n");
    }
    printf("Socket created\n");
	fcon=fopen("ws.conf","r");
	while(i<16)
	{
		dep=fgets(conf,100,fcon);
		printf("dep=%d\n",dep);	
		printf("%s\n",conf);
		//if(i==2)
		//{
			port=strstr(conf,"Listen ");
			
			if(port)
			{
				port=strtok(conf,"Listen ");
				//port1=strtok(NULL,"Listen ");
				printf("port is %s\n",port);
				abc=atoi(port);
			//char *port=NULL;
			}
			//printf("%s\n",(char *)conf);
		//}
		i++;
	}
	printf("abc is %d\n",abc);
    //Prepare the sockaddr_in structure
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons( abc );
	//Bind
    if( bind(server_sock,(struct sockaddr *)&serv , sizeof(serv)) < 0)
    {
        //print the error message
        perror("bind failed. Error\n");
        return 1;
    }
    printf("bind done on port %d\n",abc);

	//Listen
	
    listen(server_sock , 15);
	puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
	//	exit(0);
	 //accept connection from an incoming client
	while(1)
	{		
    	client_sock= accept(server_sock, (struct sockaddr *)&client, (socklen_t*)&c);
    	if (client_sock < 0)
    	{
        	perror("accept failed\n");
        	return 1;
    	}
		printf(" New Connection accepted\n return value =%d\n",client_sock);
		
		pid_t child = fork();
		
		if (child == 0)
		{	
			bzero(buffer,sizeof(buffer));
			read(client_sock,buffer,sizeof(buffer));
			if (buffer == NULL)
				printf("buffer null"); 
	
			//printf("The string is %s\n and buffer length =%d\n",buffer,(int)strlen(buffer));
			method = strtok(buffer,delimiter);
			url = strtok(NULL,delimiter);
			version = strtok(NULL,"\n");
			printf("tokens are %s %s %s\n",method,url,version);
			char string[]="HTTP/1.1 200 OK\r\n\n<html>\n<body>\n<h1>Hello, World!</h1>\n</body>\n</html>";
			//char string1[]="HTTP/1.1 200 OK\r\n";
			bzero(base,sizeof(base));
			num=strcmp(url,"/");
			if(num==0)
			{
				
				fp=fopen("index.html","rb");
				printf("First\n");
				fseek(fp, 0 , SEEK_END);	
				int fsize = ftell(fp);
				printf("File size is %d\n", fsize);
				fseek(fp, 0, SEEK_SET);
				sprintf(pstring,"HTTP/1.1 200 OK\n\n");
				write(client_sock,string1,strlen(string1));
				while((nbytes=fread(base,sizeof(char),sizeof(base),fp)) > 0)
				{	
			
					//printf("nbytes=%d\n",(int)strlen(base));
					write(client_sock,base,nbytes);
					bytes_read+=nbytes;
				}
			
				
				fclose(fp);
				nbytes=1;
				printf("Bytes read=%d\n",bytes_read);
				
			}
			else
			{	
				url+=1;	
				printf("Second\t and url is %s\n",url);
				bzero(string2,sizeof(string2));
				furl=fopen(url,"rb");
				if (furl)
				{
					printf("%p\n",furl);
					fseek(furl, 0 , SEEK_END);	
					int fsize = ftell(furl);
					printf("Third\n");
					printf("File size is %d\n", fsize);
					fseek(furl, 0, SEEK_SET);
				
					sprintf(string2,"HTTP/1.1 200 OK\n\n");
					printf("String1 is %s\n",string1);
					write(client_sock,string2,strlen(string2));
					/*if((nbytes=fread(base,sizeof(char),sizeof(base),furl)) < 0)
						perror("read error");*/
				
					while((nbytes=fread(base,sizeof(char),sizeof(base),furl)) > 0)
					{	
			
						//printf("nbytes=%d\n",nbytes);
						write(client_sock,base,nbytes);
						bytes_read+=nbytes;
					}
					printf("Fourth\n");
					printf("Bytes read=%d\n",bytes_read);
					fclose(furl);
					nbytes=1;	
				}	
			}
			printf("Exited child\n");
			bytes_read=0;
			exit(0);
			
		}
		close(client_sock);
	}
	close(server_sock);
	fclose(fcon);
		//printf("Length of string is %d\n",strlen(string1));
		//write(client_sock,string1,strlen(string1));
		
}
