import iceml 
import numpy as np
import math
import matplotlib.pyplot as plt
import time

def generate_data(nr_of_samples): 
    mean = [0, 0]
    cov = [[1, 0], [0, 1]] 
    objs = nr_of_samples
    x, y = np.random.multivariate_normal(mean, cov, objs).T
    return np.array([x, y]).T

def add_anomaly(X, anom):
    for i in range(np.size(anom, 1)):
        X = np.vstack((X, [anom[i][0], anom[i][1]]))
    return X 

def plot(X, anom):
    plt.figure(figsize=(7,7))
    plt.plot(X[:,0], X[:,1], 'bo');
    plt.plot(anom[:,0],anom[:,1], 'ro');
    plt.title("Data points")

def plot_subsample(X):
    plt.figure(figsize=(7,7))
    plt.plot(X[:,0], X[:,1], 'bo');
    plt.title("Subsamples points")

# train an isolation forest
nr_of_samples = 200000
max_depth = 200
number_of_trees = 100 
subsample_size = 2000 

X = generate_data(nr_of_samples)

# add an anomaly to the data 
anom = np.array([[8.9, 8.9], [6.9, 6.9]])
X = add_anomaly(X, anom)

print("-> creating isolation forest")
start = time.time()

pair = iceml.isolation_forest.create(X, max_depth, number_of_trees, True, subsample_size)
err = pair[1]
if err is not None:
    print("ERROR:",err.msg())
    exit(-1)
iforest = pair[0] 

# subsample = iforest.get_subsample(0)
# plot_subsample(subsample)

end = time.time()
print("-> done creating isolation forest in", ((end-start)*1000), "milliseconds")

print("-> training isolation forest")
start = time.time()
iforest.fit()
end = time.time()
print("-> done training isolation forest in", ((end-start)*1000), "milliseconds")

print("-> calc expected path lengths")
start = time.time()
expected_path_lengths = iforest.expected_path_lengths(X)
end = time.time()
print("-> done calc expected path lengths", ((end-start)*1000), "milliseconds")

print("-> calc anom score")
start = time.time()
anom_score = iforest.anom_score(X)
end = time.time()
print("-> done calc anom score", ((end-start)*1000), "milliseconds")

print("-> calc anomalies")
start = time.time()
anomalies = iforest.anomalies(X, 0.1)
end = time.time()
print("-> done anomalies", ((end-start)*1000), "milliseconds")

num_rows = np.shape(expected_path_lengths)[0]
x = np.arange(0, num_rows, 1)

print(iforest.anomalies(np.array([[3.3, 3.3]]), 0.2))

# plot anomalies
plt.figure(figsize=(7,7))
plt.plot(x, anomalies[:,0]);
plt.title("Detected anomalies")

# plot anom score
plt.figure(figsize=(7,7))
plt.plot(x, anom_score[:,0]);
plt.title("Anomalies scores")

# plot expected path lengths
plt.figure(figsize=(7,7))
plt.plot(x, expected_path_lengths[:,0]);
plt.title("Expected path lengths")

# plot data
plot(X, anom)

# shows all plots
plt.show()
