#!/usr/bin/env python3
import matplotlib.pyplot as plt
from math import sin,sqrt,cos
import random
def fn(x):
    #return (x)/(sqrt(1+((x)**2)))
    return sin(x)
    


input = []
output = []
for i in range(1000):
    # [-3, 3]
    r = random.uniform(-3, 3)
    
    input.append({'x':r,'y':fn(r)})

with open('output.txt', 'r') as f:
    for line in f:
        x,y = line.split()
        output.append({'x':float(x), 'y':float(y)})


plt.plot([p['x'] for p in input], [p['y'] for p in input], 'ro', label='input')
plt.plot([p['x'] for p in output], [p['y'] for p in output], 'bo', label='output')

plt.grid(True)
plt.legend()
plt.show()