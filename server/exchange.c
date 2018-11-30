/*
 * exchange.c
 *
 *  Created on: 2018/11/30
 *      Author: Ke CHEN
 */

#include "exchange.h"

book * buyBook = NULL;
book * sellBook = NULL;
float buyPrice = 0;
float sellPrice = 0;

// not any of orders are freed currently
// decide when to free once the way to inform client is decided

order * placeBuyOrder(float price, int amount, int orderId){
    order * currentOrder = generateOrder(price, amount, orderId);
    order * temp = matchOrder(currentOrder, &sellBook);
    if(temp == NULL){
        addToBook(currentOrder, &buyBook);
    }
    return currentOrder;
}

order * placeSellOrder(float price, int amount, int orderId){
    order * currentOrder = generateOrder(price, amount, orderId);
    order * temp = matchOrder(currentOrder, &buyBook);
    if(temp == NULL){
        addToBook(currentOrder, &sellBook);
    } else{
        return currentOrder;
    }
}

order * matchOrder(order * curOrder, book ** curBook){
    float price = curOrder -> price;
    int amount = curOrder -> amount;
    book * tempBook = NULL;
    order * tempOrder = NULL;
    HASH_FIND(hh, * curBook, &price, 4, tempBook);
    if(tempBook == NULL){
        return tempOrder;
    }
    priceBucket * tempPriceBucket = tempBook -> pb;
	priceBucket * orderPriceBucket = NULL;
	for(orderPriceBucket = tempPriceBucket; orderPriceBucket != NULL; orderPriceBucket = (priceBucket*)orderPriceBucket -> hh.next){
        if(orderPriceBucket -> curOrder -> amount == amount){
            tempOrder = orderPriceBucket -> curOrder;
            deleteFromBook(orderPriceBucket -> curOrder, curBook);
            curOrder -> status = 1;
            tempOrder -> status = 1;
            return tempOrder;
        }
	}
	tempOrder = NULL;
	return tempOrder;

}
