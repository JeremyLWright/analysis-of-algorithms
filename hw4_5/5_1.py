import numpy

def median( ns ):
    l = len(ns)
    if l % 2 == 0:
        return (ns[l/2] + ns[(l/2)-1])/2.0
    else:
        return ns[l/2]


def find_median(a, b):
    l = len(a)
    if l == 1:
        return (median(a) + median(b)) / 2
    if l == 2:
        return ( max(a[0], b[0]) + min(a[1], b[1]) ) / 2

    ma = median(a)
    mb = median(b)

    if ma == mb:
        return ma
    
    if ma < mb:
        if l % 2 == 0:
            return find_median(a[l/2:], b[:l/2])
        else:
            return find_median(a[l/2:], b[:(l/2)+1])
    else:
        if l % 2 == 0:
            return find_median(a[l/2-1:], b[l/2-1:])
        else:
            return find_median(a[:(l/2)+1], b[(l/2):])

import random
for i in range(10):
    a = [random.randint(0,10) for r in xrange(10)]
    b = [random.randint(0,10) for r in xrange(10)]
    c = a + b

    a.sort()
    b.sort()
    c.sort()
    print a, b, c
    if median(c) == find_median(a,b):
        print "PASS"
    else:
        print "FAIL"

