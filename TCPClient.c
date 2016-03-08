#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<strings.h>

int main(int argc,char *argv[])
{
	/* declare the variables */
    int sockfd,portno;
	struct sockaddr_in serverAddr;
	char filename[256],c[2000];
	
    /* initialize the port to accept from command line */
	portno=atoi(argv[1]);
    
    /* create a socket sockFd for TCP */
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("failed to open socket\n");
		exit(-1);
	}

    /*initialize the structure*/
    bzero((char *)&serverAddr,sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(portno);
	serverAddr.sin_addr.s_addr=INADDR_ANY;	

	/* establish a connection on a socket through 3-way handshake */
	if((connect(sockfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr)))==-1)
	{

		perror("failed to connect\n");
		exit(-1);

	}
    
    /* Entering the file name */
	printf("enter path with filename\n\n");
	scanf("%s",filename);
	
    /* write the filename to the socket */
    write(sockfd,filename,255);
    bzero(c,2000);
    
    /* receive the contents of the file from the buffer sent by the Server */
    recv(sockfd,c,1999,0);
    printf("\nreceived:\n%s ",c);
	
     /* close the created socket */
	close(sockfd);
	return 0;
}