// tests/test_base64url_encode.cpp
#include <iostream>
#include <string>
#include "../src/base64url.h"
#include "test_utils.h"

bool test_base64url_encode_case(const std::string& plain, const std::string& expected) {
    std::string got = base64url_encode(plain);
    bool ok = (got == expected);

    test::print_result("b64url-encode", plain, expected, got, ok);
    return ok;
}

bool run_base64url_encode_tests() {
    std::cout << "\n== Base64URL Encode Tests ==\n";

    bool ok = true;

    // Casos clásicos (Base64 sin padding + URL safe)
    ok &= test_base64url_encode_case("", "");
    ok &= test_base64url_encode_case("f", "Zg");
    ok &= test_base64url_encode_case("fo", "Zm8");
    ok &= test_base64url_encode_case("foo", "Zm9v");
    ok &= test_base64url_encode_case("foob", "Zm9vYg");
    ok &= test_base64url_encode_case("fooba", "Zm9vYmE");
    ok &= test_base64url_encode_case("foobar", "Zm9vYmFy");

    // Casos que fuerzan caracteres especiales (+, /) en Base64 normal
    // 0xFF -> "/w==" en Base64 -> "_w" en Base64URL
    ok &= test_base64url_encode_case(std::string("\xFF", 1), "_w");

    // 0xFB -> "+w==" en Base64 -> "-w" en Base64URL
    ok &= test_base64url_encode_case(std::string("\xFB", 1), "-w");

    return ok;
}
