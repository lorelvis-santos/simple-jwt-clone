// tests/test_utils.h
#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <iostream>
#include <string>

namespace test {

// Colores ANSI
static const std::string RESET  = "\033[0m";
static const std::string RED    = "\033[31m";
static const std::string GREEN  = "\033[32m";

// Tipo de test: encode/decode/roundtrip/etc.
inline void print_result(
    const std::string& kind,
    const std::string& input,
    const std::string& expected,
    const std::string& got,
    bool ok
) {
    const std::string& color = ok ? GREEN : RED;
    const std::string status = ok ? "OK" : "FAIL";

    std::cout << color
              << "[" << kind << " " << status << "]\n"
              << "  input:    \"" << input    << "\"\n"
              << "  expected: \"" << expected << "\"\n"
              << "  got:      \"" << got      << "\"\n"
              << RESET;
}

} // namespace test

#endif // TEST_UTILS_H