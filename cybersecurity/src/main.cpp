/*
 * CyberSecurity Toolkit — C++ Educational Project
 *
 * Modules:
 *   1. Caesar Cipher        — classic shift cipher
 *   2. Vigenere Cipher      — polyalphabetic substitution cipher
 *   3. XOR Cipher           — symmetric bitwise cipher
 *   4. Password Generator   — strong random password creation
 *   5. Password Strength Checker
 *   6. File Integrity Checker — hash-based verification
 *   7. Base64 Encoder/Decoder
 *
 * Build:  make  (or: g++ -std=c++17 -Iinclude src/main.cpp ... -o cybersec_toolkit)
 */

#include <iostream>
#include <string>
#include <limits>

#include "caesar_cipher.h"
#include "vigenere_cipher.h"
#include "xor_cipher.h"
#include "password_utils.h"
#include "hash_utils.h"
#include "base64.h"
#include <iomanip>
#include <sstream>

// ─── Helpers ────────────────────────────────────────────────────────────────

static void print_banner() {
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════════════════════════╗\n";
    std::cout << "  ║          C Y B E R S E C U R I T Y   T O O L K I T  ║\n";
    std::cout << "  ║               Educational C++ Project                ║\n";
    std::cout << "  ╚══════════════════════════════════════════════════════╝\n";
    std::cout << "\n";
}

static void print_menu() {
    std::cout << "  ┌─────────────────────────────────────────────────┐\n";
    std::cout << "  │  Main Menu                                      │\n";
    std::cout << "  ├─────────────────────────────────────────────────┤\n";
    std::cout << "  │  1. Caesar Cipher                               │\n";
    std::cout << "  │  2. Vigenere Cipher                             │\n";
    std::cout << "  │  3. XOR Cipher                                  │\n";
    std::cout << "  │  4. Password Generator                          │\n";
    std::cout << "  │  5. Password Strength Checker                   │\n";
    std::cout << "  │  6. File Integrity Checker                      │\n";
    std::cout << "  │  7. Base64 Encoder / Decoder                   │\n";
    std::cout << "  │  0. Exit                                        │\n";
    std::cout << "  └─────────────────────────────────────────────────┘\n";
    std::cout << "  Choice: ";
}

static void separator() {
    std::cout << "\n  " << std::string(52, '-') << "\n";
}

// Read a full line, handling trailing newline left by previous reads.
static std::string read_line(const std::string &prompt) {
    std::cout << "  " << prompt;
    std::string line;
    std::getline(std::cin >> std::ws, line);
    return line;
}

static int read_int(const std::string &prompt) {
    int val = 0;
    while (true) {
        std::cout << "  " << prompt;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Invalid input. Please enter an integer.\n";
    }
}

// ─── Module handlers ────────────────────────────────────────────────────────

static void menu_caesar() {
    separator();
    std::cout << "  [ Caesar Cipher ]\n\n";
    std::cout << "  1. Encrypt\n  2. Decrypt\n  3. Brute-force\n";
    int choice = read_int("Choice: ");

    std::string text = read_line("Enter text: ");
    if (choice == 3) {
        caesar::brute_force(text);
        return;
    }
    int shift = read_int("Shift (0-25): ");
    if (choice == 1)
        std::cout << "\n  Result: " << caesar::encrypt(text, shift) << "\n";
    else
        std::cout << "\n  Result: " << caesar::decrypt(text, shift) << "\n";
}

static void menu_vigenere() {
    separator();
    std::cout << "  [ Vigenere Cipher ]\n\n";
    std::cout << "  1. Encrypt\n  2. Decrypt\n";
    int choice = read_int("Choice: ");

    std::string text = read_line("Enter text: ");
    std::string key  = read_line("Enter key (letters only): ");
    try {
        if (choice == 1)
            std::cout << "\n  Result: " << vigenere::encrypt(text, key) << "\n";
        else
            std::cout << "\n  Result: " << vigenere::decrypt(text, key) << "\n";
    } catch (const std::exception &e) {
        std::cout << "\n  Error: " << e.what() << "\n";
    }
}

static void menu_xor() {
    separator();
    std::cout << "  [ XOR Cipher ]\n\n";
    std::cout << "  1. Encrypt (text → hex output)\n"
                 "  2. Decrypt (hex input → text)\n";
    int choice = read_int("Choice: ");
    std::string key = read_line("Enter key: ");

    try {
        if (choice == 1) {
            std::string text = read_line("Enter plaintext: ");
            std::string enc  = xor_cipher::process(text, key);
            std::cout << "\n  Encrypted (hex): " << xor_cipher::to_hex(enc) << "\n";
        } else {
            std::string hex  = read_line("Enter ciphertext (hex): ");
            std::string raw  = xor_cipher::from_hex(hex);
            std::string dec  = xor_cipher::process(raw, key);
            std::cout << "\n  Decrypted: " << dec << "\n";
        }
    } catch (const std::exception &e) {
        std::cout << "\n  Error: " << e.what() << "\n";
    }
}

static void menu_password_gen() {
    separator();
    std::cout << "  [ Password Generator ]\n\n";
    int len = read_int("Password length (min 4): ");

    auto yes_no = [](const std::string &q) -> bool {
        std::cout << "  " << q << " (y/n): ";
        char c;
        std::cin >> c;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return c == 'y' || c == 'Y';
    };
    bool up  = yes_no("Include uppercase?");
    bool dig = yes_no("Include digits?");
    bool sp  = yes_no("Include special chars?");

    try {
        for (int i = 0; i < 5; ++i)
            std::cout << "  Password " << (i+1) << ": " << password::generate(len, up, dig, sp) << "\n";
    } catch (const std::exception &e) {
        std::cout << "\n  Error: " << e.what() << "\n";
    }
}

static void menu_password_check() {
    separator();
    std::cout << "  [ Password Strength Checker ]\n\n";
    std::string pw = read_line("Enter password to check: ");
    auto s = password::check_strength(pw);
    std::cout << "\n  Strength: " << password::strength_label(s) << "\n";
    std::cout << "\n  Tips:\n" << password::improvement_tips(pw) << "\n";
}

static void menu_hash() {
    separator();
    std::cout << "  [ File Integrity Checker ]\n\n";
    std::cout << "  1. Hash a file\n  2. Verify a file against a known hash\n"
                 "  3. Hash a text string\n";
    int choice = read_int("Choice: ");

    if (choice == 1) {
        std::string path = read_line("File path: ");
        std::string h = hash_utils::hash_file(path);
        if (h.empty())
            std::cout << "\n  Error: Could not open file.\n";
        else
            std::cout << "\n  djb2 hash: " << h << "\n";
    } else if (choice == 2) {
        std::string path = read_line("File path: ");
        std::string expected = read_line("Expected hash (hex): ");
        bool ok = hash_utils::verify_file(path, expected);
        std::cout << "\n  " << (ok ? "✔ MATCH — file is intact." : "✘ MISMATCH — file may be tampered!") << "\n";
    } else {
        std::string text = read_line("Enter text: ");
        uint64_t h  = hash_utils::djb2(text);
        uint32_t h2 = hash_utils::fnv1a_32(text);
        std::cout << "\n  djb2  : " << hash_utils::to_hex64(h) << "\n";
        std::ostringstream oss;
        oss << std::hex << std::setw(8) << std::setfill('0') << h2;
        std::cout << "  FNV1a : " << oss.str() << "\n";
    }
}

static void menu_base64() {
    separator();
    std::cout << "  [ Base64 Encoder / Decoder ]\n\n";
    std::cout << "  1. Encode\n  2. Decode\n  3. Validate\n";
    int choice = read_int("Choice: ");
    std::string text = read_line("Enter text: ");

    try {
        if (choice == 1)
            std::cout << "\n  Encoded: " << base64::encode(text) << "\n";
        else if (choice == 2)
            std::cout << "\n  Decoded: " << base64::decode(text) << "\n";
        else
            std::cout << "\n  Valid Base64: " << (base64::is_valid(text) ? "Yes" : "No") << "\n";
    } catch (const std::exception &e) {
        std::cout << "\n  Error: " << e.what() << "\n";
    }
}

// ─── Entry point ────────────────────────────────────────────────────────────

int main() {
    print_banner();

    int choice = -1;
    while (choice != 0) {
        print_menu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: menu_caesar();         break;
            case 2: menu_vigenere();       break;
            case 3: menu_xor();            break;
            case 4: menu_password_gen();   break;
            case 5: menu_password_check(); break;
            case 6: menu_hash();           break;
            case 7: menu_base64();         break;
            case 0: break;
            default:
                std::cout << "\n  Unknown option. Please choose 0-7.\n";
        }
        if (choice != 0)
            std::cout << "\n  Press Enter to return to menu...";
        // Wait for any key.
        if (choice != 0)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "\n  Goodbye!\n\n";
    return 0;
}
