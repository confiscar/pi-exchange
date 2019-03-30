#include "orderBook.h"

void addToBook(order * curOrder, book ** curBook){
	book * tempBook = NULL;
	priceBucket * tempPb = NULL;
	float tempPrice = curOrder -> price;
	/*
	* check if the price is already in the book
	* if not, create a new price bucket and add it to book
	* else, add the order to corresponding price bucket retrieval from book
	*/
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
    // check if the price of order exists in book
    HASH_FIND(hh, *curBook, &tempPrice, sizeof(float), tempBook);
    if(tempBook == NULL){
        printf("not found in book \n");
        return;
    }
    tempPb = tempBook -> pb;
    /*
    * check if the price bucket only contained one element
    *if yes, delete both order from price bucket and price bucket from book
    *else, only delete order from book
    */
    if(tempPb -> hh.next == NULL){
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
}

