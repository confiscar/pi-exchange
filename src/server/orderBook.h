/**
 * @file orderBook.h
 * @brief defines data structure book and priceBucket and functions handle relation between order and book
 * @mainpage Pi Exchange - Server
 * @author Ke CHEN
 * @date 03-04-2019
 */

#ifndef ORDERBOOK_H_
#define ORDERBOOK_H_

#include "uthash.h"
#include "order.h"
#include <stdio.h>

/**
* key: exchange ID\n
* value: an order with specific exchange ID\n
*/
typedef struct priceBucket{
	 int exchangeId;
	 struct order * curOrder;
	 UT_hash_handle hh;
}priceBucket;

/**
* two book in system, one for sell, one for buy\n
* key: price\n
* value: a hash variable storing orders with specific price for buy or sell\n
*/
typedef struct book {
    double price;
    priceBucket * pb;
    UT_hash_handle hh;
} book;

/**
* add a certain order to its corresponding book
* @param curOrder the order to be added to book
* @param curBook the book which current order should be added to
*
*/
void addToBook(order * curOrder, book ** curBook);

/**
* delete a certain order from buy/sell book
* @param curOrder the order to be deleted from book
* @param curBook the book which current order should be deleted from
*
*/
void deleteFromBook(order * curOrder, book ** curBook);


#endif /* ORDERBOOK_H_ */
