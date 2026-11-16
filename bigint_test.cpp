#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

#include "bigint.h"

using std::string, std::vector, std::cout, std::cerr;

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
    check(bigint_to_string(bigint_init("0")) == "0", "zero value");
    check(bigint_to_string(bigint_init("00000")) == "0", "extra zeros");
    check(bigint_to_string(bigint_init("D4E5F6")) == "d4e5f6", "uppercase hex");
    check(bigint_to_string(bigint_init("2468a")) == "2468a", "odd digits");

    check(bigint_to_string(bigint_init("c3a7b9d2e4f618")) ==
          "c3a7b9d2e4f618", "large value");

    check(bigint_to_string(bigint_init(string(512, 'd'))) ==
          string(512, 'd'), "maximum size");

    try {
        bigint_init("");
        check(false, "empty string");
    }
    catch (...) {
        check(true, "empty string");
    }

    try {
        bigint_init("gh!");
        check(false, "non-hex characters");
    }
    catch (...) {
        check(true, "non-hex characters");
    }

    try {
        bigint_init("2" + string(512, '0'));
        check(false, "oversized input");
    }
    catch (...) {
        check(true, "oversized input");
    }
}

void test_multiply() {
    check(bigint_to_string(bigint_multiply(bigint_init("4"), bigint_init("5"))) == "14",
          "4 * 5");

    check(bigint_to_string(bigint_multiply(bigint_init("0"), bigint_init("def"))) == "0",
          "multiplication by zero");

    check(bigint_to_string(bigint_multiply(bigint_init("1"), bigint_init("def"))) == "def",
          "multiplication by one");

    check(bigint_to_string(bigint_multiply(bigint_init("ee"), bigint_init("ee"))) == "dd44",
          "ee * ee");

    check(bigint_to_string(bigint_multiply(bigint_init("120"), bigint_init("120"))) == "14400",
          "120 * 120");
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