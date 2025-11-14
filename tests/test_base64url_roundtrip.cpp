// tests/test_base64url_roundtrip.cpp
#include <iostream>
#include <string>
#include "../src/base64url.h"
#include "test_utils.h"

bool test_base64url_roundtrip_case(const std::string& input) {
    std::string encoded = base64url_encode(input);
    std::string decoded = base64url_decode(encoded);

    bool ok = (decoded == input);
    // expected = input original
    test::print_result("b64url-roundtrip", input, input, decoded, ok);
    return ok;
}

bool run_base64url_roundtrip_tests() {
    std::cout << "\n== Base64URL Roundtrip Tests ==\n";

    bool ok = true;

    ok &= test_base64url_roundtrip_case("");
    ok &= test_base64url_roundtrip_case("A");
    ok &= test_base64url_roundtrip_case("AB");
    ok &= test_base64url_roundtrip_case("Hello");
    ok &= test_base64url_roundtrip_case("Hello world");
    ok &= test_base64url_roundtrip_case("JWT test!");
    ok &= test_base64url_roundtrip_case("And");
    ok &= test_base64url_roundtrip_case("Man");

    // También probamos datos binarios crudos
    ok &= test_base64url_roundtrip_case(std::string("\xFF", 1));
    ok &= test_base64url_roundtrip_case(std::string("\xFB\xFF", 2));

    return ok;
}
