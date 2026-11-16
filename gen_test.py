import random
import sys

MAX_BITS = 2048
random.seed(12222)


def expected(a, b):
    result = a * b

    if result.bit_length() > MAX_BITS:
        return "ERR"

    return format(result, "x")


def make_hex(number):
    value = format(number, "x")

    if random.randint(0, 1) == 1:
        value = value.upper()

    zeros = random.randint(0, 5)
    value = "0" * zeros + value

    return value


def main():
    tests = []

    numbers = [
        0, 1, 2, 255, 256, 65535, 65536,
        (1 << 64) - 1, 1 << 64,
        (1 << 1024) - 1, 1 << 1024,
        (1 << 1024) + 1, (1 << 2048) - 1,
        1 << 2047
    ]

    for a in numbers:
        for b in numbers:
            tests.append((a, b))

    #random nums test
    count = int(sys.argv[1]) 

    for i in range(count):
        bits_a = random.randint(1, MAX_BITS)
        bits_b = random.randint(1, MAX_BITS)

        a = random.getrandbits(bits_a)
        b = random.getrandbits(bits_b)

        tests.append((a, b))

   
    for i in range(count):
        bits_a = random.randint(1, MAX_BITS)
        bits_b = random.randint(1, MAX_BITS - bits_a + 1)

        a = random.getrandbits(bits_a)
        b = random.getrandbits(bits_b)

        tests.append((a, b))


    for bits in [256, 512, 1024]:
        for i in range(100):
            a = random.getrandbits(bits) | (1 << (bits - 1))
            b = random.getrandbits(bits) | (1 << (bits - 1))

            tests.append((a, b))

    for a, b in tests:
        print(make_hex(a), make_hex(b), expected(a, b))


if __name__ == "__main__":
    main()
