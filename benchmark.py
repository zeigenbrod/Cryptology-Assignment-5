import sys
import time

path = sys.argv[1]
iterations = 200

if len(sys.argv) > 2:
    iterations = int(sys.argv[2])

sets = {}

with open(path) as file:
    for line in file:
        bits, a, b = line.split()

        if int(bits) not in sets:
            sets[int(bits)] = []

        sets[int(bits)].append((int(a, 16), int(b, 16)))

for bits in sorted(sets):
    pairs = sets[bits]

   
    for a, b in pairs:
        result = a * b

    # loop overhead
    start = time.perf_counter()

    for i in range(iterations):
        for a, b in pairs:
            result = a

    overhead = time.perf_counter() - start

    # track multiplication
    start = time.perf_counter()

    for i in range(iterations):
        for a, b in pairs:
            result = a * b

    elapsed = time.perf_counter() - start

    total = iterations * len(pairs)
    average = (elapsed - overhead) / total * 1000000000

    print(bits, average)
