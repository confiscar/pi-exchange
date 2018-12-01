![alt text]( https://i.imgur.com/k2kruGl.png "Logo Title Text 1")

# Pi Exchange 

This project will consist of software developed for the Rasberry Pi 3 model B. The purpose of the software is to create a low-latency interface to an exchange simulation, that can place orders and try to execute the order as quickly as it can when there is a match. 

Getting Started
------
QT/GTK/FLTK libraries 

Built With 
------
C++
Qt/GTK/FLTK


Authors
------

* Vasilis Ieropolous
* Ke Chen
* Francisco Caeiro
* Julian Henjes
* Guanghao Yang
* Shen Huan 

Acknowledgements
------

Server
------
#### 	compile: gcc tcp_server.c exchange.c orderBook.c order.c -o server
#### 	run: ./server
#### 	connect to server using ip and port 8890
note: the ip depends on whether server run local or remote, local: 127.0.0.1, remote: find the ip of device where server runs on
	
#### 	place or cancel order with 5 paramter divided by as single character ",". Sequence of parameters are as below:
* p stands for place order, c stands for cancel order
* b stands for buy, s stands for sell
* price
* amount
* order id (generated by client)

	
Thank you so much to Refinitiv for sponsoring the project
