import os
import pathlib
import matplotlib.pyplot as plt

data = []
p = '/home/cmtheit/Codes/Learn/modern_operating_system'
for (dirn, dirs, files) in os.walk(p):
    for file in files:
        data.append(os.path.getsize(f'{dirn}/{file}'))

plt.hist(data, bins=100)
plt.show()