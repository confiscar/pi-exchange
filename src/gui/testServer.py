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
        self.bp,self.sp = 100,100
        try:
            self.s.bind((self.ip,self.port))
            print("Server IP: {0}:{1}".format(self.ip,self.port))
        except:
            print("[!] Socket failed to bind port")
    def send(self,conn,data):
        """Send string data to connection conn"""
        conn.sendall(data.encode())
    def emulate(self,function):
        if function == "updateBestBuy":
            self.bp += random.randint(1,1000)/10 - 50
            if self.bp < 1:
                self.bp = random.randint(1,1000)/10
            return "best buy: {1}, time: {0}\n".format(round(time.time()-SIMULATED_LATENCY,4),self.sp)
        if function == "updateBestSell":
            self.sp += random.randint(1,1000)/10 - 50
            if self.sp < 1:
                self.sp = random.randint(1,1000)/10
            return "best sell: {1}, time: {0}\n".format(round(time.time()-SIMULATED_LATENCY,4),self.bp)
    def connection(self,conn,addr):
        """Call as thread, sets up one connection"""

        i=0
        autofunctions = ["updateBestBuy","updateBestSell"]
        manualfunctions= ["ackOrder","nackOrder"]
        while i < 10:
            i += 1
            try:
                self.send(conn,self.emulate(autofunctions[random.randint(0,len(autofunctions)-1)]))
            except Exception as e:
                print(e)
                print("Disconnected with {0}:{1}\n".format(addr[0],addr[1]))
                break
            time.sleep(random.random()/4)

        while True:
            try:
                data = conn.recv(2**16).decode()
                print("[{0}:{1}]<{2}>: {3}".format(addr[0],addr[1],time.time(),data))
                data = data.split(",")
                if data[0] == "p":
                    self.send(conn,"order ID: "+data[4]+"\nstatus: 0\n")
                    time.sleep(1)
                    self.send(conn,"order ID: "+data[4]+"\nstatus: 1\n")
            except BaseException as e:
                print("Connection with {0}:{1} closed".format(addr[0],addr[1]))
                break

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
