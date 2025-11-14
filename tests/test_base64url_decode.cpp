// tests/test_base64url_decode.cpp
#include <iostream>
#include <string>
#include "../src/base64url.h"
#include "test_utils.h"

bool test_base64url_decode_case(const std::string& b64url, const std::string& expected) {
    std::string got = base64url_decode(b64url);
    bool ok = (got == expected);

    test::print_result("b64url-decode", b64url, expected, got, ok);
    return ok;
}

bool run_base64url_decode_tests() {
    std::cout << "\n== Base64URL Decode Tests ==\n";

    bool ok = true;

    // Casos clásicos (inverso de los encode de arriba)
    ok &= test_base64url_decode_case("", "");
    ok &= test_base64url_decode_case("Zg", "f");
    ok &= test_base64url_decode_case("Zm8", "fo");
    ok &= test_base64url_decode_case("Zm9v", "foo");
    ok &= test_base64url_decode_case("Zm9vYg", "foob");
    ok &= test_base64url_decode_case("Zm9vYmE", "fooba");
    ok &= test_base64url_decode_case("Zm9vYmFy", "foobar");

    // Casos con caracteres URL-safe especiales
    ok &= test_base64url_decode_case("_w",  std::string("\xFF", 1));
    ok &= test_base64url_decode_case("-w", std::string("\xFB", 1));

    return ok;
}
