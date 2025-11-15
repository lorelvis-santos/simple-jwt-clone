# 🛡️ simple-jwt-clone

*A minimal educational implementation of a JSON Web Token
encoder/decoder in C++*

## 📌 Overview

**simple-jwt-clone** is a fully manual, from-scratch implementation of
the core mechanisms behind JSON Web Tokens (JWT), written in **modern
C++17**.

The purpose of this project is **learning through building**, exploring
step by step how JWTs work internally:

-   Base64 and Base64URL encoding/decoding
-   JSON construction for headers and payloads
-   SHA-256 hashing
-   HMAC-SHA256 signatures
-   Token construction: `header.payload.signature`
-   Token verification
-   Low-level bit manipulation

This project **does not** aim to replace real cryptographic libraries.
Its value is educational: understanding JWTs without abstractions.

------------------------------------------------------------------------

## 🎯 Learning Goals

Through this project, the author is learning and practicing:

### ✔ Low-level binary operations

Bit shifting, masking, bitwise operators (`<<`, `>>`, `&`, `|`).

### ✔ Base64 and Base64URL internals

Implementing the encoding from scratch: - 3 bytes → 24 bits → 4 blocks
of 6 bits
- Mapping to the Base64 alphabet
- Handling padding (`=`)
- Converting to Base64URL (`+`→`-`, `/`→`_`)

### ✔ JSON building in pure C++

Constructing JWT header/payload manually, without JSON libraries.

### ✔ SHA-256 hashing

Implementing a minimalist but functional version: 
- Message padding
- 512-bit block processing
- Sigma functions
- Compression rounds
- Big-endian word assembly

### ✔ HMAC-SHA256

Understanding the full HMAC algorithm:

    HMAC = SHA256((key XOR opad) + SHA256(key XOR ipad + message))

### ✔ JWT structure & validation

Understanding exactly how:

    header.payload.signature

is created and verified.

### ✔ Clean project architecture

Using headers, modules, compilation units, and a structured makefile.

### ✔ Git workflow & commit discipline

Branches like:

    core/base64
    core/sha256
    feature/jwt

with commit messages:

    feat:
    fix:
    refactor:
    test:

------------------------------------------------------------------------

## 🧱 Project Structure

    simple-jwt-clone/
    │
    ├── makefile
    ├── README.md
    ├── bin/
    │
    ├── src/
    │   ├── base64.h
    │   ├── base64.cpp
    │   ├── base64url.h
    │   ├── base64url.cpp
    │   ├── sha256.h
    │   ├── sha256.cpp
    │   ├── hmac.h
    │   ├── hmac.cpp
    │   ├── jwt.h
    │   ├── jwt.cpp
    │
    └── tests/
        ├── test_runner.cpp
        ├── test_utils.h
        ├── test_base64_encode.cpp
        ├── test_base64_decode.cpp
        ├── test_base64_roundtrip.cpp
        ├── test_base64url_encode.cpp
        ├── test_base64url_decode.cpp
        ├── test_base64url_roundtrip.cpp
        ├── test_sha256.cpp
        ├── test_hmac.cpp
        ├── test_jwt_header.cpp
        ├── test_jwt_payload.cpp

------------------------------------------------------------------------

## 🧪 Running Tests

Compile and run all tests:

``` bash
make test
```

Or manually:

``` bash
g++ -std=c++17 -Wall -Wextra tests/test_runner.cpp src/*.cpp -o bin/tests
./bin/tests
```

All tests include: - green/red colored output
- input, expected, and actual values
- success/failure indicators

------------------------------------------------------------------------

## 🚀 Running the Program

``` bash
make
bin/simple-jwt-clone
```

------------------------------------------------------------------------

## ⚠️ Disclaimer

This project is **educational only**.
Do **not** use this implementation for production authentication.

------------------------------------------------------------------------

## ✨ Why This Project Matters

Most developers use JWT libraries without understanding what happens
internally.
This project walks through every piece manually:

-   binary logic
-   encoding
-   hashing
-   signing
-   message integrity
-   token generation
-   token validation

It transforms JWT from a "magic opaque string" into a fully understood
system.

------------------------------------------------------------------------

## 📌 Roadmap

-   [x] Base64 encode
-   [x] Base64 decode
-   [x] Base64URL encode
-   [x] Base64URL decode
-   [x] Unit tests
-   [x] JWT header struct + JSON
-   [x] JWT payload struct + JSON
-   [ ] SHA-256 hash
-   [ ] HMAC-SHA256
-   [ ] JWT signing
-   [ ] JWT verification
-   [ ] Complete `jwt_encode()`
-   [ ] Complete `jwt_decode()`
-   [ ] Error handling & edge cases

------------------------------------------------------------------------

## 📜 License

MIT License --- feel free to use this as a learning reference.
