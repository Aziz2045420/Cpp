#pragma once
#include <string>

// XOR Cipher: bitwise XOR of each byte with a repeating key.
// Fast and reversible — applying the same key twice returns the original data.
// Widely used as a building block in more complex ciphers.

namespace xor_cipher {

// Encrypts or decrypts data using the given key (XOR is its own inverse).
std::string process(const std::string &data, const std::string &key);

// Encodes binary data as a hex string for safe display.
std::string to_hex(const std::string &data);

// Decodes a hex string back to raw bytes.
std::string from_hex(const std::string &hex);

} // namespace xor_cipher
