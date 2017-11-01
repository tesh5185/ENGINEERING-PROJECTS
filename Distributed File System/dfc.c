#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#define partsize 1024*1024*1024

char *part1,*part2,*part3,*part4,*ret,*con,*dfs1,*dfs2,*dfs3,*dfs4;
char *delimiter=" ";

//trial Linked lists
/*struct Node
{
  char DFS[25];
  struct Node *next;
};
*/
char *DFS1, *DFS2, *DFS3, *DFS4;
char reply[20];
void main(int argc, char *argv[])
{
	
	/*struct Node *DFS1=NULL;
	struct Node *DFS2=NULL;
	struct Node *DFS3=NULL;
	struct Node *DFS4=NULL;
	DFS1= (struct Node*)malloc(sizeof(struct Node));
	DFS2= (struct Node*)malloc(sizeof(struct Node));
	DFS3= (struct Node*)malloc(sizeof(struct Node));
	DFS4= (struct Node*)malloc(sizeof(struct Node));*/
	part1=malloc(partsize*sizeof(char));
	part2=malloc(partsize*sizeof(char));
	part3=malloc(partsize*sizeof(char));
	part4=malloc(partsize*sizeof(char));
	con=malloc(50*sizeof(char));
	DFS1=malloc(25*sizeof(char));
	DFS2=malloc(25*sizeof(char));
	DFS3=malloc(25*sizeof(char));
	DFS4=malloc(25*sizeof(char));
	FILE *fp,*ft, *fcon;
	int nbytes;
	
	char command[100];
	//fgets(command,sizeof(command),stdin);
	fcon=fopen("dfc.conf","r");
	
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
	}
	/*printf("%s %d\n",DFS1,(int)strlen(DFS1));
	printf("%s %d\n",DFS2,(int)strlen(DFS2));
	printf("%s %d\n",DFS3,(int)strlen(DFS3));
	printf("%s %d\n",DFS4,(int)strlen(DFS4));*/	
	fclose(fcon);
	int sock1,sock2,sock3,sock4;
	struct sockaddr_in server1,server2,server3,server4;
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
	/*printf("before and after %s*%s\n",DFS1,dfs1);
	printf("before and after %s*%s\n",DFS2,dfs2);
	printf("before and after %s*%s\n",DFS3,dfs3);
	printf("before and after %s*%s\n",DFS4,dfs4);*/
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
	
	if (connect(sock1 , (struct sockaddr *)&server1 , sizeof(server1)) < 0)
    {
        perror("connect failed. Error");
        //return 1;
    }
     
    puts("Connected\n");
	
	if( send(sock1 , DFS1 , strlen(DFS1) , 0) < 0)
        {
            puts("Send failed");
            //return 1;
        }
         
        //Receive a reply from the server
    if( recv(sock1, reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            //break;
        }
	printf("Received message is %s\n",reply);
	if (connect(sock2 , (struct sockaddr *)&server2 , sizeof(server2)) < 0)
    {
        perror("connect failed. Error");
        //return 1;
    }
     
    puts("Connected\n");
	
	if( send(sock2 , DFS2 , strlen(DFS2) , 0) < 0)
        {
            puts("Send failed");
            //return 1;
        }
         
        //Receive a reply from the server
    if( recv(sock2 , reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            //break;
        }
	printf("Received message is %s\n",reply);
	if (connect(sock3 , (struct sockaddr *)&server3 , sizeof(server3)) < 0)
    {
        perror("connect failed. Error");
        //return 1;
    }
     
    puts("Connected\n");
	
	if( send(sock3 , DFS3 , strlen(DFS3) , 0) < 0)
        {
            puts("Send failed");
            //return 1;
        }
         
        //Receive a reply from the server
    if( recv(sock3 , reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            //break;
        }
	printf("Received message is %s\n",reply);
	if (connect(sock4 , (struct sockaddr *)&server4 , sizeof(server4)) < 0)
    {
        perror("connect failed. Error");
        //return 1;
    }
     
    puts("Connected\n");
	
	if( send(sock4 , DFS4 , strlen(DFS4) , 0) < 0)
        {
            puts("Send failed");
            //return 1;
        }
         
        //Receive a reply from the server
    if( recv(sock4 , reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            //break;
        }
	printf("Received message is %s\n",reply);
	




	/*gets(command);
		

	fp= fopen(command,"r");
	fseek(fp, 0 , SEEK_END);
	int fsize=ftell(fp);
	
	fseek(fp, 0 , SEEK_SET);
	printf("Total file size is %d\n", fsize);
	int psize=fsize/4;
	printf("part size is %d\n", psize);
	nbytes=fread(part1,sizeof(char),psize,fp);
	printf("Bytes read are %d\n",nbytes);
	nbytes=fread(part2,sizeof(char),psize,fp);
	printf("Bytes read are %d\n",nbytes);
	nbytes=fread(part3,sizeof(char),psize,fp);
	printf("Bytes read are %d\n",nbytes);
	nbytes=fread(part4,sizeof(char),(fsize-3*psize),fp);
	printf("Bytes read are %d\n",nbytes);
	
	fclose(fp);
	*/


	/*ft=fopen("ex_copy.pdf","w");
	nbytes=fwrite(part1,sizeof(char),psize,fp);
	printf("Bytes written are %d\n",nbytes);
	nbytes=fwrite(part2,sizeof(char),psize,fp);
	printf("Bytes written are %d\n",nbytes);
	nbytes=fwrite(part3,sizeof(char),psize,fp);
	printf("Bytes written are %d\n",nbytes);
	nbytes=fwrite(part4,sizeof(char),(fsize-3*psize),fp);
	printf("Bytes written are %d\n",nbytes);
	fseek(ft,0,SEEK_END);
	fsize=ftell(ft);
	printf("Total file size is %d\n", fsize);
	fclose(ft);*/
	free(part1);
	free(part2);
	free(part3);
	free(part4);
	free(con);
	free(DFS1);
	free(DFS2);
	free(DFS3);
	free(DFS4);
}
