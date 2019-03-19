PORT = 43242
MAX_CONNS = 5

SIMULATED_LATENCY = 10

import socket
import threading
import time
import math
import random



class Server():
    """Class to encapsulate server functionality"""
    def __init__(self,port,max_conns):
        self.port, self.max_conns = port, max_conns
        self.ip = socket.gethostbyname(socket.gethostname())
        self.s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        self.conns = []
        try:
            self.s.bind((self.ip,self.port))
            print("Server IP: {0}:{1}".format(self.ip,self.port))
        except:
            print("[!] Socket failed to bind port")
    def send(self,conn,data):
        """Send string data to connection conn"""
        conn.sendall(data.encode())
    def connection(self,conn,addr):
        """Call as thread, sets up one connection"""
##        while True:
##            try:
##                data = conn.recv(2**16).decode()
##                print("[{0}:{1}]<{2}>: {3}".format(addr[0],addr[1],time.time(),data))
##            except BaseException as e:
##                print("Connection with {0}:{1} closed".format(addr[0],addr[1]))
##                break
        i=0
        bp = 100
        sp = 100
        while i < 100:
            i += 1
            try:
                bp += random.random()-0.5
                dataToSend = "best sell: {1}, time: {0}\n".format(round(time.time()-SIMULATED_LATENCY,4),bp)
                self.send(conn,dataToSend)
                sp += random.random()-0.5
                dataToSend = "best buy: {1}, time: {0}\n".format(round(time.time()-SIMULATED_LATENCY,4),sp)
                self.send(conn,dataToSend)
            except Exception as e:
                print(e)
                print("Disconnected with {0}:{1}\n".format(addr[0],addr[1]))
                break
            time.sleep(random.random()/4)
        while True:
            data = self.s.recv(1024)
            print(data.decode())
    def serverLoop(self):
        """Repeatedly accepts connections and assigns new threads to each"""
        self.s.listen(self.max_conns)
        print("Server now listening...")
        while True:
            conn, addr = self.s.accept()
            self.conns.append(conn)
            print("Connected with {0}:{1}".format(addr[0],str(addr[1])))
            threading.Thread(target=self.connection, args=(conn,addr,)).start()

s = Server(PORT,MAX_CONNS)
s.serverLoop()
