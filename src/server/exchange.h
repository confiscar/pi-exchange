#ifndef EXCHANGE_H_
#define EXCHANGE_H_

#include "orderBook.h"

typedef struct user_client{
    int userId;
    int sockfd;
}user_client;

/**
 * generate a buy order and try to match with sells
 * if matched return order with status 1
 * else add it to buy book and return order with status 0
 */
order * placeBuyOrder(double price, int amount, int orderId, int userId);

/**
 * generate a sell order and try to match with buys
 * if matched return order with status 1
 * else add it to buy book and return order with status 0
 */
order * placeSellOrder(double price, int amount, int orderId, int userId);

/**
 * remove order from buy book and return order with status 2
 * NULL if order with certain exchangeId is not in book
 */
order * cancelBuyOrder(double price, int exchangeId);

/**
 * remove order from buy book and return order with status 2
 * NULL if order with certain exchangeId is not in book
 */
order * cancelSellOrder(double price, int exchangeId);


/**
 * return the matched order with status 1 if matched, else a null pointer
 * delete the matched order from book
 */
order * matchOrder(order * curOrder, book ** curBook);


#endif /* EXCHANGE_H_ */
