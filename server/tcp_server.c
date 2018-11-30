
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

#include "exchange.h"
#include "order.h"

#define PORT  8890
#define QUEUE_SIZE   10
#define BUFFER_SIZE 1024

void handleRequest(int sockfd)
{
    char buffer[BUFFER_SIZE];
    pid_t pid = getpid();
    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        int len = recv(sockfd, buffer, sizeof(buffer),0);
        if(strcmp(buffer,"exit\n")==0)
        {
            printf("child process: %d exited.\n",pid);
            break;
        }
        printf("pid:%d receive:\n",pid);

        // split the string parameter
        char * delim = ",";
        char * pOc = strtok(buffer, delim);
        char * bOs = strtok( NULL, delim);
        float price = atof(strtok( NULL, delim));
        int amount = atoi(strtok( NULL, delim));
        int orderId = atoi(strtok( NULL, delim));
        printf("%s %s %f %d %d\n", pOc, bOs, price, amount, orderId);
        order * temp = NULL;

        // decide what kind of request
        if(strcmp(pOc, "p") == 0){
            if(strcmp(bOs, "b") == 0){
                printf("place buy order\n");
                temp = placeBuyOrder(price, amount, orderId);
            } else {
                printf("place sell order\n");
                temp = placeSellOrder(price, amount, orderId);
            }
        }

        if(temp -> status == 0){
            send(sockfd, "not matched - held in book\n", 30, 0);
        } else if(temp -> status == 1) {
            send(sockfd, "matched \n", 30, 0);
        }

    }
    close(sockfd);
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

        pid_t childid;
        if(childid=fork()==0)//child process
        {
            printf("child process: %d created.\n", getpid());
            close(server_sockfd);//close listening in child process
            handleRequest(conn);//handle listened connection
            exit(0);
        }
    }

    printf("closed.\n");
    close(server_sockfd);
    return 0;
}
