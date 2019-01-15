import numpy as np
import matplotlib as mlp
import matplotlib.pyplot as plt

x = []
y = []

file = open("zeitenpy.txt","r")
for line in file:
	arr = np.array(line.split(","))
	x.append(int(arr[0]))
	y.append(np.float(arr[2]))

fig, ax = plt.subplots()

ax.plot(x, y)

plt.show()


file.close()