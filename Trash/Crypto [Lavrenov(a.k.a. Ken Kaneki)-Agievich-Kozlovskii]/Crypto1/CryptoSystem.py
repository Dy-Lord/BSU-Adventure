import math
import argparse
import textwrap

import numpy as np
import numpy.linalg as la
from math import gcd as bltin_gcd

defAlphabet = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ "
defEn = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
defKe = "NOPQRSTUVWXYZABCDEFGHIJKLM"
hillkey = "DDCF"

def bezout(a, b):
    '''An implementation of extended Euclidean algorithm.
    Returns integer x, y and gcd(a, b) for Bezout equation:
        ax + by = gcd(a, b).
    '''
    x, xx, y, yy = 1, 0, 0, 1
    while b:
        q = a // b
        a, b = b, a % b
        x, xx = xx, x - xx*q
        y, yy = yy, y - yy*q
    return (x, y, a)

def coprime(a, b):
    return bltin_gcd(a, b) == 1

def swap(matrix):
    matrix[0][1] *= -1
    matrix[1][0] *= -1
    tmp = matrix[0][0]
    matrix[0][0] = matrix[1][1]
    matrix[1][1] = tmp
    return matrix

def shiftCipher(alphabet: list, text: list, key: list, encrypt=True):
    shift = alphabet.index(key[0])
    if encrypt:
        for i in range(len(text)):
            idx = alphabet.index(text[i]) + shift
            text[i] = alphabet[idx % len(alphabet)]
    else:
        for i in range(len(text)):
            idx = alphabet.index(text[i]) - shift
            text[i] = alphabet[idx % len(alphabet)]

    return text


def affineCipher(alphabet: list, text: list, key: list, encrypt=True):
    k1 = alphabet.index(key[0])
    k2 = alphabet.index(key[1])
    out = bezout(k1, len(alphabet))
    k3 = out[0]
    k3 = (k3 % len(alphabet) + len(alphabet)) % len(alphabet)

    if not coprime(k1, len(alphabet)) or out[2] != 1:
        return "Wrong key:("

    if encrypt:
        for i in range(len(text)):
            idx = k1 * alphabet.index(text[i]) + k2
            text[i] = alphabet[idx % len(alphabet)]
    else:
        for i in range(len(text)):
            idx = k3 * (alphabet.index(text[i]) + len(alphabet) - k2)
            text[i] = alphabet[idx % len(alphabet)]

    return text


def replaceCipher(alphabet: list, text: list, key: list, encrypt=True):
    if len(alphabet) != len(key):
        return "Wrong key:("
    if encrypt:
        for i in range(len(text)):
            text[i] = key[alphabet.index(text[i])]
    else:
        for i in range(len(text)):
            text[i] = alphabet[key.index(text[i])]

    return text


def hillCipher(alphabet: list, text: list, key: list, encrypt=True):
    dimension = 2
    if len(key) < dimension * dimension:
        return "Wrong key:("

    mkey = np.zeros((dimension, dimension))
    cnt = 0

    # key matrix fill
    for i in range(dimension):
        for j in range(dimension):
            mkey[i][j] = alphabet.index(key[cnt])
            cnt += 1
    out = bezout(int(la.det(mkey)), len(alphabet))
    if (la.det(mkey) % len(alphabet) == 0) or not coprime(int(la.det(mkey)), len(alphabet)) or out[2] != 1:
        return "Wrong key:("
    #fill blocks of text
    mtext = np.zeros((math.ceil(len(text) / dimension), dimension))
    cnt = 0

    for i in range(len(mtext)):
        for j in range(len(mtext[i])):
            if cnt < len(text):
                mtext[i][j] = alphabet.index(text[cnt])
            else:
                mtext[i][j] = 0
            cnt += 1

    if encrypt:
        for i in range(len(mtext)):
            mtext[i] = np.array(mtext[i]).dot(mkey)
            #mtext[i] = mkey.dot(mtext[i])

    else:
        #for dimension > 2 upgrade this section
        temp = (len(alphabet) + 1) / la.det(mkey)
        mkey = swap(mkey)

        for i in range(len(mkey)):
            for j in range(len(mkey[i])):
                mkey[i][j] = (mkey[i][j] * temp) % len(alphabet)
        for i in range(len(mtext)):
            mtext[i] = np.array(mtext[i]).dot(mkey)
            #mtext[i] = mkey.dot(mtext[i])

    res = []
    for i in range(len(mtext)):
        for j in range(len(mtext[i])):
            res.append(alphabet[math.ceil(mtext[i][j]) % len(alphabet)])

    return res


def transCipher(alphabet: list, text: list, key: list, encrypt=True):
    if len(key) != len(set(key)):
        return "Wrong key:("

    indx = []
    newkey = []
    for i in range(len(key)):
        indx.append(alphabet.index(key[i]))
    indx.sort()
    for i in range(len(key)):
        newkey.append(indx.index(alphabet.index(key[i])))

    if encrypt:
        for i in range(len(key) - (len(text) % len(key))):
            text.append(alphabet[0])
        res = list(text)
        for i in range(int(len(text) / len(key))):
            for j in range(len(key)):
                res[newkey[j] + len(key) * i] = text[i * len(key) + j]
    else:
        res = list(text)
        for i in range(int(len(text) / len(key))):
            for j in range(len(key)):
                res[i * len(key) + j] = text[newkey[j] + len(key) * i]

    return res


def vigenerCipher(alphabet: list, text: list, key: list, encrypt=True):
    vigquart = [[0 for i in range(len(alphabet))] for j in range(len(alphabet))]
    for i in range(len(vigquart)):
        for j in range(len(vigquart[i])):
            vigquart[i][j] = alphabet[(j + i) % len(alphabet)]

    cnt = 0
    poz = 0
    if encrypt:
        for i in range(len(text)):
            if cnt == len(key):
                cnt = 0

            for k in range(len(vigquart)):
                if vigquart[k][0] == key[cnt]:
                    poz = k
                    break
            text[i] = vigquart[poz][vigquart[0].index(text[i])]
            cnt += 1
    else:
        for i in range(len(text)):
            if cnt == len(key):
                cnt = 0

            for k in range(len(vigquart)):
                if vigquart[k][0] == key[cnt]:
                    poz = k
                    break
            text[i] = vigquart[0][vigquart[poz].index(text[i])]
            cnt += 1

    return text


parser = argparse.ArgumentParser(description="Encryption system [Vazavikou Mikita]\n launch example: python3 Cryptosystem.py --alphabet alphabet.txt --text text.txt --key key.txt --cipher 4 --method 0", formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument("--alphabet", default="59F123", help="Path to alphabet file. The default is 'АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ '")
parser.add_argument("--text", required=True, help="Path to opentext/ciphertext file")
parser.add_argument("--key", required=True, help="Path to key file")
parser.add_argument("--cipher", default=0, type=int, required=True, choices=[0, 1, 2, 3, 4, 5], help=textwrap.dedent('''\
                                                                                   Cipher method
                                                                                   0 | Shift cipher 
                                                                                   1 | Affine cipher 
                                                                                   2 | Replace cipher 
                                                                                   3 | Hill cipher 
                                                                                   4 | Transfer cipher 
                                                                                   5 | Vigenere cipher'''))
parser.add_argument("--method", default=1, type=int, choices=[0, 1], help="Decrypt or encrypt a file? The default is encryption\n 0 | decrypt\n 1 | encrypt")

args = parser.parse_args()

alphabet = args.alphabet
cipher = args.cipher
method = args.method

if method == 0:
    method = False
else:
    method = True
if alphabet == "59F123":
    alphabet = defAlphabet
else:
    alpfile = open(alphabet)
    alphabet = alpfile.read()
    alpfile.close()

textfile = open(args.text)
keyfile = open(args.key)

text = textfile.read()
key = keyfile.read()

textfile.close()
keyfile.close()
exit = False

if len(alphabet) != len(set(alphabet)):
    print("Wrong alphabet:(")
    exit = True

for a in text:
    if a not in alphabet:
        print("The text contains a non-alphabetic character:)")
        exit = True
        break
for a in key:
    if a not in alphabet:
        print("The key contains a non-alphabetic character:)")
        exit = True
        break

if not exit:
    result = ""
    if cipher == 0:
        result = result.join(shiftCipher(list(alphabet),list(text), list(key), encrypt=method))
    elif cipher == 1:
        result = result.join(affineCipher(list(alphabet), list(text), list(key), encrypt=method))
    elif cipher == 2:
        result = result.join(replaceCipher(list(alphabet), list(text), list(key), encrypt=method))
    elif cipher == 3:
        result = result.join(hillCipher(list(alphabet), list(text), list(key), encrypt=method))
    elif cipher == 4:
        result = result.join(transCipher(list(alphabet), list(text), list(key), encrypt=method))
    elif cipher == 5:
        result = result.join(vigenerCipher(list(alphabet), list(text), list(key), encrypt=method))

    if method:
        print("Encryption complete *_*")
    else:
        print("Decryption complete *_*")
    print(text)
    print(result)

    if method:
        file = open("encrypt.txt", 'w')
        file.write(result)
        file.close()
        print("Data written to encrypt.txt")
    else:
        file = open("decrypt.txt", 'w')
        file.write(result)
        file.close()
        print("Data written to decrypt.txt")

