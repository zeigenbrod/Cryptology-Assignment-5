
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdint>

using std::string, std::runtime_error, std::vector, std::uint8_t;

int hex(char c) {
    if (c >= '0' && c <= '9') { return c - '0'; }
    if (c >= 'a' && c <= 'f') { return c - 'a' + 10; }
    if (c >= 'A' && c <= 'F') { return c - 'A' + 10; }

    return -1;
}

vector<uint8_t> bigint_init(const string& hexValue) {
    if (hexValue.empty()) {
        throw runtime_error("Empty string");
    }

    vector<uint8_t> number;

    for (int i = 0; i < hexValue.length(); i++) {
        if (hex(hexValue[i]) == -1) {
            throw runtime_error("Invalid character");
        }
    }

    // remove leading zeros
    int i = 0;
    while (i < hexValue.length() - 1 && hexValue[i] == '0') {
        i++;
    }

    if (hexValue.length() - i > 512) {
        throw runtime_error("Value too large");
    }

    // convert hex into bytes
    for (int j = hexValue.length() - 1; j >= i; j -= 2) {
        int low = hex(hexValue[j]);
        int high = 0;

        if (j - 1 >= i) {
            high = hex(hexValue[j - 1]);
        }

        int byte = high * 16 + low;
        number.push_back(byte);
    }

    return number;
}

string bigint_to_string(const vector<uint8_t>& number) {
    string result = "";
    string digits = "0123456789abcdef";

    if (number.empty()) {
        return "0";
    }

    for (int i = number.size() - 1; i >= 0; i--) {
        int byte = number[i];
        int high = byte / 16;
        int low = byte % 16;

        if (i == number.size() - 1 && high == 0) {
            result += digits[low];
        }
        else {
            result += digits[high];
            result += digits[low];
        }
    }

    return result;
}

// multiply 
vector<uint8_t> bigint_multiply(const vector<uint8_t>& a, const vector<uint8_t>& b) {
    vector<uint8_t> result;

    for (int i = 0; i < a.size() + b.size(); i++) {
        result.push_back(0);
    }

    for (int i = 0; i < a.size(); i++) {
        int remainder = 0;

        for (int j = 0; j < b.size(); j++) {
            int current = result[i + j] + a[i] * b[j] + remainder;

            result[i + j] = current % 256;
            remainder = current / 256;
        }

        result[i + b.size()] = remainder;
    }

    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }

    if (result.size() > 256) {
        throw runtime_error("Value too large.");
    }

    return result;
}
