// tests/test_runner.cpp
#include <iostream>

bool run_base64_encode_tests();
bool run_base64_decode_tests();
bool run_base64_roundtrip_tests();

int main() {
    int failures = 0;

    if (!run_base64_encode_tests()) failures++;
    if (!run_base64_decode_tests()) failures++;
    if (!run_base64_roundtrip_tests()) failures++;

    std::cout << "\n== TEST SUMMARY ==\n";
    if (failures == 0) {
        std::cout << "All tests passed! 🎉\n";
    } else {
        std::cout << failures << " test group(s) failed.\n";
    }

    return failures > 0 ? 1 : 0;
}
