
t = int(input())
for i in range(t):
    n = int(input())
    x = 2**n
    print(sum([int(d) for d in str(x)]))

