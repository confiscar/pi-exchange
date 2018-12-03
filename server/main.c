/*
 * main.c
 *
 *  Created on: 2018/11/29
 *      Author: Ke CHEN
 */
#include "exchange.h"
#include <stdio.h>

extern book * buyBook;
extern book * sellBook;

// mainly for test the functions
// no need to look at this file

int main(){
    printf("%d \n",placeBuyOrder(1.1,10,1) ->status);
    printf("%d \n",placeBuyOrder(1.1,11,1) ->status);
    printf("%d \n",placeBuyOrder(1.2,20,1) ->status);
    printf("%d \n",placeSellOrder(1.1,10,2) ->status);

	book * temp = NULL;
	float price = 1.1;
	HASH_FIND(hh, buyBook, &price, sizeof(float), temp);
	if(temp == NULL){
            printf("no order for price %f exists\n", price);
        exit(0);
	}
    priceBucket * hash_packet = temp -> pb;
	struct priceBucket* tempPriceBucket = NULL;
	for (tempPriceBucket = hash_packet; tempPriceBucket != NULL; tempPriceBucket = (priceBucket*)tempPriceBucket->hh.next)
        printf("%f %d %d %d\n", tempPriceBucket -> curOrder-> price, tempPriceBucket -> curOrder-> amount, tempPriceBucket -> curOrder-> orderId,tempPriceBucket -> curOrder-> exchangeId);
}
