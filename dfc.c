#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <openssl/md5.h>
#include <stdbool.h>
#define partsize 5000000
int senddata(int socket,char* buffer,size_t length,struct sockaddr_in server);
int receivedata(int socketa,char* buffer,size_t length);
int sendpart(char *buffer,int socket,int partno,struct sockaddr_in server);
char *part1,*part2,*part3,*part4,*ret,*con,*dfs1,*dfs2,*dfs3,*dfs4, *user, *pass, *command, *file,*tempbuf, *sometoken,*sometoken1;
char *delimiter=" ";
const int chunk=1024;
void connecttoservers(void);
int authenticate(int socketa,struct sockaddr_in server);
struct sockaddr_in server1,server2,server3,server4;
int sock1,sock2,sock3,sock4,temp,rem_bytes,fsize;
uint16_t md5,mod;
bool flag=false;
//int sendrec(socket,)
char *DFS1, *DFS2, *DFS3, *DFS4,*USER, *PASS;
char reply[2000],content1[500],content2[500],content3[500],content4[500];
char argument[100],argument1[100];
char sub1[]=".1";
char sub2[]=".2";
char sub3[]=".3";
char sub4[]=".4";
int psize,returnval1,returnval2,returnval3,returnval4,bytes_sent;
char bss[100][50],ccc[100][50];
void connecttoservers(void)
{
	
		
	if (connect(sock1 , (struct sockaddr *)&server1 , sizeof(server1)) < 0)
	{
		perror("connect failed. Error");
	}
	else	 
		puts("Connected to Server1");
	if (connect(sock2 , (struct sockaddr *)&server2 , sizeof(server2)) < 0)
	{
		perror("connect failed. Error");
	}
	else	 
		puts("Connected to server 2");
	if (connect(sock3 , (struct sockaddr *)&server3 , sizeof(server3)) < 0)
	{
		perror("connect failed. Error");
	}
	else	
		puts("Connected to server 3");
	if (connect(sock4 , (struct sockaddr *)&server4 , sizeof(server4)) < 0)
	{
		perror("connect failed. Error");
	}
	else
		puts("Connected to server 4");

}
int connecttoserver(int socket,struct sockaddr_in server)
{
	if (connect(socket,(struct sockaddr *)&server,sizeof(server1))<0)
	{
		perror("connect failed. Error");
	}
	else
		printf("Connected to %d\n",socket);

}
void main(int argc, char *argv[])
{
	

	if (argc != 2)
	{
		printf ("USAGE:  <port>\n");
		exit(1);
	}
	
	MD5_CTX mdContext;
	unsigned char len[MD5_DIGEST_LENGTH];


	part1=malloc(partsize*sizeof(char));
	part2=malloc(partsize*sizeof(char));
	part3=malloc(partsize*sizeof(char));
	part4=malloc(partsize*sizeof(char));
	tempbuf=malloc(partsize*sizeof(char));
	con=malloc(100*sizeof(char));
	DFS1=malloc(25*sizeof(char));
	DFS2=malloc(25*sizeof(char));
	DFS3=malloc(25*sizeof(char));
	DFS4=malloc(25*sizeof(char));
	USER=malloc(25*sizeof(char));
	//sometoken1=malloc(25*sizeof(char));
	
	FILE *fp,*ft, *fcon;
	int nbytes;
	fcon=fopen(argv[1],"r");
	
	for(int i=0;i<=5;i++)
	{
		ret=fgets(con,50,fcon);
		//printf("%s\t%d\n",con,(int)strlen(con));
		if(strstr(con,"DFS1")!=NULL)
		{		
			dfs1=strtok(con,delimiter);
			dfs1=strtok(NULL,"\n");
			strcpy(DFS1,dfs1);
			//printf("%s %d\n",dfs1,(int)strlen(dfs1));
		}
		if(strstr(con,"DFS2")!=NULL)
		{		
			dfs2=strtok(con,delimiter);
			dfs2=strtok(NULL,"\n");
			strcpy(DFS2,dfs2);
			//printf("%s %d\n",dfs2,(int)strlen(dfs2));
		}
		if(strstr(con,"DFS3")!=NULL)
		{		
			dfs3=strtok(con,delimiter);
			dfs3=strtok(NULL,"\n");
			strcpy(DFS3,dfs3);
			//printf("%s %d\n",dfs3,(int)strlen(dfs3));
		}
		if(strstr(con,"DFS4")!=NULL)
		{		
			dfs4=strtok(con,delimiter);
			dfs4=strtok(NULL,"\n");
			strcpy(DFS4,dfs4);
			//printf("%s %d\n",dfs4,(int)strlen(dfs4));
		}
		if(strstr(con,"Username")!=NULL)
		{		
			user=strtok(con,delimiter);
			user=strtok(NULL,"\n");
			strcpy(USER,user);
			//printf("%s %d\n",user,(int)strlen(user));
		}
		if(strstr(con,"Password")!=NULL)
		{		
			pass=strtok(con,delimiter);
			pass=strtok(NULL,"\n");
			//strcpy(USER,user);
			//printf("%s %d\n",pass,(int)strlen(pass));
		}
	}
	
	printf("Username is %s and Password is %s\n",USER,pass);
	fclose(fcon);

	
	dfs1=strtok(DFS1,":");
	dfs1=strtok(NULL,":");
	DFS1=strtok(DFS1,delimiter);
	dfs2=strtok(DFS2,":");
	dfs2=strtok(NULL,":");
	DFS2=strtok(DFS2,delimiter);
	dfs3=strtok(DFS3,":");
	dfs3=strtok(NULL,":");
	DFS3=strtok(DFS3,delimiter);
	dfs4=strtok(DFS4,":");
	dfs4=strtok(NULL,":");
	DFS4=strtok(DFS4,delimiter);

	fgets(argument1,100,stdin);
	strcpy(argument,argument1);
	if(strcmp(argument1,"LIST\n")==0)
		flag=true;	

	strcat(argument,USER);
	strcat(argument,delimiter);
	strcat(argument,pass);
	printf("total string is %s\n",argument);
	if(!flag)
	{
		command=strtok(argument1,delimiter);
		file=strtok(NULL,"\n");
		printf("Command is %s and file is %s\n",argument1,file);
	}
	else
		command=strtok(argument1,"\n");
	server1.sin_addr.s_addr = inet_addr("127.0.0.1");
    server1.sin_family = AF_INET;
	server1.sin_port = htons(atoi(dfs1));
	server2.sin_addr.s_addr = inet_addr("127.0.0.1");
    server2.sin_family = AF_INET;
	server2.sin_port = htons(atoi(dfs2));
	
	server3.sin_addr.s_addr = inet_addr("127.0.0.1");
    server3.sin_family = AF_INET;
	server3.sin_port = htons(atoi(dfs3));
	server4.sin_addr.s_addr = inet_addr("127.0.0.1");
    server4.sin_family = AF_INET;
	server4.sin_port = htons(atoi(dfs4));
	
	if ((sock1 = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
	    printf("unable to create socket, sock : %d\n", sock1);
	}
	printf("Socket1 successfully created\n");
	if ((sock2 = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
	    printf("unable to create socket, sock : %d\n", sock2);
	}
	printf("Socket2 successfully created\n");
	if ((sock3 = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
	    printf("unable to create socket, sock : %d\n", sock3);
	}
	printf("Socket3 successfully created\n");
	if ((sock4 = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
	    printf("unable to create socket, sock : %d\n", sock4);
	}
	printf("Socket4 successfully created\n");
	connecttoserver(sock1,server1);
	connecttoserver(sock2,server2);
	connecttoserver(sock3,server3);
	connecttoserver(sock4,server4);

	//while(1)
	//{
		bytes_sent=0;
		if(strcmp(command,"PUT")==0)
		{
			
					
			MD5_Init (&mdContext);
			fp= fopen(file,"r");
			fseek(fp, 0 , SEEK_END);
			fsize=ftell(fp);
	
			fseek(fp, 0 , SEEK_SET);
			printf("Total file size is %d\n", fsize);
	
			psize=fsize/4;
			printf("part size is %d\n", psize);
			nbytes=fread(part1,sizeof(char),psize,fp);
			MD5_Update (&mdContext, part1, nbytes);
			printf("Bytes read are %d\n",nbytes);
			nbytes=fread(part2,sizeof(char),psize,fp);
			printf("Bytes read are %d\n",nbytes);
			MD5_Update (&mdContext, part2, nbytes);
			nbytes=fread(part3,sizeof(char),psize,fp);
			printf("Bytes read are %d\n",nbytes);
			MD5_Update (&mdContext, part3, nbytes);
			nbytes=fread(part4,sizeof(char),(fsize-3*psize),fp);
			printf("Bytes read are %d\n",nbytes);
			MD5_Update (&mdContext, part4, nbytes);
			MD5_Final (len,&mdContext);
			for(int i = 0; i < MD5_DIGEST_LENGTH; i++) 
				printf("%02x",len[i]);
			printf("\n");
			md5=len[MD5_DIGEST_LENGTH-1];
			mod=md5%4;
			printf("the modulus is %d\n",mod);
	
			fclose(fp);
	
			returnval1=authenticate(sock1,server1);
			returnval2=authenticate(sock2,server2);
			returnval3=authenticate(sock3,server3);
			returnval4=authenticate(sock4,server4);
			printf("return values are %d %d %d %d\n",returnval1,returnval2,returnval3,returnval4);
			if (mod==0)
			{
				if(returnval1==1)
				{
					sendpart(part1,sock1,1,server1);
					//senddata(sock1,".1",sizeof(".1"));
					sendpart(part2,sock1,2,server1);
					//senddata(sock1,".2",sizeof(".2"));
				}
				if(returnval2==1)
				{
					sendpart(part2,sock2,2,server2);
					//senddata(sock2,".2",sizeof(".2"));
					sendpart(part3,sock2,3,server2);
					//senddata(sock2,".3",sizeof(".2"));
				}
				if(returnval3==1)
				{
					sendpart(part3,sock3,3,server3);
					//senddata(sock3,".3",sizeof(".2"));
					sendpart(part4,sock3,4,server3);
					//senddata(sock3,".4",sizeof(".2"));
				}
				if(returnval4==1)
				{
					sendpart(part4,sock4,4,server4);	
					sendpart(part1,sock4,1,server4);
				
				}
				
			}
			else if (mod==1)
			{
				if(returnval1==1)
				{
					sendpart(part4,sock1,4,server1);
					sendpart(part1,sock1,1,server1);
				}
				if(returnval2==1)
				{
					sendpart(part1,sock2,1,server2);
					sendpart(part2,sock2,2,server2);
				}
				if(returnval3==1)
				{
					sendpart(part2,sock3,2,server3);
					sendpart(part3,sock3,3,server3);
				}
				if(returnval4==1)
				{
					sendpart(part3,sock4,3,server4);
					sendpart(part4,sock4,4,server4);
				}
				
			}
			else if (mod==2)
			{
				if(returnval1==1)
				{
					sendpart(part3,sock1,3,server1);
					sendpart(part4,sock1,4,server1);
				}
				if(returnval2==1)
				{
					sendpart(part4,sock2,4,server2);
					sendpart(part1,sock2,1,server2);
				}
				if(returnval3==1)
				{
					sendpart(part1,sock3,1,server3);
					sendpart(part2,sock3,2,server3);
				}
				if(returnval4==1)
				{
					sendpart(part2,sock4,2,server4);
					sendpart(part3,sock4,3,server4);
				}
				
			}
			else if (mod==3)
			{
				if(returnval1==1)
				{
					sendpart(part2,sock1,2,server1);
					sendpart(part3,sock1,3,server1);
				}
				if(returnval2==1)
				{
					sendpart(part3,sock2,3,server2);
					sendpart(part4,sock2,4,server2);
				}
				if(returnval3==1)
				{
					sendpart(part4,sock3,4,server3);
					sendpart(part1,sock3,1,server3);
				}
				if(returnval4==1)
				{
					sendpart(part1,sock4,1,server4);
					sendpart(part2,sock4,2,server4);
				}
				
			}
				
		}
		else if (strcmp(command,"LIST")==0)
		{
			//bzero(command,sizeof(command));
			//command=strtok(argument1,"\n");
			printf("Command is %s\n",command);
			returnval1=authenticate(sock1,server1);
			returnval2=authenticate(sock2,server2);
			returnval3=authenticate(sock3,server3);
			returnval4=authenticate(sock4,server4);
			printf("return values are %d %d %d %d\n",returnval1,returnval2,returnval3,returnval4);
			receivedata(sock1,content1,sizeof(content1));
			receivedata(sock2,content2,sizeof(content2));
			receivedata(sock3,content3,sizeof(content3));
			receivedata(sock4,content4,sizeof(content4));
			printf("Files in directory1 are %s\n",content1);
			printf("Files in directory2 are %s\n",content2);
			printf("Files in directory3 are %s\n",content3);
			printf("Files in directory4 are %s\n",content4);
			/*int i=0;
			token1[i]=strtok(content1,delimiter);
			while(token1[i]!=NULL)
			{
				token1[i+1]=strtok(NULL,delimiter);
				printf("tokens for DFS1 are is %s\n",token1[i]);				
				i++;
			}*/
			//for(int i=0;i<100;i++)
			//{
			sometoken=bss[0];
			int i=0;
			sometoken1=strtok(content1,delimiter);
			strcpy(sometoken,sometoken1);
			printf("First value is %s\n",bss[0]);
			i++;
			while(sometoken1!=NULL)
			{
				sometoken=bss[i];
				
				sometoken1=strtok(NULL,delimiter);
				printf("ANDAR\n");
				if(sometoken1!=NULL)
				{	strcpy(sometoken,sometoken1);
					printf("Next value is %s\n",bss[i]);
					i++;
				}
			}
			printf("BAHAR\n");
			sometoken=bss[i];
			sometoken1=strtok(content2,delimiter);
			strcpy(sometoken,sometoken1);
			i++;
			while(sometoken1!=NULL)
			{
				sometoken=bss[i];
				
				sometoken1=strtok(NULL,delimiter);
				printf("ANDAR\n");
				if(sometoken1!=NULL)
				{	strcpy(sometoken,sometoken1);
					printf("Next value is %s\n",bss[i]);
					i++;
				}
			}
			sometoken=bss[i];
			sometoken1=strtok(content3,delimiter);
			strcpy(sometoken,sometoken1);
			i++;
			while(sometoken1!=NULL)
			{
				sometoken=bss[i];
				
				sometoken1=strtok(NULL,delimiter);
				printf("ANDAR\n");
				if(sometoken1!=NULL)
				{	strcpy(sometoken,sometoken1);
					printf("Next value is %s\n",bss[i]);
					i++;
				}
			}
			sometoken=bss[i];
			sometoken1=strtok(content4,delimiter);
			strcpy(sometoken,sometoken1);
			i++;
			while(sometoken1!=NULL)
			{
				sometoken=bss[i];
				
				sometoken1=strtok(NULL,delimiter);
				printf("ANDAR\n");
				if(sometoken1!=NULL)
				{	strcpy(sometoken,sometoken1);
					printf("Next value is %s\n",bss[i]);
					i++;
				}
			}
			int l=0;
			for(int j=0;j<i;j++)
			{
				
				flag=false;
				//sometoken1=ccc[j];
				for(int k=0;k<l;k++)
				{
					//printf("VALUES of j and k are %d and %d %s\n",j,k,ccc[k]);
					if(strcmp(ccc[k],bss[j])==0)
					{
						flag=true;
						//puts("flag is true");
					}
				}
				if(flag==false)
				{
					strcpy(ccc[l],bss[j]);
					printf("Content is %s\n",ccc[l]);
					l++;
				}
			}
			int count=0;
			for(int j=0;j<l;j++)
			{
				if(strlen(ccc[j])>2)
				{
					sometoken1=strtok(ccc[j],".");
					sometoken=strtok(ccc[j],".");
					strcpy(ccc[j],sometoken);
					printf("the string is %s\n",ccc[j]);
					
				}
				
			}
			puts("THE LIST IS");
			for(int j=0;j<l;j++)
			{

				if(strlen(ccc[j])>2)
				{
					for(int i=0;i<l;i++)
					{
						if(strcmp(ccc[i],ccc[j])==0)
						{	count++;
							if(i!=j)
								strcpy(ccc[i],"\0");
						}
					}
					//for(int i=0;i<j;i++)
					//{	
					//if(strcmp(ccc[j],ccc[i])!=0)
					//{
					if(strcmp(ccc[j],"\0")!=0)
					{
						if(count==4)
						printf("%s\n",ccc[j]);
						else
						printf("%s[INCOMPLETE]\n",ccc[j]);
					}
					count=0;
				}
			}
		}
	if (con!=NULL)
		free(con);
	
	if (DFS1!=NULL)
		free(DFS1);

	if (DFS2!=NULL)
		free(DFS2);

	if (DFS3!=NULL)
		free(DFS3);

	if (DFS4!=NULL)
		free(DFS4);

	if (USER!=NULL)
		free(USER);
		
	//free(token1);
	//free(token11);
}
int senddata(int socket,char* buffer,size_t length,struct sockaddr_in server)
{
	if (connect(socket,(struct sockaddr *)&server,sizeof(server1))<0)
	{
		perror("connect failed. Error");
	}
	else
	{	printf("Connected to %d\n",socket);

		int returndata;
		if((returndata=send(socket , buffer , length , 0)) < 0)
		{
			puts("Send failed");
		}
		return returndata;
	}
}
int receivedata(int socketa,char* buffer,size_t length)
{
	bzero(buffer,length);
	if( recv(socketa , buffer , length , 0) < 0)
	{
		puts("recv failed");	       
	}	
	printf("Received message is %s\n",buffer);

}
int authenticate(int socketa,struct sockaddr_in server)
{
	senddata(socketa,argument,sizeof(argument),server);  
	receivedata(socketa,reply,sizeof(reply));
	if(strcmp(reply,"pass")==0)
		return 1;
	else
		return 0;
}
int sendpart(char *buffer,int socket,int partno,struct sockaddr_in server)
{
	
	
	tempbuf=buffer;
	//returnval1=chunk;
	//printf("Pehla padav, %d\n",returnval);
	
	if(partno==4)
		rem_bytes=fsize-3*psize;
	else
		rem_bytes=psize;
	
	while(rem_bytes>0)
	{
		//printf("Dusra padav\n");
		if(rem_bytes>=chunk)
			temp=chunk;

		else
			temp=rem_bytes;
	
	int	returnval=senddata(socket,tempbuf,temp,server);
		//printf("Bytes sent are%d\n",returnval);
		//printf("Data sent is %s\n",tempbuf);
		bytes_sent+=returnval;
		tempbuf+=chunk;
		rem_bytes-=chunk;
		//printf("Data sent is%s\n",tempbuf);
						
	}
	printf("Total Bytes sent are%d\n",bytes_sent);
	receivedata(socket,reply,sizeof(reply));
	if(partno==1)
		senddata(socket,".1",sizeof(".1"),server);
	else if(partno==2) 
		senddata(socket,".2",sizeof(".2"),server);
	else if(partno==3)
		senddata(socket,".3",sizeof(".3"),server);
	else
		senddata(socket,".4",sizeof(".4"),server);

	bytes_sent=0;
	bzero(tempbuf,sizeof(tempbuf));

}


