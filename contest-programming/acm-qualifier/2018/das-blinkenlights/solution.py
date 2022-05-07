
import math


def lcm(a, b):
    return abs(a*b) // math.gcd(a, b)


def sync_blink(p, q, s):
    return lcm(p, q) <= s


if __name__ == '__main__':
    (p, q, s) = map(int, input().split())
    
    if sync_blink(p, q, s):
        print("yes")
    else:
        print("no")
        
