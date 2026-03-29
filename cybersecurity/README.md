# CyberSecurity Toolkit — C++ Educational Project

A menu-driven command-line application that implements seven classic
cybersecurity concepts in standard C++17 (no external libraries required).

---

## Features

| Module | Description |
|---|---|
| **Caesar Cipher** | Shift-based substitution cipher; supports encrypt, decrypt, and brute-force analysis |
| **Vigenere Cipher** | Polyalphabetic cipher using a keyword; much stronger than Caesar |
| **XOR Cipher** | Symmetric byte-level cipher; ciphertext displayed as hex for safe output |
| **Password Generator** | Cryptographically random passwords with configurable character classes |
| **Password Strength Checker** | Scores passwords on length, diversity, and common-pattern detection |
| **File Integrity Checker** | Hashes files with djb2 / FNV-1a; verifies integrity against a stored hash |
| **Base64 Encoder/Decoder** | Standard Base64 encode, decode, and validation |

---

## Project Structure

```
cybersecurity/
├── include/               # Header files (one per module)
│   ├── caesar_cipher.h
│   ├── vigenere_cipher.h
│   ├── xor_cipher.h
│   ├── password_utils.h
│   ├── hash_utils.h
│   └── base64.h
├── src/                   # Implementation files + main menu
│   ├── main.cpp
│   ├── caesar_cipher.cpp
│   ├── vigenere_cipher.cpp
│   ├── xor_cipher.cpp
│   ├── password_utils.cpp
│   ├── hash_utils.cpp
│   └── base64.cpp
├── tests/
│   └── test_all.cpp       # 33-assertion self-test suite
├── Makefile
└── README.md
```

---

## Build & Run

### Requirements
- GCC 7+ or Clang 6+ (any compiler with C++17 support)
- GNU Make

### Build the interactive toolkit
```bash
cd cybersecurity
make
./cybersec_toolkit
```

### Run the unit tests
```bash
make test
```

### Clean build artifacts
```bash
make clean
```

### Build manually (without Make)
```bash
g++ -std=c++17 -Iinclude src/*.cpp -o cybersec_toolkit
# Exclude main.cpp for the test binary:
g++ -std=c++17 -Iinclude \
    src/caesar_cipher.cpp src/vigenere_cipher.cpp src/xor_cipher.cpp \
    src/password_utils.cpp src/hash_utils.cpp src/base64.cpp \
    tests/test_all.cpp -o build/test_all
```

---

## Module Details

### 1. Caesar Cipher
The oldest known cipher — shift each letter by a fixed amount.
- Encrypt / decrypt with any shift 0–25.
- Brute-force mode prints all 26 candidate plaintexts for analysis.

### 2. Vigenere Cipher
Uses a repeating keyword to apply a different shift to each letter,
making frequency analysis much harder.
- Key is case-insensitive; non-letter characters in plaintext pass through unchanged.

### 3. XOR Cipher
XOR each byte of the plaintext with a repeating key.
- Applying the same key twice returns the original plaintext (symmetric).
- Ciphertext is hex-encoded for safe terminal display; hex input is decoded before decryption.

### 4. Password Generator
Uses `std::random_device` + `std::mt19937` to generate cryptographically
seeded random passwords.
- Configurable length (minimum 4).
- Guarantees at least one character from each enabled character class.
- Characters are shuffled after selection so guaranteed characters don't cluster at the start.

### 5. Password Strength Checker
Scores passwords on:
- **Length** (8 / 12 / 16+ characters each add a point).
- **Character class diversity** (lower, upper, digit, special).
- **Common pattern detection** — passwords containing strings like `password`, `123456`, `qwerty`, etc. lose 2 points.

Strength levels: `Very Weak` / `Weak` / `Moderate` / `Strong` / `Very Strong`.

### 6. File Integrity Checker
- **djb2** (64-bit) and **FNV-1a** (32-bit) hash algorithms.
- Hash a file path and receive its hex digest.
- Verify a file against a previously recorded hash to detect tampering.

### 7. Base64 Encoder / Decoder
- Encodes arbitrary binary data to printable ASCII.
- Decodes Base64 strings back to raw bytes.
- Validates whether a string is well-formed Base64.

---

## Security Notes

This project is **educational**. The ciphers implemented here (Caesar, Vigenere, XOR)
are **not** suitable for production security:
- Caesar and Vigenere are trivially broken by frequency analysis.
- XOR with a short, reused key is vulnerable to known-plaintext attacks.
- djb2 / FNV-1a are non-cryptographic hashes; use SHA-256 or SHA-3 for real integrity checks.
- The password generator uses `std::random_device` for seeding, which is suitable for
  educational use but libraries like libsodium are recommended for production.
