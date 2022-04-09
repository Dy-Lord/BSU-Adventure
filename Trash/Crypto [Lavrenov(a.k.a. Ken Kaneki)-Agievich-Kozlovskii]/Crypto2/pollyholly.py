import argparse
import textwrap


def binary_to_int(ba):
    return int(ba, 2)


def binary_to_str(ba):
    return '{0:0b}'.format(ba)


def poly_max_deg(ba: int):
    if ba == 0:
        return 0
    md = [int(x) for x in list('{0:0b}'.format(ba))]
    return len(md) - md.index(1) - 1


def poly_xor(ba: int, bb: int):
    return int(ba ^ bb)


def __poly_mult(ba1: int, ba2: int):
    if ba1 == 0 or ba2 == 0:
        return 0

    shift = []
    bs = [int(x) for x in list('{0:0b}'.format(ba2))]

    for i in range(len(bs)):
        if bs[i] == 1:
            shift.append(ba1 << (len(bs) - i - 1))

    if len(shift) > 1:
        res = poly_xor(shift[0], shift[1])
        for el in shift[2:]:
            res = poly_xor(res, el)
    else:
        res = shift[0]

    return res


def __poly_div_reminder(ba1: int, mod: int):
    if mod == 0:
        raise Exception("Division by zero")
    elif mod == 1:
        return ba1, 0
    else:
        res = 0
        while poly_max_deg(ba1) >= poly_max_deg(mod):
            diff = poly_max_deg(ba1) - poly_max_deg(mod)
            res = res ^ (1 << diff)
            ba1 = ba1 ^ (mod << diff)
        return res, ba1


def poly_div(ba1: int, mod: int) -> int:
    return __poly_div_reminder(ba1, mod)[0]


def poly_rem(ba1: int, mod: int) -> int:
    return __poly_div_reminder(ba1, mod)[1]


def poly_mod_mult(ba1: int, ba2: int, mod: int):
    return poly_rem(__poly_mult(ba1, ba2), mod)


def poly_mod_div(ba1: int, ba2: int, mod: int):
    return poly_rem(poly_div(ba1, ba2), mod)


def poly_mod_xor(ba1: int, ba2: int, mod: int):
    return poly_rem(poly_xor(ba1, ba2), mod)


def poly_deg(ba1: int, deg: int, mod=None):
    if deg == 0:
        return 1
    if deg < 0:
        raise Exception("Negative degree")

    temp1 = ba1
    for n in range(1, deg):
        if mod is None:
            temp1 = __poly_mult(temp1, ba1)
        else:
            temp1 = poly_mod_mult(temp1, ba1, mod)
    return temp1


def poly_inv(ba1: int, mod: int):
    if ba1 == 0:
        raise Exception("Null polynom")
    nmod1 = mod
    unit = 1
    zero = 0

    while nmod1 != 0:
        (q, r) = __poly_div_reminder(ba1, nmod1)
        s = poly_xor(unit, __poly_mult(q, zero))
        ba1 = nmod1
        nmod1 = r
        unit = zero
        zero = s

    return unit


parser = argparse.ArgumentParser(description='''\
                                                Arithmetic in fields of characteristic 2 [Vazavikou Mikita]
                                                launch example: python3 pollyholly.py --input input.txt --polynom polynom.txt
                                                                python3 --input 10001 + 10010 --polynom 1011
                                                                                10001 * 10010
                                                                                10001 / 10010
                                                                                10001 ^ 7
                                                                                10001 ^ -1''',
                                 formatter_class=argparse.RawTextHelpFormatter)

parser.add_argument("--input", required=True, help="Path to input file")
parser.add_argument("--polynom", required=True, help="Path to polynom file")
parser.add_argument("--format", default=0, type=int, choices=[0, 1], help=textwrap.dedent('''\
                                                                                   Input format
                                                                                   0 | File  
                                                                                   1 | String
                                                                                   The default is file'''))

args = parser.parse_args()

inp = args.input
poly = args.polynom
frm = args.format

f = None
temp = None
result = None

if frm == 0:
    inputfile = open(inp)
    polyfile = open(poly)
    temp = inputfile.read()
    f = polyfile.read()
    inputfile.close()
    polyfile.close()
else:
    temp = inp
    f = poly

temp = temp.split(' ')
if len(temp) != 3:
    raise Exception("Wrong input file/string\nCheck spaces between operator and polynomials\n Example: 10001 + 10001")

a = temp[0]
b = temp[2]
op = temp[1]

a = binary_to_int(a)
f = binary_to_int(f)

if op != '^':
    b = binary_to_int(b)
else:
    b = int(b)

if op == '+':
    result = poly_mod_xor(a, b, f)
elif op == '*':
    result = poly_mod_mult(a, b, f)
elif op == '/':
    result = poly_mod_div(a, b, f)
elif op == '^':
    if b == -1:
        result = poly_inv(a, f)
        print("Check(a(x) * a(x)^(-1)): ", poly_mod_mult(a, result, f))
    elif b >= 0:
        result = poly_deg(a, b, f)
    else:
        raise Exception("Wrong degree")
else:
    raise Exception("Wrong operator")


print("int: ", result)
print("binary: ", binary_to_str(result))
file = open("output.txt", 'w')
file.write(binary_to_str(result))
file.close()
print("Data written to output.txt")
