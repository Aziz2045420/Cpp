#include "xor_cipher.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

namespace xor_cipher {

std::string process(const std::string &data, const std::string &key) {
    if (key.empty())
        throw std::invalid_argument("XOR key must not be empty.");
    std::string result;
    result.reserve(data.size());
    for (std::size_t i = 0; i < data.size(); ++i) {
        result += static_cast<char>(
            static_cast<unsigned char>(data[i]) ^
            static_cast<unsigned char>(key[i % key.size()])
        );
    }
    return result;
}

std::string to_hex(const std::string &data) {
    std::ostringstream oss;
    for (unsigned char c : data)
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    return oss.str();
}

std::string from_hex(const std::string &hex) {
    if (hex.size() % 2 != 0)
        throw std::invalid_argument("Hex string must have even length.");
    std::string result;
    result.reserve(hex.size() / 2);
    for (std::size_t i = 0; i < hex.size(); i += 2) {
        std::string byte_str = hex.substr(i, 2);
        for (char c : byte_str) {
            if (!std::isxdigit(static_cast<unsigned char>(c)))
                throw std::invalid_argument("Invalid hex character.");
        }
        result += static_cast<char>(std::stoi(byte_str, nullptr, 16));
    }
    return result;
}

} // namespace xor_cipher
