#!/usr/bin/env python
#
# hackerrank https://www.hackerrank.com/challenges/matrix-script
#
from __future__ import print_function
import re

def mysub(s):
    h = re.sub(r'[^A-Za-z0-9]+$', '', s)
    t = re.sub(r'^.*[A-Za-z0-9]([^A-Za-z0-9]*)$', r'\1', s)
    hr = re.sub(r'([A-Za-z0-9]+)[^A-Za-z0-9]*', r'\1 ', h)
    return hr[0:-1] + t

n, m = map(int, raw_input().split())
s = ""
for _ in range(n):
    s += raw_input()
ts = ""
for p in range(m):
    ts += s[p::m]
print(mysub(ts))
