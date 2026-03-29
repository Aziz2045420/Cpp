#include "vigenere_cipher.h"
#include <cctype>
#include <stdexcept>

namespace vigenere {

// Sanitises the key: keeps only alpha characters, converts to lowercase.
static std::string sanitise_key(const std::string &key) {
    std::string clean;
    for (unsigned char c : key) {
        if (std::isalpha(c))
            clean += static_cast<char>(std::tolower(c));
    }
    if (clean.empty())
        throw std::invalid_argument("Vigenere key must contain at least one letter.");
    return clean;
}

std::string encrypt(const std::string &plaintext, const std::string &key) {
    std::string k = sanitise_key(key);
    std::string result;
    result.reserve(plaintext.size());
    std::size_t ki = 0;
    for (unsigned char c : plaintext) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            int shift = k[ki % k.size()] - 'a';
            result += static_cast<char>((c - base + shift) % 26 + base);
            ++ki;
        } else {
            result += static_cast<char>(c);
        }
    }
    return result;
}

std::string decrypt(const std::string &ciphertext, const std::string &key) {
    std::string k = sanitise_key(key);
    std::string result;
    result.reserve(ciphertext.size());
    std::size_t ki = 0;
    for (unsigned char c : ciphertext) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            int shift = k[ki % k.size()] - 'a';
            result += static_cast<char>((c - base - shift + 26) % 26 + base);
            ++ki;
        } else {
            result += static_cast<char>(c);
        }
    }
    return result;
}

} // namespace vigenere
