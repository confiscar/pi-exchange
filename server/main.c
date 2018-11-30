/*
 * main.c
 *
 *  Created on: 2018/11/29
 *      Author: Ke CHEN
 */

#include "orderBook.h"
//#include "order.h"
#include <stdio.h>

// mainly for test the functions
int main(){
	book * bookTest = NULL;
	struct order * o1 = generateOrder(1.1, 10, 1);
	struct order * o2 = generateOrder(1.1, 12, 2);
	struct order * o3 = generateOrder(1.2, 20, 3);
	addToBook(o1, &bookTest);
	addToBook(o2, &bookTest);
	addToBook(o3, &bookTest);
	//deleteFromBook(o1, &bookTest);
	//deleteFromBook(o2, &bookTest);
	//deleteFromBook(o3, &bookTest);
	book * temp = NULL;
	float price = 1.2;
	HASH_FIND(hh, bookTest, &price, sizeof(float), temp);
	if(temp == NULL){
            printf("no order for price %f exists\n", price);
        exit(0);
	}
    priceBucket * hash_packet = temp -> pb;
	struct priceBucket* tempPriceBucket = NULL;
	for (tempPriceBucket = hash_packet; tempPriceBucket != NULL; tempPriceBucket = (priceBucket*)tempPriceBucket->hh.next)
        printf("%f %d %d %d\n", tempPriceBucket -> curOrder-> price, tempPriceBucket -> curOrder-> amount, tempPriceBucket -> curOrder-> orderId,tempPriceBucket -> curOrder-> exchangeId);
}
