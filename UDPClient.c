#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[])
{
    
    /* declare the variables */
    
    int sockfd,portno;
    struct sockaddr_in serverAddr;
    char filename[256],c[2000];
    unsigned int serverAddr_len;
    
    /* initialize the port to accept from command line */
    portno=atoi(argv[1]);
    
    /* create a socket sockFd for UDP */
    if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
    {
        perror("failed to open socket\n");
        exit(-1);
    }
    
    /*initialize the structure*/
    bzero((char *)&serverAddr,sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(portno);
    serverAddr.sin_addr.s_addr=INADDR_ANY;
    serverAddr_len=sizeof(serverAddr);
    
    /* Entering the file name */
    
    printf("enter path with filename\n\n");
    scanf("%s",filename);
    
    /* send the filename to Server for retrieving the data in the file */
    sendto(sockfd,filename,strlen(filename),0,(struct sockaddr *)&serverAddr,serverAddr_len);
    
    
    /* recieve the data from server of the file */
    bzero(c,2000);
    recvfrom(sockfd,c,1999,0,(struct sockaddr *)&serverAddr,&serverAddr_len);
    printf("Received Data:\n%s\n",c);

    /* close the created socket */
    close(sockfd);
    return 0;
}