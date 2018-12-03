
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <pthread.h>
#include <semaphore.h>

#include "exchange.h"
#include "order.h"
#include "requestHandlr.h"

#define PORT  8890
#define QUEUE_SIZE   10

extern sem_t synchronize;

int main(int argc, char **argv)
{
    //Socket descriptor that defines the TCP connection for IPV4
    int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);

    //define sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_sockaddr.sin_port = htons(PORT);

    //bind successfully return 0, else -1
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }
    printf("bind success.\n");

    //listen successfully return 0, else -1, allow maximum QUEUE_SIZE listening connection
    if(listen(server_sockfd,QUEUE_SIZE) == -1)
    {
        perror("listen");
        exit(1);
    }
    printf("listen success.\n");

    sem_init(&synchronize, 0, 1);

    for(;;)
    {
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);
        //进程阻塞在accept上，成功返回非负描述字，出错返回-1
        int conn = accept(server_sockfd, (struct sockaddr*)&client_addr,&length);
    	if(conn<0)
    	{
            perror("connect");
            exit(1);
    	}
        printf("new client accepted.\n");

        pthread_t tid;
        if(pthread_create(&tid, NULL, (void *)&handleRequest,&conn)!=0)//child process
        {
            //close(server_sockfd);//close listening in child process
            //handleRequest(conn);//handle listened connection
            exit(0);
        }
        printf("thread %d created.\n", tid);
    }

    printf("closed.\n");
    close(server_sockfd);
    return 0;
}
