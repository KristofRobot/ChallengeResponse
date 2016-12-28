# -*- coding: utf-8 -*-

from __future__ import division
import serial
from pylab import *
from time import time
import collections

max_size = 32
data = ""

# Read binary dump
with open(sys.argv[1],'rb') as f:
    data=f.read()
            
print 'Read ' + str(len(data)) + ' bytes'

#check for duplicates for different sizes, and print top one if found
for size in range(1, max_size+1):
    bin_chunks = [data[size*i:size*(i+1)] for i in xrange(len(data)//size)]

    print ' Found ' + str(len(bin_chunks)) + ' elements of size ' + str(size)

    for number, count in collections.Counter(bin_chunks).most_common(1):
        if (count > 1):
            print '     Top duplicate value: %s: %7d' % (number.encode('hex'), count)
        else:
            print '     No duplicates'
