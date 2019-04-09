/**
 * @file order.h
 * @brief defines data structure order and function of generating order
 * @mainpage Pi Exchange - Server
 * @author Ke CHEN
 * @date 03-04-2019
 */

#ifndef ORDER_H_
#define ORDER_H_

/**
* include specific information for a certain order \n
* status: 0 in book; 1 matched; 2 canceled \n
*/
typedef struct order
{
	double price;
	int amount;
	int orderId;
	int exchangeId;
	int status;
	int userId;
} order;

/**
* generate order with a generated key exchangeId and a initial status 0\n
* status: 0 not matched; 1 matched; 2 canceled\n
* @param price price from client input
* @param amount amount from client input
* @param orderId order ID from client input,maintained by client
* @param userId socket ID of current order's owner
*
* @return the newly generated order
*/
order * generateOrder(double price, int amount, int orderId, int userId);

#endif /* ORDER_H_ */
