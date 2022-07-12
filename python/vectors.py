import numpy as np
import matplotlib.pyplot as plt

V = np.array([[1,1],[-2,2],[4,-7]])

x = np.array([[1,1]])
p = np.array([[3,4]])
n = np.array([[1,2]])

origin = [0], [0] # origin point

plt.quiver(*origin, x[:,0], x[:,1], color=['r'], scale=21)
plt.quiver(*origin, p[:,0], p[:,1], color=['g'], scale=21)
plt.quiver(*origin, n[:,0], n[:,1], color=['b'], scale=21)
plt.show()
