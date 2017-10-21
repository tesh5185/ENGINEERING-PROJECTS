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
char end[]="\n";
char endt[]="\n\n";
char *dep;
char *method,*url,*url1, *version;
//char url2[15];
//char *url2_ptr=url2;
int main(int argc , char *argv[])
{
	int server_sock,client_sock,c,num,i=0,abc;
	struct sockaddr_in serv,client;
	char buffer[3000],base[1024],string1[5*1024],string2[5*1024];
	char conf[150],html[20],htm[20],txt[20],gif[20],jpg[20],jpeg[20],png[20];
	char *port,*port1;
	char *html1, *htm1, *txt1, *gif1, *jpg1, *jpeg1, *png1;
	char con_type[25], con_length[25], con_length1[10];
	char type[]="Content type = ";
	char length[]="Content Length = ";
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
		dep=fgets(conf,500,fcon);
		//printf("dep=%s\n",dep);	
		printf("%s\n",conf);
		port=strstr(dep,"Listen ");
		html1=strstr(dep,".html");
		htm1=strstr(dep,".htm ");
		txt1=strstr(dep,".txt");
		gif1=strstr(dep,".gif");
		jpg1=strstr(dep,".jpg");
		jpeg1=strstr(dep,".jpeg");
		png1=strstr(dep,".png");
		if(port)
		{
			port=strtok(dep,"Listen ");
			//port1=strtok(NULL,"Listen ");
			printf("Port is %s\n",port);
			abc=atoi(port);
			//char *port=NULL;
		}
		if(html1)
		{
			//printf("File type is %s\n",html1);
			html1=strtok(dep,delimiter);
			html1=strtok(NULL,delimiter);
			printf("File type is %s\n",html1);
			strcpy(html,html1);
		}
		if(htm1)
		{
			//printf("File type is %s\n",htm1);
			htm1=strtok(dep,delimiter);
			htm1=strtok(NULL,delimiter);
			printf("File type is %s\n",htm1);
			strcpy(htm,htm1);
		}
		if(txt1)
		{
			//printf("File type is %s\n",txt1);
			txt1=strtok(dep,delimiter);
			txt1=strtok(NULL,delimiter);
			printf("File type is %s\n",txt1);
			strcpy(txt,txt1);
		}
		if(gif1)
		{
			//printf("File type is %s\n",gif1);
			gif1=strtok(dep,delimiter);
			gif1=strtok(NULL,delimiter);
			printf("File type is %s\n",gif1);
			strcpy(gif,gif1);
		}
		if(jpg1)
		{
			//printf("File type is %s\n",jpg1);
			jpg1=strtok(dep,delimiter);
			jpg1=strtok(NULL,delimiter);
			printf("File type is %s\n",jpg1);
			strcpy(jpg,jpg1);
		}
		if(jpeg1)
		{
			//printf("File type is %s\n",jpeg1);
			jpeg1=strtok(dep,delimiter);
			jpeg1=strtok(NULL,delimiter);
			printf("File type is %s\n",jpeg1);
			strcpy(jpeg,jpeg1);
		}
		if(png1)
		{
			//printf("File type is %s\n",png1);
			png1=strtok(dep,delimiter);
			png1=strtok(NULL,delimiter);
			printf("File type is %s\n",png1);
			strcpy(png,png1);
		}
		i++;
	}
	printf("File type is %s\n",html);
	printf("abc is %d\n",abc);
	fclose(fcon);
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
			bzero(con_type,sizeof(con_type));
			bzero(con_length,sizeof(con_length));
			bzero(con_length1,sizeof(con_length1));
			read(client_sock,buffer,sizeof(buffer));
			/*if (buffer == NULL)
				printf("buffer null"); 
			*/
			//printf("The string is %s\n and buffer length =%d\n",buffer,(int)strlen(buffer));
			method = strtok(buffer,delimiter);
			url = strtok(NULL,delimiter);
			version = strtok(NULL,"\n");
			printf("tokens are %s %s %s\n",method,url,version);
			//strcpy(url2,url);
			//url2_ptr=&url[0];
			//printf("URL before and after %s and %s \n",url,url2);
			//printf("first character is %c\n",url2[0]);
			if(strcmp(method,"GET")!=0)
			{	
				if(strcmp(method,"POST")!=0)
				{
					if(strcmp(method,"HEAD")!=0)
					{			
						printf("400 BAD Method\n");
						char error[]="HTTP/1.1 400 Bad Request\n\n<html><body>400 Bad Request Reason: Invalid Method :<<request method>></body></html>";		
						write(client_sock,error,strlen(error));
					}
					else
					{
						printf("501 Not Implemented");
						char error[]="HTTP/1.1 501 Not Implemented\n\n<html><body>501 Not Implemented<<error type>>:<<requested data>></body></html>";				
						write(client_sock,error,strlen(error));
					}
				}
			
		
				
				exit(0);
			}
			if(strcmp(version,"HTTP/1.1\r")!=0)
			{				
				printf("400 BAD version\n");
				char error[]="HTTP/1.1 400 Bad Request\n\n<html><body>400 Bad Request Reason: Invalid HTTP-version :<<request version>></body></html>";
		
				write(client_sock,error,strlen(error));
				exit(0);
			}
			if(url[0]=='/')
			{	
				printf("400 BAD URL\n");
				char error[]="HTTP/1.1 400 Bad Request\n\n<html><body>400 Bad Request Reason: Invalid URL :<<request url>></body></html>";		
			write(client_sock,error,strlen(error));
			exit(0);
			}		
			//char string[]="HTTP/1.1 200 OK\r\n\n<html>\n<body>\n<h1>Hello, World!</h1>\n</body>\n</html>";
			//char string1[]="HTTP/1.1 200 OK\r\n";
			bzero(base,sizeof(base));
			num=strcmp(url,"/");
			if(num==0)
			{
				//sprintf(con_type,"Content type:text/html\n");
				strcpy(con_type,type);
				strcat(con_type,html);
				//strcat(con_type,end);
				fp=fopen("index.html","rb");
				printf("First\n");
				fseek(fp, 0 , SEEK_END);	
				int fsize = ftell(fp);
				printf("File size is %d\n", fsize);
				fseek(fp, 0, SEEK_SET);
				sprintf(pstring,"HTTP/1.1 200 Document Follows\n");
				sprintf(con_length1,"%d\n",fsize);
				strcpy(con_length,length);
				strcat(con_length,con_length1);
				strcat(con_length,endt);
				printf("%s %s\n",con_type,con_length);
				write(client_sock,string1,strlen(string1));
				write(client_sock,con_type,strlen(con_type));
				write(client_sock,con_length,strlen(con_length));
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
				url1=strtok(url,".");
				url1=strtok(NULL,".");
				printf("url after token =%s\n",url1);
				if (furl)
				{

					strcpy(con_type,type);
					if (strcmp(url1,"html")==0)
						strcat(con_type,html);
					else if(strcmp(url1,"htm")==0)
						strcat(con_type,html);
					else if(strcmp(url1,"txt")==0)
						strcat(con_type,txt);
					else if(strcmp(url1,"gif")==0)
						strcat(con_type,gif);
					else if(strcmp(url1,"jpg")==0)
						strcat(con_type,jpg);
					else if(strcmp(url1,"jpeg")==0)
						strcat(con_type,jpeg);
					else if(strcmp(url1,"png")==0)
						strcat(con_type,png);

					//strcat(con_type,end);
					printf("%p\n",furl);
					fseek(furl, 0 , SEEK_END);	
					int fsize = ftell(furl);
					printf("Third\n");
					printf("File size is %d\n", fsize);
					fseek(furl, 0, SEEK_SET);
					//con_type="Content"
					sprintf(string2,"HTTP/1.1 200 Document Follows\n");
					//printf("String1 is %s\n",string1);
					sprintf(con_length1,"%d\n",fsize);
					strcpy(con_length,length);
					strcat(con_length,con_length1);
					strcat(con_length,end);
					printf("%s %s\n",con_type,con_length);
					write(client_sock,string2,strlen(string2));
					write(client_sock,con_type,strlen(con_type));
					write(client_sock,con_length,strlen(con_length));
				
					while((nbytes=fread(base,sizeof(char),sizeof(base),furl)) > 0)
					{	
			
						//printf("nbytes=%d\n",nbytes);
						write(client_sock,base,nbytes);
						bytes_read+=nbytes;
					}
					//printf("Fourth\n");
					printf("Bytes read=%d\n",bytes_read);
					fclose(furl);
					nbytes=1;	
				}
				else
				{
					sprintf(string2,"HTTP/1.1 404 Not Found\n\n<html><body>404 Not Found Reason URL does not exist :<<requested url>></body></html>");
					write(client_sock,string2,strlen(string2));
				}		
			}
			printf("Exited child\n");
			bytes_read=0;
			exit(0);
			
		}
		close(client_sock);
	}
	close(server_sock);
	
		//printf("Length of string is %d\n",strlen(string1));
		//write(client_sock,string1,strlen(string1));
		
}
