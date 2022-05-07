#!/bin/python3

import sys


t = int(input().strip())
for a0 in range(t):
    n = int(input().strip())

    el = list(range(1,n+1))
    r1 = ((n * (n+1))//2) ** 2
    r2 = ((n * (n+1) * (2*n+1))//6)
    res = r1 - r2
    print(res)
