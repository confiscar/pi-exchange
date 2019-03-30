#!/usr/bin/env python
# coding: utf-8 

import socket
import threading
import time

class DataThread(threading.Thread):
    def __init__(self, clientsocket):
        threading.Thread.__init__(self)
        self.clientsocket = clientsocket

    def run(self): 
        k=20000
        t0 = time.time()
        y = 0
        
        while k>0:
            print( "waiting instructions...")
            r = self.clientsocket.recv(2048)
            print(r)
            if r=="giveMeYourData":
                x = time.time()-t0
                data = "%f"%x
                print ("sending data")
                self.clientsocket.send(data)
                print( "data sent")
                time.sleep(0.005)
                k=k-1

tcpsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcpsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
tcpsock.bind(("localhost", 50981))

print( "Listening...")
tcpsock.listen(10)
print( "Waiting for connection ...")
(clientsocket, (ip, port)) = tcpsock.accept()
newthread = DataThread(clientsocket)
print( "Starting DataThread ...")
newthread.start()
