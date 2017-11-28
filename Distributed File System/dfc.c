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
int senddata(int socketa,char* buffer,size_t length);
int receivedata(int socketa,char* buffer,size_t length);
int sendpart(char *buffer,int socket,int partno);
char *part1,*part2,*part3,*part4,*ret,*con,*dfs1,*dfs2,*dfs3,*dfs4, *user, *pass, *command, *file,*tempbuf, *sometoken,*sometoken1,*sub;
char *delimiter=" ";
const int chunk=1024;
void socket_setup(void);
int authenticate(int socketa);
struct sockaddr_in server1,server2,server3,server4;
int sock1,sock2,sock3,sock4,temp,rem_bytes,fsize;
uint16_t md5,mod;
bool flag=false;
//int sendrec(socket,)
char *DFS1, *DFS2, *DFS3, *DFS4,*USER, *PASS;
char reply[2000],content1[500],content2[500],content3[500],content4[500];
char argument[100],argument1[100];
char content[500];
int psize,returnval1,returnval2,returnval3,returnval4,bytes_sent;
char bss[100][100],ccc[100][100];
char pa,pb,pb,pc,pd,a,b,c,d;
int size1,size2,size3,size4;
struct partt{
char partnum;
char tempbuf[partsize];
};


struct rec{
bool flag1;
bool flag2;
bool flag3;
bool flag4;
};
int receivestructdata(int socketa,struct partt* buffer,size_t length);

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
/*
void xor_encrypt(char *key, char *string, int n)
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
void socket_setup(void)
{
	
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
	
	/*if (connect(sock1 , (struct sockaddr *)&server1 , sizeof(server1)) < 0)
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
	*/
}
int connectserver(int socket,struct sockaddr_in server)
{
	int num;
	num=connect(socket, (struct sockaddr *)&server , sizeof(server1));
	if (num < 0)
	{
		perror("connect failed Trying again. Error");
		usleep(500000);
		num=connect(socket, (struct sockaddr *)&server , sizeof(server1));
		if (num < 0)
		{
			usleep(500000);
			perror("connect failed Trying again. Error");
			num=connect(socket, (struct sockaddr *)&server , sizeof(server1));
			if (num < 0)
			{
				perror("SERVER NOT AVAILABLE");
				num=connect(socket, (struct sockaddr *)&server , sizeof(server1));
			}
			//else
				//continue;
		}
		/*else
		{	 
			//puts("Connected to Server %d\n",socket);
			continue;
		}*/
	}
	else	 
		printf("Connected to %d\n",socket);
	return num;
}
void closesockets(void)
{
	if(a>=0)
		close(sock1);
	if(b>=0)
		close(sock2);
	if(c>=0)
		close(sock3);
	if(d>=0)
		close(sock4);
	printf("exiting\n");


}

/*int notify(struct rec buffer)
{
	if (part->partnum==1)
		{
					strcpy(part1,part->tempbuf);
					recv.flag1=true;
				}
				else if (part->partnum==1)
				{
					strcpy(part1,part->tempbuf);
					recv.flag2=true;
				}
				else if (part->partnum==1)
				{
					strcpy(part1,part->tempbuf);
					recv.flag3=true;
				}
				else
				{
					strcpy(part4,part->tempbuf);
					recv.flag4=true;
				}	

}*/
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
	bzero(part1,partsize);
	bzero(part2,partsize);
	bzero(part3,partsize);
	bzero(part4,partsize);
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

	/*fgets(argument1,100,stdin);
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
		file=strtok(NULL," ");
		sub=strtok(NULL,"\n");
		printf("Command is %s and file is %s and sub is %s\n",argument1,file,sub);
	}
	else
	{
		command=strtok(argument1," ");
		sub=strtok(NULL,"\n");
		printf("Command is %s and subfolder is %s\n",command,sub);
	}*/
	socket_setup();
	
	while(1)
	{
		//closesockets();
		fgets(argument1,100,stdin);
		strcpy(argument,argument1);
		if(strncmp(argument1,"LIST",4)==0)
			flag=true;	
	
		strcat(argument,USER);
		strcat(argument,delimiter);
		strcat(argument,pass);
		printf("total string is %s\n",argument);
		if(!flag)
		{
			command=strtok(argument1,delimiter);
			file=strtok(NULL," ");
			sub=strtok(NULL,"\n");
			printf("Command is %s and file is %s and sub is %s\n",argument1,file,sub);
		}
		else
		{
			command=strtok(argument1," ");
			sub=strtok(NULL,"\n");
			printf("Command is %s and subfolder is %s\n",command,sub);
		}
		flag =false;
		bytes_sent=0;
		socket_setup();
		a=connectserver(sock1,server1);
		b=connectserver(sock2,server2);
		c=connectserver(sock3,server3);
		d=connectserver(sock4,server4);
		printf("%d,%d,%d,%d\n",a,b,c,d);
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
			if (a>=0)
				returnval1=authenticate(sock1);
			if (b>=0)
				returnval2=authenticate(sock2);
			if (c>=0)
				returnval3=authenticate(sock3);
			if (d>=0)
				returnval4=authenticate(sock4);

			printf("return values are %d %d %d %d\n",returnval1,returnval2,returnval3,returnval4);
			if(returnval1==0)
			{
				puts("Authentication failed");
				break;
			}
			xor_encrypt(pass,part1,psize);
			xor_encrypt(pass,part2,psize);
			xor_encrypt(pass,part3,psize);
			xor_encrypt(pass,part4,fsize-3*psize);
			if (mod==0)
			{
				if(returnval1==1)
				{
					if(a>=0)
					{
					sendpart(part1,sock1,1);
					//senddata(sock1,".1",sizeof(".1"));
					sendpart(part2,sock1,2);
					//senddata(sock1,".2",sizeof(".2"));
					}
				}
				if(returnval2==1)
				{	if(b>=0)
					{
					sendpart(part2,sock2,2);
					sendpart(part3,sock2,3);
					}
				}
				if(returnval3==1)
				{
					if(c>=0)
					{
					sendpart(part3,sock3,3);
					sendpart(part4,sock3,4);
					}
				}
				if(returnval4==1)
				{	
					if(d>=0)
					{
					sendpart(part4,sock4,4);	
					sendpart(part1,sock4,1);
					}
				}
				
			}
			else if (mod==1)
			{
				if(returnval1==1)
				{
					if(a>=0)
					{
					sendpart(part4,sock1,4);
					sendpart(part1,sock1,1);
					}
				}
				if(returnval2==1)
				{	if(b>=0)
					{
					sendpart(part1,sock2,1);
					sendpart(part2,sock2,2);}
				}
				if(returnval3==1)
				{	if(c>=0)
					{
					sendpart(part2,sock3,2);
					sendpart(part3,sock3,3);}
				}
				if(returnval4==1)
				{	if(d>=0)
					{
					sendpart(part3,sock4,3);
					sendpart(part4,sock4,4);}
				}
				
			}
			else if (mod==2)
			{
				if(returnval1==1)
				{	if(a>=0)
					{
					sendpart(part3,sock1,3);
					sendpart(part4,sock1,4);}
				}
				if(returnval2==1)
				{	if(b>=0)
					{
					sendpart(part4,sock2,4);
					sendpart(part1,sock2,1);}
				}
				if(returnval3==1)
				{	if(c>=0)
					{
					sendpart(part1,sock3,1);
					sendpart(part2,sock3,2);}
				}
				if(returnval4==1)
				{if(d>=0)
					{
					sendpart(part2,sock4,2);
					sendpart(part3,sock4,3);}
				}
				
			}
			else if (mod==3)
			{
				if(returnval1==1)
				{	if(a>=0)
					{
					sendpart(part2,sock1,2);
					sendpart(part3,sock1,3);
					}
				}
				if(returnval2==1)
				{	if(b>=0)
					{
					sendpart(part3,sock2,3);
					sendpart(part4,sock2,4);
					}
				}
				if(returnval3==1)
				{	if(c>=0)
					{
					sendpart(part4,sock3,4);
					sendpart(part1,sock3,1);
					}
				}
				if(returnval4==1)
				{	if(d>=0)
					{
					sendpart(part1,sock4,1);
					sendpart(part2,sock4,2);
					}
				}
				
			}
				
		}
		else if (strcmp(command,"LIST")==0)
		{
			//bzero(command,sizeof(command));
			//command=strtok(argument1,"\n");
			for(int i=0;i<100;i++)
			{
				bzero(ccc[i],sizeof(ccc[i]));
				bzero(bss[i],sizeof(bss[i]));	
					
			}
			printf("Command is %s\n",command);
			if (a>=0)
				returnval1=authenticate(sock1);
			if (b>=0)
				returnval2=authenticate(sock2);
			if (c>=0)
				returnval3=authenticate(sock3);
			if (d>=0)
				returnval4=authenticate(sock4);
			printf("return values are %d %d %d %d\n",returnval1,returnval2,returnval3,returnval4);
			if(returnval1==0)
			{
				puts("Authentication failed");
				break;
			}
			if(a>=0)
			{	receivedata(sock1,content1,sizeof(content1));
				printf("Files in directory1 are %s\n",content1);
			}
			if(b>=0){
				receivedata(sock2,content2,sizeof(content2));
				printf("Files in directory2 are %s\n",content2);}
			if(c>=0){
				receivedata(sock3,content3,sizeof(content3));
				printf("Files in directory3 are %s\n",content3);}
			if(d>=0){
				receivedata(sock4,content4,sizeof(content4));
				printf("Files in directory4 are %s\n",content4);}
			//printf("Files in directory1 are %s\n",content1);
			//printf("Files in directory2 are %s\n",content2);
			//printf("Files in directory3 are %s\n",content3);
			//printf("Files in directory4 are %s\n",content4);
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
				printf("ANDAR as well\n");
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
				printf("ANDAR  jnna\n");
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
			flag=false;
			int count=0;
			for(int j=0;j<l;j++)
			{
				if(strlen(ccc[j])>2)
				{
					strrev(ccc[j]);
					sometoken1=strtok(ccc[j],".");
					printf("the string is %s\n",ccc[j]);
					sometoken=strtok(NULL,"\0");
					strcpy(ccc[j],sometoken);
					printf("the string is %s\n",ccc[j]);
					ccc[j][strlen(ccc[j])-1]='\0';
					strrev(ccc[j]);
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
		else if (strcmp(command,"GET")==0)
		{
			if (a>=0)
				returnval1=authenticate(sock1);
			if (b>=0)
				returnval2=authenticate(sock2);
			if (c>=0)
				returnval3=authenticate(sock3);
			if (d>=0)
				returnval4=authenticate(sock4);
	
			if(returnval1==0)
			{
				puts("Authentication failed");
				break;
			}
			bzero(content1,sizeof(content1));
			bzero(content2,sizeof(content2));
			bzero(content3,sizeof(content3));
			bzero(content4,sizeof(content4));
			bzero(content,sizeof(content));
			bzero(part1,partsize);
			bzero(part2,partsize);
			bzero(part3,partsize);
			bzero(part4,partsize);
			struct rec recv;
			recv.flag1=false;
			recv.flag2=false;
			recv.flag3=false;
			recv.flag4=false;
			if(a>=0)
			{
				receivedata(sock1,content1,sizeof(content1));
				sometoken=strtok(content1,delimiter);
				sometoken1=strtok(NULL,delimiter);
				printf("%sand%s*\n",sometoken,sometoken1);
				if((strcmp(sometoken,"1")==0) && (recv.flag1==false))
				{
					strcat(content,sometoken);
				}
				else if((strcmp(sometoken,"2")==0) && (recv.flag2==false))
				{
					strcat(content,sometoken);
				}
				else if((strcmp(sometoken,"3")==0) && (recv.flag3==false))
				{
					strcat(content,sometoken);
				}
				else if((strcmp(sometoken,"4")==0) && (recv.flag4==false))
				{
					strcat(content,sometoken);
				}
				if(sometoken!=NULL)
					strcat(content,delimiter);
				if((strcmp(sometoken1,"1")==0) && (recv.flag1==false))
				{
					strcat(content,sometoken1);
				}
				if((strcmp(sometoken1,"2")==0) && (recv.flag2==false))
				{
					strcat(content,sometoken1);
				}
				if((strcmp(sometoken1,"3")==0) && (recv.flag3==false))
				{
					strcat(content,sometoken1);
				}
				if((strcmp(sometoken1,"4")==0) && (recv.flag4==false))
				{
					strcat(content,sometoken1);
				}
				/*	
				strcat(content,sometoken);
				strcat(content,delimiter);
				strcat(content,sometoken1);*/
				printf("buffer is %s*\n",content);
				senddata(sock1,content,sizeof(content));
				puts("zereod");
				struct partt *part;
				part=malloc(sizeof(struct partt));
				//puts("zereod");
				
				//puts("zereod");
				bzero(part->tempbuf,sizeof(part->tempbuf));
				//puts("zereod");
				//int nbytes=receivedata(sock1,part,partsize);
				//if(sometoken!=)
				int nbytes=receivestructdata(sock1,part,partsize);
				
				printf("Bytes received are %d and size is %dand part is %d\n",nbytes-1,(int)strlen(part->tempbuf),part->partnum);
				if (part->partnum==1)
				{
					strcpy(part1,part->tempbuf);
					recv.flag1=true;
					size1=nbytes-1;
				}
				else if (part->partnum==2)
				{
					strcpy(part2,part->tempbuf);
					recv.flag2=true;
					size2=nbytes-1;
				}
				else if (part->partnum==3)
				{
					strcpy(part3,part->tempbuf);
					recv.flag3=true;
					size3=nbytes-1;
				}
				else
				{
					strcpy(part4,part->tempbuf);
					recv.flag4=true;
					size4=nbytes-1;
				}
				if(strlen(content)==3)
				{
					nbytes=receivestructdata(sock1,part,partsize);
				
					printf("Bytes received are %d and size is %dand part is %d\n",nbytes-1,(int)strlen(part->tempbuf),part->partnum);
				
					if (part->partnum==1)
					{
						strcpy(part1,part->tempbuf);
						recv.flag1=true;
						size1=nbytes-1;
					}
					else if (part->partnum==2)
					{
						strcpy(part2,part->tempbuf);
						recv.flag2=true;
						size2=nbytes-1;
					}
					else if (part->partnum==3)
					{
						strcpy(part3,part->tempbuf);
						recv.flag3=true;
						size3=nbytes-1;
					}
					else
					{
						strcpy(part4,part->tempbuf);
						recv.flag4=true;
						size4=nbytes-1;
					}
				}
				bzero(content,sizeof(content));
				printf("server1 job done\n");
			}
			if(b>=0)
			{
				printf("b is %d\n",b);
				receivedata(sock2,content2,sizeof(content2));
				sometoken=strtok(content2,delimiter);
				sometoken1=strtok(NULL,delimiter);
				printf("%sand%s*\n",sometoken,sometoken1);
				
				if((strcmp(sometoken,"1")==0) && (recv.flag1==false))
				{
					strcat(content,sometoken);
				}
				if((strcmp(sometoken,"2")==0) && (recv.flag2==false))
				{
					strcat(content,sometoken);
				}
				if((strcmp(sometoken,"3")==0) && (recv.flag3==false))
				{
					strcat(content,sometoken);
				}
				if((strcmp(sometoken,"4")==0) && (recv.flag4==false))
				{
					strcat(content,sometoken);
				}
				if(content!=NULL)
					strcat(content,delimiter);
				if((strcmp(sometoken1,"1")==0) && (recv.flag1==false))
				{
					strcat(content,sometoken1);
				}
				if((strcmp(sometoken1,"2")==0) && (recv.flag2==false))
				{
					strcat(content,sometoken1);
				}
				if((strcmp(sometoken1,"3")==0) && (recv.flag3==false))
				{
					strcat(content,sometoken1);
				}
				if((strcmp(sometoken1,"4")==0) && (recv.flag4==false))
				{
					strcat(content,sometoken1);
				}
				/*	
				strcat(content,sometoken);
				strcat(content,delimiter);
				strcat(content,sometoken1);*/
				printf("buffer is%s*\n",content);
				senddata(sock2,content,sizeof(content));
				puts("zereod1");
				struct partt *part;
				part=malloc(sizeof(struct partt));
				//puts("zereod");
				puts("zereod2");
				bzero(part->tempbuf,sizeof(part->tempbuf));
				puts("zereod3");
				//int nbytes=receivedata(sock1,part,partsize);
				//if(sometoken!=)
				if(strlen(content)>1)
				{
					puts("zereod4");
					int nbytes=receivestructdata(sock2,part,partsize);
					puts("zereod5");
					printf("Bytes received are %d and size is %dand part is %d\n",nbytes-1,(int)strlen(part->tempbuf),part->partnum);
					if (part->partnum==1)
					{
						strcpy(part1,part->tempbuf);
						recv.flag1=true;
						size1=nbytes-1;
					}
					else if (part->partnum==2)
					{
						strcpy(part2,part->tempbuf);
						recv.flag2=true;
						size2=nbytes-1;
					}
					else if (part->partnum==3)
					{
						strcpy(part3,part->tempbuf);
						recv.flag3=true;
						size3=nbytes-1;
					}
					else
					{
						strcpy(part4,part->tempbuf);
						recv.flag4=true;
						size4=nbytes-1;
					}
				}
				if(strlen(content)==3)
				{
					nbytes=receivestructdata(sock2,part,partsize);
				
					printf("Bytes received are %d and size is %dand part is %d\n",nbytes-1,(int)strlen(part->tempbuf),part->partnum);
					if (part->partnum==1)
					{
						strcpy(part1,part->tempbuf);
						recv.flag1=true;
						size1=nbytes-1;
					}
					else if (part->partnum==2)
					{
						strcpy(part2,part->tempbuf);
						recv.flag2=true;
						size2=nbytes-1;
					}
					else if (part->partnum==3)
					{
						strcpy(part3,part->tempbuf);
						recv.flag3=true;
						size3=nbytes-1;
					}
					else
					{
						strcpy(part4,part->tempbuf);
						recv.flag4=true;
						size4=nbytes-1;
					}
				}
				bzero(content,sizeof(content));
				printf("server2 job done\n");
			}
			if(c>=0)
			{
				receivedata(sock3,content3,sizeof(content3));
				sometoken=strtok(content3,delimiter);
				sometoken1=strtok(NULL,delimiter);
				printf("%sand%s*\n",sometoken,sometoken1);
				if((strcmp(sometoken,"1")==0) && (recv.flag1==false))
				{
					strcat(content,sometoken);
				}
				if((strcmp(sometoken,"2")==0) && (recv.flag2==false))
				{
					strcat(content,sometoken);
				}
				if((strcmp(sometoken,"3")==0) && (recv.flag3==false))
				{
					strcat(content,sometoken);
				}
				if((strcmp(sometoken,"4")==0) && (recv.flag4==false))
				{
					strcat(content,sometoken);
				}
				if(content!=NULL)
					strcat(content,delimiter);
				if((strcmp(sometoken1,"1")==0) && (recv.flag1==false))
				{
					strcat(content,sometoken1);
				}
				if((strcmp(sometoken1,"2")==0) && (recv.flag2==false))
				{
					strcat(content,sometoken1);
				}
				if((strcmp(sometoken1,"3")==0) && (recv.flag3==false))
				{
					strcat(content,sometoken1);
				}
				if((strcmp(sometoken1,"4")==0) && (recv.flag4==false))
				{
					strcat(content,sometoken1);
				}
				/*	
				strcat(content,sometoken);
				strcat(content,delimiter);
				strcat(content,sometoken1);*/
				printf("buffer is%s*\n",content);
				senddata(sock3,content,sizeof(content));
				puts("zereod1");
				struct partt *part;
				part=malloc(sizeof(struct partt));
				//puts("zereod");
				puts("zereod2");
				bzero(part->tempbuf,sizeof(part->tempbuf));
				puts("zereod3");
				//int nbytes=receivedata(sock1,part,partsize);
				//if(sometoken!=)
				if(strlen(content)>1)
				{
					puts("zereod4");
					int nbytes=receivestructdata(sock3,part,partsize);
					puts("zereod5");
					printf("Bytes received are %d and size is %dand part is %d\n",nbytes-1,(int)strlen(part->tempbuf),part->partnum);
					if (part->partnum==1)
					{
						strcpy(part1,part->tempbuf);
						recv.flag1=true;
						size1=nbytes-1;
					}
					else if (part->partnum==2)
					{
						strcpy(part2,part->tempbuf);
						recv.flag2=true;
						size2=nbytes-1;
					}
					else if (part->partnum==3)
					{
						strcpy(part3,part->tempbuf);
						recv.flag3=true;
						size3=nbytes-1;
					}
					else
					{
						strcpy(part4,part->tempbuf);
						recv.flag4=true;
						size4=nbytes-1;
					}
				}
				if(strlen(content)==3)
				{
					nbytes=receivestructdata(sock3,part,partsize);
				
					printf("Bytes received are %d and size is %dand part is %d\n",nbytes-1,(int)strlen(part->tempbuf),part->partnum);
					if (part->partnum==1)
					{
						strcpy(part1,part->tempbuf);
						recv.flag1=true;
						size1=nbytes-1;
					}
					else if (part->partnum==2)
					{
						strcpy(part2,part->tempbuf);
						recv.flag2=true;
						size2=nbytes-1;
					}
					else if (part->partnum==3)
					{
						strcpy(part3,part->tempbuf);
						recv.flag3=true;
						size3=nbytes-1;
					}
					else
					{
						strcpy(part4,part->tempbuf);
						recv.flag4=true;
						size4=nbytes-1;
					}
					
				}
				bzero(content,sizeof(content));
				printf("server3 job done\n");
			}
			if(d>=0)
			{
				printf("%d\n",flag);
				bzero(content,sizeof(content));
				receivedata(sock4,content4,sizeof(content4));
				sometoken=strtok(content4,delimiter);
				sometoken1=strtok(NULL,delimiter);
				printf("%sand%s*\n",sometoken,sometoken1);
				if((strcmp(sometoken,"1")==0) && (recv.flag1==false))
				{
					strcat(content,sometoken);
				}
				if((strcmp(sometoken,"2")==0) && (recv.flag2==false))
				{
					strcat(content,sometoken);
				}
				if((strcmp(sometoken,"3")==0) && (recv.flag3==false))
				{
					strcat(content,sometoken);
				}
				if((strcmp(sometoken,"4")==0) && (recv.flag4==false))
				{
					strcat(content,sometoken);
				}
				if(content!=NULL)
					strcat(content,delimiter);
				if((strcmp(sometoken1,"1")==0) && (recv.flag1==false))
				{
					strcat(content,sometoken1);
				}
				if((strcmp(sometoken1,"2")==0) && (recv.flag2==false))
				{
					strcat(content,sometoken1);
				}
				if((strcmp(sometoken1,"3")==0) && (recv.flag3==false))
				{
					strcat(content,sometoken1);
				}
				if((strcmp(sometoken1,"4")==0) && (recv.flag4==false))
				{
					strcat(content,sometoken1);
				}
				/*	
				strcat(content,sometoken);
				strcat(content,delimiter);
				strcat(content,sometoken1);*/
				printf("buffer is %s* and %d\n",content,(int)strlen(content));
				senddata(sock4,content,sizeof(content));
				puts("zereod1");
				struct partt *part;
				part=malloc(sizeof(struct partt));
				//puts("zereod");
				puts("zereod2");
				bzero(part->tempbuf,sizeof(part->tempbuf));
				puts("zereod3");
				//int nbytes=receivedata(sock1,part,partsize);
				//if(sometoken!=)
				if(strlen(content)>1)
				{
					puts("zereod4");
					int nbytes=receivestructdata(sock4,part,partsize);
					puts("zereod5");
					printf("Bytes received are %d and size is %dand part is %d\n",nbytes-1,(int)strlen(part->tempbuf),part->partnum);
					if (part->partnum==1)
					{
						strcpy(part1,part->tempbuf);
						recv.flag1=true;
						size1=nbytes-1;
					}
					else if (part->partnum==2)
					{
						strcpy(part2,part->tempbuf);
						recv.flag2=true;
						size2=nbytes-1;
					}
					else if (part->partnum==3)
					{
						strcpy(part3,part->tempbuf);
						recv.flag3=true;
						size3=nbytes-1;
					}
					else
					{
						strcpy(part4,part->tempbuf);
						recv.flag4=true;
						size4=nbytes-1;
					}
				}
				if(strlen(content)==3)
				{
					nbytes=receivestructdata(sock4,part,partsize);
				
					printf("Bytes received are %d and size is %dand part is %d\n",nbytes-1,(int)strlen(part->tempbuf),part->partnum);
					if (part->partnum==1)
					{
						strcpy(part1,part->tempbuf);
						recv.flag1=true;
						size1=nbytes-1;
					}
					else if (part->partnum==2)
					{
						strcpy(part2,part->tempbuf);
						recv.flag2=true;
						size2=nbytes-1;
					}
					else if (part->partnum==3)
					{
						strcpy(part3,part->tempbuf);
						recv.flag3=true;
						size3=nbytes-1;
					}
					else
					{
						strcpy(part4,part->tempbuf);
						recv.flag4=true;
						size4=nbytes-1;
					}
				}
				bzero(content,sizeof(content));
				printf("server4 job done\n");
			}
			if((recv.flag1 && recv.flag2 && recv.flag3 && recv.flag4)==true)
			{
				strcat(file,"_copy");
				fp=fopen(file,"a");
				if(fp)
				{
					printf("%d\n,%d\n,%d\n,%d\n",size1,size2,size3,size4);
					fwrite(part1,size1,sizeof(char),fp);
					fwrite(part2,size2,sizeof(char),fp);
					fwrite(part3,size3,sizeof(char),fp);
					fwrite(part4,size4,sizeof(char),fp);
					puts("FILE COmplete");
					fclose(fp);
				}
				else
					perror("FILE open failed");

			}
			else
				puts("INCOMPLETE FILE ");
			/*nbytes=receivedata(sock1,part2,partsize);
			printf("Bytes received are %d and size is %d\n",nbytes,strlen(part1));
			receivedata(sock2,content2,sizeof(content2));
			receivedata(sock3,content3,sizeof(content3));
			receivedata(sock4,content4,sizeof(content4));
			*/
			
			
		}closesockets();
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
int senddata(int socketa,char* buffer,size_t length)
{
	
	int returndata;
	if((returndata=send(socketa , buffer , length , 0)) < 0)
	{
		puts("Send failed");
	}
	return returndata;
}
int receivedata(int socketa,char* buffer,size_t length)
{
	bzero(buffer,length);
	int nbytes;
	if(recv(socketa , buffer , length , 0) < 0)
	{
		puts("recv failed");	       
	}	
	printf("Received message is %s*\n",buffer);
	
}
int receivestructdata(int socketa,struct partt* buffer,size_t length)
{
	puts("Entered");
	bzero(buffer->tempbuf,length);
	int nbytes;
	puts("pudhe");
	nbytes=recv(socketa , buffer , length , 0);
	if(nbytes< 0)
	{
		puts("recv failed");	       
	}	
	printf("Received message is %s*\n",buffer->tempbuf);
	return nbytes;
}
int authenticate(int socketa)
{
	senddata(socketa,argument,sizeof(argument));  
	receivedata(socketa,reply,sizeof(reply));
	if(strcmp(reply,"pass")==0)
		return 1;
	else
		return 0;		
}

int sendpart(char *buffer,int socket,int partno)
{
	bzero(tempbuf,psize);
	tempbuf=buffer;
	
	//returnval1=chunk;
	//printf("Pehla padav, %d\n",returnval);
	if(partno==4)
		rem_bytes=fsize-3*psize;
	else
		rem_bytes=psize;
	
	//xor_encrypt(pass,tempbuf,rem_bytes);
	while(rem_bytes>0)
	{
		//printf("Dusra padav\n");
		if(rem_bytes>=chunk)
			temp=chunk;

		else
			temp=rem_bytes;
	
		
		//xor_encrypt(pass,tempbuf,temp);
		int	returnval=senddata(socket,tempbuf,temp);
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
		senddata(socket,".1",sizeof(".1"));
	else if(partno==2) 
		senddata(socket,".2",sizeof(".2"));
	else if(partno==3)
		senddata(socket,".3",sizeof(".3"));
	else
		senddata(socket,".4",sizeof(".4"));

	bytes_sent=0;
	bzero(tempbuf,sizeof(tempbuf));

}



