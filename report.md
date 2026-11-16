# Assignment 5: Big Integers
## Zoe Eigenbrod

## 1. Big Integer Justification

I decided to implement my big integer using C++'s `std::vector<uint8_t>`. because it is dynamic and allows you to store individual bytes. 'uint8_t' holds 1 byte, and using a vector allows for adjustments based on the integer size. This is good for multiplication because after the result is calculated, it may need additional space. 

`bigint_init` and `bigint_to_string` are implemented as required, and the main big integer program can be accessed by running `main.cpp`, though the functionality is in `bigint.cpp`. My program throws errors for empty strings, invalid hex values/hex values not being used, oversized strings (over 256 bytes). 

## 2. Big Integer Multiplication

I used basic multiplication (base 256) for my hex multiplication functionality. Bytes from number `a` are multiplied by every byte of number `b`, and then is added to result byte and remainder. The result byte is divided by 256, and the remainder carries over. The program checks for extra zeroes and validates that the result is less than 256 bytes. 

## 3. Testing and Performance Results

**Testing** 
For my test files, I made a seeded python test script `gen_test.py` that generates test cases and uses the built in integers to calculate the expected result. `bigint_test.cpp` uses the same values to compare the output. It also contains unit tests, including tests for multiplication, as well as testing edge cases. The tests are tracked and any failures are counted. 


**Test results** 

First, I tested my big int implementation.

`./test`

My implementation passed each test, as shown  in the output below.

```
PASS: zero value
PASS: extra zeros
PASS: uppercase hex
PASS: odd digits
PASS: large value
PASS: maximum size
PASS: empty string
PASS: non-hex characters
PASS: oversized input
PASS: 4 * 5
PASS: multiplication by zero
PASS: multiplication by one
PASS: ee * ee
PASS: 120 * 120

Failures: 0
```

I then ran the test generator, and did 1000 iterations.

`python3 gen_test.py 1000 > test_cases.txt`

After the generation, I ran the test program against the generated test cases. Since the test_cases.txt file is provided as an arguement, the generated multiplcation tests are tested.

`./test test_cases.txt`

`Failures: 0` was the output, so all the tests passed.

**Performance** 

For benchmarking, I created `benchmark.cpp`, `benchmark.py`, as well as a file to generate values to use `bench_inputs.py`. It generates random pairs of inputs at 256, 512, and 1024 bits. I will compare my multiplication implementation to the built in Python multiplication, and using the same generated values will ensure that I can fairly compare.

**Performance results** 

For the benchmarking, I ran 1000 iterations.

- **256 bits:** C++ = 2247.96 ns | Python = 183.33 ns
- **512 bits:** C++ = 8378.69 ns | Python = 1183.94 ns
- **1024 bits:** C++ = 42165.20 ns | Python = 2753.54 ns

The built-in Python implementation is x12.26 times faster for 256 bits, x7.08 times faster for 512 bits, and x15.31 times faster for 1024 bits. Python was faster because my implementation uses a basic schoolbook multiplication implementation. My algorithm has a time complexity of O(n^2). Python uses Karatsuba multiplicaton, which is generally faster than schoolbook multiplication. The Python Karatsuba multiplcation runs at O(n^1.585).
