/*
 * order.c
 *
 *  Created on: 2018Äê11ÔÂ29ÈÕ
 *      Author: 13245
 */


#include "order.h"
#include <stdlib.h>

int exchangeId = 0;

order * generateOrder(float price, int amount, int orderId){
	order * temp = malloc(sizeof(order));
	temp -> price = price;
	temp -> amount = amount;
	temp -> orderId = orderId;
	temp -> exchangeId = exchangeId;
	exchangeId++;
	return temp;
}
