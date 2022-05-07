#!/bin/python

import math

mod = 10**9+7

m = int(input())

upper = 10**(m)
n = 10**(m-1)

def check_three_sum(n, m):
    # digits = [(n//(10**i))%10 for i in range(math.ceil(math.log(n, 10))-1, -1, -1)]
    digits = [int(d) for d in str(n)]
    for i in range(0, m-3+1):
        if sum(digits[i:i+3]) > 9:
            return False
    
    return True

n_ctr = 0

while n < upper:

    if check_three_sum(n, m):
        # print(n)
        n_ctr += 1 % mod
    
    n += 1
    
print(n_ctr)

