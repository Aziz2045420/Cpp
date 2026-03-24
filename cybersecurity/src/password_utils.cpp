#include "password_utils.h"
#include <string>
#include <algorithm>
#include <stdexcept>
#include <random>
#include <cctype>
#include <sstream>

namespace password {

static const char LOWER[]   = "abcdefghijklmnopqrstuvwxyz";
static const char UPPER[]   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char DIGITS[]  = "0123456789";
static const char SPECIAL[] = "!@#$%^&*()-_=+[]{}|;:',.<>?/`~";

std::string generate(int length, bool use_upper, bool use_digits, bool use_special) {
    if (length < 4)
        throw std::invalid_argument("Password length must be at least 4.");

    std::string charset = LOWER;
    if (use_upper)   charset += UPPER;
    if (use_digits)  charset += DIGITS;
    if (use_special) charset += SPECIAL;

    // Use a random_device-seeded Mersenne Twister for good randomness.
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::size_t> dist(0, charset.size() - 1);

    std::string password;
    password.reserve(static_cast<std::size_t>(length));

    // Guarantee at least one character from each required class.
    auto pick_one = [&](const char *pool, std::size_t pool_size) {
        // pool_size == sizeof(pool_literal) which includes the null terminator.
        // Valid indices are [0, pool_size - 2] (last char before '\0').
        std::uniform_int_distribution<std::size_t> d(0, pool_size - 2);
        password += pool[d(rng)];
    };
    pick_one(LOWER, sizeof(LOWER));
    if (use_upper)   pick_one(UPPER,   sizeof(UPPER));
    if (use_digits)  pick_one(DIGITS,  sizeof(DIGITS));
    if (use_special) pick_one(SPECIAL, sizeof(SPECIAL));

    while (static_cast<int>(password.size()) < length)
        password += charset[dist(rng)];

    // Shuffle so the guaranteed characters aren't always at the start.
    std::shuffle(password.begin(), password.end(), rng);
    return password;
}

Strength check_strength(const std::string &pw) {
    int score = 0;

    if (pw.size() >= 8)  ++score;
    if (pw.size() >= 12) ++score;
    if (pw.size() >= 16) ++score;

    bool has_lower   = false, has_upper  = false;
    bool has_digit   = false, has_special = false;
    for (unsigned char c : pw) {
        if (std::islower(c))  has_lower   = true;
        else if (std::isupper(c)) has_upper   = true;
        else if (std::isdigit(c)) has_digit   = true;
        else                      has_special = true;
    }
    if (has_lower)   ++score;
    if (has_upper)   ++score;
    if (has_digit)   ++score;
    if (has_special) ++score;

    // Penalise common patterns.
    std::string lower_pw = pw;
    std::transform(lower_pw.begin(), lower_pw.end(), lower_pw.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    static const char *common[] = {
        "password", "123456", "qwerty", "admin", "letmein",
        "welcome", "monkey", "dragon", "master", "abc123"
    };
    for (const char *c : common) {
        if (lower_pw.find(c) != std::string::npos) {
            score -= 2;
            break;
        }
    }

    if (score <= 1) return Strength::VERY_WEAK;
    if (score <= 3) return Strength::WEAK;
    if (score <= 5) return Strength::MODERATE;
    if (score <= 7) return Strength::STRONG;
    return Strength::VERY_STRONG;
}

const char *strength_label(Strength s) {
    switch (s) {
        case Strength::VERY_WEAK:   return "Very Weak";
        case Strength::WEAK:        return "Weak";
        case Strength::MODERATE:    return "Moderate";
        case Strength::STRONG:      return "Strong";
        case Strength::VERY_STRONG: return "Very Strong";
    }
    return "Unknown";
}

std::string improvement_tips(const std::string &pw) {
    std::ostringstream tips;
    bool has_lower   = false, has_upper  = false;
    bool has_digit   = false, has_special = false;
    for (unsigned char c : pw) {
        if (std::islower(c))      has_lower   = true;
        else if (std::isupper(c)) has_upper   = true;
        else if (std::isdigit(c)) has_digit   = true;
        else                      has_special = true;
    }
    if (pw.size() < 12) tips << "  - Use at least 12 characters.\n";
    if (!has_lower)   tips << "  - Add lowercase letters.\n";
    if (!has_upper)   tips << "  - Add uppercase letters.\n";
    if (!has_digit)   tips << "  - Add digits (0-9).\n";
    if (!has_special) tips << "  - Add special characters (!@#$ etc.).\n";
    std::string result = tips.str();
    if (result.empty()) result = "  - Password looks good!\n";
    return result;
}

} // namespace password
