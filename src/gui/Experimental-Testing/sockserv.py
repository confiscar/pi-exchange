import socket
import pickle
import time

pickleSep = ':::::'

HOST = 'localhost'
PORT = 32768
server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_sock.bind( (HOST,PORT) )
print ("Binded to PORT"), PORT
server_sock.listen(1)
ROOT_sock, addr = server_sock.accept()
print ('Connected by'), addr

for ii in range(100):
    print ("ii = "), ii
    toSend = pickle.dumps(('testing', (ii, ii,ii*ii))) + pickleSep
    ROOT_sock.sendall(toSend)
    time.sleep(0.2)