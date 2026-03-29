#include "base64.h"
#include <stdexcept>

namespace base64 {

static const char TABLE[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string encode(const std::string &data) {
    std::string result;
    int val = 0, valb = -6;
    for (unsigned char c : data) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            result += TABLE[(val >> valb) & 0x3F];
            valb -= 6;
        }
    }
    if (valb > -6)
        result += TABLE[((val << 8) >> (valb + 8)) & 0x3F];
    while (result.size() % 4)
        result += '=';
    return result;
}

std::string decode(const std::string &encoded) {
    // Build reverse lookup table (256 entries).
    static const int T[256] = {
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,
        52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-1,-1,-1,
        -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
        15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
        -1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
        41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
    };

    std::string result;
    int val = 0, valb = -8;
    for (unsigned char c : encoded) {
        if (c == '=') break;
        if (T[c] == -1)
            throw std::invalid_argument("Invalid Base64 character.");
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            result += static_cast<char>((val >> valb) & 0xFF);
            valb -= 8;
        }
    }
    return result;
}

bool is_valid(const std::string &encoded) {
    if (encoded.size() % 4 != 0) return false;
    static const std::string valid_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    for (char c : encoded) {
        if (valid_chars.find(c) == std::string::npos) return false;
    }
    // Padding '=' only allowed at the end, at most two.
    std::size_t pad = 0;
    for (auto it = encoded.rbegin(); it != encoded.rend() && *it == '='; ++it)
        ++pad;
    return pad <= 2;
}

} // namespace base64
