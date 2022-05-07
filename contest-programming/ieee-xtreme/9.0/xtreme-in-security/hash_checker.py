
import sys
import subprocess
import time
import itertools
import string
import math

from tqdm import tqdm

import hash_encoder

HASH_FILE = 'hashes.txt'
INPUT_FILE = 'words_alpha.txt'
OUTPUT_FILE = 'new_hashes_found.txt'

def remove_symbols(word: str):
    whitelist = string.ascii_letters + string.digits
    return ''.join(c for c in word if c in whitelist)

def common_replace(word: str):
    def common_replace_helper(word: str, from_char: str, to_char: str):
        if len(from_char) != 1 or len(to_char) != 1:
            raise ValueError
        options = [(c,) if c != from_char else (from_char, to_char) for c in word]
        return list(''.join(o) for o in itertools.product(*options))
    
    added_words = []

    added_words += common_replace_helper(word, 'a', '4')
    added_words += common_replace_helper(word, 'e', '3')
    added_words += common_replace_helper(word, 'i', '1')
    added_words += common_replace_helper(word, 'o', '0')

    # added_words += common_replace_helper(word, 't', '7')
    # added_words += common_replace_helper(word, 's', 'z')
    # added_words += common_replace_helper(word, 's', '5')
    # added_words += common_replace_helper(word, 'b', '6')

    added_words = list(set(added_words))

    return added_words

def common_append(word: str, size_limit: int = -1):
    def common_append_helper(word: str, lower_limit: int, upper_limit: int, size_limit: int = -1, leading_zeros: int = 0):
        if lower_limit > upper_limit:
            raise ValueError
        numbers = (str(i).zfill(leading_zeros) for i in range(lower_limit, upper_limit) if i <= size_limit or size_limit < 0)
        return list(''.join([word, num]) for num in numbers)

    added_words = []

    added_words += common_append_helper(word, 0, 10)

    return added_words


def hash_and_check(input: str):
    input_hash = hash_encoder.get_encoding(input)
    found_match = False
    for hash in HASHES:
        if input_hash == hash:
            found_match = True
            break
    
    return found_match, input_hash


def load_hash_file(filename: str):
    hashes = []
    with open(filename) as f:
        hashes = [line[:-1] for line in f]

    return hashes


def generate_words_from_file():
    num_words = int(subprocess.check_output(['wc', '-l', INPUT_FILE]).split()[0])
    with open(INPUT_FILE, 'r') as f_in:
        for _ in tqdm(range(num_words)):
            word = f_in.readline()[:-1]
            filtered_word = remove_symbols(word).lower()
            password_bases = common_replace(filtered_word)
            for password_base in password_bases:
                yield password_base
                password_list = common_append(word, 20)
                for password in password_list:
                    yield password


def generate_words_from_order(lower_limit: int, upper_limit: int):
    num_words = math.ceil((1/35) * (36 ** upper_limit - 36 ** lower_limit))
    with tqdm(total=num_words) as pbar:
        for word_size in range(lower_limit, upper_limit):
            chars = string.ascii_lowercase + string.digits
            for item in itertools.product(chars, repeat=word_size):
                pbar.update()
                yield ''.join(item)


def check_word_list(password_list):
    hashes_found = set()

    with open(OUTPUT_FILE, 'a') as f_out:
        for password in password_list:
            found_match, password_hash = hash_and_check(password)

            if found_match and password_hash not in hashes_found:
                hashes_found.add(password_hash)
                result = '{:<20} -> {} {}\n'.format(password, password_hash, 'MATCH!!!')
                print(result, end='')
                f_out.write(result)
            # else:
            #     result = '{:<20} -> {}\n'.format(password, password_hash)


if __name__ == '__main__':
    global HASHES
    HASHES = load_hash_file(HASH_FILE)
    
    # check_word_list(generate_words_from_file())
    # check_word_list(generate_words_from_order(0, 5))
    check_word_list(['_'])



