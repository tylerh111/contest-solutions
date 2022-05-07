
import sys
import hashlib
import base64

HASH_SALT = 'IEEE'
HASH_PEPPER = 'Xtreme'

def get_encoding(word: str):
    # setup hash algorithm
    m = hashlib.sha256()
    m.update(HASH_SALT.encode())
    m.update(word.encode())
    m.update(HASH_PEPPER.encode())

    # compute hash and encode
    word_hash = m.digest()
    word_hash_encoded = base64.b64encode(word_hash)
    
    # return decoded binary b64 encoded string
    return word_hash_encoded.decode()



if __name__ == '__main__':
    n = len(sys.argv)
    if (n <= 1):
        print("Must provide a string to encode", file=sys.stderr)
        exit(1)

    words = sys.argv[1:]

    for word in words:
        hash = get_encoding(word)
        print(hash)

