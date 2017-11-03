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
char delimiter[]= " ";
void childprocess(void);
size_t size=1024;
char end[]="\n";
char endt[]="\n\n";
char *dep;
int flag=0;
struct timeval timeout;
//time_t starttime=time();
char *method,*url,*url1, *version;
clock_t start,stop;
char alive;
//char url2[15];
//char *url2_ptr=url2;
//char *buffer;
//buffer=malloc(3000*sizeof(char))
char buffer[3000],buffer1[3000],buffer2[3000],base[1024],string1[5*1024],string2[5*1024];
char conf[150],html[20],htm[20],txt[20],gif[20],jpg[20],jpeg[20],png[20],postdata[500];
char *port,*port1;
char *html1, *htm1, *txt1, *gif1, *jpg1, *jpeg1, *png1,*something,*alive1,*conn;
char connection[15];
char con_type[25], con_length[25], con_length1[10];
char type[]="Content type = ";
char length[]="Content Length = ";
char *pstring=&string1[0];
FILE *fp,*furl,*fcon;
int nbytes=1, bytes_read=0;
int server_sock,client_sock,client_sock1,c,num,i=0,abc;

/*signal handler*/
void ISRP(int argumet)
{
	close(client_sock);
	close(server_sock);
	//printf("Gracefullly exiting\n");
	exit(0);
}
void ISRC(int argumet)
{
	close(client_sock);
	close(server_sock);
	exit(0);
}
int main(int argc , char *argv[])
{
	signal(SIGINT,ISRP);
	struct sockaddr_in serv,client;
	
	
 	//Create socket
	/*make server socket*/
    server_sock = socket(AF_INET , SOCK_STREAM , 0);
    if (server_sock == -1)
    {
        printf("Could not create socket\n");
    }
    printf("Socket created\n");
	fcon=fopen("ws.conf","r");
	/*Parse config file*/
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
		alive1=strstr(dep,"Keep-Alive");
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
		if(alive1)
		{
			alive1=strtok(dep,delimiter);
			alive1=strtok(NULL,delimiter);
			alive1=strtok(NULL,delimiter);
			alive=atoi(alive1);			
			printf("File type is %d\n",alive);
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
	timeout.tv_sec=10;
	//Listen
	
    listen(server_sock , 25);
	puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
	//	exit(0);
	// accept connection from an incoming client
	//setsockopt(client_sock,SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&timeout, sizeof(struct timeval));
	while(1)
	{		
		/*accepting connections in while loop*/
		printf(" Waiting for new connections\n");
    	client_sock= accept(server_sock, (struct sockaddr *)&client, (socklen_t*)&c);
    	if (client_sock < 0)
    	{
        	perror("accept failed\n");
        	return 1;
    	}
		printf(" New Connection accepted\n return value =%d\n",client_sock);
		//start=clock();
		client_sock1=client_sock;
		/*create child processes*/
		pid_t child = fork();
		if (child == 0)
		{	close(server_sock);
			
			//child process
			childprocess();
			printf("Exited child\n");
			bytes_read=0;
			
			//flag=1;
			//close(server_sock);
			close(client_sock1);
			exit(0);
			
		}
		else if(child>0)
		{
			//while(flag==0);	
			printf("Parent process id =%d\n",getpid());		
			//printf("flag=%d",flag);
			//	flag=0;
			close(client_sock);
			//close(server_sock);
		}
	}
	close(server_sock);
	
		//printf("Length of string is %d\n",strlen(string1));
		//write(client_sock,string1,strlen(string1));
		
}

void childprocess(void)
{
	signal(SIGINT,ISRC);		
	//conn=strrchr(buffer2,':');
	//conn=strstr(buffer2,"Connection:");
	//conn=strtok(conn,"\n");
	//conn=conn+2;
	//printf("Connection is %s\n",conn);
	//while(strcmp(conn,"keep-alive")==0)
	//{
	//conn=strrchr(buffer1,':');
	//conn=conn+2;
	//strcpy(conn,"keep-alive");
	strcpy(connection,"keep-alive");
	conn=connection;
	printf("Connection is %s\n",conn);
	while(conn,strncmp(conn,"keep-alive",10)==0)
	{
	setsockopt(client_sock,SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&timeout, sizeof(struct timeval));
	bzero(buffer,sizeof(buffer));
	bzero(con_type,sizeof(con_type));
	bzero(con_length,sizeof(con_length));
	bzero(con_length1,sizeof(con_length1));
	char read_bytes=read(client_sock,buffer,sizeof(buffer));
	//if(read_bytes<0)
		//printf("500:internal error");
	
	printf("buffer is %s and bytes read is %d\n",buffer,read_bytes);
	strcpy(buffer1,buffer);
	strcpy(buffer2,buffer);
	if(sizeof(buffer2)<strlen(buffer))
	{	
		char error[]="HTTP/1.1 500 Internal Server Error: \n\n<html><body>500 Not Implemented<<error type>>: cannot allocate memory</body></html>";
		//invalid http version
		write(client_sock1,error,strlen(error));
		exit(0);
	}
	printf("Old Connection accepted\n return value =%d\n",client_sock1);
	printf("Child process id =%d\n",getpid());
	conn=strstr(buffer2,"Connection:");
	if(conn)
	{
		conn=strtok(conn,":");
		conn=strtok(NULL,"\r");
		conn=conn+1;
	
		printf("Connection is %s\n",conn);
	}
	puts("Stuck here?");
	method = strtok(buffer,delimiter);
	url = strtok(NULL,delimiter);
	version = strtok(NULL,"\n");
	printf("tokens are %s %s %s\n",method,url,version);
	
	if(strcmp(method,"GET")!=0)
	{	
		if(strcmp(method,"POST")!=0)
		{
			if(strcmp(method,"HEAD")!=0)
			{			
				printf("400 BAD Method\n");
				char error[]="HTTP/1.1 400 Bad Request\n\n<html><body>400 Bad Request Reason: Invalid Method :<<request method>></body></html>";			/*invalid Method*/
				write(client_sock1,error,strlen(error));
			}
			else
			{
				printf("501 Not Implemented");
				char error[]="HTTP/1.1 501 Not Implemented\n\n<html><body>501 Not Implemented<<error type>>:<<requested data>></body></html>";			//not implemented method
				write(client_sock1,error,strlen(error));
			}
			//continue;
		}
			
		
				
		
	}
	if(strncmp(version,"HTTP/1.1",8)!=0)
	{	
		if(strncmp(version,"HTTP/1.0",8)!=0)			
		{
			printf("400 BAD version\n");
			char error[]="HTTP/1.1 400 Bad Request\n\n<html><body>400 Bad Request Reason: Invalid HTTP-version :<<request version>></body></html>";
			//invalid http version
			write(client_sock1,error,strlen(error));
			continue;
		}
	}
	if(url[0]!='/')
	{	
		printf("400 BAD URL\n");
		char error[]="HTTP/1.1 400 Bad Request\n\n<html><body>400 Bad Request Reason: Invalid URL :<<request url>></body></html>";		
		write(client_sock1,error,strlen(error));
		exit(0);
		//invalid URL
	}		
	//char string[]="HTTP/1.1 200 OK\r\n\n<html>\n<body>\n<h1>Hello, World!</h1>\n</body>\n</html>";
	char string1[]="HTTP/1.1 200 OK\n\n";
	bzero(base,sizeof(base));
	if(strcmp(method,"POST")==0)
	{
		printf("just here\n");
		url+=1;
		//parsing for method, URL and version
		printf("buffer is %s\n",buffer1);
		something=strstr(buffer1,"Connection");
		//something+=2;
		printf("something is %s\n",something);
		something=strtok(something,"\n");
		printf("something is %s\n",something);
		something=strtok(NULL,"\n");
		something+=2;
		printf("something is %s\n",something);
		/*something=strtok(NULL,"\n");
		printf("something is %s\n",something);*/
		//something=strtok(NULL,"\n\n");
		//printf("something is %s\n",something);
		//open file pointer in append mode
		furl=fopen(url,"a+");
		if(furl)
		{
			//fwrite(end,sizeof(char),strlen(end),furl);
			fwrite(something,sizeof(char),strlen(something),furl);
			//fseek(furl,0,SEEK_SET);
			//fread(postdata,sizeof(char),sizeof(postdata),furl);
			//printf("postdata is %s\n",postdata); //post data
			fclose(furl);
		}
		else
		{
			sprintf(string2,"HTTP/1.1 404 Not Found\n\n<html><body>404 Not Found Reason URL does not exist :<<requested url>></body></html>");
			write(client_sock1,string2,strlen(string2));
		}
		
		furl=fopen(url,"r");// open in read mode
		fseek(furl, 0 , SEEK_END);
		int fsize=ftell(furl);
		fseek(furl, 0 , SEEK_SET);
		nbytes=fread(postdata,sizeof(char),sizeof(postdata),furl);
		fclose(furl);
		printf("postdata is %s and write size is %d\n",postdata,nbytes); //post data
		//write(client_sock1,string1,strlen(string1));
		write(client_sock1,postdata,nbytes);
		bzero(postdata,sizeof(postdata));
		//exit(0);
	}
	else
	{
		//first request for index.html
		num=strcmp(url,"/");
		if(num==0)
		{
			//sprintf(con_type,"Content type:text/html\n");
			//concatenate strings
			strcpy(con_type,type);
			strcat(con_type,html);
			//strcat(con_type,end);
			fp=fopen("index.html","rb");
			printf("First\n");
			fseek(fp, 0 , SEEK_END);	
			int fsize = ftell(fp);
			printf("File size is %d\n", fsize);
			fseek(fp, 0, SEEK_SET);
			sprintf(string1,"HTTP/1.1 200 Document Follows\n");	// header
			sprintf(con_length1,"%d\n",fsize);
			strcpy(con_length,length);
			strcat(con_length,con_length1);
			strcat(con_length,endt);
			printf("%s %s\n",con_type,con_length);
			//printf("%s %s\t %d %d\n",con_type,con_length,strlen(con_type),strlen(con_length));
			write(client_sock1,string1,strlen(string1));
			write(client_sock1,con_type,strlen(con_type));
			write(client_sock1,con_length,strlen(con_length));
			while((nbytes=fread(base,sizeof(char),sizeof(base),fp)) > 0)
			{	
			
				//printf("nbytes=%d\n",(int)strlen(base));
				write(client_sock1,base,nbytes);
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
			//printf("url after token =%s\n",url1);
			if (furl)
			{

				strcpy(con_type,type);
				//printf("con_type is %s\n",con_type);
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
				else
					strcat(con_type,end);

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
				strcat(con_length,"\n");
				printf("%s %s\n",con_type,con_length);
				write(client_sock1,string2,strlen(string2));
				write(client_sock1,con_type,strlen(con_type));
				write(client_sock1,con_length,strlen(con_length));
					
				while((nbytes=fread(base,sizeof(char),sizeof(base),furl)) > 0)
				{	
				
					//printf("nbytes=%d\n",nbytes);
					write(client_sock1,base,nbytes);
					bytes_read+=nbytes;
				}	
				//printf("Fourth\n");
				printf("Bytes read=%d\n",bytes_read);
				fclose(furl);
				nbytes=1;	
			}
		
			else
			{
				sprintf(string2,"HTTP/1.1 404 Not Found\n\n<html><body>404 Not Found Reason URL does not exist :<<requested url>></body></html>");		//requested file not found
				write(client_sock1,string2,strlen(string2));
			}
		}
		}
	}	
}
