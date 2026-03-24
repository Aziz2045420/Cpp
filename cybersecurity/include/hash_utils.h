#pragma once
#include <string>
#include <cstdint>

// Hash utilities for file/data integrity verification.
// Uses a fast non-cryptographic hash (djb2) for demonstration,
// and a simple 32-bit FNV-1a hash for comparison.

namespace hash_utils {

// djb2 hash — classic, fast, good distribution.
uint64_t djb2(const std::string &data);

// FNV-1a 32-bit hash.
uint32_t fnv1a_32(const std::string &data);

// Reads a file and returns its djb2 hash as a hex string.
// Returns an empty string if the file cannot be opened.
std::string hash_file(const std::string &filepath);

// Verifies that a file's current hash matches an expected hex hash string.
bool verify_file(const std::string &filepath, const std::string &expected_hex);

// Converts a 64-bit integer to a lowercase hex string.
std::string to_hex64(uint64_t value);

} // namespace hash_utils
