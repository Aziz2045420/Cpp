#pragma once
#include <string>

// Caesar Cipher: classic shift cipher used in classical cryptography.
// Each letter in the plaintext is shifted by 'shift' positions in the alphabet.

namespace caesar {

// Encrypts plaintext using a shift value (0-25).
std::string encrypt(const std::string &plaintext, int shift);

// Decrypts ciphertext using the same shift value used during encryption.
std::string decrypt(const std::string &ciphertext, int shift);

// Brute-force all 26 possible shifts and print them (for analysis).
void brute_force(const std::string &ciphertext);

} // namespace caesar
