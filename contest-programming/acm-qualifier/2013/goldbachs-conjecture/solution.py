

n = int(input())
testcases = []

for _ in range(n):
    testcases.append(int(input()))

m = max(testcases)


def getPrimes(n): 
    if n==2: return [2]
    elif n<2: return []
    s = list(range(3,n+1,2))
    mroot = n ** 0.5
    half = (n+1)/2-1
    i = 0
    m = 3
    while m <= mroot:
        if s[i]:
            j = (m*m-3) // 2
            s[j] = 0
            while j < half:
                s[j] = 0
                j += m
        i += 1
        m = 2*i + 3
    return [2]+[x for x in s if x]


primes = getPrimes(m+1)

for t in testcases:
    combos = []
    
    i = 0
    j = -1
    
    while primes[i] <= primes[j]:
        total = primes[i] + primes[j]
        if total == t:
            combos.append((primes[i], primes[j]))
        if total <= t:
            i += 1
        else:
            j -= 1
        
    
    print(t, 'has', len(combos), 'representation(s)')
    for c in combos:
        print(str(c[0]) + '+' + str(c[1]))
    
    print()

