import tkinter
import random

#Width and heights of the screen and canvas
W,H = 800,640
CW,CH = 640,640

#Create window
root = tkinter.Tk()
root.title("FOREX MARKET GUI PROTOTYPE")
root.geometry(str(W)+"x"+str(H)+"+80+40")

#Create canvas and add to window
canvas = tkinter.Canvas(root,width=CW,height=CH,bg='#000000')
canvas.grid(row=0,column=0)


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


#Add plot to mainloop and hand over control to gui
root.after(1,plot)
root.mainloop()


