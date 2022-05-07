import os

# pre calculate factorials
facts = [1 for _ in range(10)]
for i in range(2, 10):
    facts[i] = i * facts[i-1]


def getDigits(n):
    return [int(c) for c in str(n)]


# memo_f[k][0] := f(k)
# memo_f[k][1] := sf(k)
memo_f = {}

# memo_g[k][0] := g(k)
# memo_g[k][1] := sg(k)
memo_g = {}


def base_f(n):
    digits = getDigits(n)
    s = 0
    for d in digits:
        s += facts[d]
    
    return s


def base_sf(n):
    x = base_f(n)
    s = sum([int(c) for c in str(x)])
    return [x, s]


def sf(n):
    if n not in memo_f.keys():
        [x, s] = base_sf(n)
        memo_f[n] = [x, s]
        return s
    else:
        return memo_f[n][1]


def base_g(i):
    n = 1
    while True:
        x = sf(n)
        if x == i:
            break

        n += 1

    return n


def base_sg(i):
    x = base_g(i)
    s = sum([int(c) for c in str(x)])
    return [x, s]


def g(i):
    if i not in memo_g.keys():
        [x, s] = base_sg(i)
        memo_g[i] = [x, s]
        return s
    else:
        return memo_g[i][1]



def solve(n, prev_n, prev_res):
    res = 0
    for i in range(prev_n, n+1):
        res += g(i)
    
    return res
    


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input())
    queries = [0 for _ in range(q)]
    mods = [0 for _ in range(q)]

    for i in range(q):
        queries[i], mods[i] = [int(x) for x in input().split(' ')]

    queries.sort()
    print(queries)
    print('--------------------------')

    prev_n = 1
    prev_res = 0
    for i, n in enumerate(queries):
        res = solve(n, prev_n, prev_res)
        fptr.write(str(res % mods[i]) + '\n')
        prev_res = res

    fptr.close()

    def printdict(d):
        for k,v in d.items():
            print(k, ':', v)
    
    print('memo_f')
    printdict(memo_f)
    print('--------------------------')
    print('memo_g')
    printdict(memo_g)
    print('--------------------------')
    



