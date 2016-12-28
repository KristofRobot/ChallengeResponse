# -*- coding: utf-8 -*-
#https://gist.github.com/endolith/2568571

from __future__ import division
import serial
from pylab import *
from time import time
import Image
import numpy

size = 2**10
loops = 5
data = ""

start_time = time()

for x in range(0, loops):
    print 'Loop ' + str(x)
    with serial.Serial('/dev/ttyUSB0', 115200) as port:
        data += port.read(size)
        
elapsed_time = time() - start_time
    
print 'Read ' + str(len(data)) + ' bytes in ' + str(int(round(elapsed_time))) + ' s'
print 'Data rate: %.1f bit/s' % (len(data)*8 / elapsed_time)

# Binary dump
with open(str(int(time())) + 'out.bin','wb') as f:
    f.write(data)

a = numpy.fromstring(data, dtype = 'uint8')

# Plot
figure()
plot(a, 'bo', alpha=0.1) # Transparent to show stackups

# Histogram
figure()
hist(a, bins=64, range=[0,255])

# Image
repeat = int(sqrt(len(data)))
b = reshape(a[:len(a) - len(a)%repeat], (-1, repeat))
im = Image.fromarray(b)
im.save(str(int(time())) + 'out.png')
