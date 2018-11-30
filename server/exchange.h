/*
 * exchange.h
 *
 *  Created on: 2018/11/26
 *      Author: Ke CHEN
 */

#ifndef EXCHANGE_H_
#define EXCHANGE_H_

#include "orderBook.h";

/**
 * generate a buy order and try to match with sells
 * if matched return order with status 1
 * else add it to buy book and return order with status 0
 */
order * placeBuyOrder(float price, int amount, int orderId);

/**
 * generate a sell order and try to match with buys
 * if matched return order with status 1
 * else add it to buy book and return order with status 0
 */
order * placeSellOrder(float price, int amount, int orderId);

/**
 * remove order from buy book and return order with status 2
 */
order * cancelBuyOrder(float price, int exchangeId);

/**
 * remove order from buy book and return order with status 2
 */
order * cancelSellOrder(float price, int exchangeId);


/**
 * return the matched order with status 1 if matched, else a null pointer
 * delete the matched order from book
 */
order * matchOrder(order * curOrder, book ** curBook);


#endif /* EXCHANGE_H_ */
