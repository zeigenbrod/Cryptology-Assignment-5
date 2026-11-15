#ifndef BIGINT_H
#define BIGINT_H

#include <cstdint>
#include <string>
#include <vector>

std::vector<std::uint8_t> bigint_init(const std::string& hexValue);
std::string bigint_to_string(const std::vector<std::uint8_t>& number);
std::vector<std::uint8_t> bigint_multiply(const std::vector<std::uint8_t>& a,
const std::vector<std::uint8_t>& b);

#endif