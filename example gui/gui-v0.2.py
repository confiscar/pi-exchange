import tkinter
import random
import feedparser
#CONSTANTS

#Order form constraints
PRICE_LOWER_RANGE = 0
PRICE_UPPER_RANGE = 1000
PRICE_ACCURACY = 0.00001

QUANTITY_LOWER_RANGE = 0
QUANTITY_UPPER_RANGE = 10000

#Width and heights of the screen and canvas
W,H = 1080,640
CW,CH = 640,640
FEEDWIDTH = 30

#Style Options
RELIEF = tkinter.SUNKEN

#Create window
root = tkinter.Tk()
root.title("Stock Exchange")
root.geometry(str(W)+"x"+str(H)+"+80+40")

#Create canvas and add to window - for the graph
canvas = tkinter.Canvas(root,width=CW,height=CH,bg='#000000')
canvas.grid(row=0,column=0,rowspan=100)

#rss feed
feed = feedparser.parse('http://feeds.reuters.com/reuters/UKPersonalFinanceNews')
newsFrame = tkinter.Frame(root, relief=tkinter.RIDGE,bd=3)
newsFrame.grid(row=2,column=1)


feedstr = "Example Feed"
news = tkinter.Label(newsFrame,text=feedstr,width=FEEDWIDTH,height=1,fg="#444444",font=("Courier"))
news.grid(row=0,column=0,padx=4,pady=4)




#Buy/Sell Form
orderFrame = tkinter.Frame(root, relief=RELIEF,bd=3)
orderFrame.grid(row=1,column=1)

#Buy/Sell Radiobuttons (only one can be active at a time)
bsFrame = tkinter.Frame(orderFrame,relief=RELIEF)
bsFrame.grid(row=0,column=0,pady=10,padx=10)

buyOrSell = tkinter.StringVar()
buyButton = tkinter.Radiobutton(bsFrame,text="Buy",indicatoron=False,value="buy",variable=buyOrSell,width=10,pady=4)
buyButton.grid(row=0,column=0)
sellButton = tkinter.Radiobutton(bsFrame,text="Sell",indicatoron=False,value="sell",variable=buyOrSell,width=10,pady=4)
sellButton.grid(row=0,column=1)

#Set default state to buy
buyButton.select()

#Price Input
priceFrame = tkinter.Frame(orderFrame)
priceFrame.grid(row=1,column=0,pady=10,padx=10)

priceLabel = tkinter.Label(priceFrame,width=10,text="Price (): ")
priceLabel.grid(row=0,column=0)
priceInput = tkinter.Spinbox(priceFrame,from_=PRICE_LOWER_RANGE,to=PRICE_UPPER_RANGE,increment=PRICE_ACCURACY)
priceInput.insert(0,0)
priceInput.grid(row=0,column=1)

#Quantity
quantityFrame = tkinter.Frame(orderFrame)
quantityFrame.grid(row=2,column=0,pady=10,padx=10)

quantityLabel = tkinter.Label(quantityFrame,width=10,text="Quantity: ")
quantityLabel.grid(row=0,column=0)
quantityInput = tkinter.Spinbox(quantityFrame,from_=QUANTITY_LOWER_RANGE,to=QUANTITY_UPPER_RANGE)
quantityInput.insert(0,0)
quantityInput.grid(row=0,column=1)

#Place Order Button
confirmFrame = tkinter.Frame(orderFrame)
confirmFrame.grid(row=3,column=0,pady=10,padx=5)

confirmButton = tkinter.Button(confirmFrame,width=10,text="Confirm")
confirmButton.pack()
#Confirm button is bound to placeOrder() later on (it must first be defined)

#MADE A TABLE BUT ITS OPENING A NEW WINDOW
from tkinter import *

tableFrame = tkinter.Frame(root, relief=tkinter.RIDGE,bd=3)
tableFrame.grid(row=3,column=1)

root = tableFrame
#need to add 2 labels on top of the table for buy and sell

height = 5 #rows
width = 2 #colums
for i in range(height): #Rows
    for j in range(width): #Columns
        b = Entry(root, text="")
        b.grid(row=i, column=j)

#Stuck here (vasili)

class Graph():
    """Class to plot data to a canvas"""
    def __init__(self,canvasRef,maxCoords,CW,CH,padding=200):
        """Reference to a canvas object, max points of data shown simultaneously, canvas dimensions and padding for axis"""
        self.canvas = canvasRef
        self.values = []
        self.maxCoords = maxCoords
        self.CW, self.CH = CW-padding, CH-padding
        self.padding = padding
    def addCoords(self,coords):
        """Add (x,y) to the list of coordinates, old values are removed according to maxCoords attribute"""
        self.values.append(coords)
        while len(self.values) > self.maxCoords:
            self.values.pop(0)
    def plot(self):
        """Plot stored coordinates to the canvas"""

        #Remove previous items
        self.canvas.delete(tkinter.ALL)

        if len(self.values) < 1:
            return

        #Logic to make sure that not all y values are the same
        #Avoids /0 error later when scaling the data
        v = 0
        ok = False
        while v < len(self.values):
            if self.values[v][1] != self.values[0][1]:
                ok = True
                break
            v += 1
        if not ok:
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

                #Create line between this point and the next, applying calculations to scale and fit the points
                self.canvas.create_line(int(self.CW*((self.values[c][0]-minx)/scalex))+self.padding//2,
                                        self.CH-int(self.CH*((self.values[c][1]-miny)/scaley))+self.padding//2,
                                        int(self.CW*((self.values[c+1][0]-minx)/scalex))+self.padding//2,
                                        self.CH-int(self.CH*((self.values[c+1][1]-miny)/scaley))+self.padding//2,
                                        fill=col,width=2)

        #Create axis based on self.padding
        self.canvas.create_line(self.padding//2,self.padding//2,self.padding//2,self.CH+self.padding//2,fill="#ffffff",width=2)
        self.canvas.create_line(self.padding//2,self.CH+self.padding//2,self.CW+self.padding//2,self.CH+self.padding//2,fill="#ffffff",width=2)

        #Label axis with coordinates
        self.canvas.create_text(self.padding//2,self.CH+int(self.padding*3/4),text=str(int(minx)),fill="#ffffff",font=("fixedsys",10),anchor=tkinter.W)
        self.canvas.create_text(self.padding//4,self.CH+self.padding//2,text=str(int(miny)),fill="#ffffff",font=("fixedsys",10),anchor=tkinter.W)
        self.canvas.create_text(self.CW+self.padding//2,self.CH+int(self.padding*3/4),text=str(int(maxx)),fill="#ffffff",font=("fixedsys",10),anchor=tkinter.W)
        self.canvas.create_text(self.padding//4,self.padding//2,text=str(int(maxy)),fill="#ffffff",font=("fixedsys",10),anchor=tkinter.W)

        #Update canvas
        self.canvas.update()


#Create a graph
g = Graph(canvas,200,CW,CH)
for x in range(100):
    g.addCoords((x,random.random()*100))




#Plot function is called repeatedly in mainloop
def plot():
    global x

    #Generate example data
    x += 1
    g.addCoords((x,g.values[-1][1]+(random.random()-.5)*10))

    #Draw to canvas
    g.plot()

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
    root.after(100,scrollFeed)

#Form has been submitted
def placeOrder():
    order = {"orderType":buyOrSell.get(),"price":priceInput.get(),"quantity":quantityInput.get()}
    print(order)

#Configure confirm button to this function after the function has been defined
confirmButton.config(command=placeOrder)

def backgroundTasks():
    plot()
    scrollFeed()

#Add plot to mainloop and hand over control to gui
root.after(1,backgroundTasks)
root.mainloop()


