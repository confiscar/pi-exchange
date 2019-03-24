#include "requestHandlr.h"
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 1024

extern float buyPrice;
extern float sellPrice;

void handleRequest(user_client * pair)
{
    int sockfd = pair -> sockfd;
    int userid = pair -> userId;
    char buffer[BUFFER_SIZE];

    char invalid_msg[1024];
    memset(invalid_msg,0,sizeof(invalid_msg));
    sprintf(invalid_msg, "------------------\ninvalid input\n------------------\n");

    char not_exist_msg[1024];
    memset(not_exist_msg,0, sizeof(not_exist_msg));
    sprintf(not_exist_msg,"------------------\norder not exist, please check\n------------------\n");

    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        int len = recv(sockfd, buffer, sizeof(buffer),0);
        if(strcmp(buffer,"exit\n")==0)
        {
            printf("client %d exited.\n",sockfd);
            break;
        }
        printf("client received: %s", buffer);
        printf("client %d send:\n",sockfd);

        // split the string parameter by comma (see readme for more specific definition of parameter)
        char * delim = ",";
        char * pOc = strtok(buffer, delim); // first parameter, stands for place or cancel
        char * bOs = strtok( NULL, delim); // second parameter, stands for buy or sell

        order * temp = NULL;

        // decide what kind of request by compare 1st and 2nd parameter
        if(strcmp(pOc, "p") == 0){

            char * priceStr = strtok(NULL, delim); // third parameter, stands for price
            char * amountStr = strtok( NULL, delim); // fouth parameter, stands for amount
            char * orderIdStr = strtok(NULL, delim); // fifth parameter, stands for order id

            if(priceStr == NULL || amountStr == NULL || orderIdStr == NULL){
                    printf("invalid input\n");
                    send(sockfd, invalid_msg, sizeof(invalid_msg), 0);
                    continue;
            }

            float price = atof(priceStr);
            printf("%f | ", price);
            int amount = atoi(amountStr);
            printf("%d | ", price);
            int orderId = atoi(orderIdStr);
            printf("%d | ", price);

            if(price == 0 || amount == 0 || orderId == 0) {
                printf("invalid input\n");
                send(sockfd, invalid_msg, sizeof(invalid_msg), 0);
                continue;
            }

            if(strcmp(bOs, "b") == 0){
                temp = placeBuyOrder(price, amount, orderId, userid);
                printf("------------------\nplace buy order with \nexchange ID: %d \n", temp -> exchangeId);
                printf("price: %f \namount: %d \norder ID: %d \nbest buy price: %f, best sell price: %f\n------------------\n", price, amount, orderId, buyPrice, sellPrice);
            } else if(strcmp(bOs, "s") == 0){
                temp = placeSellOrder(price, amount, orderId, userid);
                printf("------------------\nplace sell order with \nexchange ID: %d \n", temp -> exchangeId);
                printf("price: %f \namount: %d \norder ID: %d \nbest buy price: %f, best sell price: %f\n------------------\n", price, amount, orderId, buyPrice, sellPrice);
            } else {
                printf("invalid input\n");
                send(sockfd, invalid_msg, sizeof(invalid_msg), 0);
                continue;
            }
        } else if(strcmp(pOc, "c") == 0){
            float price = atof(strtok( NULL, delim));
            int exchangeId = atoi(strtok( NULL, delim));
            if(price == 0 || exchangeId == 0){
                printf("invalid input\n");
                send(sockfd, invalid_msg, sizeof(invalid_msg), 0);
                continue;
            }
            if(strcmp(bOs, "b") == 0){
                temp = cancelBuyOrder(price, exchangeId);
                if(temp == NULL){
                    printf("------------------\norder not exist, please check again\n------------------\n");
                    send(sockfd, not_exist_msg, sizeof(not_exist_msg), 0);
                    continue;
                }
                printf("------------------\ncancel buy order with \nexchange ID %d \n", temp -> exchangeId);
                printf("price:%f \namount: %d \norder ID:%d \n------------------\n", temp -> price, temp -> amount, temp -> orderId);
            } else if(strcmp(bOs, "s") == 0){
                temp = cancelSellOrder(price, exchangeId);
                if(temp == NULL){
                    printf("------------------\norder not exist, please check again\n------------------\n");
                    send(sockfd, not_exist_msg, sizeof(not_exist_msg), 0);
                    continue;
                }
                printf("------------------\ncancel sell order with \nexchange ID %d \n", temp -> exchangeId);
                printf("price:%f \namount: %d \norder ID:%d \n------------------\n", temp -> price, temp -> amount, temp -> orderId);
            } else {
                printf("invalid input\n");
                send(sockfd, invalid_msg, sizeof(invalid_msg), 0);
                continue;
            }
        } else {
            printf("invalid input\n");
            send(sockfd, invalid_msg, sizeof(invalid_msg), 0);
            continue;
        }

        // send specific information to client
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer, "current order\norder ID: %d\nexchange ID: %d\nprice: %f\namount: %d\nstatus: %d\n",temp->orderId, temp->exchangeId, temp->price, temp->amount, temp->status);
        send(sockfd, buffer, sizeof(buffer), 0);

    }
    close(sockfd);
}
