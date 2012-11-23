/**
 *A Simple Time Server
 */
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

int main()
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    listenfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    
    listen(listenfd,LISTENQ);

    for(;; )
    {
	connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
	ticks = time(NULL);
	snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
	send(connfd,buff,strlen(buff),0);
	close(connfd);
    }
    

}
