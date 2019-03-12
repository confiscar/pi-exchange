


import socket
import threading
import matplotlib.pyplot as plt


ip = input("Server IP: ")

plotData = []
plotDataLock = threading.Lock()

class Client():
    """A class to encapsulate client funcitonality"""
    def __init__(self,hostIP):
        self.hostIP = hostIP
        self.s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        self.host,self.port = self.hostIP.split(':')
        self.port = int(self.port)
        try:
            self.s.connect((self.host,self.port))
        except BaseException as e:
            print(e)
    def send(self,data):
        """Send string data to server"""
        self.s.sendall(data.encode())
    def receiveLoop(self):
        """Listen to the server"""
        while True:
            msg = self.s.recv(2**16)
            msg = msg.decode()
            msg = msg.split("|")
            for m in msg:
                if m != '':
                    m = m.split(",")
                    plotDataLock.acquire()
                    plotData.append([float(m[0]),float(m[1])])
                    plotDataLock.release()


c = Client(ip)
threading.Thread(target=c.receiveLoop).start()
c.send("generateExampleData")

while True:
    plotDataLock.acquire()
    data = plotData[:]
    plotData = []
    plotDataLock.release()
    for d in data:
       line = plt.scatter(d[0],d[1],color='blue')
       line(False)
    plt.pause(0.00000001)

plt.show()
