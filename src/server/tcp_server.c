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
#include "notification.h"

#define PORT  8890
#define QUEUE_SIZE   10

extern notificationPoll *  nPoll;
int user_id = 0;
extern float buyPrice;
extern float sellPrice;

void addToNotificationPoll(int user_id, int conn){
    notificationPoll * temp = NULL;
    HASH_FIND_INT(nPoll, &user_id, temp);
    if(temp == NULL){
        temp = malloc(sizeof(notificationPoll));
        temp -> user_id = user_id;
        temp -> noti_sockfd = conn;
        HASH_ADD_INT(nPoll, user_id, temp);
    } else {
        temp -> noti_sockfd = conn;
    }
}

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

    pthread_t noti;
    if(pthread_create(&noti, NULL, (void *)&notify,NULL)!=0)//child process
    {
        exit(0);
    }

    for(;;)
    {
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);
        //block at accept, once success, it will return a non-negative socket_fd, else -1
        int conn = accept(server_sockfd, (struct sockaddr*)&client_addr,&length);
        printf("address of conn %d\n", &conn);
    	if(conn<0)
    	{
            perror("connect");
            exit(1);
    	}
        printf("new client accepted.\nUser ID: %d \n", user_id);
        char sendBuf[1024];
        char recvBuf[1024];

        // assign a user_id to client
        // else add it to notification poll
        sprintf(sendBuf, "sell price: %f, buy price: %f\n", sellPrice, buyPrice);
        send(conn, sendBuf, 1024, 0);
        pthread_t tid;
        user_client * pair = malloc(sizeof(user_client));
        pair -> sockfd = conn;
        pair -> userId = user_id;
        if(pthread_create(&tid, NULL, (void *)&handleRequest, pair)!=0)//create process
        {
            exit(0);
        }
        printf("thread %d created.\n", tid);
        addToNotificationPoll(user_id, conn);
        printf("socket added to notification poll \n");

        user_id ++;

    }

    printf("closed.\n");
    close(server_sockfd);
    return 0;
}
