#include "requestHandlr.h"
#include <pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 1024

sem_t synchronize;
extern float buyPrice;
extern float sellPrice;

void handleRequest(int * conn)
{
    sem_wait(&synchronize);
    int sockfd = * conn;
    sem_post(&synchronize);
    char buffer[BUFFER_SIZE];
    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        int len = recv(sockfd, buffer, sizeof(buffer),0);
        if(strcmp(buffer,"exit\n")==0)
        {
            printf("client %d exited.\n",sockfd);
            break;
        }
        printf("client %d send:\n",sockfd);

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
                printf("------------------\nplace buy order with \nexchange ID: %d \n", temp -> exchangeId);
                printf("price: %f \namount: %d \norder ID: %d \n\nbest buy price: %f, best sell price: %f\n------------------\n", price, amount, orderId, buyPrice, sellPrice);
            } else {
                temp = placeSellOrder(price, amount, orderId);
                printf("------------------\nplace sell order with \nexchange ID: %d \n", temp -> exchangeId);
                printf("price: %f \namount: %d \norder ID: %d \n\nbest buy price: %f, best sell price: %f\n------------------\n", price, amount, orderId, buyPrice, sellPrice);
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
