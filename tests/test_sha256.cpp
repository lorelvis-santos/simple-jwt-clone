// tests/test_sha256.cpp
#include <iostream>
#include <string>
#include "../src/sha256.h"
#include "test_utils.h"

bool test_sha256_case(const std::string& input, const std::string& expected_hex) {
    std::string got = sha256_hex(input);
    bool ok = (got == expected_hex);

    test::print_result("sha256", input, expected_hex, got, ok);
    return ok;
}

bool run_sha256_tests() {
    std::cout << "\n== SHA-256 Tests ==\n";

    bool ok = true;

    // Vectores de prueba conocidos (NIST / estándar)
    ok &= test_sha256_case(
        "",
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
    );

    ok &= test_sha256_case(
        "abc",
        "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
    );

    ok &= test_sha256_case(
        "hello",
        "2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824"
    );

    ok &= test_sha256_case(
        "The quick brown fox jumps over the lazy dog",
        "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592"
    );

    ok &= test_sha256_case(
        "The quick brown fox jumps over the lazy dog.",
        "ef537f25c895bfa782526529a9b63d97aa631564d5d789c2b765448c8635fb6c"
    );

    return ok;
}
