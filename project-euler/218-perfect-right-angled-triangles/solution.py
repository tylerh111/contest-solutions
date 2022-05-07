import math
import os

def isPerfectSquare(x):
    sr = math.sqrt(x)
    return ((sr - math.floor(sr)) == 0)

def isPrimitiveTriangle(a,b,c):
    return math.gcd(a,b) == 1 and math.gcd(b, c) == 1

def isPerfectTriangle(a,b,c):
    return isPerfectSquare(c) and isPrimitiveTriangle(a,b,c)

# assumes a,b,c is perfect
def isSuperPerfectTriangle(a,b,c):
    area = (a*b)/2
    return area % 6 == 0 and area % 28 == 0



def perfectTiplets(cbeg, mbeg, end):
    c, m = cbeg, mbeg
    counter = 0

    # Limiting c would limit
    # all a, b and c
    while c < end:

        # Now loop on n from 1 to m-1
        for n in range(1, m):
            a = m * m - n * n
            b = 2 * m * n
            c = m * m + n * n

            # if c is greater than
            # limit then break it
            if c > end:
                break
            
            if isPerfectTriangle(a,b,c) and not isSuperPerfectTriangle(a,b,c):
                counter += 1
            
            # memo[n] = counter

        m = m + 1
    
    return c, m, counter


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input())
    tests = [0 for _ in range(q)]

    n_max = 0
    for i in range(q):
        n = int(input())
        tests[i] = n
        if n_max < n:
            n_max = n
    
    tests.sort()
            
    # memo = {}
    # memo = [None for _ in range(n_max+1)]
    # print(memo)
    prev_c = 0
    prev_m = 2
    prev_cnt = 0
    for n in tests:
        prev_c, prev_m, cnt = perfectTiplets(prev_c, prev_m, n)
        prev_cnt += cnt
        fptr.write(str(prev_cnt) + '\n')
    
    fptr.close()


