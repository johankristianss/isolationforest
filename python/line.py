import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def generate_data():
    mean = [0, 0]
    cov = [[1, 0], [0, 1]]
    objs = 200
    x, y = np.random.multivariate_normal(mean, cov, objs).T
    return np.array([x, y]).T

def plot(X):
    plt.plot(X[:,0], X[:,1], 'bo');
    plt.show()

X = generate_data()

origin = [0], [0] 
n = np.array([1,2])
p = np.array([-2,0.5])
xs = np.array([-1,-1]) # sample point
n_p = xs - p   
s = n_p.dot(n) 
if s<=0:
    print("xs is below")
else:
    print("xs is above")

# this is our interept point
plt.figure(figsize=(13,13))
plot(X)
plt.plot(p[0],p[1], 'ro');

# plot sample point
plt.plot(xs[0],xs[1], 'rx');

# draw the split line
x = np.linspace(-3,3,100)
c = -p.dot(n)
y = n[0]*x/(-n[1])+c/-n[1]
plt.plot(x, y, '-r')

# draw normal vector
plt.quiver(*p, n[0], n[1], color=['r'], scale=15)
plt.quiver(*p, n_p[0], n_p[1], color=['g'], scale=15)

plt.axis('equal')
plt.show()
