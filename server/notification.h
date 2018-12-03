/*
 * notification.h
 *
 *  Created on: 2018/12/3
 *      Author: Ke CHEN
 */
#include "uthash.h"

 typedef struct notificationPoll{
	 int user_id;
	 int noti_sockfd;
	 UT_hash_handle hh;
}notificationPoll;

void notify();
void sendToAll(char * sendBuffer);
