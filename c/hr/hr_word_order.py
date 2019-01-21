#!/usr/bin/env python
#
# hackerrank https://www.hackerrank.com/challenges/word-order
#
from __future__ import print_function
import sys
from collections import defaultdict

n = int(raw_input())
lst = sys.stdin.read().splitlines()
cnt = defaultdict(int)
for l in lst:
    cnt[l] += 1

print(len(cnt))
for l in lst:
    if (cnt[l] > 0):
        print(cnt[l], end=' ')
        cnt[l] = 0
print()
