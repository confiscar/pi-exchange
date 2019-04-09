/**
 * @file requestHandlr.h
 * @brief defines function of handling request
 * @mainpage Pi Exchange - Server
 * @author Ke CHEN
 * @date 03-04-2019
 */

#include "exchange.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

/**
 * handle request with different parameters
 * @param sockfd the userId-clientId(socket id) pair
 */
void handleRequest(user_client * sockfd);
