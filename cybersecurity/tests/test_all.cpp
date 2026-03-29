/*
 * Standalone self-test for the CyberSecurity Toolkit.
 * Compile: g++ -std=c++17 -Iinclude src/caesar_cipher.cpp src/vigenere_cipher.cpp
 *              src/xor_cipher.cpp src/password_utils.cpp src/hash_utils.cpp
 *              src/base64.cpp tests/test_all.cpp -o build/test_all
 */

#include <iostream>
#include <cassert>
#include <string>
#include <string_view>

#include "caesar_cipher.h"
#include "vigenere_cipher.h"
#include "xor_cipher.h"
#include "password_utils.h"
#include "hash_utils.h"
#include "base64.h"

static int passed = 0, failed = 0;

#define CHECK(cond, name) \
    do { \
        if (cond) { std::cout << "  [PASS] " << name << "\n"; ++passed; } \
        else      { std::cout << "  [FAIL] " << name << "\n"; ++failed; } \
    } while(0)

// ─── Caesar Cipher ───────────────────────────────────────────────────────────
static void test_caesar() {
    std::cout << "\nCaesar Cipher:\n";
    CHECK(caesar::encrypt("Hello World", 3) == "Khoor Zruog",   "encrypt shift-3");
    CHECK(caesar::decrypt("Khoor Zruog", 3) == "Hello World",   "decrypt shift-3");
    CHECK(caesar::encrypt("Hello World", 0) == "Hello World",   "encrypt shift-0 (identity)");
    CHECK(caesar::encrypt("xyz", 3)        == "abc",            "wrap-around lowercase");
    CHECK(caesar::encrypt("XYZ", 3)        == "ABC",            "wrap-around uppercase");
    CHECK(caesar::encrypt("Hello, World!", 13) == "Uryyb, Jbeyq!", "ROT13 with punctuation");
    // decrypt should be inverse of encrypt
    std::string msg = "The quick brown fox.";
    CHECK(caesar::decrypt(caesar::encrypt(msg, 7), 7) == msg, "round-trip shift-7");
}

// ─── Vigenere Cipher ─────────────────────────────────────────────────────────
static void test_vigenere() {
    std::cout << "\nVigenere Cipher:\n";
    // Classic example: "ATTACKATDAWN" with key "LEMON"
    CHECK(vigenere::encrypt("ATTACKATDAWN", "LEMON") == "LXFOPVEFRNHR", "classic encrypt");
    CHECK(vigenere::decrypt("LXFOPVEFRNHR", "LEMON") == "ATTACKATDAWN", "classic decrypt");
    // Non-alpha characters should pass through unchanged.
    CHECK(vigenere::encrypt("Hello, World!", "key") != "Hello, World!", "encrypts alpha chars");
    std::string msg = "Meet me at midnight!";
    CHECK(vigenere::decrypt(vigenere::encrypt(msg, "secret"), "secret") == msg, "round-trip");
}

// ─── XOR Cipher ──────────────────────────────────────────────────────────────
static void test_xor() {
    std::cout << "\nXOR Cipher:\n";
    std::string key  = "mysecretkey";
    std::string plain = "Hello, World!";
    std::string enc   = xor_cipher::process(plain, key);
    CHECK(enc != plain,                             "ciphertext differs from plaintext");
    CHECK(xor_cipher::process(enc, key) == plain,  "XOR self-inverse (decrypt)");
    // Hex encoding round-trip
    std::string hex = xor_cipher::to_hex(enc);
    CHECK(xor_cipher::from_hex(hex) == enc,        "hex round-trip");
}

// ─── Password Utils ──────────────────────────────────────────────────────────
static void test_password() {
    std::cout << "\nPassword Utils:\n";
    // Generator: length, character classes
    std::string pw = password::generate(16, true, true, true);
    CHECK(pw.size() == 16, "generate length=16");

    // Strength checker
    using S = password::Strength;
    CHECK(password::check_strength("abc")      == S::VERY_WEAK,  "very weak password");
    CHECK(password::check_strength("password") == S::VERY_WEAK,  "common password is weak");
    // "Xyz!9pQ@7w": has upper, lower, digit, special, 10 chars, no common pattern
    CHECK(password::check_strength("Xyz!9pQ@7w") >= S::MODERATE,  "moderate+ password");
    auto strong_pw = password::generate(20, true, true, true);
    CHECK(password::check_strength(strong_pw) >= S::STRONG,      "generated pwd is strong");

    // Labels are non-empty
    CHECK(std::string(password::strength_label(S::VERY_WEAK)).size()   > 0, "label VERY_WEAK");
    CHECK(std::string(password::strength_label(S::VERY_STRONG)).size() > 0, "label VERY_STRONG");
}

// ─── Hash Utils ───────────────────────────────────────────────────────────────
static void test_hash() {
    std::cout << "\nHash Utils:\n";
    // djb2 should be deterministic
    CHECK(hash_utils::djb2("hello") == hash_utils::djb2("hello"),   "djb2 deterministic");
    CHECK(hash_utils::djb2("hello") != hash_utils::djb2("world"),   "djb2 differs for different input");
    // FNV-1a
    CHECK(hash_utils::fnv1a_32("hello") == hash_utils::fnv1a_32("hello"), "fnv1a deterministic");
    // to_hex64
    std::string h = hash_utils::to_hex64(0xDEADBEEFCAFEBABEULL);
    CHECK(h == "deadbeefcafebabe", "to_hex64");
    // Non-existent file returns empty string
    CHECK(hash_utils::hash_file("/tmp/no_such_file_xyz.txt").empty(), "hash_file missing returns empty");
}

// ─── Base64 ───────────────────────────────────────────────────────────────────
static void test_base64() {
    std::cout << "\nBase64:\n";
    CHECK(base64::encode("Hello") == "SGVsbG8=",    "encode 'Hello'");
    CHECK(base64::decode("SGVsbG8=") == "Hello",    "decode 'SGVsbG8='");
    CHECK(base64::encode("Man")   == "TWFu",        "encode 'Man' (no padding)");
    CHECK(base64::decode("TWFu") == "Man",          "decode 'TWFu'");
    // Round-trip with arbitrary string
    std::string data = "CyberSecurity test data 1234!@#$";
    CHECK(base64::decode(base64::encode(data)) == data, "round-trip arbitrary data");
    // Validation
    CHECK(base64::is_valid("SGVsbG8="),  "is_valid true");
    CHECK(!base64::is_valid("SGVsbG8"),  "is_valid false (bad length)");
}

int main() {
    std::cout << "========================================\n";
    std::cout << "  CyberSecurity Toolkit -- Self Tests\n";
    std::cout << "========================================\n";

    test_caesar();
    test_vigenere();
    test_xor();
    test_password();
    test_hash();
    test_base64();

    std::cout << "\n========================================\n";
    std::cout << "  Results: " << passed << " passed, " << failed << " failed\n";
    std::cout << "========================================\n";
    return (failed == 0) ? 0 : 1;
}
