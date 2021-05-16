#!/usr/bin/env python
from __future__ import print_function
import sys
import socket
 
s = sys.stdin.readline().rstrip()
 
try:
    socket.inet_aton(s)
    print("Good")
except:
    print("Bad")
