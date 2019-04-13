#!/usr/bin/env python

"""
Plot data received over a ZeroMQ port in real time using matplotlib.
Notes
-----
This appears to segfault when run using the WxAgg backend.
"""

import time
import multiprocessing as mp

import zmq
import numpy as np
import matplotlib
matplotlib.use('GTKAgg')
import matplotlib.pyplot as plt

def is_poll_in(sock, poller, timeout=100):
    """
    Poll for received input data on a specified socket.
    """
    
    socks = dict(poller.poll(timeout))
    if sock in socks and socks[sock] == zmq.POLLIN:
        return True
    else:
        return False

def plot():
    """
    Plot received data.
    """
    
    ctx = zmq.Context()
    sock = ctx.socket(zmq.SUB)
    sock.setsockopt(zmq.SUBSCRIBE, '')
    sock.connect('tcp://localhost:5000')

    poller = zmq.Poller()
    poller.register(sock, zmq.POLLIN)

    fig = plt.gcf()
    ax = fig.add_subplot(111)
    ax.set_ylim((-1, 1))
    line, = ax.plot([], [], linewidth=2)

    data = [[], []]
    while True:
        if is_poll_in(sock, poller):
            data = sock.recv_pyobj()        
        if type(data) == str and data == 'quit':
            break
        else:
            x, y = data
        line.set_data(x, y)

        # Adjust the X axis labels to enable scrolling effect as X values
        # increase:
        if x != []:
            ax.set_xbound(lower=min(x), upper=max(x))
        fig.canvas.draw()

def data_gen():
    """
    Generate data and send it to the plotting process.
    """
    
    ctx = zmq.Context()
    sock = ctx.socket(zmq.PUB)
    sock.bind('tcp://*:5000')

    offset = 0
    dt = 0.001
    for i in xrange(1000):
        time.sleep(0.01)
        offset += 0.075
        x = np.arange(0, 5, dt)+offset
        y = np.sin(2*np.pi*x)        
        sock.send_pyobj((x, y))

    sock.send_pyobj('quit')

if __name__ == '__main__':
    plt.figure()
    plt.show()
    d = mp.Process(target=data_gen)
    d.start()
    time.sleep(1)
plot()
