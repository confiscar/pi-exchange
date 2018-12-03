//#include "exchange.h"

#include <stdlib.h>
#include <stdio.h>
#include "notification.h"
#include <sys/socket.h>

#define BUFFER_SIZE 1024

extern float buyPrice;
extern float sellPrice;

notificationPoll * nPoll = NULL;

void notify(){

    float tempBuyPrice = 0;
    float tempSellPrice = 0;
    char sendBuffer[BUFFER_SIZE];
    // do endless loop to check if best price changes
    // once changed, send info to all connect client
    while(1){
        if(tempBuyPrice != buyPrice){
            tempBuyPrice = buyPrice;
            sprintf(sendBuffer, "best buy: %f", tempBuyPrice);
            sendToAll(sendBuffer);
        }
        if(tempSellPrice != sellPrice){
            tempSellPrice = sellPrice;
            sprintf(sendBuffer, "best sell: %f", tempSellPrice);
            sendToAll(sendBuffer);
        }

    }
}

void sendToAll(char * sendBuffer){
    notificationPoll * temp = NULL;
    printf("%s \n", sendBuffer);
    for(temp = nPoll; temp != NULL; temp = (notificationPoll *)temp -> hh.next){
        int len = send(temp -> noti_sockfd, sendBuffer, 1024,0);
    }
}

