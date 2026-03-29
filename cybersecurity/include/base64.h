#pragma once
#include <string>

// Base64 encoding/decoding — fundamental in security contexts for encoding
// binary data (certificates, tokens, etc.) into printable ASCII text.

namespace base64 {

// Encodes arbitrary binary data to a Base64 string.
std::string encode(const std::string &data);

// Decodes a Base64 string back to the original binary data.
// Throws std::invalid_argument if the input is not valid Base64.
std::string decode(const std::string &encoded);

// Returns true if the given string is a valid Base64-encoded value.
bool is_valid(const std::string &encoded);

} // namespace base64
