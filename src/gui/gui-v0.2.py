#CONSTANTS

#Socket Options
HOST_IP = "127.0.0.1:8890"

#Order form constraints
PRICE_LOWER_RANGE = 0
PRICE_UPPER_RANGE = 1000
PRICE_ACCURACY = 0.00001

QUANTITY_LOWER_RANGE = 0
QUANTITY_UPPER_RANGE = 10000

#Width and heights of the window/screen
FEEDWIDTH = 100
TABLE_WIDTH = 4
TABLE_HEIGHT = 5

#Graph Settings
DELAY_BEFORE_AUTO_DRAW = 2000000
GRAPH_MAX_COORDS = 100

import tkinter
import random
import feedparser
import socket
import threading
import platform
import psutil
import time

#Style Options
RELIEF = tkinter.RIDGE

import time

#Variable to store the balance locally
balance = 1000
stockCount = 10000

#Variables for best buy and sell
bestBuy = None
bestSell = None

#Code to parse data from socket
#Possible Formats:

#-----------------
#<key>: <value>
#<key2>: <value2>
#<key3>: <value3>, time: <int>
#-----------------

def inferDataType(string):
    """Converts data type to best matching and returns"""
    if string.isalpha():
        return string
    elif '.' in string:
        return float(string)
    else:
        return int(string)

def parseToDict(data):
    """Convert data from socket into a dictionary object for easier manipulation"""
    dataDict = {}

    data = data.lstrip()

    #Split into lines
    data = data.split("\n")

    #For each line in the received data
    for d in data:

        #Ignore blank lines
        if d != '':

            #If not a separator line
            if d[0] != '-':

                #If multiple key/value pairs on one line, split
                d = d.split(", ")
                for pair in d:

                    #Separate key and value then save in dataDict
                    pair = pair.split(": ")
                    if len(pair) == 2:
                        dataDict[pair[0]] = inferDataType(pair[1])

    #Add a timestamp
    dataDict["time"] = time.time()

    #Return created dictionary object
    return dataDict


#Create window
root = tkinter.Tk()
win_width = root.winfo_screenwidth()
win_height = root.winfo_screenheight()

root.title("Stock Exchange GUI")
root.geometry(str(win_width)+"x"+str(win_height)+"+0+0")
root.attributes("-fullscreen",False)


#Create canvas frame
canvasFrame = tkinter.Frame(root,width=win_width-300,height=(win_height-100))
canvasFrame.grid(row=0,column=0,rowspan=10)

#Create canvas for graph
canvas = tkinter.Canvas(canvasFrame,width=win_width-300,height=(win_height-100)/2,bg='#001100')
canvas.grid(row=0,column=0)

#Create a canvas for the other graph
canvas2 = tkinter.Canvas(canvasFrame,width=win_width-300,height=(win_height-100)/2,bg='#110000')
canvas2.grid(row=1,column=0)


#rss feed
feed = feedparser.parse('http://feeds.reuters.com/reuters/UKPersonalFinanceNews')
newsFrame = tkinter.Frame(canvasFrame, relief=tkinter.RIDGE,bd=3)
newsFrame.grid(row=2,column=0)

feedstr = ""
for entry in feed['entries']:
    feedstr = feedstr + entry['summary_detail']['value'].split("<")[0] + "  ---  "
news = tkinter.Label(newsFrame,text=feedstr,width=FEEDWIDTH,height=1,fg="#444444",font=("Courier"))
news.grid(row=0,column=0,padx=4,pady=4)

#Buy/Sell Form
orderFrame = tkinter.Frame(root, relief=RELIEF, bd=3, width=100)
orderFrame.grid(row=1,column=1,columnspan=2)

#Balance display
balanceText = tkinter.Label(orderFrame,text="Balance (£): {0}\nStock Count: {1}".format(balance,stockCount))
balanceText.grid(row=0,column=0)

orderLabel = tkinter.Label(orderFrame, text="Order Form", font=("",12))
orderLabel.grid(row=1,column=0)

#Buy/Sell Radiobuttons (only one can be active at a time)
bsFrame = tkinter.Frame(orderFrame,relief=RELIEF)
bsFrame.grid(row=2,column=0,pady=10,padx=10)

buyOrSell = tkinter.StringVar()
buyButton = tkinter.Radiobutton(bsFrame,text="Buy",indicatoron=False,value="buy",variable=buyOrSell,width=10,pady=4)
buyButton.grid(row=0,column=0)
sellButton = tkinter.Radiobutton(bsFrame,text="Sell",indicatoron=False,value="sell",variable=buyOrSell,width=10,pady=4)
sellButton.grid(row=0,column=1)

#Set default state to buy
buyButton.select()

#Price Input
priceFrame = tkinter.Frame(orderFrame)
priceFrame.grid(row=4,column=0,pady=10,padx=10)

priceLabel = tkinter.Label(priceFrame,width=10,text="Price (): ")
priceLabel.grid(row=0,column=0)
priceInput = tkinter.Spinbox(priceFrame,from_=PRICE_LOWER_RANGE,to=PRICE_UPPER_RANGE,increment=PRICE_ACCURACY)  

def ValidateIfNum(self, s, S):
        # disallow anything but numbers
        valid = S.isdigit()
        if not valid:
            self.root.bell()
        return valid
        
priceInput.insert(0,0)
priceInput.config(state=tkinter.DISABLED)
priceInput.grid(row=0,column=1)

#Quantity
quantityFrame = tkinter.Frame(orderFrame)
quantityFrame.grid(row=5,column=0,pady=10,padx=10)

quantityLabel = tkinter.Label(quantityFrame,width=10,text="Quantity: ")
quantityLabel.grid(row=0,column=0)
quantityInput = tkinter.Spinbox(quantityFrame,from_=QUANTITY_LOWER_RANGE,to=QUANTITY_UPPER_RANGE)
quantityInput.delete(0,tkinter.END)
quantityInput.insert(0,10)
quantityInput.grid(row=0,column=1)

#Place Order Button
confirmFrame = tkinter.Frame(orderFrame)
confirmFrame.grid(row=6,column=0,pady=10,padx=5)

confirmButton = tkinter.Button(confirmFrame,width=10,text="Confirm")
confirmButton.pack()
#Confirm button is bound to placeOrder() later on (it must first be defined)

#Create an error message Label
errorLabel = tkinter.Label(orderFrame,width=10,text="")
errorLabel.grid(row=7,column=0,columnspan=2)

#Book display
tableFrame = tkinter.Frame(root, relief=RELIEF, bd=3, padx=30, pady=10)
tableFrame.grid(row=3,column=1)
buyTableLabel = tkinter.Label(tableFrame, text="Order History", pady=4, font=("",12))
buyTableLabel.grid(row=0,column=0, columnspan=2)

class Table():
    """Class to act as a table widget"""

    def __init__(self,width,height,frame,headers):
        """Initialise object and place Text widgets into the frame"""
        self.width,self.height,self.frame = width,height,frame
        self.headerTitles = headers
        self.headers = []
        self.rows = []

        #Create the headers of the columns
        for x in range(self.width):
            self.headers.append(tkinter.Text(self.frame, width=6,height=1,bg="#eeeeef",fg="#666666"))
            self.headers[-1].grid(row=1,column=x)
            self.headers[-1].insert(tkinter.END,self.headerTitles[x])
            self.headers[-1].config(state=tkinter.DISABLED)

        #Create the cells of the table
        for y in range(1,self.height+1):
            self.rows.append([])
            for x in range(self.width):
                self.rows[-1].append(tkinter.Text(self.frame, width=6,height=1,bg="#eeeeef",fg="#666666"))
                self.rows[-1][-1].grid(row=y+1,column=x)
                self.rows[-1][-1].config(state=tkinter.DISABLED)

    #Clear the value in a cell
    def clear(self,column,row):
        self.rows[row][column].config(state=tkinter.NORMAL)
        self.rows[row][column].delete(1.0,tkinter.END)
        self.rows[row][column].config(state=tkinter.DISABLED)
        
    #Insert a value into a cell
    def insert(self,column,row,text):
        self.clear(column,row)
        self.rows[row][column].config(state=tkinter.NORMAL)
        self.rows[row][column].insert(tkinter.END,text)
        self.rows[row][column].config(state=tkinter.DISABLED)

table = Table(TABLE_WIDTH, TABLE_HEIGHT, tableFrame, ["ID","Price","Qty","Status"])

for y in range(TABLE_HEIGHT):
    table.insert(0,y,"")
    table.insert(1,y,"")
    table.insert(2,y,"")
    table.insert(3,y,"")

#created second frame with class
#tableFrame2 = tkinter.Frame(root, relief=RELIEF, bd=3, padx=30, pady=10)
#tableFrame2.grid(row=4,column=1)
#buyTableLabel = tkinter.Label(tableFrame2, text="Sell", pady=4, font=("",12))
#buyTableLabel.grid(row=0, column=0, columnspan=2)


#table2 = Table(TABLE_WIDTH, TABLE_HEIGHT, tableFrame2, ["Order ID","Price","Quantity","Ack?"])


#EXTRA STUFF
#CPU LABEL POWER
statsFrame = tkinter.Frame(root, relief=RELIEF, bd=3, width=200)
statsFrame.grid(row=5,column=1,columnspan=2)
cputext = tkinter.Label(statsFrame, text= "")
cputext.grid(row=0,column=0)
#FIGURE THIS OUT LATER

graphLock = threading.Lock()

#Secondary lock for second graph
graphLock2 = threading.Lock()

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
        global bestBuy, bestSell
        """Listen to the server"""
        #Get initial prices
        msg = self.s.recv(2**16)
        msg = msg.decode()
        print(msg)
        bestBuy=""
        bestSell=""
        #Sanitize inputs
        for letter in msg:
            if letter in ['0','1','2','3','4','5','6','7','8','9','.']:
                bestBuy += letter
            else:
                break
        for letter in msg:
            if letter in ['0','1','2','3','4','5','6','7','8','9','.']:
                bestSell += letter
            else:
                break
        bestBuy = float(bestBuy)
        bestSell = float(bestSell)
        while True:
            msg = self.s.recv(2**16)
            msg = msg.decode()
            print(msg)
            data = parseToDict(msg)
            if "best sell" in data.keys():
                bestSell = data["best sell"]
                x = data["time"]
                y = data["best sell"]
                graphLock.acquire()
                g.addCoords((x,y))
                graphLock.release()
            if "best buy" in data.keys():
                bestBuy = data["best buy"]
                x = data["time"]
                y = data["best buy"]
                graphLock2.acquire()
                g2.addCoords((x,y))
                graphLock2.release()

class Graph():
    """Class to plot data to a canvas"""
    def __init__(self,canvasRef,maxCoords,padding=200):
        """Reference to a canvas object, max points of data shown simultaneously, canvas dimensions and padding for axis"""
        self.canvas = canvasRef
        self.values = []
        self.maxCoords = maxCoords
        self.CW, self.CH = self.canvas.winfo_reqwidth()-padding, self.canvas.winfo_reqheight()-padding
        self.padding = padding
    def addCoords(self,coords):
        """Add (x,y) to the list of coordinates, old values are removed according to maxCoords attribute"""
        self.values.append(coords)
        while len(self.values) > self.maxCoords:
            self.values.pop(0)
    def autoScroll(self):
        if len(self.values) >= 1:
            if time.time() - self.values[-1][0] < DELAY_BEFORE_AUTO_DRAW:
                self.addCoords((time.time(),self.values[-1][1]))
    def plot(self):
        """Plot stored coordinates to the canvas"""

        #Remove previous items
        self.canvas.delete(tkinter.ALL)

        if len(self.values) < 1:
            return

        #Establish minimums and maximums for the data
        minx = self.values[0][0]
        maxx = self.values[-1][0]
        miny = self.values[0][1]
        maxy = self.values[0][1]
        for c in self.values:
            if c[1] < miny:
                miny = c[1]
            elif c[1] > maxy:
                maxy = c[1]

        #Prevent the scales from being 0, but favour using only the necessary graph space
        if maxx-minx == 0:
            maxx+=0.5
            minx-=0.5
        if maxy-miny == 0:
            maxy+=0.5
            miny-=0.5

        #Calculate the scale
        scalex = maxx-minx
        scaley = maxy-miny

        #Plot all coordinates
        for c in range(len(self.values)):

            #Calculate colour based on increasing or decreasing value
            if c != len(self.values)-1:
                if self.values[c][1] > self.values[c+1][1]:
                    col = "#ff8888"
                elif self.values[c][1] < self.values[c+1][1]:
                    col = "#88ff88"
                else:
                    col = "#bebebe"

                #print("values[c] = {0}\nminx, maxx, miny, maxy = {1}, {2}, {3}, {4}\n scalex = {5}\nscaley = {6}".format(values[c],minx,maxx,miny,maxy,scalex,scaley))
                #Create line between this point and the next, applying calculations to scale and fit the points
                self.canvas.create_line(int(self.CW*((self.values[c][0]-minx)/scalex))+self.padding//2,
                                        self.CH-int(self.CH*((self.values[c][1]-miny)/scaley))+self.padding//2,
                                        int(self.CW*((self.values[c+1][0]-minx)/scalex))+self.padding//2,
                                        self.CH-int(self.CH*((self.values[c+1][1]-miny)/scaley))+self.padding//2,
                                        fill=col,width=2)

        #Write the current balance to the screen
        if len(self.values) > 1:

            c = len(self.values)-2
            if self.values[c][1] > self.values[c+1][1]:
                col = "#ff8888"
            elif self.values[c][1] < self.values[c+1][1]:
                col = "#88ff88"
            else:
                col = "#bebebe"

            #Label the balance at the text
            self.canvas.create_text(int(self.CW*((self.values[-1][0]-minx)/scalex))+self.padding//2 + 6,
                                            self.CH-int(self.CH*((self.values[-1][1]-miny)/scaley))+self.padding//2,
                                            fill=col,text="£"+str(self.values[-1][1]),anchor=tkinter.NW)

        #Create axis based on self.padding
        self.canvas.create_line(self.padding//2,self.padding//2,self.padding//2,self.CH+self.padding//2,fill="#ffffff",width=2)
        self.canvas.create_line(self.padding//2,self.CH+self.padding//2,self.CW+self.padding//2,self.CH+self.padding//2,fill="#ffffff",width=2)

        #Label axis with coordinates
        #X Axis
        #Convert time to string
        minx = time.ctime(minx)
        maxx = time.ctime(maxx)
        #Place text on canvas
        self.canvas.create_text(self.padding//2,self.CH+int(self.padding*3/4),text=minx,fill="#ffffff",font=("fixedsys",7),anchor=tkinter.W)
        self.canvas.create_text(self.CW+self.padding//2,self.CH+int(self.padding*3/4),text=maxx,fill="#ffffff",font=("fixedsys",7),anchor=tkinter.E)
        #Y Axis
        self.canvas.create_text(self.padding//4,self.padding//2,text=str(int(maxy)),fill="#ffffff",font=("fixedsys",7),anchor=tkinter.W)
        self.canvas.create_text(self.padding//4,self.CH+self.padding//2,text=str(int(miny)),fill="#ffffff",font=("fixedsys",7),anchor=tkinter.W)

        #Update canvas
        self.canvas.update()


#Create graphs
g = Graph(canvas,GRAPH_MAX_COORDS)
g2 = Graph(canvas2,GRAPH_MAX_COORDS)

c = Client(HOST_IP)
threading.Thread(target=c.receiveLoop).start()

x = 0
#Plot function is called repeatedly in mainloop
def plot():
    global x

    #Draw to canvas
    graphLock.acquire()
    g.autoScroll()
    g.plot()
    graphLock.release()

    graphLock2.acquire()
    g2.autoScroll()
    g2.plot()
    graphLock2.release()

    #Call in next mainloop
    root.after(10,plot)

#Scroll through the feed
scrollAmount = 0
def scrollFeed():
    global scrollAmount
    global feedstr
    news.config(text=(" "*FEEDWIDTH + feedstr + " "*FEEDWIDTH)[scrollAmount:scrollAmount+FEEDWIDTH])
    scrollAmount += 1
    if scrollAmount+FEEDWIDTH > len(feedstr) + FEEDWIDTH*2:
        scrollAmount = 0
    root.after(70,scrollFeed)

#For generating client order IDs
class OrderID():
    currentID = 0
    def getNextOrderID():
        OrderID.currentID += 1
        return OrderID.currentID

def displayErrorOutput(text,col):
    errorLabel.config(text=text,fg=col)

#Validate buy/sell form input
def validateFormInput(quantity,price):
    #Make sure it is numeric data
    try:
        quantity = int(quantity)
        price = float(price)
    except ValueError:
        displayErrorOutput("Error: Invalid/non-numerical input","#ff0000")
        return False
    if quantity <= QUANTITY_LOWER_RANGE or quantity >= QUANTITY_UPPER_RANGE:
        displayErrorOutput("Error: Quantity must be in range {0} < quantity < {1}".format(QUANTITY_LOWER_RANGE, QUANTITY_UPPER_RANGE),"#ff0000")
        return False
    if price <= PRICE_LOWER_RANGE or price >= PRICE_UPPER_RANGE:
        displayErrorOutput("Error: Price must be in range {0} < price < {1}".format(PRICE_LOWER_RANGE, PRICE_UPPER_RANGE),"#ff0000")
        return False
    displayErrorOutput("Success!","#00ff00")
    return True


#Form has been submitted
def placeOrder():
    order = {"orderType":buyOrSell.get(),"price":priceInput.get(),"quantity":quantityInput.get()}
    #Format for the server
    if validateFormInput(order["quantity"], order["price"]):
        if order["orderType"][0] == "b" and bestBuy == None:
            return
        elif ["orderType"][0] == "s" and bestSell == None:
            return
        data = "p," + order["orderType"][0] + "," + str({"b": bestBuy, "s": bestSell}[order["orderType"][0]]) + "," + str(order["quantity"]) + "," + str(OrderID.getNextOrderID())
        print(data)
        #Send through socket
        c.send(data)

def updateStats():
    global bestBuy, bestSell
    cputext.config(text="CPU Usage: {0}%\nRAM Usage: {1}%".format(psutil.cpu_percent(),psutil.virtual_memory().percent))
    #Set the price to current buy or sell price
    priceInput.config(state=tkinter.NORMAL)
    priceInput.delete(0,tkinter.END)
    if buyOrSell.get()[0] == 'b':
        priceInput.insert(0,str(bestBuy))
    elif buyOrSell.get()[0] == 's':
        priceInput.insert(0,str(bestSell))
    priceInput.config(state=tkinter.DISABLED)
    root.after(500,updateStats)


#Configure confirm button to this function after the function has been defined
confirmButton.config(command=placeOrder)

def backgroundTasks():
    plot()
    scrollFeed()
    updateStats()

#Add plot to mainloop and hand over control to gui
root.after(1,backgroundTasks)
root.mainloop()
