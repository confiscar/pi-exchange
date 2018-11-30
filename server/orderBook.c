/*
 * orderBook.c
 *
 *  Created on: 2018/11/29
 *      Author: Ke CHEN
 */

#include "orderBook.h"

void addToBook(order * curOrder, book ** curBook){
	book * tempBook = NULL;
	priceBucket * tempPb = NULL;
	float tempPrice = curOrder -> price;
	HASH_FIND(hh, *curBook, &tempPrice, sizeof(float), tempBook);
	if(tempBook == NULL){
		tempBook = malloc(sizeof(book));
		tempBook -> price = tempPrice;
		tempBook -> pb = NULL;
		tempPb = malloc(sizeof(priceBucket));
		tempPb -> exchangeId = (curOrder -> exchangeId) ;
		tempPb -> curOrder = curOrder;
		HASH_ADD_INT((tempBook -> pb), exchangeId, tempPb);
		HASH_ADD(hh, *curBook, price, sizeof(float), tempBook);
	} else{
		tempPb = malloc(sizeof(priceBucket));
		tempPb -> exchangeId = (curOrder -> exchangeId);
		tempPb -> curOrder = curOrder;
		HASH_ADD_INT((tempBook -> pb), exchangeId, tempPb);
	}
}

void deleteFromBook(order * curOrder, book ** curBook){
    book * tempBook = NULL;
    priceBucket * tempPb = NULL;
    float tempPrice = curOrder -> price;
    HASH_FIND(hh, *curBook, &tempPrice, sizeof(float), tempBook);
    if(tempBook == NULL){
        printf("not found in book \n");
        return;
    }
    tempPb = tempBook -> pb;
    if(tempPb ->hh.next == NULL){
        HASH_DEL(tempPb, tempPb);
        HASH_DEL(*curBook, tempBook);
        free(tempPb);
        free(tempBook);
    } else {
        priceBucket * orderPb = NULL;
        HASH_FIND_INT(tempPb, &(curOrder -> exchangeId), orderPb);
        order * ot = orderPb -> curOrder;
        HASH_DEL(tempPb, orderPb);
        tempBook -> pb = tempPb;
        free(orderPb);
    }
    //free(curOrder);
}

