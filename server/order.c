/*
 * order.c
 *
 *  Created on: 2018Äê11ÔÂ29ÈÕ
 *      Author: 13245
 */


#include "order.h"
#include <stdlib.h>

order * generateOrder(int price, int amount, int orderId){
	order * temp = malloc(sizeof(order));
	temp -> price = price;
	temp -> amount = amount;
	temp -> orderId = orderId;
	return temp;
}
