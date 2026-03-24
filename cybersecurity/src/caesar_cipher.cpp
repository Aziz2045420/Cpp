#include "caesar_cipher.h"
#include <cctype>
#include <iostream>

namespace caesar {

std::string encrypt(const std::string &plaintext, int shift) {
    // Normalise shift to [0, 25]
    shift = ((shift % 26) + 26) % 26;
    std::string result;
    result.reserve(plaintext.size());
    for (unsigned char c : plaintext) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            result += static_cast<char>((c - base + shift) % 26 + base);
        } else {
            result += static_cast<char>(c);
        }
    }
    return result;
}

std::string decrypt(const std::string &ciphertext, int shift) {
    return encrypt(ciphertext, 26 - ((shift % 26 + 26) % 26));
}

void brute_force(const std::string &ciphertext) {
    std::cout << "\n  Brute-force Caesar cipher analysis:\n";
    std::cout << "  " << std::string(50, '-') << "\n";
    for (int s = 0; s < 26; ++s) {
        std::cout << "  Shift " << s << ": " << decrypt(ciphertext, s) << "\n";
    }
}

} // namespace caesar
