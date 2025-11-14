// tests/test_base64_decode.cpp
#include <iostream>
#include <string>
#include "../src/base64.h"
#include "test_utils.h"

bool test_decode_case(const std::string& b64, const std::string& expected) {
    std::string got = base64_decode(b64, false);
    bool ok = (got == expected);

    test::print_result("decode", b64, expected, got, ok);
    return ok;
}

bool run_base64_decode_tests() {
    std::cout << "\n== Base64 Decode Tests ==\n";

    bool ok = true;
    ok &= test_decode_case("", "");
    ok &= test_decode_case("Zg==", "f");
    ok &= test_decode_case("Zm8=", "fo");
    ok &= test_decode_case("Zm9v", "foo");
    ok &= test_decode_case("Zm9vYg==", "foob");
    ok &= test_decode_case("Zm9vYmE=", "fooba");
    ok &= test_decode_case("Zm9vYmFy", "foobar");
    ok &= test_decode_case("QQ==", "A");
    ok &= test_decode_case("QUI=", "AB");
    ok &= test_decode_case("QUJD", "ABC");
    ok &= test_decode_case("QW5k", "And");

    return ok;
}