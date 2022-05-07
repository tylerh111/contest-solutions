#!/bin/python3

import math

m = int(input())

upper = 10**m

prop_sum = 0

n = 10
while n < upper:

    x = (n % 10)*10**(int(math.log10(n))) + (n // 10)

    if x % n == 0:
        prop_sum += n % 10**5
    
    n += 1


print(prop_sum)

