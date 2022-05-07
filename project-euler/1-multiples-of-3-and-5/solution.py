#!/bin/python3

import sys

t = int(input().strip())
for a0 in range(t):
    n = int(input().strip())

    total = 0

    x = n//3
    x = x if n%3 != 0 else x-1
    total += 3 * (x * (x+1)) // 2

    y = n//5
    y = y if n%5 != 0 else y-1
    total += 5 * (y * (y+1)) // 2

    z = n//15
    z = z if n%15 != 0 else z-1
    total -= 15 * (z * (z+1)) // 2

    print(total)
