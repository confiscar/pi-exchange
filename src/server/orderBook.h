#ifndef ORDERBOOK_H_
#define ORDERBOOK_H_

#include "uthash.h"
#include "order.h"
#include <stdio.h>

/**
* key: exchange ID
* value: an order with specific exchange ID
*/
typedef struct priceBucket{
	 int exchangeId;
	 struct order * curOrder;
	 UT_hash_handle hh;
}priceBucket;

/**
* two book in system, one for sell, one for buy
* key: price
* value: a hash variable storing orders with specific price for buy or sell
*/
typedef struct book {
    double price;
    priceBucket * pb;
    UT_hash_handle hh;
} book;

/**
* temporary set return type to void, to be decided further
*/
void addToBook(order * curOrder, book ** curBook);

/**
* temporary set return type to void, to be decided further
*/
void deleteFromBook(order * curOrder, book ** curBook);


#endif /* ORDERBOOK_H_ */
