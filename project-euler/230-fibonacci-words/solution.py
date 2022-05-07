
memo_words = ['1', '0']
memo_lens = [(1+0j), (0+1j)]

def getLenOfWord(num, len_a, len_b):
    return num.real * len_a + num.imag * len_b

def binarySearchOnMemoLens(n, la, lb):
    

def getDigit(a,b,n,word):
    # word = memo_words[i]
    for c in word:
        #remove a
        if c == '1':
            if n - len(a) <= 0:
                return a[n-1]
            else:
                n -= len(a)
        elif c == '0':
            if n - len(b) <= 0:
                return b[n-1]
            else:
                n -= len(b)


def findNDigitFib(a,b,n):
    biggest_len = getLenOfWord(memo_lens[len(memo_lens)-1])
    i = len(memo_lens)
    while n > biggest_len:
        memo_words.append(memo_words[i-2] + memo_words[i-1])
        biggest_len = memo_lens[i-2] + memo_lens[i-1]
        memo_lens.append(biggest_len)
        i += 1

    word = binarySearchOnMemoLens(n, len(a), len(b))
    
    return getDigit(a,b,n,i-1)


    



if __name__ == '__main__':
    q = int(input())
    for i in range(q):
        a, b, n = input().split(' ')
        n = int(n)
        print(findNDigitFib(a,b,n))




