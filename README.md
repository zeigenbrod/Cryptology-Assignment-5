
# Cryptology-Assignment-5

**Zoe Eigenbrod**

**Language:** C++17, Python 3.13.7

## Files

- `main.cpp`: Multiplies two hexadecimal values.
- `bigint_test.cpp`: Contains unit tests and generated test cases for the main bigint functionality.
- `gen_test.py`: Generates test cases using Pythons built-in `int`.
- `bench_inputs.py`: Generates benchmark inputs.
- `benchmark.cpp`: Runs `bigint_multiply` and measures multiplication time.
- `benchmark.py`: Runs Python multiplication using the same inputs as `benchmark.cpp`.

## Build

```bash
g++ -std=c++17 -O2 bigint.cpp bigint_test.cpp -o test
g++ -std=c++17 -O2 bigint.cpp benchmark.cpp -o bench_bigint
g++ -std=c++17 -O2 bigint.cpp main.cpp -o bigint
```

## Tests

**1. Run unit tests:**

```bash
./test
```

**2. Run generated test cases:**

```bash
python3 gen_test.py 1000 > tests.txt
./test tests.txt
```

## Run Benchmarks

```bash
python3 bench_inputs.py > bench_inputs.txt
./bench_bigint bench_inputs.txt 1000
python3 benchmark.py bench_inputs.txt 1000
```
