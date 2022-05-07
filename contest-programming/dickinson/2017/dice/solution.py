
dice = [int(x) for x in input().rstrip().split(' ')]

while dice[0] != -1:
    print('Minimum total:', len(dice))
    print('Maximum total:', sum(dice))
    
    dice = [int(x) for x in input().rstrip().split(' ')]

