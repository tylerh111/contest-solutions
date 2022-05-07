from sys import stdin, stdout

lines = [stdin.readline() for _ in range(5)]

base, numbers = lines[0].split(' ')
base = int(base)

digits = {}
for i, d in enumerate(numbers):
    digits[d] = i

s1 = lines[1].strip()
s2 = lines[2][1:].strip()


def convertToInt(s):
    n = 0
    for i, c in enumerate(reversed(s)):
        n += digits[c] * base ** i
    
    return n

def convertToStr(n):
    s = ''
    while n > 0:
        s += numbers[n % base]
        n //= base
    
    return ''.join(reversed(s))


n1 = convertToInt(s1)
n2 = convertToInt(s2)

lines[4] = ' ' + convertToStr(n1 + n2)

stdout.write(''.join(lines))

