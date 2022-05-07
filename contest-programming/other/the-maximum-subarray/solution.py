#!/bin/python3

import math
import os
import random
import re
import sys

ARR_MAX = 10**4
ARR_MIN = -ARR_MAX

memo = []
    

# Complete the maxSubarray function below.
def maxSubarray(arr):
    # arr = map(lambda x:x+(-ARR_MIN), arr)
    max_val = max(arr)
    max_sa = max_val
    num_ss = 0
    max_ss = 0
    for i in range(0, len(arr)):
        if arr[i] > 0:
            num_ss += 1
            max_ss += arr[i]
            
        for j in range(i, len(arr)):
            sum_sa = sum(arr[i:j+1])
            # print(i, j, sum_sa)
            if sum_sa > max_sa:
                max_sa = sum_sa
    
    if num_ss == 0:
        max_ss = max_val
    
    return [max_sa, max_ss]
    
    
    

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        n = int(input())

        arr = list(map(int, input().rstrip().split()))
        # memo = [None for _ in range(len(arr))]
        
        result = maxSubarray(arr)

        fptr.write(' '.join(map(str, result)))
        fptr.write('\n')

    fptr.close()
