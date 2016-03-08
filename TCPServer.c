#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    /* declare the variables */
	int sockFd,port,clientSock;
	unsigned int addrLength, clientLength;
	int fd,msgSent;
	char filename[256],c[2000];
	struct sockaddr_in serverAddress, clientAddress;
    
    /* initialize the port to accept from command line */
	port=atoi(argv[1]);
    
    /* create a socket sockFd for TCP */
	if((sockFd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("Failed to create a socket\n");
		exit(-1);
	}
    
     /*initialize the structure*/
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_port=htons(port);
	serverAddress.sin_addr.s_addr=INADDR_ANY;
	bzero(&(serverAddress.sin_zero),8);
	addrLength=sizeof(struct sockaddr_in);
    
    /* assigns the local protocol address along with port number to the socket*/
	if(bind(sockFd,(struct sockaddr *)&serverAddress, addrLength)==-1)
	{
		perror("Bind Error\n");
		exit(-1);
	}

    /* listens for socket connections and limit the queue of incoming connections */
     if((listen(sockFd,5))==-1)
	{

		perror("failed to Listen\n");
		exit(-1);
	}
    
    

    printf("\nTCP server is waiting for the client to get connected on port %d\n", port);
	fflush(stdout);
	
	clientLength=sizeof(clientAddress);
    
    /* extracts the first connection on the queue of pending connections */
    if ((clientSock=accept(sockFd, (struct sockaddr *)&clientAddress, &clientLength))==-1)
    {
        perror("Failed to accept\n");
        exit(-1);
    }

		
    bzero(filename,256);
	/* reads the file name from Client */
    read(clientSock,filename,255);
    
    /* check if file exists */
    fd=open(filename,O_RDONLY);
		if( access( filename, F_OK ) != -1 )
			 {
				printf("Reading the file \"%s\".\n",filename);
             }
        else
			 {
 		   		// file doesn't exist
				printf("\nThe file does not exist\n.");
			 }
    
        /* Read the file contents and store it in Buffer C */
		read(fd,c,1999);
    
        /* send the buffer contents to Client */
		send(clientSock,c,1999,0);
    
        /* close the socket created */
		close(clientSock);
		
        close(sockFd);		

	return 0;
}