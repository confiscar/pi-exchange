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

#define PORT  8890
#define BUFFER_SIZE 1024

int user_id = -1;
int request_status = 0;

void receiver(int * sock_cli){
    int sock_fd = *sock_cli;
    char recvbuf[BUFFER_SIZE];
    while(1){
        recv(sock_fd, recvbuf, 1024, 0);
        if(recvbuf[0] == '-'){
            request_status = 1;
        }
        printf("%s", recvbuf);
        memset(recvbuf,0,sizeof(recvbuf));
    }
}

int main(int argc, char **argv)
{
    if(argc!=2)
    {
        printf("usage: client IP \n");
        exit(0);
    }

    //define socket for client
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);
    int sock_cli_noti = socket(AF_INET,SOCK_STREAM, 0);

    //define sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); // get server address as command line parameter
    servaddr.sin_port = htons(PORT);  //port of server

    //connect to server, return 1 if success, else -1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("connect");
        exit(1);
    }
    printf("connect server(IP:%s).\n",argv[1]);

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];

    // send a negative user_id to server and receive a user_id assigned by server
    // once a user_id is assigned, send a response to server
    recv(sock_cli, recvbuf, sizeof(recvbuf),0);
    printf("%s", recvbuf);

    pthread_t tid;
    // create a thread for handle notification
    if(pthread_create(&tid, NULL, (void *)&receiver,&sock_cli)!=0){
        exit(0);
    }

    // client send the message input in terminal to server and receive a response
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    {
        send(sock_cli, sendbuf, strlen(sendbuf),0); //send
        request_status = 0;
        if(strcmp(sendbuf,"exit\n")==0)
        {
	    printf("client exited.\n");
            break;
        }
        while(request_status == 0){

        }

        memset(sendbuf, 0, sizeof(sendbuf));
    }

    close(sock_cli);
    return 0;
}




