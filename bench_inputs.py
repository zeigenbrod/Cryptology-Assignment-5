import random
import sys

random.seed(2026)

pairs_per_size = int(sys.argv[1]) if len(sys.argv) > 1 else 100

for bits in (256, 512, 1024):
    for _ in range(pairs_per_size):
        a = random.getrandbits(bits) | (1 << (bits - 1))
        b = random.getrandbits(bits) | (1 << (bits - 1))
        print(bits, format(a, "x"), format(b, "x"))