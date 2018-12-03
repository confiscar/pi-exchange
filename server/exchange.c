/*
 * exchange.c
 *
 *  Created on: 2018/11/30
 *      Author: Ke CHEN
 */

#include "exchange.h"
#include <stdio.h>

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
        if(sellPrice < currentOrder -> price){
            sellPrice = currentOrder -> price;
        }
    }
    book * tempBook;
    for(tempBook = sellBook; tempBook != NULL; tempBook = (book *)tempBook -> hh.next){
        if(buyPrice > tempBook -> price){
            buyPrice = tempBook -> price;
        }
    }
    return currentOrder;
}

order * cancelBuyOrder(float price, int exchangeId){
    book * tempBook = NULL;
    priceBucket * tempPriceBucket = NULL;
    priceBucket * orderPriceBucket = NULL;
    order * tempOrder = NULL;
    HASH_FIND(hh, buyBook, &price, 4, tempBook);
    if(tempBook == NULL){
        return tempOrder;
    }
    tempPriceBucket = tempBook -> pb;
    HASH_FIND_INT(tempPriceBucket, &exchangeId, orderPriceBucket);
    if(orderPriceBucket == NULL){
        return tempOrder;
    }
    tempOrder = orderPriceBucket -> curOrder;
    deleteFromBook(tempOrder, &buyBook);
    tempOrder -> status = 2;
    return tempOrder;
}

order * placeSellOrder(float price, int amount, int orderId){
    order * currentOrder = generateOrder(price, amount, orderId);
    order * temp = matchOrder(currentOrder, &buyBook);
    if(temp == NULL){
        addToBook(currentOrder, &sellBook);
        if(buyPrice > currentOrder -> price || buyPrice == 0){
            buyPrice = currentOrder -> price;
        }
    }
    book * tempBook;
    for(tempBook = buyBook; tempBook != NULL; tempBook = (book *)tempBook -> hh.next){
        if(sellPrice < tempBook -> price || sellPrice == 0){
            sellPrice = tempBook -> price;
        }
    }
    return currentOrder;
}

order * cancelSellOrder(float price, int exchangeId){
    book * tempBook = NULL;
    priceBucket * tempPriceBucket = NULL;
    priceBucket * orderPriceBucket = NULL;
    order * tempOrder = NULL;
    HASH_FIND(hh, sellBook, &price, 4, tempBook);
    if(tempBook == NULL){
        return tempOrder;
    }
    tempPriceBucket = tempBook -> pb;
    HASH_FIND_INT(tempPriceBucket, &exchangeId, orderPriceBucket);
    if(orderPriceBucket == NULL){
        return tempOrder;
    }
    tempOrder = orderPriceBucket -> curOrder;
    deleteFromBook(tempOrder, &sellBook);
    tempOrder -> status = 2;
    return tempOrder;
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
