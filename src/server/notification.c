#include <stdlib.h>
#include <stdio.h>
#include "notification.h"
#include <sys/socket.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024

extern float buyPrice;
extern float sellPrice;

notificationPoll * nPoll = NULL;

void notify(){

    float tempBuyPrice = 0;
    float tempSellPrice = 0;
    char sendBuffer[BUFFER_SIZE];
    struct timeval time;
    // do endless loop to check if best price changes
    // once changed, send info to all connect client
    while(1){
        memset(sendBuffer,0, sizeof(sendBuffer));
        gettimeofday(&time, NULL);
        if(tempBuyPrice != buyPrice){
            tempBuyPrice = buyPrice;
            sprintf(sendBuffer, "best buy: %f, time: %ld \n", tempBuyPrice, time.tv_sec);
            sendToAll(sendBuffer);
        }
        if(tempSellPrice != sellPrice){
            tempSellPrice = sellPrice;
            sprintf(sendBuffer, "best sell: %f, time: %ld \n", tempSellPrice, time.tv_sec);
            sendToAll(sendBuffer);
        }

    }
}

void sendToAll(char * sendBuffer){
    notificationPoll * temp = NULL;
    // printf("this info will notify all users: %s \n", sendBuffer);
    for(temp = nPoll; temp != NULL; temp = (notificationPoll *)temp -> hh.next){
        int len = send(temp -> noti_sockfd, sendBuffer, 1024,0);
    }
}

void sendToUser(order * orderTobeInform){
    int userId = orderTobeInform ->userId;
    notificationPoll * user_notify;
    HASH_FIND_INT(nPoll,&userId,user_notify);
    if(user_notify != NULL){
        char buffer[1024];
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer, "~~~~~~~~~~~~~~~~~~\n~user ID: %d\n~order ID: %d\n~exchange ID: %d\n~price: %f\n~amount: %d\n~status: %d\n~~~~~~~~~~~~~~~~~~\n",orderTobeInform ->userId, orderTobeInform->orderId, orderTobeInform->exchangeId, orderTobeInform->price, orderTobeInform->amount, orderTobeInform->status);
        printf("print for test: \n%s", buffer);
        send(user_notify -> noti_sockfd, buffer, sizeof(buffer), 0);
    }
}

