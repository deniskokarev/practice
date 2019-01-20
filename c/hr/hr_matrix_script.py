#!/usr/bin/env python
#
# hackerrank https://www.hackerrank.com/challenges/matrix-script
#
from __future__ import print_function
import numpy as np
import re

def mysub(s):
    h = re.sub(r'[^A-Za-z0-9]+$', '', s)
    t = re.sub(r'^.*[A-Za-z0-9]([^A-Za-z0-9]+)$', r'\1', s)
    hr = re.sub(r'([A-Za-z0-9]+)[^A-Za-z0-9]*', r'\1 ', h)
    return hr[0:-1] + t

n, m = map(int, raw_input().split())
s = ""
for _ in xrange(n):
    s += raw_input()
mm = np.array(map(ord, s), np.int8) # str -> 1d
mm = np.reshape(mm, (n, m)) # 1d -> 2d
mm = np.transpose(mm)
mm = np.reshape(mm, (n*m)) # 2d -> 1d
s = ''.join(map(chr, mm)) # 1d -> str
print(mysub(s))
