
n = int(input())

for _ in range(n):
    test = input()
    
    i,j = [int(x) for x in input().split(' ')]
    
    if i == 0:
        print(test[:i] + test[j::-1] + test[j+1:])
    else:
        print(test[:i] + test[j:i-1:-1] + test[j+1:])

