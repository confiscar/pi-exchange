#!/bin/bash

echo -e $TEXT_YELLOW
echo 'compiling server'
echo -e $TEXT_RESET

gcc tcp_server.c exchange.c order.c orderBook.c requestHandlr.c notification.c  -o server -pthread


echo -e $TEXT_YELLOW
echo 'Give me a second'
echo -e $TEXT_RESET

sleep 1

echo -e $TEXT_YELLOW
echo 'Server is up and running'
echo -e $TEXT_RESET

sleep 1
./server


