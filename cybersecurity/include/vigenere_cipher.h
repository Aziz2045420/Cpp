#pragma once
#include <string>

// Vigenere Cipher: polyalphabetic substitution cipher.
// Uses a keyword to shift each letter by a different amount, making it
// significantly harder to crack than a simple Caesar cipher.

namespace vigenere {

// Encrypts plaintext using the provided keyword (letters only, case-insensitive).
std::string encrypt(const std::string &plaintext, const std::string &key);

// Decrypts ciphertext using the same keyword.
std::string decrypt(const std::string &ciphertext, const std::string &key);

} // namespace vigenere
