#!/usr/bin/env python
#
# hackerrank https://www.hackerrank.com/challenges/maximize-it
#
from __future__ import print_function

class Res:
    pass

def sel(aa, p, sm, res):
    if (p < 0):
        if sm % res.m > res.mx:
            res.mx = sm % m
    else:
        for e in aa[p]:
            sel(aa, p-1, sm+e, res)

def my_sq(s):
    i = int(s)
    return i*i
        
k, m = map(int, raw_input().split())
aa = []
for _ in xrange(k):
    aa.append(map(my_sq, raw_input().split()[1:]))
    
res = Res()
res.m = m
res.mx = 0
sel(aa, len(aa)-1, 0, res)
print(res.mx)
