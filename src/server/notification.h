/**
 * @file notification.h
 * @brief defines data structure notificationPoll and notify functions
 * @mainpage Pi Exchange - Server
 * @author Ke CHEN
 * @date 03-04-2019
 */

#include "uthash.h"
#include "order.h"

/**
 * key: user ID assigned to client by server
 * value: connection ID of socket
 */
 typedef struct notificationPoll{
	 int user_id;
	 int noti_sockfd;
	 UT_hash_handle hh;
}notificationPoll;

/**
 * check if price changes and decide whether send notification or not\n
 */
void notify();

/**
 * send specific information to all client connected
 *
 * @param sendBuffer the information to be sent
 */
void sendToAll(char * sendBuffer);

/**
 * generate a buy order and try to match with sells\n
 * if matched return order with status 1\n
 * else add it to buy book and return order with status 0\n
 *
 * @param the order to be informed to a specific user
 */
void sendToUser(order * orderTobeInform);
