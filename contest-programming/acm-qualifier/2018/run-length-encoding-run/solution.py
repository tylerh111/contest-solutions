

def encode_str(s):
    ctr = 1
    c = s[0]
    out = ''
    for i in range(1, len(s)):
        if s[i] == c:
            ctr += 1
        else:
            out += c + str(ctr)
            c = s[i]
            ctr = 1
    
    out += c + str(ctr)
    
    return out
            

def decode_str(s):
    out = ''
    for i in range(0, len(s), 2):
        c = s[i]
        ctr = int(s[i+1])
        out += c*ctr
        
    return out



if __name__ == '__main__':
    (f, s) = input().split()
    
    if f == 'E':
        print(encode_str(s))
    elif f == 'D':
        print(decode_str(s))
        
