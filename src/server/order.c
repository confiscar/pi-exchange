#include "order.h"
#include <stdlib.h>

int exchangeId = 1;

order * generateOrder(double price, int amount, int orderId, int userId){
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
