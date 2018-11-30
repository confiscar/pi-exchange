/*
 * order.h
 *
 *  Created on: 2018/11/26
 *      Author: Ke CHEN
 */

#ifndef ORDER_H_
#define ORDER_H_


// order's status: 0 in book; 1 matched; 2 cancel; 3 NACH
typedef struct order
{
	int price;
	int amount;
	int orderId;
	int exchangeId;
	int status;
} order;

order * generateOrder(int price, int amount, int orderId);

#endif /* ORDER_H_ */
