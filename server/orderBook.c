/*
 * orderBook.c
 *
 *  Created on: 2018Äê11ÔÂ29ÈÕ
 *      Author: 13245
 */

#include "orderBook.h"
int exchangeId = 0;

void addToBook(order * curOrder, book ** curBook){
	book * tempBook = NULL;
	priceBucket * tempPb = NULL;
	int tempPrice = curOrder -> price;
	HASH_FIND_INT(*curBook, &tempPrice, tempBook);
	if(tempBook == NULL){
		tempBook = malloc(sizeof(book));
		tempBook -> price = tempPrice;
		tempBook -> pb = NULL;
		tempPb = malloc(sizeof(priceBucket));
		tempPb -> exchangeId = exchangeId;
		curOrder -> exchangeId = exchangeId;
		tempPb -> curOrder = curOrder;
		HASH_ADD_INT((tempBook -> pb), exchangeId, tempPb);
		HASH_ADD_INT(*curBook, price, tempBook);
	} else{
		tempPb = malloc(sizeof(priceBucket));
		tempPb -> exchangeId = exchangeId;
		curOrder -> exchangeId = exchangeId;
		tempPb -> curOrder = curOrder;
		HASH_ADD_INT((tempBook -> pb), exchangeId, tempPb);
	}
	exchangeId ++ ;
}

void deleteFromBook(order * curOrder, book ** curBook){
    book * tempBook = NULL;
    priceBucket * tempPb = NULL;
    int tempPrice = curOrder -> price;
    HASH_FIND_INT(*curBook, &tempPrice, tempBook);
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
    free(curOrder);

}

