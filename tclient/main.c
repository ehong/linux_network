#include    <time.h>
#include    <netinet/in.h>
#include    <sys/socket.h>
#include    <sys/types.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <errno.h>
#include    <sys/wait.h>

#define MAXLINE 177
#define LISTENQ 174

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if(argc != 2){
	printf("usage: a.out <IPaddress>");
	return 0;
    }
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
    
    connect(sockfd,(struct sockaddr*)&servaddr, sizeof(servaddr));

    n=recv(sockfd,recvline,MAXLINE,0);
    recvline[n]='\0';

    printf("Receive: %s",recvline);
    close(sockfd);
}
