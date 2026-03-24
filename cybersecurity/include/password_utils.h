#pragma once
#include <string>

// Password utilities: generator and strength checker.

namespace password {

// Generates a cryptographically random password of the given length.
// Optionally includes uppercase, digits, and special characters.
std::string generate(int length,
                     bool use_upper   = true,
                     bool use_digits  = true,
                     bool use_special = true);

// Strength levels returned by check_strength().
enum class Strength {
    VERY_WEAK,
    WEAK,
    MODERATE,
    STRONG,
    VERY_STRONG
};

// Evaluates password strength based on length, character diversity, and
// common-pattern detection.
Strength check_strength(const std::string &password);

// Returns a human-readable label for a Strength value.
const char *strength_label(Strength s);

// Returns suggestions for improving a weak password.
std::string improvement_tips(const std::string &password);

} // namespace password
