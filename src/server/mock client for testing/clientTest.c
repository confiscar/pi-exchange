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
#include <sys/time.h>

#define PORT  8890
#define BUFFER_SIZE 1024
#define times 10

long int getDifferenceInMicroSeconds(struct timeval start, struct timeval end)
{
	long int iSeconds = end.tv_sec - start.tv_sec;
	long int iUSeconds = end.tv_usec - start.tv_usec;
 	long int mtime = (iSeconds * 1000 * 1000 + iUSeconds);
	return mtime;
}

long int getDifferenceInMilliSeconds(struct timeval start, struct timeval end)
{
	long int iSeconds = end.tv_sec - start.tv_sec;
	long int iUSeconds = end.tv_usec - start.tv_usec;
 	long int mtime = (iSeconds * 1000 + iUSeconds / 1000.0);
	return mtime;
}

int main(int argc, char **argv)
{
    if(argc!=2)
    {
        printf("usage: client IP \n");
        exit(0);
    }

    // define tcp socket
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

    // define sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(PORT);  // server port

    // connect to server, return 0 for succuess, otherwise -1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    printf("connect server(IP:%s).\n",argv[1]);

    char recvbuf[BUFFER_SIZE];
    int count = 0;
    struct timeval initial;
    gettimeofday(&initial, NULL);
    struct timeval latency;
    struct timeval temp;
    // send repeated request to sever
    while (count < times)
    {
        //gettimeofday(&temp, NULL);
        send(sock_cli, "p,b,1.1,10,1", 15,0); /// send
        //printf("client receive:\n");
        recv(sock_cli, recvbuf, sizeof(recvbuf),0); /// receive
        if(recvbuf[0] !=  'c'){
            recv(sock_cli, recvbuf, sizeof(recvbuf), 0);
        }
        //gettimeofday(&latency, NULL);
        //printf("latency: %d micro seconds\n", getDifferenceInMicroSeconds(temp,latency));
        //fputs(recvbuf, stdout);
        count++;

        //memset(recvbuf, 0, sizeof(recvbuf));
    }
    while (count < 2 * times)
    {
        //gettimeofday(&temp, NULL);
        send(sock_cli, "p,s,1.1,10,1", 15,0); /// send
        //printf("client receive:\n");
        recv(sock_cli, recvbuf, sizeof(recvbuf),0); /// receive
        if(recvbuf[0] !=  'c'){
            recv(sock_cli, recvbuf, sizeof(recvbuf), 0);
        }
        //gettimeofday(&latency, NULL);
        //printf("latency: %d micro seconds\n", getDifferenceInMicroSeconds(temp,latency));
        //fputs(recvbuf, stdout);
        count++;

        //memset(recvbuf, 0, sizeof(recvbuf));
    }
    struct timeval end;
    gettimeofday(&end, NULL);
    printf("time consumed for %d request: %d\n",2 * times, getDifferenceInMilliSeconds(initial,end));


    //close(sock_cli);
    return 0;
}
