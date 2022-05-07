#!/bin/python3
import math
import sys


def largest_prime_factor(x):
    
    n = x
    lpf = -1

    while n%2 == 0:
        n = n // 2
        lpf = 2

    for i in range(3, int(math.sqrt(n))+1, 2):
        while n%i == 0:
            n = n // i
            lpf = i
    
    if n > 2:
        lpf = n
    
    return lpf
    


t = int(input().strip())
for a0 in range(t):
    n = int(input().strip())

    res = largest_prime_factor(n)
    print(res)

