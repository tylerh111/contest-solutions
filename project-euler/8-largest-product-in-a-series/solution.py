#!/bin/python3
import math
import sys
from functools import reduce
import operator

reduce(operator.mul, (3, 4, 5), 1)


t = int(input().strip())
for a0 in range(t):
    n,k = input().strip().split(' ')
    n,k = [int(n),int(k)]
    num = input().strip()

    numel = [int(d) for d in str(num)]

    maxprod = 0

    for i in range(0, n-k+1):
        prod = reduce(operator.mul, numel[i:i+k])
        maxprod = max(maxprod, prod)

    print(maxprod)