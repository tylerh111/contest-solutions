
import sys

n, m = [int(x)+1 for x in input().split(' ')]

add_blocks = []
sub_blocks = []

def count_blocks(rec):
    blocks = 0
    x0, y0, x1, y1 = rec
    # print('query rec =', rec)
    is_in = lambda x,y : x0 <= x and x <= x1 and y0 <= y and y <= y1
    
    for rx0, ry0, rx1, ry1 in add_blocks:
        for y in range(ry0, ry1+1):
            for x in range(rx0, rx1+1):
                if (is_in(x, y)):
                    blocks += 1
    
    for rx0, ry0, rx1, ry1 in sub_blocks:
        for y in range(ry0, ry1+1):
            for x in range(rx0, rx1+1):
                if (is_in(x, y)):
                    blocks -= 1
    
    return blocks

num_ops = int(input())
for i in range(0, num_ops):
    op = input().split(' ')
    rec = [int(x) for x in op[1:5]]
    print(op, file=sys.stderr)
    if op[0] == 'a':
        add_blocks.append(rec)
    elif op[0] == 'r':
        sub_blocks.append(rec)
    else:
        print(count_blocks(rec))
    
    print(add_blocks, file=sys.stderr)
    print(sub_blocks, file=sys.stderr)
