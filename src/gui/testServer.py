PORT = 80
MAX_CONNS = 5



import socket
import threading
import time
import math



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
        while True:
            try:
                data = conn.recv(2**16).decode()
                print("[{0}:{1}]<{2}>: {3}".format(addr[0],addr[1],time.time(),data))
            except BaseException as e:
                print("Connection with {0}:{1} closed".format(addr[0],addr[1]))
                break
            if data == "generateExampleData":
                for i in range(1000):
                    self.send(conn,"{0},{1}|".format(round(time.clock(),4),math.sin(i/100)*100))
                    time.sleep(0.01)
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
