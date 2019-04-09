/**
 * @file exchange.c
 * @brief implementation of exchange.h
 * @mainpage Pi Exchange - Server
 * @author Ke CHEN
 * @date 03-04-2019
 */

#include "exchange.h"
#include <stdio.h>
#include "notification.h"

book * buyBook = NULL;
book * sellBook = NULL;
double buyPrice = 0;
double sellPrice = 0;

// not any of orders are freed currently
// decide when to free once the way to inform client is decided
/// status of order: 0 not matched, 1 matched, 2 canceled

order * placeBuyOrder(double price, int amount, int orderId, int userId){
    order * currentOrder = generateOrder(price, amount, orderId, userId);
    order * temp = matchOrder(currentOrder, &sellBook);
    // if the order is not matched, add it to buy book and update the best sell price
    // else update the best buy price
    if(temp == NULL){
        addToBook(currentOrder, &buyBook);
        if(sellPrice < currentOrder -> price){
            sellPrice = currentOrder -> price;
        }
    } else {
        if(buyPrice == price){
            book * tempBook = NULL;
            HASH_FIND(hh, sellBook, &price, 8, tempBook);
            if(tempBook == NULL){
                double tempBuyPrice = 0;
                // loop through the sell book to find the lowest price (best buy price)
                for(tempBook = sellBook; tempBook != NULL; tempBook = (book *)tempBook -> hh.next){
                    if(tempBuyPrice > tempBook -> price || tempBuyPrice == 0){
                        tempBuyPrice = tempBook -> price;
                    }
                }
                buyPrice = tempBuyPrice;
            }
        }

        sendToUser(temp);
    }

    return currentOrder;
}

order * cancelBuyOrder(double price, int exchangeId){
    book * tempBook = NULL;
    priceBucket * tempPriceBucket = NULL;
    priceBucket * orderPriceBucket = NULL;
    order * tempOrder = NULL;
    HASH_FIND(hh, buyBook, &price, 8, tempBook);
    // check if price exists in book
    if(tempBook == NULL){
        return tempOrder;
    }
    // tempPriceBucket is just the head of the price bucket (in hash structure)
    tempPriceBucket = tempBook -> pb;
    HASH_FIND_INT(tempPriceBucket, &exchangeId, orderPriceBucket);
    // check if order exists in retrieved price bucket
    if(orderPriceBucket == NULL){
        return tempOrder;
    }
    tempOrder = orderPriceBucket -> curOrder;
    deleteFromBook(tempOrder, &buyBook);
    tempOrder -> status = 2;
    return tempOrder;
}

order * placeSellOrder(double price, int amount, int orderId, int userId){
    order * currentOrder = generateOrder(price, amount, orderId, userId);
    order * temp = matchOrder(currentOrder, &buyBook);
    // if the order is not matched, add it to sell book and update the best buy price
    // else update the best sell price
    if(temp == NULL){
        addToBook(currentOrder, &sellBook);
        if(buyPrice > currentOrder -> price || buyPrice == 0){
            buyPrice = currentOrder -> price;
        }
    } else {
        if(sellPrice == price){
            book * tempBook = NULL;
            HASH_FIND(hh, buyBook, &price, 8, tempBook);
            if(tempBook == NULL){
                double tempSellPrice = 0;
                // loop through the sell book to find the lowest price (best buy price)
                for(tempBook = buyBook; tempBook != NULL; tempBook = (book *)tempBook -> hh.next){
                    if(tempSellPrice < tempBook -> price){
                        tempSellPrice = tempBook -> price;
                    }
                }
                sellPrice = tempSellPrice;
            }
        }

        sendToUser(temp);
    }

    return currentOrder;
}

order * cancelSellOrder(double price, int exchangeId){
    book * tempBook = NULL;
    priceBucket * tempPriceBucket = NULL;
    priceBucket * orderPriceBucket = NULL;
    order * tempOrder = NULL;
    HASH_FIND(hh, sellBook, &price, 8, tempBook);
    // check if price exists in book
    if(tempBook == NULL){
        return tempOrder;
    }
    // tempPriceBucket is just the head of the price bucket (in hash structure)
    tempPriceBucket = tempBook -> pb;
    HASH_FIND_INT(tempPriceBucket, &exchangeId, orderPriceBucket);
    // check if order exists in retrieved price bucket
    if(orderPriceBucket == NULL){
        return tempOrder;
    }
    tempOrder = orderPriceBucket -> curOrder;
    deleteFromBook(tempOrder, &sellBook);
    tempOrder -> status = 2;
    return tempOrder;
}

order * matchOrder(order * curOrder, book ** curBook){
    double price = curOrder -> price;
    int amount = curOrder -> amount;
    book * tempBook = NULL;
    order * tempOrder = NULL;
    // check if the price exists in the book
    HASH_FIND(hh, * curBook, &price, 8, tempBook);
    if(tempBook == NULL){
        return tempOrder;
    }
    priceBucket * tempPriceBucket = tempBook -> pb;
	priceBucket * orderPriceBucket = NULL;
	// loop through the retrieved price bucket to see if there exists an order with amount
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
