import sys
import time

path = sys.argv[1]
repeats = 200

if len(sys.argv) > 2:
    repeats = int(sys.argv[2])

sets = {}

with open(path) as file:
    for line in file:
        bits, a, b = line.split()

        if int(bits) not in sets:
            sets[int(bits)] = []

        sets[int(bits)].append((int(a, 16), int(b, 16)))

for bits in sorted(sets):
    pairs = sets[bits]

    # Warm-up
    for a, b in pairs:
        result = a * b

    # Measure loop overhead
    start = time.perf_counter()

    for repeat in range(repeats):
        for a, b in pairs:
            result = a

    overhead = time.perf_counter() - start

    # Measure multiplication
    start = time.perf_counter()

    for repeat in range(repeats):
        for a, b in pairs:
            result = a * b

    elapsed = time.perf_counter() - start

    total = repeats * len(pairs)
    average = (elapsed - overhead) / total * 1000000000

    print(bits, average)

print("Last product bits:", result.bit_length(), file=sys.stderr)