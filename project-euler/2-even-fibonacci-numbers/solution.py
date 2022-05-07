#!/bin/python3

import sys

t = int(input().strip())
for a0 in range(t):
    n = int(input().strip())
    
    sumef = 10
    e_im2 = 2
    e_im1 = 8
    e = 34
    while(e < n):
        sumef += e
        e_im2 = e_im1
        e_im1 = e
        e = 4*e_im1 + e_im2
    
    print(sumef)

