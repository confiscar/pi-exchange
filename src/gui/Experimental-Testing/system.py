import matplotlib.pyplot as plt
import numpy as np

# Create the figure and axes, keeping the object references
fig = plt.figure()
ax = fig.add_subplot(111)

p, = ax.plot(np.linspace(0,1))

# First display
plt.show()

 # Some time to let you look at the result and move/resize the figure
plt.pause(3)

# Replace the contents of the Axes without making a new window
ax.cla()
p, = ax.plot(2*np.linspace(0,1)**2)

# Since the figure is shown already, use draw() to update the display
plt.draw()
plt.pause(3)

# Or you can get really fancy and simply replace the data in the plot
p.set_data(np.linspace(-1,1), 10*np.linspace(-1,1)**3)
ax.set_xlim(-1,1)
ax.set_ylim(-1,1)

plt.draw()