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

void receiver(int * sock_client_noti){
    int sock_fd = *sock_client_noti;
    char recvbuf[BUFFER_SIZE];
    while(1){
        recv(sock_fd, recvbuf, 1024, 0);
        if(recvbuf[0] == 'b'){
            printf("// %s", recvbuf);
        } else {
            printf("%s", recvbuf);
        }
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

    sprintf(sendbuf, "%d\n", user_id);

    // send a negative user_id to server for indicating it is the first socket of a client, which is used to send request and get response
    send(sock_cli, sendbuf, sizeof(sendbuf),0);
    recv(sock_cli, recvbuf, sizeof(recvbuf),0);
    user_id = atoi(recvbuf);
    printf("user_id assigned: %d \n", user_id);

    // if server assigned a i=user_id to client, create second socket for receive notification
    // also sent user_id to help server identify it is a socket for notification
    if(user_id >= 0){
        if (connect(sock_cli_noti, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
            perror("connect");
            exit(1);
        }
        printf("notification socket connected \n");
        sprintf(sendbuf, "%d", user_id);
        send(sock_cli_noti, sendbuf, sizeof(sendbuf),0);
        pthread_t tid;
        // create a thread for handle notification
        if(pthread_create(&tid, NULL, (void *)&receiver,&sock_cli_noti)!=0){
            exit(0);
        }
        printf("receiver thread created \n");
    }

    // client send the message input in terminal to server and receive a response
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    {
        send(sock_cli, sendbuf, strlen(sendbuf),0); //send
        if(strcmp(sendbuf,"exit\n")==0)
        {
	    printf("client exited.\n");
            break;
        }
        printf("client receive:\n");
        recv(sock_cli, recvbuf, sizeof(recvbuf),0); //receive
        fputs(recvbuf, stdout);

        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }

    close(sock_cli);
    return 0;
}




