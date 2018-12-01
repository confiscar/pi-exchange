#include "requestHandlr.h"
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

        order * temp = NULL;

        // decide what kind of request
        if(strcmp(pOc, "p") == 0){
            float price = atof(strtok( NULL, delim));
            int amount = atoi(strtok( NULL, delim));
            int orderId = atoi(strtok( NULL, delim));
            if(strcmp(bOs, "b") == 0){
                temp = placeBuyOrder(price, amount, orderId);
                printf("------------------\nplace buy order with \nexchange ID %d \n", temp -> exchangeId);
                printf("price:%f \namount: %d \norder ID:%d \n------------------\n", price, amount, orderId);
            } else {
                temp = placeSellOrder(price, amount, orderId);
                printf("------------------\nplace sell order with \nexchange ID %d \n", temp -> exchangeId);
                printf("price:%f \namount: %d \norder ID:%d \n------------------\n", price, amount, orderId);
            }
        } else{
            float price = atof(strtok( NULL, delim));
            int exchangeId = atoi(strtok( NULL, delim));
            if(strcmp(bOs, "b") == 0){
                temp = cancelBuyOrder(price, exchangeId);
                if(temp == NULL){
                    printf("------------------\norder not exist, please check again\n------------------\n");
                    send(sockfd, "order not exist, please check\n", 30, 0);
                    continue;
                }
                printf("------------------\ncancel buy order with \nexchange ID %d \n", temp -> exchangeId);
                printf("price:%f \namount: %d \norder ID:%d \n------------------\n", temp -> price, temp -> amount, temp -> orderId);
            } else {
                temp = cancelSellOrder(price, exchangeId);
                if(temp == NULL){
                    printf("------------------\norder not exist, please check again\n------------------\n");
                    send(sockfd, "order not exist, please check\n", 30, 0);
                    continue;
                }
                printf("------------------\ncancel sell order with \nexchange ID %d \n", temp -> exchangeId);
                printf("price:%f \namount: %d \norder ID:%d \n------------------\n", temp -> price, temp -> amount, temp -> orderId);
            }
        }

        if(temp -> status == 0){
            send(sockfd, "not matched - held in book\n", 30, 0);
        } else if(temp -> status == 1) {
            send(sockfd, "matched \n", 30, 0);
        } else{
            send(sockfd, "canceled \n", 30, 0);
        }

    }
    close(sockfd);
}
