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
    int sockFd,port;
    unsigned int addrLength, clientLength;
    int fd,msgSent;
    char filename[256],c[2000];
    struct sockaddr_in serverAddress, clientAddress;
    
    /* initialize the port to accept from command line */
    port=atoi(argv[1]);
    
    /* create a socket sockFd for UDP */
    if((sockFd=socket(AF_INET,SOCK_DGRAM,0))==-1)
    {
        perror("Failed to create a socket\n");
        exit(-1);
    }
    
    /*initialize the structure*/
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_port=htons(port);
    serverAddress.sin_addr.s_addr=INADDR_ANY;
    bzero(&(serverAddress.sin_zero),8);
    addrLength=sizeof(serverAddress);
    
    /* assigns the local protocol address along with port number to the socket*/
    if(bind(sockFd,(struct sockaddr *)&serverAddress, addrLength)==-1)
    {
        perror("Bind Error\n");
        exit(-1);
    }
    
    
    printf("\nUDP server is waiting for the client to get connected on port %d\n", port);
    //fflush(stdout);
    
    clientLength=sizeof(clientAddress);
    bzero(filename,256);
    
    
    /* reads the file name from Client */
    recvfrom(sockFd,filename,255,0,(struct sockaddr *)&clientAddress,&clientLength);
    
    
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
    sendto(sockFd,c,strlen(c),0,(struct sockaddr *)&clientAddress,clientLength);
    
    /* close the socket created */
    close(sockFd);		
    
    return 0;
}