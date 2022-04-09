from functools import reduce

m = 7 # GF(2^m)/f(x)
n = 2 ** m - 1
errorCount = 1
k = n - 2 * errorCount
P = [1, 1, 0, 0, 0, 0, 0, 1] # f(x) = x^3 + x + 1
alpha_to = [0]*(n + 1)
index_of = [0]*(n + 1)


def create_look_up():
    mask = 1
    alpha_to[m] = 0

    for i in range(m):
        alpha_to[i] = mask
        index_of[alpha_to[i]] = i
        if P[i] != 0:
            alpha_to[m] ^= mask
        mask <<= 1

    index_of[alpha_to[m]] = m
    mask >>= 1

    for i in range(m + 1, n):
        if alpha_to[i - 1] >= mask:
            alpha_to[i] = alpha_to[m] ^ ((alpha_to[i - 1] ^ mask) << 1)
        else:
            alpha_to[i] = alpha_to[i - 1] << 1
        index_of[alpha_to[i]] = i

    index_of[0] = -1


def mult(a, b):
    if (a == 0) or (b == 0):
        return 0
    res = (index_of[a] + index_of[b]) % n
    return index_of.index(res)


def div(a, b):
    if a == 0:
        return 0
    if b == 0:
        return -1
    res = (index_of[a] - index_of[b]) % n
    return index_of.index(res)


def inv(a, deg):
    if a == 0:
        return 0
    res = (index_of[a] * deg) % n
    return index_of.index(res)

def byte_xor(ba1, ba2):
    return bytes([_a ^ _b for _a, _b in zip(ba1, ba2)])



create_look_up()
print(alpha_to)
print(index_of)
print(index_of.index(119))
print(mult(131, 74))
print(div(131, 74))
print(inv(5, 2))

from functools import reduce

# constants used in the multGF2 function
mask1 = mask2 = polyred = None


def setGF2(degree, irPoly):
    """Define parameters of binary finite field GF(2^m)/g(x)
       - degree: extension degree of binary field
       - irPoly: coefficients of irreducible polynomial g(x)
    """

    def i2P(sInt):
        """Convert an integer into a polynomial"""
        return [(sInt >> i) & 1
                for i in reversed(range(sInt.bit_length()))]

    global mask1, mask2, polyred
    mask1 = mask2 = 1 << degree
    mask2 -= 1
    polyred = reduce(lambda x, y: (x << 1) + y, i2P(irPoly)[1:])


def multGF2(p1, p2):
    """Multiply two polynomials in GF(2^m)/g(x)"""
    p = 0
    while p2:
        if p2 & 1:
            p ^= p1
        p1 <<= 1
        if p1 & mask1:
            p1 ^= polyred
        p2 >>= 1
    return p & mask2


    # Define binary field GF(2^3)/x^3 + x + 1
setGF2(7, 0b10000011)

    # Evaluate the product (x^2 + x + 1)(x^2 + 1)
print(multGF2(0b10000011, 0b1001010))

