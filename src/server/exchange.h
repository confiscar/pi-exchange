/**
 * @file exchange.h
 * @brief defines data structure user_client and logic functions of server
 * @mainpage Pi Exchange - Server
 * @author Ke CHEN
 * @date 03-04-2019
 */

#ifndef EXCHANGE_H_
#define EXCHANGE_H_

#include "orderBook.h"

/**
 * user_client contains user ID assigned by server and socket ID as pair
 */
typedef struct user_client{
    int userId;
    int sockfd;
}user_client;



/**
 * generate a buy order and try to match with sells\n
 * if matched return order with status 1\n
 * else add it to buy book and return order with status 0\n
 *
 * @param price price of order to be matched
 * @param amount amount of order to be matched
 * @param orderId order ID of order to be matched
 * @param userId user ID of order to be matched
 *
 * @return an order with specific status
 */
order * placeBuyOrder(double price, int amount, int orderId, int userId);

/**
 * generate a sell order and try to match with buys
 * if matched return order with status 1
 * else add it to buy book and return order with status 0
 *
 * @param price price of order to be matched
 * @param amount amount of order to be matched
 * @param orderId order ID of order to be matched
 * @param userId user ID of order to be matched
 *
 * @return an order with specific status
 */
order * placeSellOrder(double price, int amount, int orderId, int userId);

/**
 * remove order from buy book and return order with status 2
 * NULL if order with certain exchangeId is not in book
 *
 * @param price price of order to be canceled
 * @param exchangeId exchangeId of order to be canceled
 *
 * @return an order with status 2 if cancel successfully, else NULL
 */
order * cancelBuyOrder(double price, int exchangeId);

/**
 * remove order from buy book and return order with status 2
 * NULL if order with certain exchangeId is not in book
 *
 * @param price price of order to be canceled
 * @param exchangeId exchangeId of order to be canceled
 *
 * @return an order with status 2 if cancel successfully, else NULL
 */
order * cancelSellOrder(double price, int exchangeId);


/**
 * return the matched order with status 1 if matched, else a null pointer
 * delete the matched order from book
 *
 * @param curOrder order to be matched
 * @param curBook buy/sell book for the function to search if matched order exists
 *
 * @return the matched order with status 1 if matched, else NULL
 */
order * matchOrder(order * curOrder, book ** curBook);


#endif /* EXCHANGE_H_ */
