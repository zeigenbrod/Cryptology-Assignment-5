#include "bigint.h"

#include <exception>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./bigint <hex_number_1> <hex_number_2>\n";
        return 1;
    }

    try {
        std::vector<uint8_t> a = bigint_init(argv[1]);
        std::vector<uint8_t> b = bigint_init(argv[2]);

        std::vector<uint8_t> result = bigint_multiply(a, b);

        std::cout << bigint_to_string(result) << '\n';
    }
    catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}