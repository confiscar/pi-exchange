/*
 * order.c
 *
 *  Created on: 2018Äê11ÔÂ29ÈÕ
 *      Author: 13245
 */


#include "order.h"
#include <stdlib.h>

int exchangeId = 0;

order * generateOrder(float price, int amount, int orderId, int userId){
	order * temp = malloc(sizeof(order));
	temp -> price = price;
	temp -> amount = amount;
	temp -> orderId = orderId;
	temp -> exchangeId = exchangeId;
	temp -> status = 0;
	temp -> userId = userId;
	exchangeId++;
	return temp;
}
