
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

#include "bigint.h"

using std::string;
using std::vector;
using std::cout;
using std::cerr;

int failures = 0;

void check(bool passed, string message) {
    if (passed) {
        cout << "PASS: " << message << "\n";
    }
    else {
        cout << "FAIL: " << message << "\n";
        failures++;
    }
}

void test_init() {
    check(bigint_to_string(bigint_init("0")) == "0", "zero");
    check(bigint_to_string(bigint_init("0000")) == "0", "leading zeros");
    check(bigint_to_string(bigint_init("ABCDEF")) == "abcdef", "uppercase");
    check(bigint_to_string(bigint_init("123")) == "123", "odd length");

    check(bigint_to_string(bigint_init("ab54a98ceb1f0ad2")) ==
          "ab54a98ceb1f0ad2", "large number");

    check(bigint_to_string(bigint_init(string(512, 'f'))) ==
          string(512, 'f'), "2048 bits");

    try {
        bigint_init("");
        check(false, "empty input");
    }
    catch (...) {
        check(true, "empty input");
    }

    try {
        bigint_init("xyz");
        check(false, "invalid characters");
    }
    catch (...) {
        check(true, "invalid characters");
    }

    try {
        bigint_init("1" + string(512, '0'));
        check(false, "number too large");
    }
    catch (...) {
        check(true, "number too large");
    }
}

void test_multiply() {
    check(bigint_to_string(bigint_multiply(bigint_init("2"), bigint_init("3"))) == "6",
          "2 * 3");

    check(bigint_to_string(bigint_multiply(bigint_init("0"), bigint_init("abc"))) == "0",
          "zero multiplication");

    check(bigint_to_string(bigint_multiply(bigint_init("1"), bigint_init("abc"))) == "abc",
          "multiply by one");

    check(bigint_to_string(bigint_multiply(bigint_init("ff"), bigint_init("ff"))) == "fe01",
          "ff * ff");

    check(bigint_to_string(bigint_multiply(bigint_init("100"), bigint_init("100"))) == "10000",
          "100 * 100");
}

void test_cases(string filename) {
    std::ifstream file(filename);

    if (!file) {
        cerr << "Could not open test file\n";
        failures++;
        return;
    }

    string a, b, expected;

    while (file >> a >> b >> expected) {
        try {
            string result = bigint_to_string(
                bigint_multiply(bigint_init(a), bigint_init(b))
            );

            check(result == expected, "multiplication test");
        }
        catch (...) {
            check(expected == "ERR", "overflow test");
        }
    }
}

int main(int argc, char* argv[]) {
    test_init();
    test_multiply();

    if (argc > 1) {
        test_cases(argv[1]);
    }

    cout << "\nFailures: " << failures << "\n";

    return failures == 0 ? 0 : 1;
}
