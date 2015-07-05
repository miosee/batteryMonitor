# -*- coding: ISO-8859-1 -*-
import numpy
import math
import time
from matplotlib import pyplot


voltage = [0]
count = 0
t = [count]
pyplot.figure(1)
pyplot.ion()
pyplot.show()
while (count < 21):
    count = count+1
    voltage.append(math.sin(2*math.pi*count/20))
    t.append(count)
    pyplot.plot(t[count-1:count], voltage[count-1:count], 'ro')
    time.sleep(1)
    pyplot.draw()

