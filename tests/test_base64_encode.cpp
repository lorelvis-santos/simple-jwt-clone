// tests/test_base64_encode.cpp
#include <iostream>
#include <string>
#include "../src/base64.h"
#include "test_utils.h"

bool test_encode_case(const std::string& plain, const std::string& expected) {
    std::string got = base64_encode(plain);
    bool ok = (got == expected);

    test::print_result("encode", plain, expected, got, ok);
    return ok;
}

bool run_base64_encode_tests() {
    std::cout << "\n== Base64 Encode Tests ==\n";

    bool ok = true;
    
    ok &= test_encode_case("", "");
    ok &= test_encode_case("f", "Zg==");
    ok &= test_encode_case("fo", "Zm8=");
    ok &= test_encode_case("foo", "Zm9v");
    ok &= test_encode_case("foob", "Zm9vYg==");
    ok &= test_encode_case("fooba", "Zm9vYmE=");
    ok &= test_encode_case("foobar", "Zm9vYmFy");
    ok &= test_encode_case("A", "QQ==");
    ok &= test_encode_case("AB", "QUI=");
    ok &= test_encode_case("ABC", "QUJD");
    ok &= test_encode_case("And", "QW5k");

    return ok;
}
