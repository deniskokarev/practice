#!/usr/bin/env python
#
# hackerrank https://www.hackerrank.com/challenges/piling-up
#
t = int(raw_input())
while t > 0:
    t -= 1
    n = int(raw_input())
    aa = map(int, raw_input().split())
    l = 0
    r = len(aa)-1
    if aa[l] >= aa[r]:
        b = aa[l]
        l += 1
    else:
        b = aa[r]
        r -= 1
    while l <= r:
        if b >= aa[l] and aa[l] >= aa[r]:
            b = aa[l]
            l += 1
        elif b >= aa[r] and aa[r] >= aa[l]:
            b = aa[r]
            r -= 1
        else:
            break
    print ("Yes" if l>r else "No")
