// tests/test_roundtrip.cpp
#include <iostream>
#include <string>
#include "../src/base64.h"
#include "test_utils.h"

bool test_roundtrip_case(const std::string& input) {
    std::string encoded = base64_encode(input);
    std::string decoded = base64_decode(encoded, false);

    bool ok = (decoded == input);

    // Aquí el "expected" es el input original
    test::print_result("roundtrip", input, input, decoded, ok);
    return ok;
}

bool run_base64_roundtrip_tests() {
    std::cout << "\n== Base64 Roundtrip Tests ==\n";

    bool ok = true;
    ok &= test_roundtrip_case("");
    ok &= test_roundtrip_case("A");
    ok &= test_roundtrip_case("AB");
    ok &= test_roundtrip_case("Hello");
    ok &= test_roundtrip_case("Hello world");
    ok &= test_roundtrip_case("JWT test!");
    ok &= test_roundtrip_case("And");
    ok &= test_roundtrip_case("Man");

    return ok;
}
