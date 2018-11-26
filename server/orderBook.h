/*
 * orderBook.h
 *
 *  Created on: 2018/11/26
 *      Author: Ke CHEN
 */

#ifndef ORDERBOOK_H_
#define ORDERBOOK_H_

#include "uthash.h";
#include "order.h";

typedef struct priceBucket{
	 int exchangeId;
	 order curOrder;
	 UT_hash_handle hh;
}priceBucket;

typedef struct book {
    double price;
    priceBucket pb;
    UT_hash_handle hh;
} book;

void addToBook(order * curOrder, book * curBook);
void deleteFromBook(order * curOrder, book * curBook);


#endif /* ORDERBOOK_H_ */
