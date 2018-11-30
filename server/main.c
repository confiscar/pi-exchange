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
	struct order * o1 = generateOrder(11, 10, 1);
	struct order * o2 = generateOrder(11, 12, 2);
	struct order * o3 = generateOrder(12, 20, 3);
	addToBook(o1, &bookTest);
	addToBook(o2, &bookTest);
	addToBook(o3, &bookTest);
	deleteFromBook(o1, &bookTest);
	deleteFromBook(o2, &bookTest);
	deleteFromBook(o3, &bookTest);
	book * temp = NULL;
	int price = 11;
	HASH_FIND_INT(bookTest, &price, temp);
	if(temp == NULL){
            printf("exit\n");
        exit(0);
	}
    priceBucket * hash_packet = temp -> pb;
	struct priceBucket* tempPriceBucket = NULL;
	for (tempPriceBucket = hash_packet; tempPriceBucket != NULL; tempPriceBucket = (priceBucket*)tempPriceBucket->hh.next)
        printf("%d %d %d %d\n", tempPriceBucket -> curOrder-> price, tempPriceBucket -> curOrder-> amount, tempPriceBucket -> curOrder-> orderId,tempPriceBucket -> curOrder-> exchangeId);
}
