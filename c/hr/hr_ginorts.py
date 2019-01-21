#!/usr/bin/env python
#
# hackerrank https://www.hackerrank.com/challenges/ginorts
#
rng_lc = range(ord('a'), ord('z')+1)
rng_uc = range(ord('A'), ord('Z')+1)
rng_dig = range(ord('0'), ord('9')+1)
str = raw_input()
l = []
for ch in str:
    c = ord(ch)
    if c in rng_lc:
        l.append((0, ch))
    elif c in rng_uc:
        l.append((1, ch))
    elif c in rng_dig:
        if c % 2 == 1: # ord(0) is even
            l.append((2, ch))
        else:
            l.append((3, ch))

ans = ''.join([ch for (_, ch) in sorted(l)])
print ans
