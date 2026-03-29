#include "hash_utils.h"
#include <fstream>
#include <sstream>
#include <iomanip>

namespace hash_utils {

uint64_t djb2(const std::string &data) {
    uint64_t hash = 5381ULL;
    for (unsigned char c : data)
        hash = ((hash << 5) + hash) + static_cast<uint64_t>(c); // hash * 33 + c
    return hash;
}

uint32_t fnv1a_32(const std::string &data) {
    uint32_t hash  = 2166136261UL;
    uint32_t prime = 16777619UL;
    for (unsigned char c : data) {
        hash ^= static_cast<uint32_t>(c);
        hash *= prime;
    }
    return hash;
}

std::string to_hex64(uint64_t value) {
    std::ostringstream oss;
    oss << std::hex << std::setw(16) << std::setfill('0') << value;
    return oss.str();
}

std::string hash_file(const std::string &filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open())
        return "";
    std::ostringstream buf;
    buf << file.rdbuf();
    return to_hex64(djb2(buf.str()));
}

bool verify_file(const std::string &filepath, const std::string &expected_hex) {
    return hash_file(filepath) == expected_hex;
}

} // namespace hash_utils
